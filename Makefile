files := src/main.cpp src/tiq.cpp src/utils.cpp

tiq:
	g++ -o bin/tiq-level-chooser $(files) -Wall -Wextra -pedantic -std=c++20