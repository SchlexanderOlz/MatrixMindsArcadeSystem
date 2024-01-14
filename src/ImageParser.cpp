#include "ImageParser.hpp"


using namespace matrix_minds;


vector<PositionalObject> image_parser::parse(const cv::Mat& image) {
    vector<PositionalObject> pixels;
    for (size_t y = 0; y < image.rows; ++y) {
        for (size_t x = 0; x < image.cols; ++x) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(x, y);

            for (size_t i = 0; i < pixel.channels; ++i) {
                if (pixel[i] == 0) continue;
                pixels.emplace_back(PositionalObject(x / image.cols, y / image.rows, rgb_matrix::Color((uint8_t)pixel[0], (uint8_t)pixel[1], (uint8_t)pixel[2])));
                break;
            }
        }
    }
    return pixels;
}