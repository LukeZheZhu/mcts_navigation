#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

#define MAP_HEIGHT 5
#define MAP_WIDTH  5

#define START_X 1.0
#define START_Y 1.0
#define TERMINAL_X 3.0
#define TERMINAL_Y 3.0

namespace nsMap {
    struct sCoordination {
        int x;
        int y;

        sCoordination() :
            x(0),
            y(0) {
        };

        sCoordination(int coordX, int coordY) :
            x(coordX),
            y(coordY) {
        };
    };

    enum eProperty {
        AVAILABLE,
        OBSTACLE,
        HOTZONE,
        START,
        TERMINAL,
        ARRIVED
    };

    class cGrid {
    public:
        int m_visited;
        struct sCoordination m_grid;
        eProperty m_property;

        cGrid() :
            m_visited(0),
            m_grid(),
            m_property(AVAILABLE) {
        };

        cGrid(int gridX, int gridY,
              eProperty property = AVAILABLE,
              int visit = 0) :
            m_visited(visit),
            m_grid(gridX, gridY),
            m_property(property) {
        };

        bool setGridLocation(int x, int y) {
            m_grid.x = x;
            m_grid.y = y;
            return true;
        }

        bool setGridVisited(int visit = 0) {
            m_visited = visit;
            return true;
        }

        bool setGridProperty(eProperty property = AVAILABLE) {
            m_property = property;
            return true;
        }

        struct sCoordination getGridLocation() {
            return m_grid;
        }

        int getGridVisited() {
            return m_visited;
        };

        eProperty getGridProperty() {
            return m_property;
        };
    }; //cGrid

    class cMap {
    public:
        std::vector<std::vector<cGrid> > m_map;
        struct sCoordination m_start;
        struct sCoordination m_terminal;

        cMap();
        cMap(int startX, int startY, int terminalX, int terminalY);
        cMap(const cMap& map);

        void initMap();
        bool setMapGrid(int x, int y, eProperty property = AVAILABLE);

        struct sCoordination getStart();
        struct sCoordination getTerminal();

        bool isLegal(int x, int y);
        bool isLegal(float x, float y, float radius);
        bool isEnd();
    }; //cMap
} //nsMap
#endif //MAP_HPP
