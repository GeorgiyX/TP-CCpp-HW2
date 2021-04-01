set(STRESS_EXE_NAME ${PROJECT_NAME}-STRESS)

include_directories(include)

add_executable(${STRESS_EXE_NAME}-ST src/main.c)
target_link_libraries(${STRESS_EXE_NAME}-ST ${LIB_NAME}-ST)

add_executable(${STRESS_EXE_NAME}-MT src/main.c)
#target_link_libraries(${STRESS_EXE_NAME}-MT ${LIB_NAME}-MT)