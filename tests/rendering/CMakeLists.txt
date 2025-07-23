set(NAME rendering)

add_executable(${NAME} ${NAME}.cc)

target_link_libraries(${NAME} PRIVATE unofficial::skia::skia)

add_test(NAME ${NAME} COMMAND ${NAME})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output/tests/${DIR})

set_tests_properties(${NAME}
        PROPERTIES
        WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}"
)

message(STATUS "Added test [${NAME}] to ${EXECUTABLE_OUTPUT_PATH}")

add_custom_command(TARGET ${NAME}
        POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E
        copy_directory
        ${PROJECT_SOURCE_DIR}/resources/xmls
        ${EXECUTABLE_OUTPUT_PATH}
)
