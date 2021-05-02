compiler = g++
result = maze
src = $(shell find -name "*.cpp")
$(compiler) $(src) -std=c++11 -o $(result)
