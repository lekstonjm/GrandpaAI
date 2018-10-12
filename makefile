CFLAGS=-std=c++11
build_obj_folder := $(shell mkdir -p obj)
tests: test_reference test_node test_negater
clean:
	rm obj/*.o test_reference test_node test_negater
test_reference: test_reference.o exception.o
	g++ -o test_reference obj/test_reference.o obj/exception.o
test_node: test_node.o logic_node.o exception.o
	g++ -o test_node  obj/logic_node.o obj/test_node.o obj/exception.o
test_negater: test_negater.o logic_node.o negater.o exception.o
	g++ -o test_negater obj/logic_node.o obj/negater.o obj/test_negater.o obj/exception.o
test_reference.o: src/test_reference.cpp
	g++ $(CFLAGS) -o obj/test_reference.o -c src/test_reference.cpp
test_node.o: src/test_node.cpp
	g++ $(CFLAGS) -o obj/test_node.o -c src/test_node.cpp
test_negater.o: src/test_negater.cpp
	g++ $(CFLAGS) -o obj/test_negater.o -c src/test_negater.cpp
logic_node.o: src/exception.hpp src/reference.hpp src/logic_node.hpp src/logic_node.cpp
	g++ $(CFLAGS) -o obj/logic_node.o -c src/logic_node.cpp
negater.o: src/reference.hpp src/negater.hpp src/negater.cpp
	g++ $(CFLAGS) -o obj/negater.o -c src/negater.cpp
exception.o: src/exception.hpp src/exception.cpp
	g++ $(CFLAGS) -o obj/exception.o -c src/exception.cpp
