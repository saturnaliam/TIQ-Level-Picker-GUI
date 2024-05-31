#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <memory>
#include <thread>

#include "tiq.hpp"
#include "gui.hpp"

constexpr unsigned int sleep_time = 10;

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previousInstance, PWSTR arguments, int commandShow) {
  gui::CreateHWindow("hi", "ballin");
  gui::CreateDevice();
  gui::CreateImGui();

  while (gui::exit) {
    gui::BeginRender();
    gui::Render();
    gui::EndRender();

    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }

  gui::DestroyImGui();
  gui::DestroyDevice();
  gui::DestroyHWindow();

  return 0;
}