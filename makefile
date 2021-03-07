all: topk.out

topk.out: topk.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out