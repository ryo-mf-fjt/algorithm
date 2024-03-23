run: compile
	./main < in.txt

test: test_compiple
	./test

compile:
	python3 tools/resolve.py main.cpp > main_resolved.cpp
	g++ -std=c++17 -O2 main_resolved.cpp -o main

test_compiple:
	python3 tools/resolve.py **/*.spec.hpp > test.cpp
	g++ -std=c++17 -O2 test.cpp -o test -lgtest -lgtest_main
