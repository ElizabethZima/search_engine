cmake_minimum_required(VERSION 3.24)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(search_engine main.cpp
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp)

include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


set(JSON_BuildTests OFF CACHE INTERNAL "") #JSON
add_subdirectory(nlohmann_json) #JSON
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json) #JSON



