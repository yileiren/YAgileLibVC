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

std::wstring * YTextEncode::utf8ToUnicode(const std::string & text)
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

std::string * YTextEncode::utf8ToMultibyte(const std::string &text)
{
	std::string *strRet = NULL;  
  
  
    //先把 utf8 转为 unicode   
    std::wstring *wstr = YTextEncode::utf8ToUnicode(text);  
  
    //最后把 unicode 转为 ascii  
    
	if(wstr != NULL)
	{
		strRet = YTextEncode::unicodeToMultibyte(*wstr); 
		delete wstr;
	}
  
    return strRet;  
}

std::string * YTextEncode::unicodeToMultibyte(const std::wstring &text)
{
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, text.c_str(), -1, NULL, 0, NULL, NULL);  
    if (asciisize == ERROR_NO_UNICODE_TRANSLATION)  
    {  
        return NULL;  
    }  
    if (asciisize == 0)  
    {  
        return NULL;
    }  
    std::vector<char> resultstring(asciisize);  
    int convresult =::WideCharToMultiByte(CP_OEMCP, 0, text.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);  
  
    if (convresult != asciisize)  
    {  
        return NULL;  
    }  
  
    return new std::string(&resultstring[0]); 
}

std::string * YTextEncode::unicodeToUtf8(const std::wstring & text)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1, NULL, 0, NULL, NULL);  
    if (utf8size == 0)  
    {  
        return NULL;  
    }  
  
    std::vector<char> resultstring(utf8size);  
  
    int convresult = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);  
  
    if (convresult != utf8size)  
    {  
        return NULL; 
    }  
  
    return new std::string(&resultstring[0]);  
}

std::wstring * YTextEncode::multibyteToUnicode(const std::string & text)
{
	int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)text.c_str(), -1, NULL, 0);  
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)  
    {  
        return NULL;  
    }  
    if (widesize == 0)  
    {  
        return NULL;  
    }  
    std::vector<wchar_t> resultstring(widesize);  
    int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)text.c_str(), -1, &resultstring[0], widesize);  
  
    if (convresult != widesize)  
    {  
        return NULL;  
    }  
  
    return new std::wstring(&resultstring[0]);  
}

std::string * YTextEncode::multibyteToUtf8(const std::string & text)
{
	std::string *strRet = NULL;  
  
  
    //先把 ascii 转为 unicode   
    std::wstring *wstr = YTextEncode::multibyteToUnicode(text);  
  
    //最后把 unicode 转为 utf8  
	if(wstr != NULL)
	{
		strRet = YTextEncode::unicodeToUtf8(*wstr);  
		delete wstr;
	}
  
    return strRet;  
}