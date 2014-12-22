#include "../Intersector.h"
#include "../Mixture.h"
#include <vector>
#include <algorithm>


struct Detection : public FFLD::Rectangle
{
	FFLD::HOGPyramid::Scalar score;
	int x;
	int y;
	int z;

	Detection() : score(0), x(0), y(0), z(0)
	{
	}

	Detection(FFLD::HOGPyramid::Scalar score, int x, int y, int z, FFLD::Rectangle bndbox) : FFLD::Rectangle(bndbox), score(score), x(x), y(y), z(z)
	{
	}

	bool operator<(const Detection & detection) const
	{
		return score > detection.score;
	}
};

// interval = 5, padding = 6, overlap = 0.9, threshold = 0.3
void detect(const FFLD::Mixture & mixture, const unsigned char* image,
            const int width, const int height, const int padding,
            const int interval, const double threshold, const double overlap,
			std::vector<Detection>& detections);
