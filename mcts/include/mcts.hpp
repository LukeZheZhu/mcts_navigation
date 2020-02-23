#ifndef MCTS_HPP
#define MCTS_HPP

#include <iostream>

#include "mcts_defs.hpp"

namespace nsMcts {
    class cMcts {
    public:
        int m_index;

    public:
        cMcts();
        cMcts(std::shared_ptr<cNode> node);

        std::shared_ptr<cNode> treePolicy(std::shared_ptr<cNode> &node,
                                          nsModel::cModel &model,
                                          nsMap::cMap &map);
        std::shared_ptr<cNode> nodeExpand(std::shared_ptr<cNode> &node,
                                          nsModel::cModel &model,
                                          int &index);


        std::shared_ptr<cNode> bestChild(std::shared_ptr<cNode> &node);

        float defaultPolicy(std::shared_ptr<cNode> &node,
                            nsModel::cModel &model,
                            std::shared_ptr<nsMap::cMap> &map);
        void backUp(std::shared_ptr<cNode> &node, float reward);
    }; // class cMcts

} //namespace nsMcts

#endif //MCTS_HPP
