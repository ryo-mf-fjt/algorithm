RESOLVE:=python3 tools/resolve.py
GPP:=g++ -std=c++17 -fsanitize=address -O2 -Wall -Wextra

run: compile
	./main < in.txt

test: test_compiple
	./test

compile:
	$(RESOLVE) main.cpp > main_resolved.cpp
	$(GPP) main_resolved.cpp -o main

test_compiple:
	$(RESOLVE) **/*.spec.hpp > test.cpp
	$(GPP) test.cpp -o test -lgtest -lgtest_main

oj/%: T=${@:oj/%=%}
oj/%@download: T=${@:oj/%@download=%}
oj/%@clear: T=${@:oj/%@clear=%}

oj/%@clear:
	rm -rf oj/$(T)/test

oj/%@download:
	if [ ! -d oj/$(T)/test ]; then \
		cd oj/$(T) && \
		oj download `head -n 1 main.cpp | cut -c 3-`; \
	fi

oj/%: FORCE
	make oj/$(T)@download && \
	$(RESOLVE) oj/$(T)/main.cpp > oj/$(T)/main_resolved.cpp && \
	cd oj/$(T) && \
	$(GPP) main_resolved.cpp -o main && \
	oj test --command ./main

FORCE:
