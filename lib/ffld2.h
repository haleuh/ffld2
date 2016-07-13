#ifndef _FFLD2_H_
#define _FFLD2_H_
#ifdef _WIN32
#define DllExport   __declspec( dllexport )
#else
#define DllExport
#endif // _WIN32

typedef struct Rect
{
	int x;
	int y;
	int w;
	int h;
} Rect;

// Detect using a loaded model
extern "C" {
	DllExport bool detect(Rect* output_detected_rect,
		const unsigned char* image_data,
		const int width,
		const int height,
		const int n_channels,
		const int padding,
		const int interval,
		const double threshold,
		const bool cacheWisdom,
		const double overlap,
		const double adaptive_min_size);
}

#endif