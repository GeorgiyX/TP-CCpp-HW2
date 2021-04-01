set(LIB_NAME ${PROJECT_NAME}-LIB)

set(HW_SRC include/check_sum.h
           src/check_sum.c)

include_directories(include)
add_library(${LIB_NAME}-ST STATIC ${HW_SRC})
add_library(${LIB_NAME}-MT SHARED ${HW_SRC})