CFLAGS=-std=c++11
tests: test_reference test_node test_inverter
clean:
	rm *.o test_reference test_node test_inverter
test_reference: test_reference.o
	g++ -o test_reference test_reference.o
test_node: test_node.o node.o
	g++ -o test_node  node.o test_node.o
test_inverter: test_inverter.o node.o inverter.o
	g++ -o test_inverter node.o inverter.o test_inverter.o
test_reference.o:
	g++ $(CFLAGS) -o test_reference.o -c test_reference.cpp
test_node.o:
	g++ $(CFLAGS) -o test_node.o -c test_node.cpp
test_inverter.o:
	g++ $(CFLAGS) -o test_inverter.o -c test_inverter.cpp
node.o:
	g++ $(CFLAGS) -o node.o -c node.cpp
inverter.o:
	g++ $(CFLAGS) -o inverter.o -c inverter.cpp
