set(TEST_RUNNER_NAME "test${PROJECT_NAME}.exe")

if(UNIX)
	set(TEST_RUNNER_PATH wine ${CMAKE_CURRENT_SOURCE_DIR}/test/${TEST_RUNNER_NAME})
else()
	set(TEST_RUNNER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test/${TEST_RUNNER_NAME})
endif()

include (CTest)
enable_testing()

add_test(
        NAME ${TEST_RUNNER_NAME}
        COMMAND ${TEST_RUNNER_PATH} ${PROJECT_NAME}
)

set_tests_properties(${TEST_RUNNER_NAME} PROPERTIES DEPENDS ${PROJECT_NAME})
