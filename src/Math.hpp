#ifndef MATH_H
#define MATH_H

#include <cmath>

Vector2<T>& rotateBy(float degrees, const Vector2<T>& center=Vector2<T>()){
		degrees *= 3.14159f/180.f;
		const float cs = std::cos(degrees);
		const float sn = std::sin(degrees);

		x -= center.x;
		y -= center.y;

		T nx = (T)(x*cs - y*sn);
		T ny = (T)(x*sn + y*cs);

        x = nx;
        y = ny;

		x += center.x;
		y += center.y;
		return *this;
}

#endif
