#ifndef __STRINGHELPERS_H__
#define __STRINGHELPERS_H__

#include "start.h"

namespace sce
{

	std::string
	removeWhiteSpace(const std::string& str);

	std::string
	removeTabs(const std::string& str);

	void
	removeDelims(const std::string& str, const std::string& delims, std::string& retString);

	std::string
	replaceTabsWithWhitespace(const std::string& str);

	template<typename T> void 
	tokenizeString(const std::string& str, const std::string& delims, T& tokens);

	void
	tolowerString(const std::string& str, std::string& tolowerStr);

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //**************************************************************************
    
    
    template<typename T> inline void 
    tokenizeString(const std::string& str, const std::string& delims, T& tokens)
    {
        std::string::size_type begIdx, endIdx, searchIdx;
        begIdx = str.find_first_not_of(delims);
        
        std::string token;
        
        while( begIdx != std::string::npos ) 
        {
            endIdx = str.find_first_of(delims, begIdx);
            
            if( endIdx == std::string::npos )
            {
                endIdx = str.length();
            }
            
            token = std::string(str, begIdx, endIdx-begIdx);	
            
            // check if there are "" for string definitions
            if( token.find("\"") != std::string::npos ) 
            {
                searchIdx = str.find_first_of("\"", begIdx+1);
                token = std::string(str, begIdx+1, searchIdx-begIdx-1);
                if( searchIdx == begIdx+1 ) 
                {
                    endIdx = searchIdx+2;
                    token = "";
                }
                else 
                {
                    endIdx = searchIdx+1;
                }
            }
            
            tokens.push_back(token);
            
            begIdx = str.find_first_not_of(delims, endIdx);
        }
    }

}	// namespace sce

#endif
