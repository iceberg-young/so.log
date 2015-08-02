add_subdirectory(import/datetime/source)
add_dependencies(${PROJECT_NAME} so.datetime)
target_link_libraries(${PROJECT_NAME} so.datetime)
