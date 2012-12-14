OBJ = array.o item.o test.o sort.o
HEAD = array.h item.h sort.h

a.out: $(OBJ) $(HEAD)
	g++ -g $(OBJ)
array.o: $(HEAD) array.cc
	g++ -g -c array.cc
item.o: item.h item.cc
	g++ -g -c item.cc
test.o: $(HEAD) test.cc
	g++ -g -c test.cc
sort.o: sort.h sort.cc
	g++ -g -c sort.cc
clean:	
	rm $(OBJ)
