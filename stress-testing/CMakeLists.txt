set(STRESS_EXE_NAME ${PROJECT_NAME}-STRESS)
set(HW_STRESS_SRC src/main.c include/utils.h src/utils.c)

include_directories(include ../project/include)

add_executable(${STRESS_EXE_NAME}-ST ${HW_STRESS_SRC})
target_link_libraries(${STRESS_EXE_NAME}-ST ${LIB_NAME}-ST)

add_executable(${STRESS_EXE_NAME}-MT src/main.c src/lib_loader.c include/lib_loader.h)
target_link_libraries(${STRESS_EXE_NAME}-MT HW_STRESS_SRC)
target_compile_definitions(${STRESS_EXE_NAME}-MT PUBLIC DYNAMIC)