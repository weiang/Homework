a.out: test.o graph.o graph.h
	g++ -g test.o graph.o
test.o: test.cc graph.h
	g++ -g -c test.cc
graph.o: graph.h graph.cc
	g++ -g -c graph.cc
clean:
	rm *.o
