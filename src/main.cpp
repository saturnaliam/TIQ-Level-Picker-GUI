#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <memory>
#include <thread>

#include "tiq.hpp"
#include "gui.hpp"

constexpr unsigned int sleep_time = 10;

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previousInstance, PWSTR arguments, int commandShow) {
  // to prevent these being shown as errors
  (void)instance;
  (void)previousInstance;
  (void)arguments;
  (void)commandShow;

  gui::CreateHWindow("Level Chooser", "Main Window");
  gui::CreateDevice();
  gui::CreateImGui();

  std::unique_ptr<TIQ> tiq = nullptr;

  try {
    tiq = std::make_unique<TIQ>(L"Adobe Flash Player 32");
  } catch (std::exception &e) {
    std::string message = e.what();
    message += "\nIs Flash Player running?";
    MessageBoxA(NULL, message.c_str(), "Error!", MB_ICONERROR | MB_OK);
    goto end;
  }

  while (gui::exit) {
    gui::BeginRender();
    tiq = gui::Render(std::move(tiq));
    gui::EndRender();

    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }

end:
  gui::DestroyImGui();
  gui::DestroyDevice();
  gui::DestroyHWindow();

  return 0;
}