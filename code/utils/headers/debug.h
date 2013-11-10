
#ifndef __DEBUG_H__
#define __DEBUG_H__


#include "start.h"


namespace sce
{

	struct DebugListener
	{
		DebugListener() {}
		virtual ~DebugListener() {}

		virtual void	pipe(const std::string& str) = 0;
	};

	template<typename T>
	struct Generic_Debug
	{
		// construction and destruction
			Generic_Debug() {}
			~Generic_Debug() {}

		// tracing 
		void	trace(const char* info);

		// debugging 
		void	log(const char* info,
					const char* logFile = NULL,
					const char* file = NULL, 
					const int line = 0);

		// assertions
		void	assertDb(bool expression, const char* info);

		//
		void	registerListener(DebugListener* dbgListener);

	private:
		T							printDevice_;
		std::list<DebugListener*>	listeners_;
	};

    struct OutputDevice
    {
        // construction and destruction
            OutputDevice();
            ~OutputDevice();
        
        enum AssertDevice
		{
			MESSAGE_BOX
		};

        void	operator()(const char* s);
        void	operator()(const char* s, const char* file);
        void	operator()(const char* s, AssertDevice a);

    private:
        bool	fileCreated_;
    };

    typedef Generic_Debug<OutputDevice>	Debugger;
    

	


	// create a singleton and support access
	Debugger&		theDebugger();

	// the following funcs are very useful during development
	// to prevent the user from memory leaks
	void	dumpMemoryLeaksInTheEnd();

    
    
    
    //******************************************************************************************************
    
    
                                //*******************************************
    #ifdef SCE_DEBUG            //******* handle trace stuff here ***********
    
        #define SCE_TRACE(info)			{ \
                                            std::stringstream ss; \
                                            ss << info; \
                                            sce::theDebugger().log(ss.str().c_str(), "traceLog.log"); \
                                        } \
    
    #else	// disable TRACE
    
        #define SCE_TRACE(info)
    
    #endif // SCE_DEBUG
        
                                //*******************************************
    #ifdef SCE_DEBUG            //******* handle assert stuff here **********
        
        #define SCE_ASSERT_1(test)				{															\
                                                    sce::theDebugger().assertDb(test, "");	\
                                                    assert(test);											\
                                                }
            
        #define SCE_ASSERT_2(test, info)		{															\
                                                    std::stringstream ss;										\
                                                    ss << "\n" << info << "\nfile: " << __FILE__ << "\nline: " << __LINE__;	\
                                                    sce::theDebugger().assertDb(test, ss.str().c_str());		\
                                                    assert(test);                                               \
                                                }
        
        #else	// disable SCE_ASSERT
    
            #define SCE_ASSERT_1(test)
            #define SCE_ASSERT_2(test, info)
    
        #endif	//SCE_DEBUG
        
        /**
         *	SCE_REPORT_MEM_LEAKS on exit the application will 
         *	report memory leaks, only win32
         */
        //#define SCE_REPORT_MEM_LEAKS			sce::dumpMemoryLeaksInTheEnd();
        
        /**
         *	SCE_NEW wraps the normal new operator and convertes it into 
         *	malloc_dbg to inform the win32 memory debug heap about file and line
         *	release versions do not wrap !
         */
        /*
        #if defined SCE_DEBUG
            
            #define SCE_NEW		new	 (__FILE__, __LINE__)
        #else
            #define SCE_NEW		new
        #endif
        */
        
    //******************************************************************************************************  
        
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename T> void
    Generic_Debug<T>::trace(const char* info)
    {
        //sprintf_s(str, length, "%s", info);
        printDevice_(info);
        
        // pipe to listeners
        std::list<DebugListener*>::iterator it; 
        for( it = listeners_.begin() ; it != listeners_.end() ; ++it ) 
        {
            (*it)->pipe(info);
        }
    }
    
    template<typename T> void
    Generic_Debug<T>::log(const char* info,
                          const char* logFile,
                          const char* file, 
                          const int line)
    {
        
        if( file != NULL && logFile != NULL ) 
        {
            printDevice_(info, logFile);		
            printDevice_(info);
        }
        else if( logFile != NULL ) {
            printDevice_(info, logFile);
        }
        else {
            printDevice_(info);
        }
    }
    
    template<typename T> void
    Generic_Debug<T>::assertDb(bool test, const char* info)
    {
        if( test ) return;
        else 
        {
            printDevice_(info, OutputDevice::MESSAGE_BOX);		
            assert(test);
        }
    }
    
    template<typename T> void
    Generic_Debug<T>::registerListener(DebugListener* dbgListener)
    {
        listeners_.push_back(dbgListener);
    }
    
    
} // namespace sce

#endif
