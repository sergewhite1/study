message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")

add_executable(test-sso $<TARGET_OBJECTS:wht_string_lib>
	main.cpp
)

include_directories(test-sso
	${CMAKE_SOURCE_DIR}/src/sso
)

foreach(i RANGE 0)
	add_test(test-sso-${i} test-sso ${i})
endforeach(i)

