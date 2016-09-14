hotpotato: main.o random.o
	g++ main.o random.o -o hotpotato

main.o: main.cpp RevList.h random.h
	g++ -c main.cpp

random.o: random.cpp random.h
	g++ -c random.cpp

clean: 
	rm *.o -f