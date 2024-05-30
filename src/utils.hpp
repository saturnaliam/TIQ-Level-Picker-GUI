#ifndef UTILS_HPP_
#define UTILS_HPP_

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif 

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <stdexcept>
#include <iostream>
#include <string>

std::string get_last_error_message();

#endif // UTILS_HPP_