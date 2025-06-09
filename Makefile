CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

OBJS = Arithmetic.o BigInteger.o List.o
TEST_OBJS = BigIntegerTest.o BigInteger.o List.o

all: Arithmetic BigIntegerTest

Arithmetic: $(OBJS)
	$(CXX) $(CXXFLAGS) -o Arithmetic $(OBJS)

BigIntegerTest: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o BigIntegerTest $(TEST_OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o Arithmetic BigIntegerTest
