
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

#ifndef INCLUDE_RCF_SERVERINTERFACES_HPP
#define INCLUDE_RCF_SERVERINTERFACES_HPP

#include <RCF/Idl.hpp>
#include <RCF/SerializationProtocol.hpp>
#include <RCF/TypeTraits.hpp>

#ifdef RCF_USE_SF_SERIALIZATION
#include <SF/string.hpp>
#include <SF/vector.hpp>
#endif

#ifdef RCF_USE_BOOST_SERIALIZATION
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#endif

RCF_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION(std::vector<boost::int32_t>)

namespace RCF {

    //--------------------------------------------------------------------------
    // I_Null

    RCF_BEGIN(I_Null, "")
    RCF_END(I_Null)
   

    //--------------------------------------------------------------------------
    // I_ObjectFactory

    RCF_BEGIN(I_ObjectFactory, "")

        RCF_METHOD_R2(
            boost::int32_t, 
                CreateObject, 
                    const std::string &, 
                    Token &)

        // Deprecated (use I_SessionObjectFactory)
        RCF_METHOD_R1(
            boost::int32_t, 
                CreateSessionObject, 
                    const std::string &)

        RCF_METHOD_R1(
            boost::int32_t, 
                DeleteObject, 
                    const Token &)

        // Deprecated (use I_SessionObjectFactory)
        RCF_METHOD_R0(
            boost::int32_t, 
                DeleteSessionObject)

    RCF_END(I_ObjectFactory)


    //--------------------------------------------------------------------------
    // I_SessionObjectFactory

    RCF_BEGIN(I_SessionObjectFactory, "")

        RCF_METHOD_R1(
            boost::int32_t, 
                CreateSessionObject, 
                    const std::string &)

        RCF_METHOD_R0(
            boost::int32_t, 
                DeleteSessionObject)

    RCF_END(I_SessionObjectFactory)
   

    //--------------------------------------------------------------------------
    // I_EndpointBroker

    RCF_BEGIN(I_EndpointBroker, "")

        RCF_METHOD_R3(
            boost::int32_t, 
                OpenEndpoint, 
                    const std::string &, 
                    const std::string &, 
                    std::string &)

        RCF_METHOD_R2(
            boost::int32_t, 
                CloseEndpoint, 
                    const std::string &, 
                    const std::string &)

        RCF_METHOD_R2(
            boost::int32_t, 
                EstablishEndpointConnection, 
                    const std::string &, 
                    const std::string &)

        RCF_METHOD_R2(
            boost::int32_t, 
                ConnectToEndpoint, 
                    const std::string &, 
                    const std::string &)

    RCF_END(I_EndpointBroker)
   

    //--------------------------------------------------------------------------
    // I_EndpointServer

    RCF_BEGIN(I_EndpointServer, "")

        RCF_METHOD_V1(
            void, 
                SpawnConnections, 
                    boost::uint32_t)

    RCF_END(I_EndpointServer)
   

    //--------------------------------------------------------------------------
    // I_RequestSubscription

    RCF_BEGIN( I_RequestSubscription, "" )

        RCF_METHOD_R1(
            boost::int32_t, 
                RequestSubscription, 
                    const std::string &)

        RCF_METHOD_R3(
            boost::int32_t, 
                RequestSubscription, 
                    const std::string &,    // subscriber name
                    boost::uint32_t,        // sub-to-pub ping interval
                    boost::uint32_t &)      // pub-to-sub ping interval

    RCF_END(I_RequestSubscription)


    //--------------------------------------------------------------------------
    // I_RequestTransportFilters

    RCF_BEGIN(I_RequestTransportFilters, "")

        RCF_METHOD_R1(
            boost::int32_t, 
                RequestTransportFilters, 
                    const std::vector<boost::int32_t> &)

        RCF_METHOD_R1(
            boost::int32_t, 
                QueryForTransportFilters, 
                    const std::vector<boost::int32_t> &)

    RCF_END(I_RequestTransportFilters)

} // namespace RCF

#ifdef RCF_USE_PROTOBUF

// This file is generated by running protoc on 
// RCF/include/RCF/protobuf/RcfMessages.proto.
#include <RCF/protobuf/RcfMessages.pb.h>

namespace RCF {

    //--------------------------------------------------------------------------
    // I_ObjectFactoryPb

    RCF_BEGIN(I_ObjectFactoryPb, "")

        RCF_METHOD_R1(
            PbCreateRemoteObjectResponse, 
                CreateRemoteObject, 
                    const PbCreateRemoteObject &)

        RCF_METHOD_V1(
            void, 
                DeleteRemoteObject, 
                    const PbDeleteRemoteObject &)

    RCF_END(I_ObjectFactoryPb)


    //--------------------------------------------------------------------------
    // I_SessionObjectFactoryPb

    RCF_BEGIN(I_SessionObjectFactoryPb, "")
        
        RCF_METHOD_V1(
            void, 
                CreateSessionObject, 
                    const PbCreateSessionObject &)

        RCF_METHOD_V1(
            void, 
                DeleteSessionObject, 
                    const PbDeleteSessionObject &)

    RCF_END(I_SessionObjectFactoryPb)


    //--------------------------------------------------------------------------
    // I_RequestSubscriptionPb

    RCF_BEGIN(I_RequestSubscriptionPb, "")

        RCF_METHOD_V1(
            void, 
                RequestSubscription, 
                    const PbRequestSubscription &)
    
    RCF_END(I_RequestSubscriptionPb)


    //--------------------------------------------------------------------------
    // I_RequestTransportFiltersPb

    RCF_BEGIN(I_RequestTransportFiltersPb, "")

        RCF_METHOD_V1(
            void, 
                RequestTransportFilters, 
                    const PbRequestTransportFilters &)

    RCF_END(I_RequestTransportFiltersPb)
    
} // namespace RCF

#endif // RCF_USE_PROTOBUF

#endif // ! INCLUDE_RCF_SERVERINTERFACES_HPP