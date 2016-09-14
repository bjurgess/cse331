quicksort: Actors.o Main.o
	    g++ Actors.o Main.o -o quicksort

Actors.o: Actors.cpp Actors.h moviepointer.h
	  g++ -c Actors.cpp

Main.o: Main.cpp moviepointer.h QuickSort.h VerifySort.h DuplicatesRemove.h
	g++ -c Main.cpp
