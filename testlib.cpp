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
    string model_path = argv[2];

    if (set_mixture_model(model_path))
        rects = detect(image.data, image.cols, image.rows, image.channels(), 6, 5, 0.5, true, 0.3);
    if(rects.size()>=1){
        for(unsigned int i = 0; i < rects.size(); i++){
            cout << rects[i].x << " " << rects[i].y << " " << rects[i].w << " " << rects[i].h << endl;
        }
    }
    return 0;
}