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
		bool operator==(Vector2 other) {
			if (other.x == x && other.y == y) return true;
			else return false;
		}
		bool operator!=(Vector2 other) {
			return !operator==(other);
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