#pragma once
#include <string>
#include <tchar.h>

#ifdef _UNICODE
using tstring = std::basic_string<wchar_t>;
template<typename T>
tstring to_tstring(T n)
{
    return std::to_wstring(n);
}
#else
using tstring = std::basic_string<char>;
template<typename T>
tstring to_tstring(T n)
{
    return std::to_string(n);
}
#endif
