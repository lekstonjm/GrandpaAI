CFLAGS=-std=c++11
build_obj_folder := $(shell mkdir -p obj)
tests: test_reference test_node test_negater test_implication_cnf_transformer test_negation_cnf_transformer
clean:
	rm obj/*.o test_*
test_reference: test_reference.o exception.o
	g++ -o test_reference obj/test_reference.o obj/exception.o
test_node: test_node.o logic_node.o exception.o
	g++ -o test_node  obj/logic_node.o obj/test_node.o obj/exception.o
test_negater: test_negater.o negater.o logic_node.o exception.o
	g++ -o test_negater obj/logic_node.o obj/negater.o obj/test_negater.o obj/exception.o
test_implication_cnf_transformer: test_implication_cnf_transformer.o implication_cnf_transformer.o logic_node.o exception.o
	g++ -o test_implication_cnf_transformer obj/test_implication_cnf_transformer.o obj/implication_cnf_transformer.o  obj/logic_node.o obj/exception.o
test_negation_cnf_transformer: test_negation_cnf_transformer.o negation_cnf_transformer.o negater.o logic_node.o exception.o
	g++ -o test_negation_cnf_transformer obj/test_negation_cnf_transformer.o obj/negation_cnf_transformer.o  obj/negater.o obj/logic_node.o obj/exception.o
test_reference.o: src/test_reference.cpp
	g++ $(CFLAGS) -o obj/test_reference.o -c src/test_reference.cpp
test_node.o: src/test_node.cpp
	g++ $(CFLAGS) -o obj/test_node.o -c src/test_node.cpp
test_negater.o: src/test_negater.cpp
	g++ $(CFLAGS) -o obj/test_negater.o -c src/test_negater.cpp
test_implication_cnf_transformer.o: src/test_implication_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/test_implication_cnf_transformer.o -c src/test_implication_cnf_transformer.cpp
test_negation_cnf_transformer.o: src/test_negation_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/test_negation_cnf_transformer.o -c src/test_negation_cnf_transformer.cpp
exception.o: src/exception.hpp src/exception.cpp
	g++ $(CFLAGS) -o obj/exception.o -c src/exception.cpp
logic_node.o: src/exception.hpp src/reference.hpp src/logic_node.hpp src/logic_node.cpp
	g++ $(CFLAGS) -o obj/logic_node.o -c src/logic_node.cpp
negater.o: src/reference.hpp src/negater.hpp src/negater.cpp
	g++ $(CFLAGS) -o obj/negater.o -c src/negater.cpp	
implication_cnf_transformer.o: src/reference.hpp src/implication_cnf_transformer.hpp src/implication_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/implication_cnf_transformer.o -c src/implication_cnf_transformer.cpp
negation_cnf_transformer.o: src/reference.hpp src/negation_cnf_transformer.hpp src/negation_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/negation_cnf_transformer.o -c src/negation_cnf_transformer.cpp
