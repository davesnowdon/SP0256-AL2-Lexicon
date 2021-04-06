cmake_minimum_required(VERSION 3.17)
project(SP0256_AL2_Lexicon)

set(CMAKE_CXX_STANDARD 14)

include_directories(SP0256-AL2-Lexicon)

add_executable(SP0256_AL2_Lexicon SP0256-AL2-Lexicon/Source.cpp SP0256-AL2-Lexicon/Lexicon.cpp)