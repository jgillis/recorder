cmake_minimum_required (VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(Recorder)

add_library(recorder SHARED recorder.hpp recorder.cpp)
target_compile_definitions(recorder PRIVATE MAKEDLL)

add_executable(test test.cpp)
target_link_libraries(test recorder)

install(TARGETS test DESTINATION bin)
file(GLOB HEADERS *.hpp)
install(FILES ${HEADERS} DESTINATION include)
install(TARGETS recorder
	PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE 
				GROUP_READ GROUP_WRITE GROUP_EXECUTE 
				WORLD_READ WORLD_EXECUTE
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	)
