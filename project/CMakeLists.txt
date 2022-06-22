set(HW_SRC include/check_sum.h
           src/check_sum.c
           include/check_sum_private.h
           src/check_sum_private.c)

include_directories(include)
add_library(${LIB_NAME_SEQ} STATIC ${HW_SRC} src/check_sum_seq.c)
add_library(${LIB_NAME_PAR} SHARED ${HW_SRC} src/check_sum_par.c)