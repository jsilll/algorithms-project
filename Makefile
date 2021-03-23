OBJS	= src/project.o src/randomDAG.o
OUT	= project randomDAG

OBJS0	= src/project.o
SOURCE0	= src/project.cpp
HEADER0	= 
OUT0	= project

OBJS1	= src/randomDAG.o
SOURCE1	= src/randomDAG.cpp
HEADER1	= 
OUT1	= randomDAG

CC	 = g++
FLAGS	 = -g3 -c -O3 -Wall
LFLAGS	 = -lm
# -g option enables debugging mode 
# -c flag generates object code for separate files


all: project

project: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

randomDAG: $(OBJS1) $(LFLAGS)
	$(CC) -g $(OBJS1) -o $(OUT1)

# create/compile the individual files >>separately<<
src/project.o: src/project.cpp
	$(CC) $(FLAGS) src/project.cpp -std=c++11 -o $(OBJS0)

src/randomDAG.o: src/randomDAG.cpp
	$(CC) $(FLAGS) src/randomDAG.cpp -std=c++11 -o $(OBJS1)


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# run the program
run: $(OUT)
	# ./project
	# Execução: ./randomDAG N p [seed] > testfile (podem variar os parâmetros e gerar vários ficheiros de teste)
	./project

# compile program with debugging information
debug: $(OUT)
	valgrind ./project

# run program with valgrind for errors
valgrind: $(OUT)
	valgrind ./project

# run program with valgrind for leak checks
valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full ./project

# run program with valgrind for leak checks (extreme)
valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./project