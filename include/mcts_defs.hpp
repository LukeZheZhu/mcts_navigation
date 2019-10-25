#ifndef MCTS_DEFS_HPP
#define MCTS_DEFS_HPP

#include <iostream>
#include <vector>

#define MAP_HEIGHT 301
#define MAP_WIDTH  301

#define START_X 1
#define START_Y 1
#define TERMINAL_X 30
#define TERMINAL_Y 30

#define MCTS_BUDGET 1000
#define ROLLOUT_BUDGET 500

namespace mcts {
    struct SCoordinate {
        int x;
        int y;

        SCoordinate() {
            x = 0;
            y = 0;
        };
    };

    enum EProperty {
        AVAILABLE,
        OBSTACLE,
        HOTZONE,
        START,
        TERMINAL,
        ARRIVED
    };

    class CGrid {
    private:
        struct SCoordinate m_position;
        float m_rewarded;
        int m_visited;
        enum EProperty m_property;

    public:
        CGrid() {
            m_rewarded = 0.0;
            m_visited = 0;
            m_property = AVAILABLE;
        }

        bool setGridLocation(int x, int y) {
            m_position.x = x;
            m_position.y = y;
            return true;
        }

        bool setGridRewarded(float rewarded = 0.0) {
            m_rewarded = rewarded;
            return true;
        }

        bool setGridVisited(int visited = 0) {
            m_visited = visited;
            return true;
        }

        bool setGridProperty(EProperty property = AVAILABLE) {
            m_property = property;
            return true;
        }

        struct SCoordinate getGridLocation() {
            return m_position;
        }

        float getGridRewarded() {
            return m_rewarded;
        }

        int getGridVisited() {
            return m_visited;
        }

        EProperty getGridProperty() {
            return m_property;
        }
    };


    class CNode {
        struct SCoordinate m_position;
        float m_rewarded;
        int m_visited;
        int m_status;
        int m_count;

        CNode* m_parent;
        CNode* m_child;
        std::vector<CNode*> m_children;

        CNode() {
            m_rewarded = 0.0;
            m_visited = 0;
            m_status = 0;
            m_count = 0;
            m_parent = NULL;
            m_child = NULL;
        }

        bool setPosition(int x, int y) {
            m_position.x = x;
            m_position.y = y;
            return true;
        }

        bool setParent(CNode* parent) {
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
            if(m_count == 8) {
                return true;
            } else {
                return false;
            }
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
} //namespace mcts

#endif //MCTS_DEFS_HPP
