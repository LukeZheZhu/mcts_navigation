#include <iostream>
#include <cmath>

#include "map.hpp"

namespace nsMap {
    cMap::cMap() :
        m_map(MAP_HEIGHT, std::vector<cGrid>(MAP_WIDTH)),
        m_start(),
        m_terminal() {
        initMap();
    };

    cMap::cMap(int startX, int startY, int terminalX, int terminalY) :
        m_map(MAP_HEIGHT, std::vector<cGrid>(MAP_WIDTH)),
        m_start(startX, startY),
        m_terminal(terminalX, terminalY) {
        initMap();
    };

    cMap::cMap(const cMap& map) {
        m_map = map.m_map;
        m_start = map.m_start;
        m_terminal = map.m_terminal;
    };

    void cMap::initMap() {
        for(int i = 0; i < MAP_HEIGHT; ++i) {
            for(int j = 0; j <MAP_WIDTH; ++j) {
                m_map[i][j].setGridLocation(j, i);
                m_map[i][j].setGridVisited(0);
                m_map[i][j].setGridProperty(eProperty::AVAILABLE);
            }
        }
        m_map[m_start.y][m_start.x].setGridProperty(eProperty::START);
        m_map[m_terminal.y][m_terminal.x].setGridProperty(eProperty::TERMINAL);
    };

    bool cMap::setMapGrid(int x, int y, eProperty property) {
        m_map[y][x].setGridProperty(property);

        if(property == eProperty::START) {
            m_start.x = x;
            m_start.y = y;
        }

        if(property == eProperty::TERMINAL) {
            m_terminal.x = x;
            m_terminal.y = y;
        }

        return true;
    };

    sCoordination cMap::getStart() {
        return m_start;
    };

    sCoordination cMap::getTerminal() {
        return m_terminal;
    };

    bool cMap::isLegal(int x, int y) {
        if((0 <= x) && (x < MAP_WIDTH) && (0 <= y) &&(y < MAP_HEIGHT)) {
            return true;
        } else {
            return false;
        }
    };

    bool cMap::isLegal(float x, float y, float radius) {
        int xMin = std::floor(x - radius);
        int yMin = std::floor(y - radius);
        int xMax = std::ceil(x + radius);
        int yMax = std::ceil(y + radius);


        for(int j = yMin; j <= yMax; ++j) {
            for(int i = xMin; i <= xMax; ++ i) {
                if((x < 0) || (x >= MAP_WIDTH) ||
                   (y < 0) || (y >= MAP_HEIGHT)) {
                    return false;
                } else {
                    if(m_map[j][i].m_property != AVAILABLE) {
                        return false;
                    }
                }
            }
        }
        return true;
    };

    bool cMap::isEnd() {
        if (m_map[m_terminal.y][m_terminal.x].getGridProperty() != eProperty::ARRIVED)
            return false;
        else
            return true;
    };

} //namespace msMap
