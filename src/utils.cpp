#include "utils.hpp"

std::string get_last_error_message() {
  DWORD error_id = GetLastError();
  if (error_id == 0) {
    return std::string();
  }

  LPSTR buffer = nullptr;

  size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error_id, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);

  std::string message(buffer, size);

  LocalFree(buffer);
  
  return message;
}