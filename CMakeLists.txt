cmake_minimum_required(VERSION 3.30)
project(APIEXP)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
 #
# Fetch Google Test
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Fetch CPR
set(CPR_FORCE_USE_SYSTEM_CURL ON)
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.10.4
)

# Fetch nlohmann JSON
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)

# Enable testing
enable_testing()

# Make all dependencies available
FetchContent_MakeAvailable(googletest cpr json)

# Main app executable
add_executable(APIEXP
        main.cpp
        apiaccess.cpp
        apiaccess.h
        circularDeque.h
        MovingAvg.cpp
        MovingAvg.h
        data.h
        MemoryPool.cpp
)
target_link_libraries(APIEXP
        PRIVATE
        cpr::cpr
        nlohmann_json::nlohmann_json
)

# Test executable (separate)
add_executable(APIEXP_tests
        case_tester.cpp
)
target_link_libraries(APIEXP_tests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        cpr::cpr
        nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(APIEXP_tests)
