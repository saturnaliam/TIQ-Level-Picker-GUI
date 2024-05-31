#ifndef TIQ_HPP_
#define TIQ_HPP_

#include "utils.hpp"

constexpr unsigned int scene_map[100] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 29,
                                          30, 31, 32, 33, 34, 35, 36, 37, 38,
                                          58, 59, 60, 61, 62, 63, 64, 65, 66,
                                          67, 68, 69, 70, 71, 72, 91, 92, 93,
                                          94, 95, 96, 97, 98, 99, 100, 101,
                                          102, 103, 104, 105, 106, 107, 108,
                                          109, 110, 129, 130, 131, 132, 133,
                                          134, 135, 136, 137, 138, 139, 140,
                                          141, 142, 143, 144, 145, 146, 147,
                                          148, 168, 169, 170, 171, 172, 173,
                                          174, 175, 176, 177, 178, 179, 180,
                                          181, 182, 183, 184, 185, 186, 187,
                                          188, 189, 190, 191, 192 };

class TIQ {
  private:
    DWORD PID;
    DWORD64 base_address;
    DWORD base_size;
    DWORD64 hook_address;
    HANDLE process_handle;

    unsigned char hook_bytes[10] = { 0xC7, 0x45, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90 };
    const unsigned char old_bytes[10] = { 0x80, 0x7D, 0x0C, 0x00, 0x0F, 0x84, 0xA3, 0x00, 0x00, 0x00 };

    void get_level_address();
    void get_hook_address();
    void get_module_base(const wchar_t *module_name);
    void get_pid(const wchar_t *window_name);
    void get_process_handle();

  public:
    DWORD64 level_address;
    TIQ(const wchar_t *window_name);
    ~TIQ(); 
    unsigned int get_current_level();
    void enable_hook(unsigned int scene);
    void disable_hook();
    unsigned int map_to_scene(unsigned int level);
};

#endif // TIQ_HPP_