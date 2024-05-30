#ifndef TIQ_HPP_
#define TIQ_HPP_

#include "utils.hpp"

class TIQ {
  private:
    DWORD PID;
    DWORD64 base_address;
    DWORD base_size;
    HANDLE process_handle;
    DWORD64 hook_address;

    const unsigned char hook_bytes[11] = { 0xC7, 0x45, 0x08, 0x0A, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90 };
    const unsigned char old_bytes[7] = { 0x80, 0x7D, 0x0C, 0x00, 0x0F, 0x84, 0xA3 };

    void get_hook_address();
    void get_module_base(const wchar_t *module_name);
    void get_pid(const wchar_t *window_name);
    void get_process_handle();

  public:
    TIQ(const wchar_t *window_name);
    void enable_hook();
    void disable_hook();
};

#endif // TIQ_HPP_