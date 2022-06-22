set(EXE_NAME ${PROJECT_NAME}-TESTS)
set(TEST_SEED 777)
set(ARR_SIZE 10000)
set(PATH_TO_SHARED_LIB ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib${LIB_NAME_PAR}.so)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include ../project/include/)

add_executable(${EXE_NAME} src/main.cpp src/sequential_tests.cpp src/utils.cpp src/parallel_tests.cpp)
target_link_libraries(${EXE_NAME} ${GTEST_BOTH_LIBRARIES} pthread ${LIB_NAME_SEQ} dl stdc++fs)

add_test(NAME SequentialTests COMMAND ${EXE_NAME} ${TEST_SEED} ${ARR_SIZE} ${PATH_TO_SHARED_LIB} --gtest_filter=SEQUENTIAL_TESTS.*)
add_test(NAME ParallelTests COMMAND ${EXE_NAME} ${TEST_SEED} ${ARR_SIZE} ${PATH_TO_SHARED_LIB} --gtest_filter=PARALLEL_TESTS.*)