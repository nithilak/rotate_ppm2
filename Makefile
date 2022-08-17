CXX = clang++
FLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic
INCLUDES = includes

exec: src/* includes/*
	$(CXX) -Iincludes $(FLAGS) src/* -o bin/exec