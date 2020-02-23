#ifndef MCTS_HPP
#define MCTS_HPP

#include <iostream>

#include "mcts_defs.hpp"

namespace nsMcts {
    class cMcts {
    public:
        int m_index;
        std::vector<struct SCoordinate> m_move =
            std::vector<struct SCoordinate>(8);

    public:
        CMcts();
        CMcts(CNode* node);

        std::shared_ptr<cNode>  treePolicy(std::shared_ptr<cNode> &node,
                                           cMap* &map);
        float defaultPolicy(CNode* &node, CMap* &map);

        std::shared_ptr<cNode> nodeExpand(std::shared_ptr<cNode> &node,
                                          nsModel::cModel model,
                                          cMap* &map, int &index);
        CNode* bestChild(CNode* node);
        void backUp(CNode* &node, float reward);
    };
} //namespace nsMcts

#endif //MCTS_HPP
