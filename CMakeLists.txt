cmake_minimum_required(VERSION 3.0.0)
project(temperaturecontrol VERSION 1.0.0)

#C++14 required by GoogleTest
set(CMAKE_CXX_STANDARD 14)

#Get GoogleTest. Based on the tutorial at https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



add_library(temperaturesensor TemperatureSensor.cpp)
add_library(acsystem ACSystem.cpp)
add_library(temperaturecontrol TemperatureControl.cpp)

add_executable(tests test_temperaturecontrol.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main temperaturecontrol)
