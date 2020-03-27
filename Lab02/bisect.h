#pragma once

#include <optional>

std::optional<float> bisect(float begin, float end, float (*func)(float x));
void test_bisect();
