a.out: graph.o test.o
	g++ -g graph.o test.o
graph.o: graph.cc graph.h
	g++ -c graph.cc
test.o: graph.h test.cc
	g++ -c test.cc
clean: graph.o test.o
	rm graph.o test.o
