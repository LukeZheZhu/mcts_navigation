#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "mcts.hpp"

namespace mcts {
    CMap::CMap() {
        for(int i = 0; i < MAP_HEIGHT; ++i) {
            for(int j = 0; j <MAP_WIDTH; ++j) {
                m_map[i][j]->setGridLocation(i, j);
                m_map[i][j]->setGridRewarded(0);
                m_map[i][j]->setGridVisited(0);
                m_map[i][j]->setGridProperty(EProperty::AVAILABLE);
                m_start.x = 0;
                m_start.y = 0;
                m_terminal.x = 0;
                m_terminal.y = 0;
            }
        }
    }

    bool CMap::setStart(int x, int y) {
        m_map[y][x]->setGridProperty(CGrid::START);
        m_start.x = x;
        m_start.y = y;
        return true;
    }

    bool CMap::setTerminal(int x, int y) {
        m_map[y][x]->setGridProperty(CGrid::TERMINAL);
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

    bool CMap::isLegel(int x, int y) {
        if((0 <= x) && (x < MAP_WIDTH) && (0 <= y) &&(y < MAP_HEIGHT)) {
            return true;
        } else {
            return false;
        }
    }

    bool CMap::isEnd() {
        if (m_map[m_terminal.y][m_terminal.x]->m_property != CGrid::ARRIVED)
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

    CNode* CMcts::nodeExpand(CNode* node, CMap* &map, int &index) {
        int x;
        int y;

        while(node->m_count <= 8) {
            index = index % 8;
            ++(node->m_count);
            x = node->m_position.x + m_move[index].x;
            y = node->m_position.y + m_move[index].y;

            if(node->m_parent != NULL) {
                if((node->m_parent->m_position.x == x) &&
                   (node->m_parenr->m_position.y == y)) {
                    ++index;
                    ++(node->m_count);
                    continue;
                }
            }

            if(!(map->isLegal(x, y)) ||
               (map[y][x]->getProperty() == mctsMap::CGrid::OBSTACLE)) {
                ++index;
                ++(node->m_count);
                continue;
            }
        }

        CNode* sub_node;
        sub_node->setPosition(x, y);
        sub_node->setParent(node);
        node.addChild(sub_node);
        return sub_node;

    }

    CNode* CMcts::treePolicy(CNode* &node, CMap* &map) {
        while(!node.isTerminal) {
            if(node.isAllExpanded()) {
                m_index = 0;
                node = bestChild(node,true);
            } else {
                m_index = m_index % 8;
                CNode* tempNode = new CNode();
                tempNode = nodeExpand(node, map, m_index);
                ++m_index;
                return tempNode;
            }
        }
        return node;
    }

    float CMcts::defaultPolicy(CNode* node, CMap* &map) {
        float reward = 0.0;
        CNode* tempNode = node;
        for(int i = 0; i <= ROLLOUT_BUDGET; ++i) {
            int tempIndex = (std:srand((unsigned)time(NULL))) % 8;
            tempNode = nodeExpand(tempNode, map, tempIndex);

            if(tempNode.isTerminal()) {
                return (1.0 / float(i));
            }

        }
        return 0.0;
    }

    void CMcts::backUp(CNode* node, float reward) {
        while(node != NULL) {
            ++(node->m_visited);
            node->m_rewarded += m_rewarded;
            node = node->m_parent;
        }
    }

    CNode* CMcts::bestChild(CNode* node) {
        float best = 0.0;
        float cp = 1.414;
        CNode* tempNode = NULL;
        for(int i = 0; i < node->m_children.size(); ++i) {
            float part1 = node->m_children[i]->rewarded /
                          node->m_children[i]->m_visited;
            float part2 = cp * sqrt(2 * log(node->m_visited) /
                                    node->m_children[i]->m_visited);
            float sum = part1 + part2;

            if(sum > best) {
                best = sum;
                tempNode = node->m_children[i];
                node->m_child = node->m_children[i];
            }
        }
        return tempNode;
    }
} //namespace mcts
