files := src/main.cpp src/tiq.cpp src/utils.cpp src/gui.cpp $(wildcard src/imgui/*.cpp)
external := -ld3d9 -ld3dcompiler
CXXFLAGS = -Wall -Wextra -pedantic -std=c++20 -ggdb -O2

tiq:
	clang++ -o bin/tiq-level-chooser.exe $(files) $(external) $(CXXFLAGS)