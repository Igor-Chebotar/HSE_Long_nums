CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
INCLUDES = -I./include

# Исходники библиотеки и программ (без literal.cpp)
LIB_SOURCES = src/LongNumber.cpp
TEST_SOURCES = tests/test_longnumber.cpp
PI_SOURCES = src/pi_calculator.cpp

# Объектные файлы
LIB_OBJECTS = $(LIB_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
PI_OBJECTS = $(PI_SOURCES:.cpp=.o)

# Цели
all: HSE_Long_nums test pi

HSE_Long_nums: src/main.cpp $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) src/main.cpp $(LIB_OBJECTS) -o HSE_Long_nums

test: $(TEST_OBJECTS) $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST_OBJECTS) $(LIB_OBJECTS) -o test_longnumber

pi: $(PI_OBJECTS) $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(PI_OBJECTS) $(LIB_OBJECTS) -o pi_calculator

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

check: test
	./test_longnumber

run-pi: pi
	./pi_calculator 100

clean:
	rm -f *.o src/*.o tests/*.o pi_calculator test_longnumber HSE_Long_nums
