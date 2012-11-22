
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

#include <RCF/AmiThreadPool.hpp>

#include <RCF/ConnectionOrientedClientTransport.hpp>
#include <RCF/Exception.hpp>
#include <RCF/IpAddress.hpp>
#include <RCF/ThreadLocalData.hpp>
#include <RCF/ThreadPool.hpp>

namespace RCF {

    boost::scoped_ptr<AmiThreadPool> gAmiThreadPoolPtr;

} // namespace RCF
