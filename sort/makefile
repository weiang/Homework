a.out: sort.o test.o sort.h
	g++ -g sort.o test.o
#a.out: sort.o sort.h
#	g++ -g sort.o
sort.o: sort.cc sort.h
	g++ -c sort.cc
test.o: test.cc sort.cc sort.h
	g++ -c test.cc
clean:
	rm *.o
