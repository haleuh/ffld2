//
// Created by hale on 7/7/16.
//
#include <opencv2/opencv.hpp>
#include "lib/ffld2.h"


using namespace std;

int main( int argc, char **argv )
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " image_path" << endl;
        return 1;
    }

    Rect output_detected_rect;
    cv::Mat image = cv::imread(argv[1]);
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << endl ;
        return 1;
    }
    if (detect(&output_detected_rect, image.data, image.cols, image.rows, image.channels(), 6, 5, 0.5, true, 0.3, 0.1)) {
        cv::rectangle(image, cv::Point( output_detected_rect.x, output_detected_rect.y ),
                      cv::Point( output_detected_rect.x + output_detected_rect.w, output_detected_rect.y + output_detected_rect.h ),
                      cv::Scalar( 0, 255, 255 ));
        cout << output_detected_rect.x << " " << output_detected_rect.y << " " << output_detected_rect.w << " " << output_detected_rect.h << endl;
    }

    cv::namedWindow( "Display window", cv::WINDOW_NORMAL );// Create a window for display.
    cv::imshow( "Display window", image );                   // Show our image inside it.

    cv::waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}