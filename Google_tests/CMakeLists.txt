project(Google_tests)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#add_subdirectory(lib)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR} ../SP0256-AL2-Lexicon)

# adding the Google_Tests_run target
add_executable(Google_Tests_run NumberExpansionTests.cpp AcronymExpansionTests.cpp ../SP0256-AL2-Lexicon/NumberExpander.cpp ../SP0256-AL2-Lexicon/AcronymExpander.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
#target_link_libraries(Google_Tests_run DateConverter_lib)

target_link_libraries(Google_Tests_run gtest ${CONAN_LIBS})