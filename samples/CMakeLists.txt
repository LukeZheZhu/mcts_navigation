list( APPEND include_path
  ${PROJECT_SOURCE_DIR}/mcts/include
  ${PROJECT_SOURCE_DIR}/map/include
  ${PROJECT_SOURCE_DIR}/model)

include_directories(${include_path})

add_executable(main main.cpp)

target_link_libraries(main mcts map)
