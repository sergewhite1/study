message(STATUS "test-sso: CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")

message(STATUS "test-sso: before update: CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWHT_STRING_TESTING")

message(STATUS "test-sso: after  update: CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

add_executable(test-sso $<TARGET_OBJECTS:wht_string_lib>
	main.cpp
)

include_directories(test-sso
	${CMAKE_SOURCE_DIR}/src/sso
)

foreach(i RANGE 1 25)
	add_test(test-sso-${i} test-sso ${i})
endforeach(i)

