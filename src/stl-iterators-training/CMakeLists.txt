message(STATUS "stl-iterators-demo: before update: CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS "")

message(STATUS "stl-iterators-demo: after  update: CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

project(stl-iterators-training)

add_executable(${PROJECT_NAME} 
  binder_demo.cpp
  binder_demo.h
  person.cpp
  person.h
  main.cpp
)
