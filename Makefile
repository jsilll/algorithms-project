all:
	g++ -std=c++11 -O3 -g -Wall src/main.cpp -lm -o main.out
	g++ -std=c++11 -O3 -g -Wall src/gen2procs.cpp -lm -o gen2procs.out


clean:
	find . -type f -name 'vgcore*' -delete
	find . -type f -name '*.o' -delete
	find . -type f -name '*.out' -delete
