#include "utils.h"
#include <cmath>
namespace utils{
	double EulerDistance(Vector2 a, Vector2 b) {
		int xdist = std::abs(a.x - b.x);
		int ydist = std::abs(a.y - b.y);
		return std::sqrt((xdist * xdist) + (ydist * ydist));
	}
	int ManhattanDistance(Vector2 a, Vector2 b) {
		int xdist = std::abs(a.x - b.x);
		int ydist = std::abs(a.y - b.y);
		return xdist + ydist;
	}
	int ClampInt(int toClamp, int min, int max) {
		return std::fmax(min, std::fmin(max, toClamp));
	}
}