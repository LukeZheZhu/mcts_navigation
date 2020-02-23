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

    std::shared_ptr<cNode> cMcts::nodeExpand(std::shared_ptr<cNdoe> node,
                                             nsModel::cModel &model,
                                             nsMap::cMap &map,
                                             int &index) {
        float x = 0.0;
        float y = 0.0;
        float yaw = 0.0;

        while(!(node->isAllExpanded())) {
            index = index % DIRECTION_NUM;
            struct nsModel::modelPose tmpMove = model.calcMove(index);
            x = node->pose.position.x + tmpMove.position.x;
            y = node->pose.position.y + tmpMove.position.y;
            yaw = node->pose.rotation.yaw + tmpMove.rotation.yaw;
            node->m_status[index] = true;

            //        std::cout << "xx: " << x << ", yy: " << y << std::endl;

            if(node->m_parent) {
                if((node->m_parent->m_pose.position.x == x) &&
                   (node->m_parent->m_pose.position.y == y)) {
                    ++index;
                    continue;
                }
            } //This part should not be triggered, as model only have five direction and no backward

            float tmpRadius = model.getRadius();
            if(map->isLegal(x, y, tmpRadius)) {
                std::shared_ptr<cNode> subNode = std::make_shared<cNode>();
                subNode->setPose(x, y, yaw);
                subNode->setParent(node);
                node->addChild(subNode);

                return subNode;

            } else {
                ++index;
                continue;
            }
        }

        return nullptr;

    }

    std::shared_ptr<cNode> cMcts::treePolicy(std::shared_ptr<cNode> &node,
                                             nsModel::cModel &model,
                                             nsMap::cMap &map) {

        float tmpX = node->m_pose.position.x - float(TERMINAL_X);
        float tmpY = node->m_pose.position.y - float(TERMINAL_Y);
        if((std::abs(tempX) <= 1.0) && (std::abs(tempY) <= 1.0)) {
            std::shared_ptr<cNode> final = std::make_shared<cNode>();
            final->setPose(float(TERMINAL_X), float(TERMINAL_Y),
                           node.rotation.yaw);
            final->setParent(node);
            node->addChild(final);
            node = final;
        }

        while(!(node->isTerminal())) {
            if(node->isAllExpanded()) {
                m_index = 0;
                node = bestChild(node);
            } else {
                m_index = m_index % DIRECTION_NUM;
                std::shared_ptr<cNode> tmpNode = nodeExpand(node, model,
                                                            m_index);
                if(tmpNode) {
                    ++m_index;
                    return tmpNode;
                } else {
                    return nullptr;
                }
            }
        }

        return nullptr;
    }

    float cMcts::defaultPolicy(std::shared_ptr<cNode> &node,
                               nsModel::cModel &model,
                               std::shared_ptr<nsMap::cMap> &map) {
        std::shared_ptr<cNode> tmpNode(new cNode(*node));

        int cout = 0;
        float reward = 0.0;
        std::srand((unsigned)std::time(NULL));
        while(true) {
            ++count;
            int tmpIndex = std::rand() % DIRECTION_NUM;
            tmpNode = nodeExpand(tmpNode, model, map);

            float tmpX = tmpNode->m_pose.position.x - float(TERMINAL_X);
            float tmpY = tmpNode->m_pose.position.y - float(TERMINAL_Y);
            if((std::abs(tempX) <= 1.0) && (std::abs(tempY) <= 1.0)) {
                std::shared_ptr<cNode> final = std::make_shared<cNode>();
                final->setPose(float(TERMINAL_X), float(TERMINAL_Y),
                               tmpNode.);
                final->setParent(tmpNode);
                tmpNode->addChild(final);
                tmpNode = final;
            }
            if(tmpNode->isTerminal()) {
                return (1.0 / float(count));
            }
        }
        return 0.0;

#if 0
        CNode* tempNode = new CNode();
        *tempNode = *node;
        std::srand((unsigned)std::time(NULL));
//        for(int i = 0; i <= ROLLOUT_BUDGET; ++i) {
        int count = 0;
        while(1) {
            ++count;
            int tempIndex = std::rand() % 8;
//            std::cout << "randomValue " << std::rand() << std::endl;
//            std::cout << "randomIndex: " << tempIndex << std::endl;
            tempNode = nodeExpand(tempNode, map, tempIndex);
            int tempX = tempNode->m_position.x - TERMINAL_X;
            int tempY = tempNode->m_position.y - TERMINAL_Y;
            if((-1 <= tempX) && (tempX <=1) && (-1 <= tempY) && (tempY <= 1)) {
                CNode* final = new CNode();
                final->setPosition(TERMINAL_X, TERMINAL_Y);
                final->setParent(tempNode);
                tempNode->addChild(final);
                tempNode = final;
            }

            if(tempNode->isTerminal()) {

                return (1.0 / float(count));
            }

        }
        return 0.0;
#endif
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
