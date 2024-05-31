#ifndef GUI_HPP_
#define GUI_HPP_

#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "utils.hpp"

namespace gui {
  constexpr int width = 500;
  constexpr int height = 300;

  inline bool exit = true;

  inline HWND window = nullptr;
  inline WNDCLASSEXA windowClass = { };

  inline POINTS position = { };

  inline PDIRECT3D9 d3d = nullptr;
  inline LPDIRECT3DDEVICE9 device = nullptr;
  inline D3DPRESENT_PARAMETERS presentParameters = { };
  
  void CreateHWindow(
    const char *windowName,
    const char *className) noexcept;
  void DestroyHWindow() noexcept;

  bool CreateDevice() noexcept;
  void ResetDevice() noexcept;
  void DestroyDevice() noexcept;

  void CreateImGui() noexcept;
  void DestroyImGui() noexcept;

  void BeginRender() noexcept;
  void EndRender() noexcept;
  void Render() noexcept;
};

#endif // GUI_HPP_