//
// Created by hale on 7/7/16.
//
#include <opencv2/opencv.hpp>
#include "lib/ffld2.h"


using namespace std;

int main( int argc, char **argv )
{
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " image_path model_path" << endl;
        return 1;
    }

    vector<Rect> rects;
    cv::Mat image = cv::imread(argv[1]);
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << endl ;
        return 1;
    }
    string model_path = argv[2];
    if (set_mixture_model(model_path))
        rects = detect(image.data, image.cols, image.rows, image.channels(), 6, 5, 0.5, true, 0.3);
    for(unsigned int i = 0; i < rects.size(); i++){
        cv::rectangle(image, Point( rects[i].x, rects[i].y ),
                      Point( rects[i].x + rects[i].w, rects[i].y + rects[i].h ),
                      Scalar( 0, 255, 255 ));
        cout << rects[i].x << " " << rects[i].y << " " << rects[i].w << " " << rects[i].h << endl;
    }

    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "Display window", image );                   // Show our image inside it.

    cv::waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}