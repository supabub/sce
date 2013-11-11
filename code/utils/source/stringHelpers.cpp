#include "../headers/stringHelpers.h"

namespace sce
{

    // func def.
    void tokenizeString(const std::string& str, const std::string& delims, std::vector<std::string>& tokens);
    
    
	std::string
	removeWhiteSpace(const std::string& str)
	{
		std::string newString;
		newString.reserve(str.length());

		for( unsigned int i = 0 ; i < str.size() ; ++i ) {
			if( str[i] != ' ' ) {
				newString.push_back(str[i]);
			}
		}

		return newString;
	}

	std::string
	removeTabs(const std::string& str)
	{
		std::string newString;
		newString.reserve(str.length());

		for( unsigned int i = 0 ; i < str.size() ; ++i ) {
			if( str[i] != '\t' ) {
				newString.push_back(str[i]);
			}
		}

		return newString;
	}

	void
	removeDelims(const std::string& str, const std::string& delims, std::string& retString)
	{
		retString = "";
		size_t numDelims = delims.length();

		for( unsigned int i = 0 ; i < str.size() ; ++i ) 
		{
			bool charIsDelim = false;
			for( size_t index = 0 ; index < numDelims ; ++index )
			{
				if( str[i] == delims[index])
				{
					charIsDelim = true;
					break;
				}
			}
			if( !charIsDelim )
				retString.push_back(str[i]);
		}
	}

	std::string
	replaceTabsWithWhitespace(const std::string& str)
	{
		std::string newString;
		newString.reserve(str.length());

		for( unsigned int i = 0 ; i < str.size() ; ++i ) {
			if( str[i] == '\t' ) {
				newString.push_back(' ');
			}
			else {
				newString.push_back(str[i]);
			}
		}

		return newString;
	}

	void 
	tokenizeString(const std::string& str, const std::string& delims, std::vector<std::string>& tokens)
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

	void	
	tolowerString(const std::string& str, std::string& tolowerStr)
	{
		tolowerStr = str;
		std::transform(tolowerStr.begin(), tolowerStr.end(), tolowerStr.begin(), tolower);
	}

}	// namespace sce
