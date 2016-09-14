CPPFLAGS=-g -O3

imdbtree: Actor.o Actors.o Movie.o main.o
	g++ $(CPPFLAGS) Actor.o Actors.o Movie.o main.o -o imdbtree

Actor.o: Actor.cpp Actor.h Tree.h Movie.h
	g++ $(CPPFLAGS) -c Actor.cpp

Actors.o: Actors.cpp Actors.h Movie.h Tree.h
	g++ $(CPPFLAGS) -c Actors.cpp

Movie.o: Movie.cpp Movie.h Tree.h
	g++ $(CPPFLAGS) -c Movie.cpp

main.o: main.cpp Movie.h Tree.h Actors.h Actor.h CTAGradeHook.h
	g++ $(CPPFLAGS) -c main.cpp

clean:
	rm *.o -f