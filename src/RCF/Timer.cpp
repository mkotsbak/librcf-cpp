
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

#include <RCF/Timer.hpp>

#include <RCF/Tools.hpp>

namespace RCF {

    Timer::Timer() 
    { 
        restart(); 
    }

    Timer::Timer(boost::uint32_t startTimeMs)
    {
        restart(startTimeMs);
    }

    bool Timer::elapsed(boost::uint32_t durationMs) 
    { 
        boost::uint32_t nowMs = RCF::getCurrentTimeMs();
        return nowMs - mStartTimeMs >= durationMs;
    }

    void Timer::restart()
    {
        mStartTimeMs = RCF::getCurrentTimeMs();
    }

    void Timer::restart(boost::uint32_t startTimeMs)
    {
        mStartTimeMs = startTimeMs;
    }

    boost::uint32_t Timer::getStartTimeMs()
    {
        return mStartTimeMs;
    }

    boost::uint32_t Timer::getDurationMs()
    {
        boost::uint32_t nowMs = RCF::getCurrentTimeMs();
        return nowMs - mStartTimeMs;
    }

} // namespace RCF
