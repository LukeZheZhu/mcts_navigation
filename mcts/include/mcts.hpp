#ifndef MCTS_HPP
#define MCTS_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

#include "mcts_defs.hpp"
#include "display.hpp"

namespace nsMcts {
    class cMcts {
    public:
        int m_index;

    public:
        cMcts();
        cMcts(std::shared_ptr<cNode> node);

        std::shared_ptr<cNode> treePolicy(std::shared_ptr<cNode> &node,
                                          nsModel::cTmpModelCar &model,
                                          nsMap::cMap &map,
                                          nsDisplay::cDisplay &display);
        std::shared_ptr<cNode> nodeExpand(std::shared_ptr<cNode> &node,
                                          nsModel::cTmpModelCar &model,
                                          nsMap::cMap &map, int index = 0,
                                          bool isSimulation = false);


        std::shared_ptr<cNode> bestChild(std::shared_ptr<cNode> &node);

        float defaultPolicy(std::shared_ptr<cNode> &node,
                            nsModel::cTmpModelCar &model,
                            nsMap::cMap &map);
        void backUp(std::shared_ptr<cNode> &node, float reward);
    }; // class cMcts

} //namespace nsMcts

#endif //MCTS_HPP
