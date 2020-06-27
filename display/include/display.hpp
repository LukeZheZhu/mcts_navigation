#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "map.hpp"

namespace nsDisplay {
    struct sPoint {
        int x;
        int y;

        sPoint() :
            x(0),
            y(0) {
        };

        sPoint(int pointX, int pointY) :
            x(pointX),
            y(pointY) {
        };
    };

    class cDisplay {
    public:
        struct sPoint m_point;
        cv::Mat m_mat;

        cDisplay();

        void drawCMLine(cv::Mat &mat);
        void drawMMLine(cv::Mat &mat);

        void drawGrid(cv::Mat &mat, float x, float y, int r, int g, int b);
    }; // class cDisplay
} //namesapce nsDisplay
