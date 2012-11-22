
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

#ifndef INCLUDE_RCF_AMITHREADPOOL_HPP
#define INCLUDE_RCF_AMITHREADPOOL_HPP

#include <memory>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>

#include <RCF/Heap.hpp>
#include <RCF/ThreadLibrary.hpp>
#include <RCF/Tools.hpp>

namespace RCF {

    class AmiNotification
    {
    public:

        typedef boost::function0<void> Cb;

        // Need mutexPtr so that the mutex doesn't die before the lock.
        void set(Cb cb, std::auto_ptr<Lock> lockPtr, boost::shared_ptr<Mutex> mutexPtr)
        {
            mCb = cb;
            mLockPtr = lockPtr;
            mMutexPtr = mutexPtr;
        }

        void run()
        {
            mLockPtr.reset();
            if (mCb)
            {
                Cb cb = mCb;
                mCb = Cb();
                cb();
            }
        }

        void clear()
        {
            mLockPtr.reset();
            mMutexPtr.reset();
            mCb = Cb();
        }

    private:
        Cb mCb;
        boost::shared_ptr<Mutex> mMutexPtr;
        std::auto_ptr<Lock> mLockPtr;
    };

} // namespace RCF

namespace RCF {

    // TODO: Non-Windows implementation.

    class OverlappedAmi;
    typedef boost::shared_ptr<OverlappedAmi> OverlappedAmiPtr;

    class I_OverlappedAmi
    {
    public:
        I_OverlappedAmi() {}
        virtual ~I_OverlappedAmi() {}
        virtual void onCompletion(std::size_t numBytes) = 0;

        typedef std::pair<boost::uint32_t, OverlappedAmiPtr> TimerEntry;

        virtual void onTimerExpired(const TimerEntry & timerEntry) = 0;
    };

    class AmiThreadPool
    {
    public:
        void cancelConnect(int fd)
        {
			RCF_UNUSED_VARIABLE(fd);
        }
    };


} // namespace RCF

namespace RCF {

    extern boost::scoped_ptr<AmiThreadPool> gAmiThreadPoolPtr;

} // namespace RCF

#endif // ! INCLUDE_RCF_AMITHREADPOOL_HPP
