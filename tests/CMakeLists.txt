macro(TEST_CASE DIR NAME)
    add_executable(${NAME} ${NAME}.cc)

    add_test(NAME ${NAME} COMMAND ${NAME})

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output/tests/${DIR})

    set_tests_properties(${NAME}
            PROPERTIES
            WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}"
    )

    message(STATUS "added test [${NAME}] to ${EXECUTABLE_OUTPUT_PATH}")
endmacro(TEST_CASE)

add_subdirectory(simple_type)
add_subdirectory(complex_type)
add_subdirectory(serialization)
