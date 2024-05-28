files := src/main.cpp src/tiq.cpp

tiq:
	g++ -o bin/tiq-level-chooser $(files) -Wall -Wextra -pedantic -std=c++20