cmake_minimum_required(VERSION 3.26.4)
project(REST)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        REST
        main.cpp
        CurrencyMoneyRate.cpp
        CurrencyMoneyRate.h
)

include(FetchContent)

if (WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()


FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1ad1cd2daf138aefdcdb1c35d99608387d230ec1)
FetchContent_MakeAvailable(cpr)
target_link_libraries(REST PRIVATE cpr::cpr)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(REST PRIVATE nlohmann_json::nlohmann_json)

