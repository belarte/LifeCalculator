add_library(life
	types.cpp
	rle.cpp
	create.cpp)

add_executable(test_life
	tests/main.cpp
	tests/types.cpp
	tests/board.cpp
	tests/rle.cpp
)

target_link_libraries(test_life life)
linkTestLibraries(test_life)

add_test(
	NAME Life
	COMMAND test_life
)
