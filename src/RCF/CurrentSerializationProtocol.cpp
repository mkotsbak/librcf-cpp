
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

#include <RCF/CurrentSerializationProtocol.hpp>

#include <RCF/ClientStub.hpp>
#include <RCF/RcfSession.hpp>
#include <RCF/ThreadLocalData.hpp>

namespace RCF {

    SerializationProtocolIn *getCurrentSerializationProtocolIn()
    {
        ClientStub * pClientStub = RCF::getCurrentClientStubPtr();
        RcfSession * pRcfSession = RCF::getCurrentRcfSessionPtr();
        if (pClientStub)
        {
            return &pClientStub->getSpIn();
        }
        else if (pRcfSession)
        {
            return &pRcfSession->getSpIn();
        }
        else
        {
            return NULL;
        }
    }

    SerializationProtocolOut *getCurrentSerializationProtocolOut()
    {
        ClientStub * pClientStub = RCF::getCurrentClientStubPtr();
        RcfSession * pRcfSession = RCF::getCurrentRcfSessionPtr();
        if (pClientStub)
        {
            return &pClientStub->getSpOut();
        }
        else if (pRcfSession)
        {
            return &pRcfSession->getSpOut();
        }
        else
        {
            return NULL;
        }
    }

} // namespace RCF
