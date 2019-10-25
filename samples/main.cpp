#include <iostream>

#include <mcts.hpp>



int main() {
    mcts::CMap* map;
    map->setStart(START_X, START_Y);
    map->setTerminal(TERMINAL_X, TERMINAL_Y);

    mcts::CNode* root = new mcts::CNode();
    root->setPosition(START_X, START_Y);

    mcts::CNode* node = root;
    mcts::CMcts cmcts;
    int budget = MCTS_BUDGET;
    while((budget != 0) && (!(node->isTerminal()))) {
        --budget;
        node = cmcts.treePolicy(node, map); //This part has problem,need correct
        float reward = cmcts.defaultPolicy(node, map);
        cmcts.backUp(node, reward);
        node = cmcts.bestChild(node);
    }


    return 1;
}
