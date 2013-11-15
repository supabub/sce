//
//  utils_unittests.cpp
//  code_unittests
//
//  Created by Christian Schmutzer on 13.11.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "utils_unittests.h"



// declarations
bool testDatabase();
bool testTimer();


bool testDatabase()
{
    {
        if( !sce::DataBase::deleteFile("/models/mirror.cpp") )
        {
            SCE_TRACE("Check -> DataBase::deleteFile()\n")
            return false; 
        }
        
        if( sce::DataBase::doesExist("/models") )
        {
            sce::DataBase::deleteDirectory("/models");
        }
        
        if( !sce::DataBase::createDirectory("/models") )
        {
            SCE_TRACE("Check -> DataBase::createDirectory()\n")
            return false;
        }

        if( !sce::DataBase::createDirectory("/models/entities") )
        {
            SCE_TRACE("Check -> DataBase::createDirectory()\n")
            return false;            
        }
        

    }
    
    return true;
}



bool testTimer()
{
    {
        sce::Timer timer1;
        timer1.reset();
        unsigned long startTime = timer1.getCurTime();
        timer1.sleep(sce::MILLI_TO_NANO(1000));
        unsigned long stopTime = timer1.getCurTime();
        unsigned long sleepTime = stopTime - startTime;
        
        if( sleepTime < 1000 )
        {
            SCE_TRACE("Check -> Timer::sleep()\n")
            return false;
        }
    }
    
    {
        sce::Timer t1;
        sce::Timer t2;
        
        t1.pause();
        unsigned long cT0 = t1.getCurTime();
        t2.sleep(10000);
        unsigned long cT1 = t1.getCurTime();
        if( cT0 != cT1 )
        {
            SCE_TRACE("Check -> Timer::pause()\n")
            return false;
        }
    }
    
    {
        sce::Timer t1;
        sce::Timer t2;

        t1.pause();
        t2.sleep(10000);
        unsigned long endTime = t1.getCurTime();
        t1.proceed();
        
        if( t1.getCurTime() <= endTime )
        {
            SCE_TRACE("Check -> Timer::proceed()\n")
            return false;           
        }
    }
    
    return true;
}









bool checkUtils()
{
    if( !testDatabase() )
        return false;
    else if( !testTimer() )
        return false;
    else
        return true;
}






