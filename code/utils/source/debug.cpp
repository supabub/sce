
#include "../headers/debug.h"



namespace sce
{

#ifdef _WIN32
    #include <windows.h>
#endif

    //--------------------------------------------------------------------
    OutputDevice::OutputDevice()
    :fileCreated_(false)
    {
    }


    //--------------------------------------------------------------------
    OutputDevice::~OutputDevice()
    {
    }


    //--------------------------------------------------------------------
    void 
    OutputDevice::operator()(const char* s)
    {
        std::ostringstream ss;
        ss << s;
        
        #ifdef _WIN32
            OutputDebugString(ss.str().c_str());
        #endif
        
        std::cout << s;
    }


    //--------------------------------------------------------------------
    void
    OutputDevice::operator()(const char* s, const char* logFile)
    {
        if( !fileCreated_ ) 
        {
            std::ofstream file(logFile, std::ios::trunc);		
            file << s;
            std::cout << s;
            fileCreated_ = true;
        }
        else 
        {
            std::ofstream file(logFile, std::ios::app);		
            file << s;
            std::cout << s;
        }	
    }


    //--------------------------------------------------------------------
    void	
    OutputDevice::operator()(const char* s, AssertDevice a)
    {
        if( a == MESSAGE_BOX ) 
        {
            std::ostringstream ss;
            ss << "**************************************" << std::endl;
            ss << "ASSERTION" << s << std::endl;
            ss << "**************************************" << std::endl;
            std::cout << ss.str();
            
            #ifdef _WIN32
                OutputDebugString(ss.str().c_str());
                MessageBox(0, s, "Assertion", MB_OK);
            #endif  // _WIN32
        }
    }

    
    
    
    
    
    
    Debugger& theDebugger()
    {
        static Debugger d;
        return d;
    }

    //--------------------------------------------------------------------
    void dumpMemoryLeaksInTheEnd()
    {
    #ifdef _WIN32
        _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG );
        _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

        _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG );
        _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );

        _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG );
        _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

        int flags = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
        flags |= _CRTDBG_LEAK_CHECK_DF;

        _CrtSetDbgFlag(flags);
    #endif // _WIN32
    }



} // namespace sce
