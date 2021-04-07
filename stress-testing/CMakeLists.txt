set(STRESS_EXE_NAME_SEQ ${PROJECT_NAME}-STRESS-SEQ)
set(STRESS_EXE_NAME_PAR ${PROJECT_NAME}-STRESS-PAR)
set(HW_STRESS_SRC src/main.c include/utils.h src/utils.c)

include_directories(include ../project/include)

add_executable(${STRESS_EXE_NAME_SEQ} ${HW_STRESS_SRC})
target_link_libraries(${STRESS_EXE_NAME_SEQ} ${LIB_NAME_SEQ})
message("lib name:" ${LIB_NAME_SEQ})

add_executable(${STRESS_EXE_NAME_PAR} ${HW_STRESS_SRC} src/main.c src/lib_loader.c include/lib_loader.h)
target_compile_definitions(${STRESS_EXE_NAME_PAR} PUBLIC DYNAMIC)
target_link_libraries(${STRESS_EXE_NAME_PAR} dl)
