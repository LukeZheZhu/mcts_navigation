#include <iostream>
#include <thread>

#include <mcts_defs.hpp>
#include <mcts.hpp>

#include <model.hpp>
#include <map.hpp>
#include "display.hpp"


int main() {
    nsMap::cMap map = nsMap::cMap(START_X, START_Y, TERMINAL_X, TERMINAL_Y);
//    map.setMapGrid(2, 1, nsMap::eProperty::OBSTACLE);

    nsDisplay::cDisplay display = nsDisplay::cDisplay();
    display.drawGrid(display.m_mat, START_X, START_Y, 100, 0, 0);
    display.drawGrid(display.m_mat, TERMINAL_X, TERMINAL_Y, 0, 0, 100);
    cv::namedWindow("MCTS", cv::WINDOW_AUTOSIZE);
    cv::imshow("MCTS", display.m_mat);
    cv::waitKey(1);
//    nsModel::cModel car (std::shared_ptr<nsModel::cModelCar>());
    nsModel::cTmpModelCar car(0.0, 0.0);

    std::shared_ptr<nsMcts::cNode> root = std::make_shared<nsMcts::cNode>(map);
    std::shared_ptr<nsMcts::cMcts> mcts = std::make_shared<nsMcts::cMcts>();
    std::shared_ptr<nsMcts::cNode> node(root);
    root->setPose(START_X, START_Y, 0);

    int count = 0;


#if 0
    int budget = MCTS_BUDGET;

    while(!(node->isTerminal()) && (budget != 0)) {
#else
    while(!(node->isTerminal())) {
        std::cout << "Budget: " << count << std::endl;
        ++count;
        std::shared_ptr<nsMcts::cNode> tmpNode(node);
        tmpNode = mcts->treePolicy(node, car, map, display);
        if(tmpNode && (!(node->isTerminal()))) {
            float reward = mcts->defaultPolicy(tmpNode, car, map);
            std::cout << "reward: " << reward << std::endl;

            mcts->backUp(tmpNode, reward);
            //            std::cout << "node.address: " << node << std::endl;
        }
#endif
    }
    std::cout << "arrived" << std::endl;
    std::shared_ptr<nsMcts::cNode> tmpNode(root);
    while(tmpNode) {
        std::cout << "Plan: " <<
            tmpNode->m_pose.position.x << ", " <<
            tmpNode->m_pose.position.y << ", " <<
            tmpNode->m_pose.rotation.yaw << std::endl;

        if(!(tmpNode->m_child)) {
            display.drawArrow(display.m_mat,
                              tmpNode->m_pose.position.x,
                              tmpNode->m_pose.position.y,
                              TERMINAL_X,
                              TERMINAL_Y,
                              0, 0, 0);
            cv::imshow("MCTS", display.m_mat);
            cv::waitKey(1);
        }
        tmpNode = tmpNode->m_child;
    }
    cv::waitKey(0);

#if 0
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
#endif


    return 1;
}
