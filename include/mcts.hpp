#ifndef MCTS_HPP
#define MCTS_HPP

#include <iostream>

#include "mcts_defs.hpp"

namespace mcts {
    class CMap {
    private:
        std::vector<std::vector<CGrid*> > m_map =
            std::vector<std::vector<CGrid*> > (MAP_HEIGHT,
                                               std::vector<CGrid*>(MAP_WIDTH));

        struct SCoordinate m_start;
        struct SCoordinate m_terminal;

    public:
        CMap();

        bool setStart(int x, int y);
        bool setTerminal(int x, int y);
        struct SCoordinate getStart();
        struct SCoordinate getTerminal();

        bool isLegel(int x, int y);
        bool isEnd();
    };

    class CMcts {
        int m_index;
        std::vector<struct SCoordinate> m_move =
            std::vector<struct SCoordinate>(8);

        CMcts();
        CMcts(CNode* node);

        CNode* treePolicy(CNode* &node);
        int defaultPolicy(CNode* node);

        CNode* nodeExpand(CNode* &node);
        CNode* bestChild();
        void backUp(CNode* node, float reward);
    };
} //namespace mcts

#endif //MCTS_HPP
