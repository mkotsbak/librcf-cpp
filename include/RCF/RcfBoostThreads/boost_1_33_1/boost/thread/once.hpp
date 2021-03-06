
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

// Copyright (C) 2001-2003
// William E. Kempf
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  William E. Kempf makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.

#ifndef RCF_BOOST_ONCE_WEK080101_HPP
#define RCF_BOOST_ONCE_WEK080101_HPP

namespace boost {

#if defined(BOOST_HAS_PTHREADS)

typedef pthread_once_t once_flag;
#define RCF_BOOST_ONCE_INIT PTHREAD_ONCE_INIT

#elif (defined(BOOST_HAS_WINTHREADS) || defined(BOOST_HAS_MPTASKS))

typedef long once_flag;
#define RCF_BOOST_ONCE_INIT 0

#endif

void RCF_BOOST_THREAD_DECL call_once(void (*func)(), once_flag& flag);

} // namespace boost

#endif // RCF_BOOST_ONCE_WEK080101_HPP
