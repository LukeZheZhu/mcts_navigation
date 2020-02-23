#ifndef MCTS_HPP
#define MCTS_HPP

#include <iostream>

#include "mcts_defs.hpp"

namespace mcts {
    class CMap {
    public:
        std::vector<std::vector<CGrid*>> m_map;

        struct SCoordinate m_start;
        struct SCoordinate m_terminal;

    public:
        CMap();

        bool setStart(int x, int y);
        bool setTerminal(int x, int y);
        struct SCoordinate getStart();
        struct SCoordinate getTerminal();

        bool isLegal(int x, int y);
        bool isEnd();
    };

    class CMcts {
    public:
        int m_index;
        std::vector<struct SCoordinate> m_move =
            std::vector<struct SCoordinate>(8);

    public:
        CMcts();
        CMcts(CNode* node);

        CNode* treePolicy(CNode* &node, CMap* &map);
        float defaultPolicy(CNode* &node, CMap* &map);

        CNode* nodeExpand(CNode* &node, CMap* &map, int &index);
        CNode* bestChild(CNode* node);
        void backUp(CNode* &node, float reward);
    };
} //namespace mcts

#endif //MCTS_HPP
