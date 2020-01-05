add_executable(test_life
	tests/main.cpp
	tests/board.cpp
)

linkTestLibraries(test_life)

add_test(
	NAME Life
	COMMAND test_life
)
