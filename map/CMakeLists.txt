set (map_include_path "${PROJECT_SOURCE_DIR}/map/include")
set (map_src_path "${PROJECT_SOURCE_DIR}/map/src/map.cpp")

include_directories(${map_include_path})
add_library(map SHARED ${map_src_path})
