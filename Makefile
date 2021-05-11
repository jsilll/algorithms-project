all:
	g++ -std=c++11 -O3 -g -Wall src/main.cpp -lm

clean:
	find . -type f -name 'vgcore*' -delete
	find . -type f -name '*.o' -delete
	find . -type f -name '*.out' -delete
