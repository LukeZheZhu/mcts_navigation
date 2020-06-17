#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

#include "mcts.hpp"

namespace nsMcts {
    cMcts::cMcts() :
        m_index(0) {
    }

    cMcts::cMcts(std::shared_ptr<cNode> node) :
        m_index(0) {
    }

    std::shared_ptr<cNode> cMcts::nodeExpand(std::shared_ptr<cNode> &node,
                                             nsModel::cTmpModelCar &model,
                                             nsMap::cMap &map,
                                             int index, bool isSimulation) {
        if(isSimulation)
            std::cout << "DefaultPolicyCall, inSimulation" << std::endl;
        else
            std::cout << "TreePolicyCall, inTreePolicy" << std::endl;

        float x = 0.0;
        float y = 0.0;
        float yaw = 0.0;

        int nodeIndex = index;

        while(!(node->isAllExpanded())) {
            if(nodeIndex >= node->m_childStatus.size())
                break;

            if(node->m_childStatus[nodeIndex].isVisited) {
                ++nodeIndex;
                nodeIndex = nodeIndex % DIRECTION_NUM;
                continue;
            }

            std::cout << "Yaw is: " << node->m_pose.rotation.yaw << std::endl;
            struct nsModel::sModelPose tmpMove = model.calcMove(node->m_pose.rotation.yaw,
                                                                nodeIndex);
            x = node->m_pose.position.x + tmpMove.position.x;
            y = node->m_pose.position.y + tmpMove.position.y;
            std::cout << "nodeIndex: " << nodeIndex << std::endl;
            std::cout << "x : " << x << ", y: " << y << std::endl;

            //Need to fix
            yaw = tmpMove.rotation.yaw;
            node->m_childStatus[nodeIndex].isVisited = true;

            float tmpRadius = model.getRadius();
            if(map.isLegal(x, y, tmpRadius)) {
                std::shared_ptr<cNode> subNode = std::make_shared<cNode>();
                subNode->setPose(x, y, yaw);
                subNode->setParent(node);
                node->addChild(subNode);
                node->m_childStatus[nodeIndex].isCreated = true;

                return subNode;
            } else {
                ++nodeIndex;
                nodeIndex = nodeIndex % DIRECTION_NUM;
                continue;
            }

        }

        return nullptr;

    }



    std::shared_ptr<cNode> cMcts::treePolicy(std::shared_ptr<cNode> &node,
                                             nsModel::cTmpModelCar &model,
                                             nsMap::cMap &map) {
        std::cout << " In TreePolicy Function" << std::endl;
        float tmpX = node->m_pose.position.x - float(TERMINAL_X);
        float tmpY = node->m_pose.position.y - float(TERMINAL_Y);
        if((std::abs(tmpX) <= 1.0) && (std::abs(tmpY) <= 1.0)) {
            std::shared_ptr<cNode> final = std::make_shared<cNode>();
            final->setPose(float(TERMINAL_X), float(TERMINAL_Y),
                           node->m_pose.rotation.yaw);
            final->setParent(node);
            node->addChild(final);
            node = final;
            return final;
        }

        while(!(node->isTerminal())) {
            if(node->isAllExpanded()) {
                node = bestChild(node);
                std::cout << "BestNode x: " << node->m_pose.position.x << std::endl;
                std::cout << "BestNode y: " << node->m_pose.position.y << std::endl;
                std::cout << "BestNode yaw: " << node->m_pose.rotation.yaw << std::endl;
//                break;
            } else {
                std::shared_ptr<cNode> tmpNode = nodeExpand(node, model, map);

                if(tmpNode) {
                    std::cout << "TreePolicy x: " << tmpNode->m_pose.position.x << std::endl;
                    std::cout << "TreePolicy y: " << tmpNode->m_pose.position.y << std::endl;
                    std::cout << "TreePolicy yaw: " << tmpNode->m_pose.rotation.yaw << std::endl;
                    return tmpNode;
                } else {
                    return nullptr;
                }
            }
        }

        return nullptr;
    }

    float cMcts::defaultPolicy(std::shared_ptr<cNode> &node,
                               nsModel::cTmpModelCar &model,
                               nsMap::cMap &map) {
        std::cout << "In DefaultPolicy function " << std::endl;
        std::shared_ptr<cNode> simNode(new cNode(*node));
        std::shared_ptr<cNode> tmpNode(simNode);

        int count = 0;
        float reward = 0.0;
        std::srand((unsigned)std::time(NULL));
        while(true) {
            ++count;
            std::cout << "Count is : "<< count << std::endl;
            int tmpIndex = std::rand() % DIRECTION_NUM;
            tmpNode = nodeExpand(tmpNode, model, map, tmpIndex, true);
            if((tmpNode == nullptr)) {
                return 0.0;
            }

                std::cout << "DefaultPolicy x: " << tmpNode->m_pose.position.x << std::endl;
                std::cout << "DefaultPolicy y: " << tmpNode->m_pose.position.y << std::endl;
                std::cout << "DefaultPolicy yaw: " << tmpNode->m_pose.rotation.yaw << std::endl;
            float tmpX = tmpNode->m_pose.position.x - float(TERMINAL_X);
            float tmpY = tmpNode->m_pose.position.y - float(TERMINAL_Y);
            if((std::abs(tmpX) <= 1.0) && (std::abs(tmpY) <= 1.0)) {
                std::shared_ptr<cNode> final = std::make_shared<cNode>();
                final->setPose(float(TERMINAL_X), float(TERMINAL_Y),
                               tmpNode->m_pose.rotation.yaw);
                final->setParent(tmpNode);
                tmpNode->addChild(final);
                tmpNode = final;
            }
            if(tmpNode->isTerminal()) {
                return (1.0 / float(count));
            }
        }
        return 0.0;

    }

    void cMcts::backUp(std::shared_ptr<cNode> &node, float reward) {
        while(node != NULL) {
            ++(node->m_visited);
            node->m_rewarded += reward;
            node = node->m_parent;
        }
    }

    std::shared_ptr<cNode> cMcts::bestChild(std::shared_ptr<cNode> &node) {
        float best = 0.0;
        float cp = 1.414;
        std::shared_ptr<cNode> tmpNode;
        for(int i = 0; i < node->m_children.size(); ++i) {
            float part1 = node->m_children[i]->m_rewarded /
                          node->m_children[i]->m_visited;
            float part2 = cp * sqrt(2 * log(node->m_visited) /
                                    node->m_children[i]->m_visited);
            float sum = part1 + part2;
            std::cout << "part1: " << part1 << ", part2: " << part2 << ", sum: " << sum << std::endl;
            if(sum > best) {
                std::cout << "sum: " << sum << ", i: " << i << std::endl;
                best = sum;
                tmpNode = node->m_children[i];
                node->m_child = node->m_children[i];
            }
        }
        if(!tmpNode) {
            tmpNode = node->m_children[0];
            node->m_child = node->m_children[0];
        }
        return tmpNode;

#if 0
        CNode* tempNode = NULL;
        for(int i = 0; i < node->m_children.size(); ++i) {
            float part1 = node->m_children[i]->m_rewarded /
                          node->m_children[i]->m_visited;
            float part2 = cp * sqrt(2 * log(node->m_visited) /
                                    node->m_children[i]->m_visited);
            float sum = part1 + part2;
            std::cout << "part1: " << part1 << ", part2: " << part2 << ", sum: " << sum << std::endl;
            if(sum > best) {
                std::cout << "sum: " << sum << ", i: " << i << std::endl;
                best = sum;
                tempNode = node->m_children[i];
                node->m_child = node->m_children[i];
            }
        }
        return tempNode;
#endif
    }
} //namespace mcts
