#include "tiq.hpp"

TIQ::TIQ(const wchar_t *window_name) {
  try {
    this->PID = this->get_pid(window_name);
    this->module_base = this->get_module_base(window_name);
    this->process_handle = this->get_process_handle();
  } catch (std::runtime_error &e) {
    throw e;
  }
}

DWORD64 TIQ::get_module_base(const wchar_t *module_name) {
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
      return (DWORD64)module_entry.modBaseAddr;
    }
  } while (Module32Next(snapshot, &module_entry));

  CloseHandle(snapshot);
  throw std::runtime_error("couldn't find module!");
}

DWORD TIQ::get_pid(const wchar_t *window_name) {
  DWORD PID;

  HWND window_handle = FindWindowW(NULL, window_name);
  
  if (GetWindowThreadProcessId(window_handle, &PID) == 0) {
    throw std::runtime_error("invalid window handle!");
  }

  return PID;
}

HANDLE TIQ::get_process_handle() {
  HANDLE process_handle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, this->PID);

  if (process_handle == NULL) {
    throw std::runtime_error("error getting process handle!");
  }

  return process_handle;
}