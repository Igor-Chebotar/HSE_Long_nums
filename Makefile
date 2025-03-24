# Минимальная версия Makefile

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
INCLUDES = -I./include

# Исходники библиотеки и программ
LIB_SOURCES = src/LongNumber.cpp src/literal.cpp
TEST_SOURCES = tests/test_longnumber.cpp
PI_SOURCES = src/pi_calculator.cpp

# Объектные файлы
LIB_OBJECTS = $(LIB_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
PI_OBJECTS = $(PI_SOURCES:.cpp=.o)

# Цели
all: HSE_Long_nums test pi

# Сборка основной библиотеки в виде исполняемого (для демонстрации)
HSE_Long_nums: src/main.cpp $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) src/main.cpp $(LIB_OBJECTS) -o HSE_Long_nums

# Сборка тестов
test: $(TEST_OBJECTS) $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST_OBJECTS) $(LIB_OBJECTS) -o test_longnumber

# Сборка программы для вычисления Пи
pi: $(PI_OBJECTS) $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(PI_OBJECTS) $(LIB_OBJECTS) -o pi_calculator

# Правила для объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Запуск тестов
check: test
	./test_longnumber

# Запуск вычисления Пи (пример на 100 знаков)
run-pi: pi
	./pi_calculator 100

clean:
	rm -f *.o src/*.o tests/*.o pi_calculator test_longnumber HSE_Long_nums
