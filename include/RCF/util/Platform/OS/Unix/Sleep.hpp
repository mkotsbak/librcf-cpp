
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

#ifndef INCLUDE_UTIL_PLATFORM_OS_UNIX_SLEEP_HPP
#define INCLUDE_UTIL_PLATFORM_OS_UNIX_SLEEP_HPP

#include <unistd.h>

namespace Platform {

    namespace OS {

        inline void Sleep(unsigned int seconds) { ::sleep(seconds); }

    }

}

#endif // ! INCLUDE_UTIL_PLATFORM_OS_UNIX_SLEEP_HPP
