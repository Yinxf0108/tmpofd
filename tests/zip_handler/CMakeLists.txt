set(NAME zip_handler)

add_executable(${NAME} ${NAME}.cc)

target_link_libraries(${NAME} PRIVATE libzip::zip)

add_test(NAME ${NAME} COMMAND ${NAME})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output/tests/${NAME})

set_tests_properties(${NAME}
        PROPERTIES
        WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}"
)

message(STATUS "Added test [${NAME}] to ${EXECUTABLE_OUTPUT_PATH}")

add_custom_command(TARGET zip_handler
        POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E
        copy_directory
        ${PROJECT_SOURCE_DIR}/resources/ofds
        ${EXECUTABLE_OUTPUT_PATH}
)
