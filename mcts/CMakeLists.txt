set (mcts_include_path "${PROJECT_SOURCE_DIR}/mcts/include")
set (mcts_src_path "${PROJECT_SOURCE_DIR}/mcts/src/mcts.cpp")

include_directories(${mcts_include_path})
add_library(mcts SHARED ${mcts_src_path})
