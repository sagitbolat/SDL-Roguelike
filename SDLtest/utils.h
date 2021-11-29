#pragma once

namespace utils {
	struct Vector2 {
		int x;
		int y;
		Vector2() {
			x = 0;
			y = 0;
		}
	};
	enum class Direction {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 4
	};
}