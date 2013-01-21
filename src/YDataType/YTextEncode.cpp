#include <vector>

#include <Windows.h>

#include "../../include/YDataType/YTextEncode.h"

using namespace YLR;

void YTextEncode::freeText(std::string * text)
{
	delete text;
}

void YTextEncode::freeText(std::wstring * text)
{
	delete text;
}

std::wstring * utf8ToUnicode(const std::string & text)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);  
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)  
    {  
        return NULL;
    }  
    if (widesize == 0)  
    {  
        return NULL; 
    }  
  
    std::vector<wchar_t> resultstring(widesize);  
  
    int convresult = ::MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, &resultstring[0], widesize);  
  
    if (convresult != widesize)  
    {  
        return NULL;
    }  
  
    return new std::wstring(&resultstring[0]); 
}