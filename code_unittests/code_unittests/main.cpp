//
//  main.cpp
//  code_unittests
//
//  Created by Christian Schmutzer on 10.11.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "../../code/utils/utils.h"


int main (int argc, const char * argv[])
{
    {
        sce::Timer timer1;
        timer1.reset();
        unsigned long startTime = timer1.getCurTime();
        timer1.sleep(1000);
        unsigned long stopTime = timer1.getCurTime();
        unsigned long sleepTime = stopTime - startTime;
        
        std::cout << "Timer sleeped for: " << sleepTime << "nanosecs" << std::endl;
    }
    
    {
        SCE_TRACE("FIRST TIME CALLING TRACE\n")
        // SCE_ASSERT_2(false, "First time calling assertion 2")
    }
    
    return 0;
}

