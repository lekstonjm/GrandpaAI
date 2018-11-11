CFLAGS=-std=c++11 -I "./include"  -I "./include/0_infrastructure" -I "./include/1_core"
build_obj_folder := $(shell mkdir -p obj)
build_bin_folder := $(shell mkdir -p bin)
build_bin_0_infrastucture := $(shell mkdir -p bin/0_infrastructure)
build_bin_1_core := $(shell mkdir -p bin/1_core)
build_bin_2_transformer := $(shell mkdir -p bin/2_transformer)
build_bin_2_transformer_cnf := $(shell mkdir -p bin/2_transformer/cnf)

tests: test_reference \
		test_logic_node \
		test_negater \
		test_implication_cnf_transformer \
		test_negation_cnf_transformer \
		test_connective_cnf_transformer \
		test_quantifier_cnf_transformer \
		test_cnf_transformer
clean:
	rm -r obj bin
test_reference: test_reference.o exception.o
	g++ -o bin/0_infrastructure/test_reference obj/test_reference.o obj/exception.o
test_logic_node: test_logic_node.o logic_node.o exception.o
	g++ -o bin/1_core/test_logic_node  obj/logic_node.o obj/test_node.o obj/exception.o
test_negater: test_negater.o negater.o logic_node.o exception.o
	g++ -o bin/2_transformer/test_negater obj/logic_node.o obj/negater.o obj/test_negater.o obj/exception.o
test_implication_cnf_transformer: test_implication_cnf_transformer.o implication_cnf_transformer.o logic_node.o exception.o
	g++ -o bin/2_transformer/cnf/test_implication_cnf_transformer obj/test_implication_cnf_transformer.o obj/implication_cnf_transformer.o  obj/logic_node.o obj/exception.o
test_negation_cnf_transformer: test_negation_cnf_transformer.o negation_cnf_transformer.o negater.o logic_node.o exception.o
	g++ -o bin/2_transformer/cnf/test_negation_cnf_transformer obj/test_negation_cnf_transformer.o obj/negation_cnf_transformer.o  obj/negater.o obj/logic_node.o obj/exception.o
test_connective_cnf_transformer: test_connective_cnf_transformer.o connective_cnf_transformer.o logic_node.o exception.o
	g++ -o bin/2_transformer/cnf/test_connective_cnf_transformer obj/test_connective_cnf_transformer.o obj/connective_cnf_transformer.o  obj/logic_node.o obj/exception.o
test_quantifier_cnf_transformer: test_quantifier_cnf_transformer.o quantifier_cnf_transformer.o logic_node.o exception.o
	g++ -o bin/2_transformer/cnf/test_quantifier_cnf_transformer obj/test_quantifier_cnf_transformer.o obj/quantifier_cnf_transformer.o  obj/logic_node.o obj/exception.o
test_cnf_transformer: test_cnf_transformer.o cnf_transformer.o quantifier_cnf_transformer.o connective_cnf_transformer.o negation_cnf_transformer.o implication_cnf_transformer.o negater.o logic_node.o exception.o  
	g++ -o bin/2_transformer/test_cnf_transformer obj/test_cnf_transformer.o obj/cnf_transformer.o obj/quantifier_cnf_transformer.o obj/connective_cnf_transformer.o obj/negation_cnf_transformer.o obj/implication_cnf_transformer.o obj/negater.o obj/logic_node.o obj/exception.o
test_reference.o: src/0_infrastructure/test_reference.cpp
	g++ $(CFLAGS) -o obj/test_reference.o -c src/0_infrastructure/test_reference.cpp
test_logic_node.o: src/1_core/test_logic_node.cpp
	g++ $(CFLAGS) -o obj/test_node.o -c src/1_core/test_logic_node.cpp
test_negater.o: src/2_transformer/test_negater.cpp
	g++ $(CFLAGS) -o obj/test_negater.o -c src/2_transformer/test_negater.cpp
test_implication_cnf_transformer.o: src/2_transformer/cnf/test_implication_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/test_implication_cnf_transformer.o -c src/2_transformer/cnf/test_implication_cnf_transformer.cpp
test_negation_cnf_transformer.o: src/2_transformer/cnf/test_negation_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/test_negation_cnf_transformer.o -c src/2_transformer/cnf/test_negation_cnf_transformer.cpp
test_connective_cnf_transformer.o: src/2_transformer/cnf/test_connective_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/test_connective_cnf_transformer.o -c src/2_transformer/cnf/test_connective_cnf_transformer.cpp
test_quantifier_cnf_transformer.o: src/2_transformer/cnf/test_quantifier_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/test_quantifier_cnf_transformer.o -c src/2_transformer/cnf/test_quantifier_cnf_transformer.cpp
test_cnf_transformer.o: src/2_transformer/test_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/test_cnf_transformer.o -c src/2_transformer/test_cnf_transformer.cpp
exception.o: include/0_infrastructure/exception.hpp
	g++ $(CFLAGS) -o obj/exception.o -c src/0_infrastructure/exception.cpp
logic_node.o: src/1_core/logic_node.cpp
	g++ $(CFLAGS) -o obj/logic_node.o -c src/1_core/logic_node.cpp
negater.o: src/2_transformer/negater.cpp
	g++ $(CFLAGS) -o obj/negater.o -c src/2_transformer/negater.cpp
implication_cnf_transformer.o: src/2_transformer/cnf/implication_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/implication_cnf_transformer.o -c src/2_transformer/cnf/implication_cnf_transformer.cpp
negation_cnf_transformer.o: src/2_transformer/cnf/negation_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/negation_cnf_transformer.o -c src/2_transformer/cnf/negation_cnf_transformer.cpp
connective_cnf_transformer.o: src/2_transformer/cnf/connective_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/connective_cnf_transformer.o -c src/2_transformer/cnf/connective_cnf_transformer.cpp
quantifier_cnf_transformer.o: src/2_transformer/cnf/quantifier_cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/quantifier_cnf_transformer.o -c src/2_transformer/cnf/quantifier_cnf_transformer.cpp
cnf_transformer.o: src/2_transformer/cnf_transformer.cpp
	g++ $(CFLAGS) -o obj/cnf_transformer.o -c src/2_transformer/cnf_transformer.cpp
