main:	main.o functions.o
		g++ -Wall -o ass4 main main.o functions.o

main.o:	main.cpp header.h
		g++ -c main.cpp

ass4:	main.o functions.o
		g++ -Wall -o ass4 main.o functions.o

functions.o: functions.cpp header.h
		g++ -c functions.cpp

cleanLab:
		rm main.o main

cleanTest:
		rm ass4 functions.o
