add_library(expression
	expression.cpp
	parser.cpp
)

target_link_libraries(expression life)

add_executable(test_expression
	tests/expression.cpp
	tests/parser.cpp
)

target_link_libraries(test_expression expression)
linkTestLibraries(test_expression)

add_test(
	NAME Expression
	COMMAND test_expression
)
