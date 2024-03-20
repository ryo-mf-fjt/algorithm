run: compile
	./out
compile:
	python3 tools/resolve.py test.cpp > out.cpp
	g++ -std=c++20 out.cpp -o out
