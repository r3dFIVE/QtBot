# CMake generated Testfile for 
# Source directory: C:/workspace/QtBot/vendor/spdlog-1.x/tests
# Build directory: C:/workspace/QtBot/vendor/spdlog-1.x/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(spdlog-utests "C:/workspace/QtBot/vendor/spdlog-1.x/tests/Debug/spdlog-utests.exe")
  set_tests_properties(spdlog-utests PROPERTIES  _BACKTRACE_TRIPLES "C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;49;add_test;C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;54;spdlog_prepare_test;C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(spdlog-utests "C:/workspace/QtBot/vendor/spdlog-1.x/tests/Release/spdlog-utests.exe")
  set_tests_properties(spdlog-utests PROPERTIES  _BACKTRACE_TRIPLES "C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;49;add_test;C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;54;spdlog_prepare_test;C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(spdlog-utests "C:/workspace/QtBot/vendor/spdlog-1.x/tests/MinSizeRel/spdlog-utests.exe")
  set_tests_properties(spdlog-utests PROPERTIES  _BACKTRACE_TRIPLES "C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;49;add_test;C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;54;spdlog_prepare_test;C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(spdlog-utests "C:/workspace/QtBot/vendor/spdlog-1.x/tests/RelWithDebInfo/spdlog-utests.exe")
  set_tests_properties(spdlog-utests PROPERTIES  _BACKTRACE_TRIPLES "C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;49;add_test;C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;54;spdlog_prepare_test;C:/workspace/QtBot/vendor/spdlog-1.x/tests/CMakeLists.txt;0;")
else()
  add_test(spdlog-utests NOT_AVAILABLE)
endif()
