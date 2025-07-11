test_case(serialization serialization)

add_custom_command(TARGET serialization
        POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E
        copy_directory
        ${PROJECT_SOURCE_DIR}/resources/xmls
        ${EXECUTABLE_OUTPUT_PATH}
)
