set(TEST_RUNNER_NAME "test${PROJECT_NAME}.exe")
set(TEST_RUNNER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test/${TEST_RUNNER_NAME})

if(UNIX)
	set(TEST_RUNNER_PATH "wine ${TEST_RUNNER_PATH}")
endif(UNIX)

include (CTest)
enable_testing()

add_test(
        NAME ${TEST_RUNNER_NAME}
        COMMAND ${TEST_RUNNER_PATH} ${PROJECT_NAME}
)

set_tests_properties(${TEST_RUNNER_NAME} PROPERTIES DEPENDS ${PROJECT_NAME})
