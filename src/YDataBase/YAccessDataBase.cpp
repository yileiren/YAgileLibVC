#include "../../include/YDataBase/YAccessDataBase.h"

using namespace YLR;

YAccessDataBase::YAccessDataBase() :
	_filePath(new std::string()),
	_password(new std::string())
{
}

YAccessDataBase::YAccessDataBase(const YAccessDataBase & item)
{
}