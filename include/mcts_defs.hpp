#ifndef MCTS_DEFS_HPP
#define MCTS_DEFS_HPP

#include <iostream>
#include <vector>

#define MCTS_BUDGET 1000
#define ROLLOUT_BUDGET 500

namespace nsMctss {
    struct sCoordinate {
        float x;
        float y;

        sCoordinate() :
            x(0),
            y(0) {
        };

        sCoordinate(float coordX, float coordY) :
            x(coordX),
            y(coordY) {
        };
    };



    class cNode {
    public:
        struct SCoordinate m_position;
        float m_rewarded;
        int m_visited;
        int m_status;
        std::vector<bool> m_count;

        std::shared_ptr<cNode> m_parent;
        std::shared_ptr<cNode> m_child;
        std::vector<std::shared_ptr<cNode>> m_children;

        cNode() :
            m_position(),
            m_rewarded(0.0),
            m_visited(0),
            m_status(0),
            m_count(8, false),
            m_parent(std::make_shared<cNode>()),
            m_child(std::make_shared<cNode>()),
            m_children(8, std::make_shared<cNode>()) {
        };

        bool setPosition(float x, float y) {
            m_position.x = x;
            m_position.y = y;
            return true;
        }

        bool setParent(std::shared_ptr<cNode> parent) {
            if(parent) {
                m_parent = parent;
                return true;
            }
            return false;
        }

        bool addChild(CNode* node) {
            if(node) {
                m_children.push_back(node);
                return true;
            }
            return false;
        }

        bool isAllExpanded() {
            for(int i = 0; i < m_count.size(); ++i) {
                if(m_count[i] == false) {
                    return false;
                }
            }
            return true;
        }

        bool isTerminal() {
            if((m_position.x == TERMINAL_X) &&
               (m_position.y == TERMINAL_Y)) {
                return true;
            } else {
                return false;
            }
        }

    };

} //namespace nsMcts

#endif //MCTS_DEFS_HPP
