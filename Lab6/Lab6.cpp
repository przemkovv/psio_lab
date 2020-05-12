// Lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "histogram.h"


#include <random>
#include <vector>


template <typename T>
T convert(const std::string& data) {
	static_assert(false, "Function is not implemented yet.");
	return T{};
}


template <>
int convert(const std::string& data) {
	std::cout << "convert_int\n";
	return std::stoi(data);
}

template <>
float convert(const std::string& data) {
	std::cout << "convert_float\n";
	return std::stof(data);
}

template <>
double convert(const std::string& data) {
	std::cout << "convert_double\n";
	return std::stod(data);
}

template <>
std::string convert(const std::string& data) {
	std::cout << "convert_string\n";
	return data;
}


template <typename T>
T read_from_csv(const std::string& data) {

	return convert<T>(data);

}

template <typename Operation >
void fill(int rows, int columns, Operation &&operation) {

	for (int rowIndex = 0; rowIndex < rows; ++rowIndex)
	{
		for (int colIndex = 0; colIndex < columns; ++colIndex)
		{
			int mat = operation();
		}
	}
}

void foo(int&& x) {
	
};

int main() {

	/*
	std::cout << read_from_csv<int>("1") << '\n';
	std::cout << read_from_csv<float>("1.0") << '\n';
	std::cout << read_from_csv<std::string>("foo") << '\n';
	std::cout << read_from_csv<double>("1.0") << '\n';
	
	*/

	foo(5);

	Histogram<float> histogram;

	std::cout << histogram;

	Histogram<int> histogram2(std::vector<int>({10, 15, 6, 9, 10, 12}));

	std::cout << histogram2;
	std::cout << "--------------------\n";
	histogram2.emplace(10);
	std::cout << histogram2;

	std::cout << "--------------------\n";
	histogram2.emplace(std::vector<int>({ 10, 15, 6, 9, 10, 12 }));
	std::cout << histogram2;


	std::cout << "--------------------\n";
	//histogram2.clear();
	//std::cout << histogram2;


	std::pair<int, Frequency> max = histogram2.max();
	std::cout << "max_freq at " << max.first << " with " << max.second << '\n';
	auto [max_key, max_freq] = histogram2.max();
	std::cout << "max_freq at " << max_key << " with " << max_freq << '\n';








	
	{
		static std::default_random_engine e{};
		std::uniform_int_distribution<int> distribution{0, 100};

		auto func = [&distribution]()
		{
			return distribution(e);
		};
		fill(3, 3, func);
		fill(3, 3, [&distribution]()
		{
			return distribution(e);
		});
		fill(3, 3, []()
		{
			return 0;
		});
		//Matrix<int>  Y = Matrix::fill(3, 3, [&distribution]() { return distribution(e); });
	}

}
