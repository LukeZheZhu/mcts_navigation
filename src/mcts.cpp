#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

#include "mcts.hpp"

namespace mcts {
    CMap::CMap() :
        m_map(MAP_HEIGHT, std::vector<CGrid*>(MAP_WIDTH))
    {
        for(int i = 0; i < MAP_HEIGHT; ++i) {
            for(int j = 0; j <MAP_WIDTH; ++j) {
                m_map[i][j] = new CGrid();
                m_map[i][j]->setGridLocation(j, i);
                m_map[i][j]->setGridRewarded(0);
                m_map[i][j]->setGridVisited(0);
                m_map[i][j]->setGridProperty(EProperty::AVAILABLE);
            }
        }
        m_start.x = 0;
        m_start.y = 0;
        m_terminal.x = 0;
        m_terminal.y = 0;
    }

    bool CMap::setStart(int x, int y) {
        m_map[y][x]->setGridProperty(EProperty::START);
        m_start.x = x;
        m_start.y = y;
        return true;
    }

    bool CMap::setTerminal(int x, int y) {
        m_map[y][x]->setGridProperty(EProperty::TERMINAL);
        m_terminal.x = x;
        m_terminal.y = y;
        return true;
    }

    struct SCoordinate CMap::getStart() {
        return m_start;
    }

    struct SCoordinate CMap::getTerminal() {
        return m_terminal;
    }

    bool CMap::isLegal(int x, int y) {
        if((0 <= x) && (x < MAP_WIDTH) && (0 <= y) &&(y < MAP_HEIGHT)) {
            return true;
        } else {
            return false;
        }
    }

    bool CMap::isEnd() {
        if (m_map[m_terminal.y][m_terminal.x]->getGridProperty() != EProperty::ARRIVED)
            return false;
        else
            return true;
    }


    CMcts::CMcts() : m_index(0) {
        m_move[0].x = -1; m_move[0].y =  0;
        m_move[1].x = -1; m_move[1].y =  1;
        m_move[2].x =  0; m_move[2].y =  1;
        m_move[3].x =  1; m_move[3].y =  1;
        m_move[4].x =  1; m_move[4].y =  0;
        m_move[5].x =  1; m_move[5].y = -1;
        m_move[6].x =  0; m_move[6].y = -1;
        m_move[7].x = -1; m_move[7].y = -1;
    }

    CMcts::CMcts(CNode* node) {
    }

    CNode* CMcts::nodeExpand(CNode* &node, CMap* &map, int &index) {
        int x = 0;
        int y = 0;

        while(!(node->isAllExpanded())) {
            index = index % 8;
            node->m_count[index] = true;
            x = node->m_position.x + m_move[index].x;
            y = node->m_position.y + m_move[index].y;
            //        std::cout << "xx: " << x << ", yy: " << y << std::endl;
            if(node->m_parent != NULL) {
                if((node->m_parent->m_position.x == x) &&
                   (node->m_parent->m_position.y == y)) {
                    ++index;
                    continue;
                }
            }

            if((map->isLegal(x, y)) &&
               (map->m_map[y][x]->getGridProperty() == EProperty::AVAILABLE)) {
                break;
            } else {
                ++index;
                continue;
            }
        }

        CNode* sub_node = new CNode();
        std::cout << "index: " << index <<", x: " << x << ", y: " << y << std::endl;
        sub_node->setPosition(x, y);
        sub_node->setParent(node);
        node->addChild(sub_node);
        return sub_node;

    }

    CNode* CMcts::treePolicy(CNode* &node, CMap* &map) {
        int tempX = node->m_position.x - TERMINAL_X;
        int tempY = node->m_position.y - TERMINAL_Y;
        if((-1 <= tempX) && (tempX <=1) && (-1 <= tempY) && (tempY <= 1)) {
            CNode* final = new CNode();
            final->setPosition(TERMINAL_X, TERMINAL_Y);
            final->setParent(node);
            node->addChild(final);
            node = final;
        }

        while(!node->isTerminal()) {
            if(node->isAllExpanded()) {
                m_index = 0;
                node = bestChild(node);
            } else {
                m_index = m_index % 8;
                CNode* tempNode = nodeExpand(node, map, m_index);
                ++m_index;
                return tempNode;
            }
        }
        return NULL;
    }

    float CMcts::defaultPolicy(CNode* &node, CMap* &map) {
        float reward = 0.0;
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
    }

    void CMcts::backUp(CNode* &node, float reward) {
        while(node != NULL) {
            ++(node->m_visited);
            node->m_rewarded += reward;
            node = node->m_parent;
        }
    }

    CNode* CMcts::bestChild(CNode* node) {
        float best = 0.0;
        float cp = 1.414;
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
    }
} //namespace mcts
