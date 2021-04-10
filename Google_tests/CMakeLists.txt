project(Google_tests)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(Google_Tests_run NumberExpansionTests.cpp AcronymExpansionTests.cpp ../SP0256-AL2-Lexicon/NumberExpander.cpp ../SP0256-AL2-Lexicon/AcronymExpander.cpp)
target_link_libraries(Google_Tests_run gtest ${CONAN_LIBS})