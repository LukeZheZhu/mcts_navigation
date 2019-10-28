set (include_path "${PROJECT_SOURCE_DIR}/include")

include_directories(${include_path})
add_library(mctsNavigation SHARED mcts.cpp)
