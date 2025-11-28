#pragma once

#include <cstddef>
#include <vector>

void PrintVector(const std::vector<int> &vec, const char *title);
void PrintRange(const std::vector<int> &vec, size_t low, size_t high,
                const char *title);
