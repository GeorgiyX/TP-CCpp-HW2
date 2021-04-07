set(EXE_NAME ${PROJECT_NAME}-TESTS)
set(TEST_SEED 777)
set(ARR_SIZE 10000)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include ./../project/include/)

add_executable(${EXE_NAME} src/main.cpp
               src/common_tests.cpp src/utils.cpp)
target_link_libraries(${EXE_NAME} ${GTEST_BOTH_LIBRARIES} pthread ${LIB_NAME-SEQ}  stdc++fs)

add_test(NAME CommonTest COMMAND ${EXE_NAME} ${TEST_SEED} ${TEST_ARR_SIZE}  --gtest_filter=COMMON.*)