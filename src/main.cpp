#define WIN32_LEAN_AND_MEAN
#include "tiq.hpp"
#include <iostream>
#include <memory>

int main(void) {
  std::unique_ptr<TIQ> game = nullptr;
  
  try {
    game = std::unique_ptr<TIQ>(new TIQ(L"Adobe Flash Player 32"));
    std::cout << game->PID;
  } catch (std::exception &e) {
    std::cout << e.what() << "\n";
    return 1;
  }
}