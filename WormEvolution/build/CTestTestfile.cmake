# CMake generated Testfile for 
# Source directory: /Users/kbladin/Documents/C++projects/git_projects/creature_evolution/EvolutionHelloWorld
# Build directory: /Users/kbladin/Documents/C++projects/git_projects/creature_evolution/EvolutionHelloWorld/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(that-test-I-made "/Users/kbladin/Documents/C++projects/git_projects/creature_evolution/EvolutionHelloWorld/build/runUnitTests")
ADD_TEST(that-other-test-I-made "runUnitTests")
SUBDIRS(lib/gtest-1.7.0)
