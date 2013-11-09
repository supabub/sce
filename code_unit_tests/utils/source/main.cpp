//
//  main.cpp
//  utils_unittest
//
//  Created by Christian Schmutzer on 04.11.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "../../../code/utils/utils.h"


int main (int argc, const char * argv[])
{
    //*************
    //*** TIMER ***
    //*************
     // sleep()
    {
        sce::Timer t1;
        
        unsigned long start = t1.getCurTime();
        t1.sleep(sce::MILLI_TO_NANO(500));       // 500 millisecs
        unsigned long delta = t1.getCurTime() - start;
        // TEST: delta > 500000000 && delta < 50010000 10.000stel ok sein (sehr ungenau...)
    }
    
    // pause()
    {
        sce::Timer timer1, timer2;
        timer1.reset();
        timer2.reset();
        
        timer1.pause();
        unsigned long t0 = timer1.getCurTime();
        timer2.sleep(sce::MILLI_TO_NANO(1000));
        unsigned long deltaTime = timer1.getCurTime() - t0;
        // TEST: deltaTime == 0
        timer1.proceed();
        unsigned long t1 = timer1.getCurTime();
        timer1.sleep(sce::MILLI_TO_NANO(500));
        unsigned long t2 = timer1.getCurTime();
        // TEST: curTime == sce::MILLI_TO_NANO(500)+-        
    }
    
    // 
}
