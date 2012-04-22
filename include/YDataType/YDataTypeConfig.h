#ifndef Y_DATA_TYPE_CONFIG
#define Y_DATA_TYPE_CONFIG

#ifdef YDATATYPE_EXPORTS
#	define YBYTETYPE_API __declspec(dllexport)
#else
#	define YBYTETYPE_API __declspec(dllimport)
#endif

#endif