//
//  timer.h
//  utils
//
//  Created by Christian Schmutzer on 04.11.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef utils_timer_h
#define utils_timer_h

#include "start.h"


namespace sce 
{
 
    // timer works with nanosces
    // to work with millisces, use macros below
    template<typename T>
    struct Generic_Timer
    {
        // construction and destruction
            Generic_Timer();
            ~Generic_Timer();

        unsigned long   getCurTime();

        void            reset();                // starts time counting again
        
        void            sleep(unsigned long nanoSecs);
        void            pause();
        void            proceed();

    private:		     
        bool            paused_;
        
        unsigned long	startTime_;	
        unsigned long	lastTime_;
        
        T				clock_;	
    };
    
    #ifdef _WIN32

        struct WinClock
        {
            WinClock();
            ~WinClock();
            
            unsigned long	operator()();
        };
    
        typedef Generic_Timer<WinClock>		Timer;
    
    #elif __APPLE__
    
        struct AppleClock
        {
            AppleClock();
            ~AppleClock();
            
            unsigned long	operator()();
        };
        typedef Generic_Timer<AppleClock>   Timer;
    
    #endif

    // helpers
    inline unsigned long    MILLI_TO_NANO(unsigned long milli)                          { return milli*1000000; }
    inline unsigned long    NANO_TO_MILLI(unsigned long nano)                           { return static_cast<unsigned long>(nano/1000000);}
    
    Timer&	theTimer();

    int     getFps();

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //****************************************************************************************************
    template<typename T>
    Generic_Timer<T>::Generic_Timer()
    {
        reset();
    }
    
    template<typename T>
    Generic_Timer<T>::~Generic_Timer()
    {
    }
    
    template<typename T> inline unsigned long   
    Generic_Timer<T>::getCurTime()
    { 
        if( paused_ )
        {
            return static_cast<float>(lastTime_);
        }
        else
        {
            return static_cast<float>(clock_() - startTime_);
        }
    }
        
    template<typename T> inline void
    Generic_Timer<T>::reset()
    {
        startTime_ = clock_();
        paused_ = false;
    }
    
    template<typename T> inline void            
    Generic_Timer<T>::sleep(unsigned long nanoSecs)
    {
        unsigned long startTime = getCurTime();
        
        while( (getCurTime() - startTime) <= nanoSecs )
        {
        }
    }
    
    template<typename T> inline void            
    Generic_Timer<T>::pause()
    {
        lastTime_ = clock();
        paused_ = true;
    }
    
    template<typename T> inline void            
    Generic_Timer<T>::proceed()
    {
        if( paused_ )
        {
            paused_ = false;
            startTime_ = startTime_ + (getCurTime() - lastTime_);   // add the paused time to startTime_
        }
    }

} // namespace sce


#endif
