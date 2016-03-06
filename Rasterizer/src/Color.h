#pragma once

class Color
{
public:
	Color() {};
	Color(float nr, float ng, float nb, float na) : r(nr), g(ng), b(nb), a(na) {};

	~Color() {};

	Color operator+(const Color& color)
	{
		return Color(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	Color operator-(const Color& color)
	{
		return Color(r - color.r, g - color.g, b - color.b, a - color.a);
	}

	Color operator*(float s)
	{
		return Color(r * s, g * s, b * s, a * s);
	}

	uint32_t ToU32T()
	{
		uint32_t R = (uint32_t)r;
		uint32_t G = (uint32_t)g;
		uint32_t B = (uint32_t)b;
		uint32_t A = (uint32_t)a;

#ifdef __APPLE__
		uint32_t value = (B << 24) | (G << 16) | (R << 8) | A;
		// visual studio
#elif _WIN32
		uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
#else
		uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
#endif
		return value;
	}
public:
	float r;
	float g;
	float b;
	float a;
};