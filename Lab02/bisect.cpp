#include "bisect.h"

#include <iostream>

const float epsilon = 0.0000001f;
const int max_iterations = 10000;


//float f(float x) {
//}

float sign(float x) {
	if (x < 0)
	{
		return -1;
	}
	else if (x > 0)
	{
		return 1;
	}
	return 0;
}

float f(float x) {
	return x * x - 5;
}

float g(float x) {
	float arg = x + 2;
	return arg * arg - 5;
}


std::optional<float> bisect(float begin, float end, float (*func)(float)) {

	float begin_value = func(begin);
	float end_value = func(end);

	int iteration = 0;

	if (sign(begin_value) == sign(end_value))
	{
		return {};
	}

	while (end - begin > epsilon
		&& sign(begin_value) != sign(end_value)
		&& iteration < max_iterations
	)
	{
		const float middle_point = (begin + end) / 2.0f;
		const float middle_point_value = func(middle_point);
		if (sign(middle_point_value) == sign(begin_value))
		{
			begin = middle_point;
			begin_value = middle_point_value;
		}
		else
		{
			end = middle_point;
			end_value = middle_point_value;
		}

		++iteration;
	}

	return (begin + end) / 2.0f;
}

void test_bisect() {

	{
		std::optional<float> zero_point = bisect(-3, 3, sign);
		if (zero_point)
		{
			std::cout << "Miejsce zerowe funkcji g w (-3..2) = " << zero_point.value() << '\n';
		}
		else
		{
			std::cout << "Nie wiemy czy jest tam miejsce zerowe\n";
		}
	}
	{
		std::optional<float> zero_point = bisect(-3,	 2, f);
		if (zero_point)
		{
			std::cout << "Miejsce zerowe funkcji f w (-3..2) = " << zero_point.value() << '\n';
		}
		else
		{
			std::cout << "Nie wiemy czy jest tam miejsce zerowe\n";
		}
	}
	//std::cout << "Miejsce zerowe w (-3..-2) = " << bisect(-3, -2) << '\n';

}
