# CMake generated Testfile for 
# Source directory: /Users/kbladin/Documents/C++projects/git_projects/creature_evolution
# Build directory: /Users/kbladin/Documents/C++projects/git_projects/creature_evolution/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
IF("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  ADD_TEST(that-test-I-made "/Users/kbladin/Documents/C++projects/git_projects/creature_evolution/build/Debug/runUnitTests")
ELSEIF("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  ADD_TEST(that-test-I-made "/Users/kbladin/Documents/C++projects/git_projects/creature_evolution/build/Release/runUnitTests")
ELSEIF("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  ADD_TEST(that-test-I-made "/Users/kbladin/Documents/C++projects/git_projects/creature_evolution/build/MinSizeRel/runUnitTests")
ELSEIF("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  ADD_TEST(that-test-I-made "/Users/kbladin/Documents/C++projects/git_projects/creature_evolution/build/RelWithDebInfo/runUnitTests")
ELSE()
  ADD_TEST(that-test-I-made NOT_AVAILABLE)
ENDIF()
ADD_TEST(that-other-test-I-made "runUnitTests")
SUBDIRS(src)
SUBDIRS(external_libs/gtest-1.7.0)
