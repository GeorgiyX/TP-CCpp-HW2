set(LIB_NAME ${PROJECT_NAME}-LIB)

set(HW_SRC include/check_sum.h
           src/check_sum.c
           include/check_sum_private.h
           src/check_sum_private.c)

include_directories(include)
add_library(${LIB_NAME}-ST STATIC ${HW_SRC} src/check_sum_st.c)
add_library(${LIB_NAME}-MT SHARED ${HW_SRC} src/check_sum_mt.c)