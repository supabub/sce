//
//  timer.cpp
//  utils
//
//  Created by Christian Schmutzer on 04.11.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "../headers/timer.h"

namespace sce
{

    
//****************************************************
#if defined _WIN32
    
#include <windows.h>
    
    WinClock::WinClock()
    {
    }
    
    WinClock::~WinClock()
    {
    }
    
    unsigned long	
    WinClock::operator()()
    {
        return timeGetTime();   !!!!use: QueryPerformanceCounter!!!!
    }
    
#endif // _WIN32
    
//****************************************************
#if defined __APPLE__  
    
#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h> 
    
    AppleClock::AppleClock()
    {
    }
    
    AppleClock::~AppleClock()
    {
    }
    
    unsigned long	
    AppleClock::operator()()
    {
        uint64_t curTime = mach_absolute_time();
        
        static mach_timebase_info_data_t    sTimebaseInfo;
        if ( sTimebaseInfo.denom == 0 ) 
        {
            mach_timebase_info(&sTimebaseInfo);
        }
        
        uint64_t timeNano = curTime * sTimebaseInfo.numer / sTimebaseInfo.denom;
        
        return timeNano;
    }
    
#endif // __APPLE__   
    
    
    Timer& theTimer()
    {
        static Timer t;
        return t;
    }
    
    int	getFps()
    {
        static int fps;
        static int frameCounter;
        static float frameTime = 0;
        
        float appTime = theTimer().getCurTime();
        
        frameCounter++;
        float time = appTime - frameTime;
        if(time > 1) 
        {
            fps = (int)((frameCounter)/time);
            frameTime = appTime;
            frameCounter = 0;		
        }	
        
        return fps;
    }

} // namespace sce
