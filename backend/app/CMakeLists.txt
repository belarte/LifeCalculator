add_executable(life-calculator
	main.cpp
)

target_link_libraries(life-calculator
	expression
	websocket
)
