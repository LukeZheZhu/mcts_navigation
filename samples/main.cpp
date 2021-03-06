#include <iostream>

#include <mcts_defs.hpp>
#include <mcts.hpp>



int main() {
    mcts::CMap* map = new mcts::CMap();
    map->setStart(START_X, START_Y);
    map->setTerminal(TERMINAL_X, TERMINAL_Y);

    mcts::CNode* root = new mcts::CNode();
    root->setPosition(START_X, START_Y);

    mcts::CNode* node = root;
    mcts::CMcts cmcts;
    int budget = MCTS_BUDGET;
//    while((budget != 0) && (!(node->isTerminal()))) {
//        std::cout << "Budget: " << budget << std::endl;
//        --budget;
    int count = 0;
    while(!(node->isTerminal())) {
        std::cout << "Budget: " << count << std::endl;
        ++count;
        mcts::CNode* tempNode;

        tempNode = cmcts.treePolicy(node, map);

        if(tempNode != NULL) {
            float reward = cmcts.defaultPolicy(tempNode, map);
            std::cout << "reward: " << reward << std::endl;

            cmcts.backUp(tempNode, reward);

            //            node = cmcts.bestChild(node);
            std::cout << "node.address: " << node << std::endl;

        }
    }
    std::cout << "arrived" << std::endl;


    while(node != NULL) {
        std::cout << "plan: " << node->m_position.x << ", " << node->m_position.y << std::endl;
        node = node->m_parent;
    }

    return 1;
}
