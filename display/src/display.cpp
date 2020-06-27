#include "display.hpp"

namespace nsDisplay {
    cDisplay::cDisplay() :
        m_point(0, 0),
        m_mat(MAP_HEIGHT * 100, MAP_WIDTH * 100, CV_8UC3, cv::Scalar::all(255)) {
        drawMMLine(m_mat);
        drawCMLine(m_mat);
//        cv::namedWindow("MCTS", cv::WINDOW_AUTOSIZE);
//        cv::imshow("MCTS", m_mat);
//        cv::waitKey(0);
    }

    void cDisplay::drawMMLine(cv::Mat &mat) {
        int cols = mat.cols;
        int rows = mat.rows;

        for(int i = 0; i < cols; i = i + 10) {
            cv::Point start = cv::Point(i, 0);
            cv::Point end = cv::Point(i, rows);
            cv::line(mat, start, end, cv::Scalar(0, 255, 0));

            start = cv::Point(0, i);
            end = cv::Point(cols, i);
            cv::line(mat, start, end, cv::Scalar(0, 255, 0));
        }
    }

    void cDisplay::drawCMLine(cv::Mat &mat) {
        int cols = mat.cols;
        int rows = mat.rows;

        for(int i = 0; i < cols; i = i + 100) {
            cv::Point start = cv::Point(i, 0);
            cv::Point end = cv::Point(i, rows);
            cv::line(mat, start, end, cv::Scalar(0, 0, 0), 2);

            start = cv::Point(0, i);
            end = cv::Point(cols, i);
            cv::line(mat, start, end, cv::Scalar(0, 0, 0), 2);
        }
    }

    void cDisplay::drawGrid(cv::Mat &mat, float x, float y,
                            int r, int g, int b) {
        int xPoint = (int)(x * 100.0);
        int yPoint = (int)(y * 100.0);
        std::cout << "x: " << xPoint << ", y: " << yPoint << std::endl;
        cv::Point start = cv::Point(xPoint, yPoint);
        cv::Point end = cv::Point(xPoint + 10, yPoint + 10);
        cv::rectangle(mat, start, end, cv::Scalar(r, g, b), cv::FILLED);
    }
} //namespace nsDisplay
