#ifndef IMAGE_PARSER
#define IMAGE_PARSER


#include <iostream>
#include <led-matrix.h>
#include <opencv2/core.hpp>

#include "PositionalObject.hpp"

using namespace std;


namespace matrix_minds::image_parser
{
    /**
     * @brief Parses an opencv image matrix into points. Every pixel in the image represents a point. 
     * @todo How should resoltion play into this
    */
    vector<PositionalObject> parse(const cv::Mat& image);

} // namespace matrix_minds

#endif