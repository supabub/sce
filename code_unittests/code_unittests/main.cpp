//
//  main.cpp
//  code_unittests
//
//  Created by Christian Schmutzer on 10.11.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "utils_unittests.h"


int main (int argc, const char * argv[])
{
    if( !checkUtils() )
    {
        SCE_TRACE("Testsuite UTILS failed!!!")
    }
    else
    {
        SCE_TRACE("Testsuits comleted successfuly!\n")
    }
    
    return 0;
}

