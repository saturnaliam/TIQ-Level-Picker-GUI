#include "tiq.hpp"

TIQ::TIQ(const wchar_t *window_name) {
  try {
    this->get_pid(window_name);
    this->get_process_handle();
    this->get_module_base(window_name);
    this->get_hook_address();
    this->get_level_address();
  } catch (std::runtime_error &e) {
    throw e;
  }
}

TIQ::~TIQ() {
  this->disable_hook();
}

void TIQ::get_module_base(const wchar_t *module_name) {
  MODULEENTRY32 module_entry;
  ZeroMemory(&module_entry, sizeof(module_entry));

  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->PID);

  if (!snapshot) {
    throw std::runtime_error("error while getting snapshot!");
  }

  module_entry.dwSize = sizeof(module_entry);

  // getting the first module in the process
  if (!Module32First(snapshot, &module_entry)) {
    throw std::runtime_error("error while getting first module!");
  }
  
  do {
    // BUG idk why but gcc thinks szModule is char* not WCHAR*, so i need to cast it
    if (wcscmp(reinterpret_cast<wchar_t*>(module_entry.szModule), module_name)) {
      CloseHandle(snapshot);
      this->base_address = (DWORD64)module_entry.modBaseAddr;
      this->base_size = (DWORD64)module_entry.modBaseSize;
      return;
    }
  } while (Module32Next(snapshot, &module_entry));

  CloseHandle(snapshot);
  throw std::runtime_error("couldn't find module!");
}

void TIQ::get_pid(const wchar_t *window_name) {
  DWORD PID;

  HWND window_handle = FindWindowW(NULL, window_name);
  
  if (GetWindowThreadProcessId(window_handle, &PID) == 0) {
    throw std::runtime_error("invalid window handle!");
  }

  this->PID = PID;
}

void TIQ::get_process_handle() {
  HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->PID);

  if (process_handle == NULL) {
    throw std::runtime_error("error getting process handle!");
  }

  this->process_handle = process_handle;
}

void TIQ::get_hook_address() {
  unsigned char *buffer = reinterpret_cast<unsigned char*>(calloc(1, this->base_size));
  DWORD64 bytes_read = 0;

  ReadProcessMemory(this->process_handle, (void*)this->base_address, buffer, this->base_size, &bytes_read);

  printf("scanning for pattern\n");
  for (unsigned int i = 0; i < this->base_size - sizeof(this->old_bytes); i++) {
    for (unsigned int j = 0; j < sizeof(this->old_bytes); j++) {
      if (this->old_bytes[j] != buffer[i + j]) {
        break;
      }

      if (j + 1 == sizeof(this->old_bytes)) {
        this->hook_address = (DWORD)this->base_address + i;
        goto end;
      }
    }
  }

  throw std::runtime_error("pattern not found!");
end:
  free(buffer);
}

void TIQ::enable_hook(unsigned int level) {
  this->hook_bytes[3] = level;

  if (WriteProcessMemory(this->process_handle, reinterpret_cast<LPVOID>(this->hook_address), this->hook_bytes, sizeof(this->hook_bytes), NULL) == 0) {
    throw std::runtime_error(get_last_error_message());
  }
}

void TIQ::disable_hook() {
  if (WriteProcessMemory(this->process_handle, reinterpret_cast<LPVOID>(this->hook_address), this->old_bytes, sizeof(this->old_bytes), NULL) == 0) {
    throw std::runtime_error(get_last_error_message());
  }
}

void TIQ::get_level_address() {
  constexpr int offsets[7] = { 0xC95B64, 0x24, 0xA8C, 0x4, 0x2C, 0x50, 0x264 };

  DWORD64 temp = this->base_address;
  for (int i = 0; i < 7; i++) {
    temp += offsets[i];
    ReadProcessMemory(this->process_handle, (LPVOID)temp, &temp, sizeof(int), NULL);
  }

  this->level_address = temp + 0x4C;
}

unsigned int TIQ::get_current_level() {
  unsigned int level;
  ReadProcessMemory(this->process_handle, (LPVOID)(this->level_address), &level, sizeof(level), NULL);
  return level;
}

unsigned int TIQ::map_to_scene(unsigned int level) {
  return scene_map[level - 1];
}