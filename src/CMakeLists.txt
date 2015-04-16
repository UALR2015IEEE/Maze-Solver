set(TARGET_NAME Maze-Solver)

set(SRC_FILES main.cpp sensor.cpp ard-comm.cpp solver.cpp)

add_executable(${TARGET_NAME} ${SRC_FILES})
target_include_directories(${TARGET_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include")
