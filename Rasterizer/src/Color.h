#pragma once

#include <stdint.h>

class Color
{
public:
	Color() {}
	Color(float nr, float ng, float nb, float na) : r(nr), g(ng), b(nb), a(na) {}

	~Color() {}

	Color operator+(const Color& color) const
	{
		return Color(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	Color operator-(const Color& color) const
	{
		return Color(r - color.r, g - color.g, b - color.b, a - color.a);
	}

	Color operator*(float s)
	{
		return Color(r * s, g * s, b * s, a * s);
	}

	Color Interpolate(const Color &c, float factor) const
	{
		return *this + (c - *this) * factor;
	}

	uint32_t ToU32T()
	{
		uint32_t R = (uint32_t)(r * 255);
		uint32_t G = (uint32_t)(g * 255);
		uint32_t B = (uint32_t)(b * 255);
		uint32_t A = (uint32_t)(a * 255);

#ifdef __APPLE__
		uint32_t value = (B << 24) | (G << 16) | (R << 8) | A;
#elif _WIN32
		uint32_t value = (B << 24) | (G << 16) | (R << 8) | A;
#else
		uint32_t value = (B << 24) | (G << 16) | (R << 8) | A;
#endif
		return value;
	};
public:
	float r;
	float g;
	float b;
	float a;
};