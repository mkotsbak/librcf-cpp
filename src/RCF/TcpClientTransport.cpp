
//******************************************************************************
// RCF - Remote Call Framework
//
// Copyright (c) 2005 - 2011, Delta V Software. All rights reserved.
// http://www.deltavsoft.com
//
// RCF is distributed under dual licenses - closed source or GPL.
// Consult your particular license for conditions of use.
//
// Version: 1.3.1
// Contact: support <at> deltavsoft.com 
//
//******************************************************************************

#include <RCF/TcpClientTransport.hpp>

#include <boost/bind.hpp>

#include <RCF/ClientStub.hpp>
#include <RCF/InitDeinit.hpp>
#include <RCF/TcpEndpoint.hpp>
#include <RCF/ThreadLocalData.hpp>
#include <RCF/TimedBsdSockets.hpp>
#include <RCF/TcpEndpoint.hpp>
#include <RCF/Tools.hpp>

#ifdef BOOST_WINDOWS
#include <RCF/Iocp.hpp>
#include <RCF/IocpServerTransport.hpp>
#endif

#include <RCF/RcfServer.hpp>

// missing stuff in mingw and vc6 headers
#if defined(__MINGW32__) || (defined(_MSC_VER) && _MSC_VER == 1200)

typedef
BOOL
(PASCAL FAR * LPFN_CONNECTEX) (
    IN SOCKET s,
    IN const struct sockaddr FAR *name,
    IN int namelen,
    IN PVOID lpSendBuffer OPTIONAL,
    IN DWORD dwSendDataLength,
    OUT LPDWORD lpdwBytesSent,
    IN LPOVERLAPPED lpOverlapped
    );

#define WSAID_CONNECTEX \
    {0x25a207b9,0xddf3,0x4660,{0x8e,0xe9,0x76,0xe5,0x8c,0x74,0x06,0x3e}}

#endif

namespace RCF {

    TcpClientTransport::TcpClientTransport(const TcpClientTransport &rhs) :
        BsdClientTransport(rhs),
        mRemoteAddr(rhs.mRemoteAddr)
    {}

    TcpClientTransport::TcpClientTransport(const IpAddress &remoteAddr) :
        BsdClientTransport(),
        mRemoteAddr(remoteAddr)
    {}

    TcpClientTransport::TcpClientTransport(const std::string & ip, int port) :
        BsdClientTransport(),
        mRemoteAddr(ip, port)
    {}

    TcpClientTransport::TcpClientTransport(int fd) :
        BsdClientTransport(fd)
    {}

    TcpClientTransport::~TcpClientTransport()
    {
        RCF_DTOR_BEGIN
            if (mOwn)
            {
                close();
            }
        RCF_DTOR_END
    }

    std::auto_ptr<I_ClientTransport> TcpClientTransport::clone() const
    {
        return ClientTransportAutoPtr( new TcpClientTransport(*this) );
    }

    void TcpClientTransport::implConnect(
        I_ClientTransportCallback &clientStub,
        unsigned int timeoutMs)
    {
        // TODO: replace throw with return, where possible

        RCF_ASSERT(!mAsync);

        // TODO: should be closed already?
        implClose();

        if (!mRemoteAddr.isResolved())
        {
            RCF::ExceptionPtr e;
            mRemoteAddr.resolve(e);
            RCF_VERIFY(!e, *e);
        }

        RCF_ASSERT(mRemoteAddr.isResolved());
        setupSocket();

        unsigned int startTimeMs = getCurrentTimeMs();
        mEndTimeMs = startTimeMs + timeoutMs;

        PollingFunctor pollingFunctor(
            mClientProgressPtr,
            ClientProgress::Connect,
            mEndTimeMs);

        int err = 0;

        sockaddr * pSockAddr = NULL;
        Platform::OS::BsdSockets::socklen_t sockAddrSize = 0;
        mRemoteAddr.getSockAddr(pSockAddr, sockAddrSize);

        int ret = timedConnect(
            pollingFunctor,
            err,
            mFd,
            pSockAddr,
            sockAddrSize);

        if (ret != 0)
        {
            close();

            if (err == 0)
            {
                Exception e( _RcfError_ClientConnectTimeout(
                    timeoutMs, 
                    mRemoteAddr.string()));
                
                RCF_THROW(e);
            }
            else
            {
                Exception e( _RcfError_ClientConnectFail(), err, RcfSubsystem_Os);
                RCF_THROW(e)(mRemoteAddr.string());
            }
        }

        mAssignedLocalIp = IpAddress(mFd, mRemoteAddr.getType());

        clientStub.onConnectCompleted();
    }

    void TcpClientTransport::implConnectAsync(
        I_ClientTransportCallback &clientStub,
        unsigned int timeoutMs)
    {
        RCF_ASSERT(0);
		RCF_UNUSED_VARIABLE(clientStub);
		RCF_UNUSED_VARIABLE(timeoutMs);
    }

    void TcpClientTransport::endDnsLookup(
        OverlappedAmiPtr overlappedPtr, 
        IpAddress ipAddress, 
        ExceptionPtr e)
    {
        RCF_ASSERT(0);
    }

    void TcpClientTransport::beginDnsLookup()
    {
        RCF_ASSERT(0);
    }

    void TcpClientTransport::dnsLookupTask(
        OverlappedAmiPtr overlappedPtr,
        IpAddress ipAddress)
    {
        RCF_ASSERT(0);
    }

    void TcpClientTransport::setupSocket()
    {
        RCF::Exception e;
        setupSocket(e);
        if (e.bad())
        {
            RCF_THROW(e);
        }
    }

    void TcpClientTransport::setupSocket(Exception & e)
    {
        e = Exception();

        RCF_ASSERT_EQ(mFd , INVALID_SOCKET);
        mFd = mRemoteAddr.createSocket();
        Platform::OS::BsdSockets::setblocking(mFd, false);

        // Bind to local interface, if one has been specified.
        if (!mLocalIp.empty())
        {
            mLocalIp.resolve();

            sockaddr * pSockAddr = NULL;
            Platform::OS::BsdSockets::socklen_t sockAddrSize = 0;
            mLocalIp.getSockAddr(pSockAddr, sockAddrSize);

            int ret = ::bind(
                mFd, 
                pSockAddr, 
                sockAddrSize);

            if (ret < 0)
            {
                int err = Platform::OS::BsdSockets::GetLastError();
                if (err == Platform::OS::BsdSockets::ERR_EADDRINUSE)
                {
                    e = Exception(_RcfError_PortInUse(mLocalIp.getIp(), mLocalIp.getPort()), err, RcfSubsystem_Os, "bind() failed");
                    //RCF_THROW(e)(mAcceptorFd);
                }
                else
                {
                    e = Exception(_RcfError_SocketBind(mLocalIp.getIp(), mLocalIp.getPort()), err, RcfSubsystem_Os, "bind() failed");
                    //RCF_THROW(e)(mAcceptorFd);
                }
            }
        }
    }

    void TcpClientTransport::implClose()
    {
        if (mFd != -1)
        {
            if (mRegisteredForAmi && gAmiThreadPoolPtr.get())
            {
                gAmiThreadPoolPtr->cancelConnect(mFd);
            }

            int ret = Platform::OS::BsdSockets::closesocket(mFd);
            int err = Platform::OS::BsdSockets::GetLastError();

            RCF_VERIFY(
                ret == 0,
                Exception(
                _RcfError_Socket(),
                err,
                RcfSubsystem_Os,
                "closesocket() failed"))
                (mFd);
        }

        mFd = -1;
    }



    EndpointPtr TcpClientTransport::getEndpointPtr() const
    {
        return EndpointPtr( new TcpEndpoint(mRemoteAddr) );
    }

    void TcpClientTransport::setRemoteAddr(const IpAddress &remoteAddr)
    {
        mRemoteAddr = remoteAddr;
    }

    IpAddress TcpClientTransport::getRemoteAddr() const
    {
        return mRemoteAddr;
    }

} // namespace RCF
