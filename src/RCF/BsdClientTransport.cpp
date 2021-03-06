
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

#include <RCF/BsdClientTransport.hpp>

#include <RCF/ClientStub.hpp>
#include <RCF/Exception.hpp>
#include <RCF/RcfServer.hpp>
#include <RCF/ThreadLocalData.hpp>
#include <RCF/TimedBsdSockets.hpp>

#ifdef BOOST_WINDOWS
#include <RCF/IocpServerTransport.hpp>
#endif

namespace RCF {

    BsdClientTransport::BsdClientTransport() :
        mFd(-1)
    {}

    BsdClientTransport::BsdClientTransport(int fd) :
        mFd(fd)
    {
        mClosed = false;
    }

    BsdClientTransport::BsdClientTransport(const BsdClientTransport & rhs) :
        ConnectionOrientedClientTransport(rhs),
        mFd(-1)
    {}

    BsdClientTransport::~BsdClientTransport()
    {
        RCF_DTOR_BEGIN
            close();
        RCF_DTOR_END
    }

#ifdef BOOST_WINDOWS

    // return -2 for timeout, -1 for error, 0 for ready
    int pollSocketWithProgressMwfmo(
        const ClientProgressPtr &clientProgressPtr,
        ClientProgress::Activity activity,
        unsigned int endTimeMs,
        int fd,
        int &err,
        bool bRead)
    {
        RCF_UNUSED_VARIABLE(err);
        RCF_UNUSED_VARIABLE(activity);

        ClientStub & clientStub = *getCurrentClientStubPtr();

        int uiMessageFilter = clientProgressPtr->mUiMessageFilter;

        HANDLE readEvent = WSACreateEvent();
        using namespace boost::multi_index::detail;
        scope_guard WSACloseEventGuard = make_guard(WSACloseEvent, readEvent);
        RCF_UNUSED_VARIABLE(WSACloseEventGuard);

        int nRet = WSAEventSelect(fd, readEvent, bRead ? FD_READ : FD_WRITE);
        RCF_ASSERT_EQ(nRet , 0);
        HANDLE handles[] = { readEvent };

        while (true)
        {
            unsigned int timeoutMs = generateTimeoutMs(endTimeMs);
            timeoutMs = clientStub.generatePollingTimeout(timeoutMs);

            DWORD dwRet = MsgWaitForMultipleObjects(
                1, 
                handles, 
                0, 
                timeoutMs, 
                uiMessageFilter);

            if (dwRet == WAIT_TIMEOUT)
            {
                clientStub.onPollingTimeout();

                if (generateTimeoutMs(endTimeMs) == 0)
                {
                    return -2;
                }
            }
            else if (dwRet == WAIT_OBJECT_0)
            {
                // File descriptor is ready to be read.
                return 0;
            }
            else if (dwRet == WAIT_OBJECT_0 + 1)
            {
                clientStub.onUiMessage();                
            }
        }
    }

#endif

    PollingFunctor::PollingFunctor(
        ClientProgressPtr clientProgressPtr,
        ClientProgress::Activity activity,
        unsigned int endTimeMs) :
            mClientProgressPtr(clientProgressPtr),
            mActivity(activity),
            mEndTimeMs(endTimeMs)
    {}

#ifdef BOOST_WINDOWS

    // On Windows, the user may have requested callbacks on UI messages, in 
    // which case we'll need to use MsgWaitForMultipleObjects() rather than
    // plain old select().

    int PollingFunctor::operator()(int fd, int &err, bool bRead)
    {
        if (
            mClientProgressPtr.get() &&
            mClientProgressPtr->mTriggerMask & ClientProgress::UiMessage)
        {
            return pollSocketWithProgressMwfmo(
                mClientProgressPtr,
                mActivity,
                mEndTimeMs,
                fd,
                err,
                bRead);
        }
        else
        {
            return pollSocket(
                mEndTimeMs,
                fd,
                err,
                bRead);
        }
    }

#else

    int PollingFunctor::operator()(int fd, int &err, bool bRead)
    {
        return pollSocket(
            mEndTimeMs,
            fd,
            err,
            bRead);
    }

#endif

    std::size_t BsdClientTransport::implRead(
        const ByteBuffer &byteBuffer,
        std::size_t bytesRequested)
    {
        std::size_t bytesToRead = RCF_MIN(bytesRequested, byteBuffer.getLength());

        PollingFunctor pollingFunctor(
            mClientProgressPtr,
            ClientProgress::Receive,
            mEndTimeMs);

        RCF_LOG_4()(byteBuffer.getLength())(bytesToRead) << "BsdClientTransport - initiating read from socket.";

        int err = 0;
        int ret = RCF::timedRecv(
            *this,
            pollingFunctor,
            err,
            mFd,
            byteBuffer,
            bytesToRead,
            0);

        switch (ret)
        {
        case -2:
            {
                Exception e(_RcfError_ClientReadTimeout());
                RCF_THROW(e);
            }
            break;

        case -1:
            {
                Exception e(
                    _RcfError_ClientReadFail(),
                    err,
                    RcfSubsystem_Os);
            
                RCF_THROW(e);
            }
            break;

        case  0:
            {
                Exception e(_RcfError_PeerDisconnect());
                RCF_THROW(e);
            }
            break;

        default:
            
            RCF_ASSERT(
                0 < ret && ret <= static_cast<int>(bytesRequested))
                (ret)(bytesRequested);
        }

        return ret;
    }

    std::size_t BsdClientTransport::implReadAsync(
        const ByteBuffer &byteBuffer,
        std::size_t bytesRequested)
    {
        RCF_ASSERT(0);
		RCF_UNUSED_VARIABLE(byteBuffer);
		RCF_UNUSED_VARIABLE(bytesRequested);
        return 0;
    }

    std::size_t BsdClientTransport::implWrite(
        const std::vector<ByteBuffer> &byteBuffers)
    {
        PollingFunctor pollingFunctor(
            mClientProgressPtr,
            ClientProgress::Send,
            mEndTimeMs);

        int err = 0;

        RCF_LOG_4()(lengthByteBuffers(byteBuffers)) 
            << "BsdClientTransport - initiating send on socket.";

        int ret = RCF::timedSend(
            pollingFunctor,
            err,
            mFd,
            byteBuffers,
            getMaxSendSize(),
            0);

        switch (ret)
        {
        case -2:
            {
                Exception e(_RcfError_ClientWriteTimeout());
                RCF_THROW(e);
            }
            break;

        case -1:
            {
                Exception e(
                    _RcfError_ClientWriteFail(),
                    err,
                    RcfSubsystem_Os);
            
                RCF_THROW(e);
            }
            break;

        case 0:
            {
                Exception e(_RcfError_PeerDisconnect());            
                RCF_THROW(e);
            }
            break;

        default:
            
            RCF_ASSERT(
                0 < ret && ret <= static_cast<int>(lengthByteBuffers(byteBuffers)))
                (ret)(lengthByteBuffers(byteBuffers));            

            onTimedSendCompleted(ret, 0);
        }

        return ret;
    }

    std::size_t BsdClientTransport::implWriteAsync(
        const std::vector<ByteBuffer> &byteBuffers)
    {
        RCF_ASSERT(0);
		RCF_UNUSED_VARIABLE(byteBuffers);
        return 0;
    }

    bool BsdClientTransport::isConnected()
    {
        return isFdConnected(mFd);
    }

    int BsdClientTransport::releaseFd()
    {
        // We've got problems if there is a close functor involved.
        RCF_ASSERT( !mNotifyCloseFunctor );

        int myFd = mFd;
        mFd = -1;
        return myFd;
    }

    int BsdClientTransport::getFd() const
    {
        return mFd;
    }

    int    BsdClientTransport::getNativeHandle() const
    {
        return mFd;
    }
    
} // namespace RCF
