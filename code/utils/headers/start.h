//
//  start.h
//  base
//
//  Created by Christian Schmutzer on 02.07.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef base_start_h
#define base_start_h



#include <ostream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <assert.h>
#include <list>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>


#ifdef _WIN32            // handle WIN32 dbg release macros

    #ifdef  _DEBUG
        #define     SCE_DEBUG
    #elif
        #define     SCE_RELEASE
    #endif

#endif  // WIN32


#ifdef  __APPLE__       // handle APPLE dbg release macros

    #ifdef  DEBUG
        #define     SCE_DEBUG
    #elif
        #define     SCE_RELEASE
    #endif

#endif  // __APPLE__


// ********************************************************************
// *************        global memory managment     *******************
// ********************************************************************

#ifdef  _WIN32

    #ifdef ML_DEBUG
        #define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
    #else
        #define DEBUG_CLIENTBLOCK
    #endif

    #ifdef ML_DEBUG
        #define new DEBUG_CLIENTBLOCK
    #endif

#endif


#endif
