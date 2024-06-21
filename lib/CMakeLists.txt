cmake_minimum_required(VERSION 3.21)

project(ignosi-ecs)

set(CMAKE_CXX_STANDARD 20)
find_package(ignosi-memory CONFIG REQUIRED)
find_path(IGNOSI_MEMORY_INC "dll_allocate.h")

add_library(${PROJECT_NAME} STATIC "entity.cpp" "system.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}
                                                  ${IGNOSI_MEMORY_INC})
target_link_libraries(${PROJECT_NAME}
                      PUBLIC ignosi-memory::ignosi-memory-allocate)
