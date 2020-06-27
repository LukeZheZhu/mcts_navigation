find_package(OpenCV REQUIRED)

list( APPEND display_include_path
  ${PROJECT_SOURCE_DIR}/display/include
  ${PROJECT_SOURCE_DIR}/map/include
  ${OpenCV_INCLUDE_DIRS})

set (display_src_path "${PROJECT_SOURCE_DIR}/display/src/display.cpp")



include_directories(${display_include_path})
add_library(display SHARED ${display_src_path})
target_link_libraries(display ${OpenCV_LIBS})
