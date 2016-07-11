#ifndef _FFLD2_H_
#define _FFLD2_H_
#ifdef _WIN32
#define DllExport   __declspec( dllexport )
#else
#define DllExport
#endif // _WIN32

#include <vector>

typedef struct Rect
{
	double score;
	int x;
	int y;
	int w;
	int h;

	Rect(float score, int x, int y, int w, int h) : score(score), x(x), y(y), w(w), h(h)
	{
	}
} Rect;

DllExport bool init_face_detection_model();

// Detect using a loaded model
DllExport std::vector<Rect> detect(const unsigned char* image,
            const int width, const int height, const int n_channels, const int padding, 
            const int interval, const double threshold, const bool cacheWisdom,
            const double overlap);

#endif