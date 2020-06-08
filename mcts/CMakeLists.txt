list( APPEND include_path
  ${PROJECT_SOURCE_DIR}/mcts/include
  ${PROJECT_SOURCE_DIR}/map/include
  ${PROJECT_SOURCE_DIR}/model)

set (mcts_src_path "${PROJECT_SOURCE_DIR}/mcts/src/mcts.cpp")


include_directories(${include_path})
add_library(mcts SHARED ${mcts_src_path})
#target_link_libraries(mcts map)
