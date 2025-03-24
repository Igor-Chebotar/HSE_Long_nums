cmake_minimum_required(VERSION 3.30)
project(HSE_Long_nums)

set(CMAKE_CXX_STANDARD 20)

# Создаём статическую библиотеку из общих исходников
add_library(LongArithmetic STATIC
        src/LongNumber.cpp
)

# Исполняемый файл для main
add_executable(HSE_Long_nums
        src/main.cpp
)
target_link_libraries(HSE_Long_nums PRIVATE LongArithmetic)

# Исполняемый файл для pi_calculator
add_executable(pi_calculator
        src/pi_calculator.cpp
)
target_link_libraries(pi_calculator PRIVATE LongArithmetic)

# Исполняемый файл для тестов
add_executable(test_longnumber
        tests/test_longnumber.cpp
)
target_link_libraries(test_longnumber PRIVATE LongArithmetic)

include_directories(${CMAKE_SOURCE_DIR}/include)
