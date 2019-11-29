CC= g++
OPTIONS= -c -O2 -m64 -march=native -std=c++11 -w

all: Main
Main: Main.o Functions.o Parser.o 
	$(CC) -o Main main_irace.o functions.o parser.o -lm

Main.o: main_irace.cpp parser.h functions.h 
	$(CC) $(OPTIONS) main_irace.cpp 

Functions.o: functions.cpp functions.h 
	$(CC) $(OPTIONS) functions.cpp 

Parser.o: parser.cpp parser.h 
	$(CC) $(OPTIONS) parser.cpp  

clean:
	rm *.o Main -f

#./Main instances/Pa280_n837_bounded-strongly-corr_07.ttp --IR_GRASP 10 --SIZE_RCL 0.3 --seed 18
