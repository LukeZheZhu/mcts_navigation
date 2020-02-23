#ifndef MCTS_DEFS_HPP
#define MCTS_DEFS_HPP

#include <iostream>
#include <vector>

#include "model.hpp"

#define MCTS_BUDGET 1000
#define ROLLOUT_BUDGET 500
#define DIRECTION_NUM 5

namespace nsMcts {
    struct sCoordinate {
        float x;
        float y;

        sCoordinate() :
            x(0.0),
            y(0.0) {
        };

        sCoordinate(float coordX, float coordY) :
            x(coordX),
            y(coordY) {
        };
    };



    class cNode {
    public:
        struct nsModel::sModelPose m_pose;
        float m_rewarded;
        int m_visited;
        std::vector<bool> m_status;

        std::shared_ptr<cNode> m_parent;
        std::shared_ptr<cNode> m_child;
        std::vector<std::shared_ptr<cNode>> m_children;

        nsMap::cMap m_map;

        cNode() :
            m_pose(),
            m_rewarded(0.0),
            m_visited(0),
            m_status(DIRECTION_NUM, false),
            m_parent(std::make_shared<cNode>()),
            m_child(std::make_shared<cNode>()),
            m_children(8, std::make_shared<cNode>()),
            m_map() {
        };

        cNode(const cNode &node) :
            m_pose(nodde.m_pose),
            m_rewarded(node.m_rewarded),
            m_visited(node.m_visited),
            m_status(node.m_status),
            m_parent(node.m_parent),
            m_child(node.m_child),
            m_children(node.m_children),
            m_map(node.m_map) {

        };

        cNode(nsMap::cMap &map) :
            m_position(),
            m_pose(),
            m_rewarded(0.0),
            m_visited(0),
            m_status(DIRECTION_NUM, false),
            m_parent(std::make_shared<cNode>()),
            m_child(std::make_shared<cNode>()),
            m_children(8, std::make_shared<cNode>()),
            m_map(map) {
        };

        bool setPose(float x, float y, float z = 0.0,
                     float yaw = 0.0, float roll = 0.0, float pitch = 0.0) {
            m_pose.position.x = x;
            m_pose.position.y = y;
            m_pose.position.z = z;
            m_pose.rotation.yaw = yaw;
            m_pose.rotation.roll = roll;
            m_pose.rotation.pitch = pitch;
            return true;
        };

        bool setParent(std::shared_ptr<cNode> parent) {
            if(parent) {
                m_parent = parent;
                return true;
            }
            return false;
        };

        bool addChild(std::share_ptr<cNdoe> child) {
            if(child) {
                m_children.push_back(child);
                return true;
            }
            return false;
        };

        bool isAllExpanded() {
            for(int i = 0; i < m_status.size(); ++i) {
                if(m_status[i] == false) {
                    return false;
                }
            }
            return true;
        };

        bool isTerminal() {
            if((m_pose.position.x == TERMINAL_X) &&
               (m_pose.position.y == TERMINAL_Y)) {
                return true;
            } else {
                return false;
            }
        };

        bool isLegal(float x, float y) {
            if ((x < 0.0) || (x >= float(MAP_WIDTH)) ||
                (y < 0.0) || (y >= float(MAP_HEIGHT))) {
                return false;
            }
        };

        bool detectObstacle(int x, int y, nsModel::cModel &model) {
            int tmpRadius = std::ceil(model.m_radius);
            for(int r = 1; r <= tmpRadius; ++r) {
            }
        };

    }; //class cNode

} //namespace nsMcts

#endif //MCTS_DEFS_HPP
