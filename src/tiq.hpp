#ifndef TIQ_HPP_
#define TIQ_HPP_

#include "utils.hpp"

class TIQ {
  private:
    DWORD64 get_module_base(const wchar_t *module_name);
    DWORD get_pid(const wchar_t *window_name);
    HANDLE get_process_handle();

  public:
    DWORD PID;
    DWORD64 module_base;
    HANDLE process_handle;

    TIQ(const wchar_t *window_name);
};

#endif // TIQ_HPP_