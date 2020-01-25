add_library(life
	board.cpp
	create.cpp
	rle.cpp
	types.cpp
)

add_executable(test_life
	tests/board.cpp
	tests/create.cpp
	tests/main.cpp
	tests/rle.cpp
	tests/types.cpp
)

target_link_libraries(test_life life)
linkTestLibraries(test_life)

add_test(
	NAME Life
	COMMAND test_life
)
