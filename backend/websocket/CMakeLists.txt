add_library(websocket
	websocket.cpp
)

target_link_libraries(websocket ${Boost_LIBRARIES})
target_link_libraries(websocket pthread)
