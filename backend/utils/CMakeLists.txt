add_library(utils
	parser.cpp
)

add_executable(test_utils
	tests/parser.cpp
)

target_link_libraries(test_utils utils)
linkTestLibraries(test_utils)

add_test(
	NAME Utils
	COMMAND test_utils
)
