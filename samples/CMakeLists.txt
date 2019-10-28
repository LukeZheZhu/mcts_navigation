set (include_path "${PROJECT_SOURCE_DIR}/include")
include_directories(${include_path})

add_executable(main main.cpp)
target_link_libraries(main mctsNavigation)
