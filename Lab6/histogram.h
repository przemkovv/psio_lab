#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>


//using Bin = int;
using Frequency = int;

template <typename Bin>
class Histogram
{
	std::map<Bin, Frequency> histogram_;

private:
	void computeFrequency(const std::vector<Bin>& input_data);

public:
	Histogram() = default;

	Histogram(const std::vector<Bin>& inputData);


	void emplace(Bin value);
	void emplace(const std::vector<int>& values);
	void clear();

	std::pair<Bin, Frequency> max();

	template <typename Bin2>
	friend std::ostream& operator<<(std::ostream& out, const Histogram<Bin2>& histogram);

	//friend std::ostream& operator<<(std::ostream& out, const Histogram<Bin>& histogram);
};



template <typename Bin>
void Histogram<Bin>::computeFrequency(const std::vector<Bin>& input_data) {

	for (Bin value : input_data)
	{
		++histogram_[value];
	}
}

template <typename Bin>
Histogram<Bin>::Histogram(const std::vector<Bin>& inputData) {
	computeFrequency(inputData);
}

template <typename Bin>
void Histogram<Bin>::emplace(Bin value) {
	++histogram_[value];
}

template <typename Bin>
void Histogram<Bin>::emplace(const std::vector<int>& values) {
	computeFrequency(values);
}

template <typename Bin>
void Histogram<Bin>::clear() {
	histogram_.clear();
}

template <typename Bin>
std::pair<Bin, Frequency> Histogram<Bin>::max() {

	std::pair<Bin, Frequency> max_pair = *histogram_.begin();
	for (auto [key,value] : histogram_)
	{
		if (value > max_pair.second)
		{
			max_pair = { key, value };
		}
	}

	return max_pair;

}

template <typename Bin>
std::ostream& operator<<(std::ostream& out, const Histogram<Bin>& histogram) {

	for (const auto [key, value] : histogram.histogram_)
	{
		out << "freq(" << key << ")=" << value << '\n';
	}
	/*
	for (const auto p : histogram.histogram_)
	{
		out << "freq(" << p.first << ")=" << p.second << '\n';
		
	}
	*/


	return out;
}
