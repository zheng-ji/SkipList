builtin_type_example: builtin_type_example.o
	g++ -std=c++11 -Wall -o builtin_type_example builtin_type_example.o

builtin_type_example.o: builtin_type_example.cpp
	g++ -std=c++11 -Wall -g -c builtin_type_example.cpp

clean:
	rm builtin_type_example *.o

test: builtin_type_example
	./builtin_type_example
