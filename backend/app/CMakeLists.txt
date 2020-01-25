add_executable(life-calculator
	main.cpp
)

target_link_libraries(life-calculator ${Boost_LIBRARIES})
target_link_libraries(life-calculator pthread)
