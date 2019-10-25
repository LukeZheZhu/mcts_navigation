set (include_path "${PROJECT_SOURCE_DIR}/include")

include_directories(${include_path})
add_library(libmctsNavigation mcts.cpp)
