#pragma once

namespace utils {
	struct Vector2 {
		int x;
		int y;
		Vector2() {
			x = 0;
			y = 0;
		}
		Vector2(int x_, int y_) {
			x = x_;
			y = y_;
		}
	};
	enum class Direction {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 4
	};

	double EulerDistance(Vector2 a, Vector2 b);
	int ManhattanDistance(Vector2 a, Vector2 b);
	int ClampInt(int toClamp, int min, int max);
}