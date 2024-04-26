cmake_minimum_required(VERSION 3.27)
project(rest_api)

set(CMAKE_CXX_STANDARD 23)

add_executable(rest_api main.cpp
        CurrencyMoneyRate.cpp
        CurrencyMoneyRate.h)

include(FetchContent)

FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1ad1cd2daf138aefdcdb1c35d99608387d230ec1)
FetchContent_MakeAvailable(cpr)
target_link_libraries(rest_api PRIVATE cpr::cpr)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(rest_api PRIVATE nlohmann_json::nlohmann_json)

