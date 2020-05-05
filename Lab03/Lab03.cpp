// Lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <vector>

enum Color1
{
	Red,
	Blue
};

enum Color2
{
	White,
	//Red,  // compilation error
	Black
};

enum class Color
{
	Red,
	Blue,
	White,
	Black
};

enum class SwordType { Bastard, Great, Short, Katana };

struct Sword
{
	SwordType type;
	float length;
};

void print(const std::vector<Sword>& swords) {
	for (auto& sword : swords)
	{
		std::cout << "Sword type: " << static_cast<int>(sword.type) << " Length: " << sword.length << '\n';
	}
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {

	out << '[';
	for (auto& elem : vec)
	{
		out << elem << '\n';
	}
	out << "]\n";
	return out;
}


void test_lambda() {
	Color1 c1 = Red;
	Color2 c2 = Black;

	if (c2 == 1)
	{
	}

	Color c3 = Color::Red;
	//if (c3 == 1) // compilation error
	//{
	//	
	//}


	std::vector<Sword> swords{
		//{SwordType::Bastard, 2.0f},
		{SwordType::Great, 3.0f},
		{SwordType::Short, 1.0f},
		{SwordType::Katana, 2.5f},
	};

	auto is_bastard = [](const Sword& sword)
	{
		return sword.type == SwordType::Bastard;
	};

	if (std::none_of(swords.begin(), swords.end(), is_bastard))
	{
		std::cout << "No bastard swords\n";
	}

	const float m2ft = 3.28084f; // 1 metr = 3.24084 stopy
	auto metric_to_imperial = [m2ft](Sword sword)
	{
		sword.length *= m2ft;
		return sword;
	};

	print(swords);
	std::vector<Sword> swordImperial(swords.size());
	std::transform(swords.begin(), swords.end(), swordImperial.begin(), metric_to_imperial);
	print(swordImperial);
	std::vector<Sword> swordImperial2;
	std::transform(swords.begin(), swords.end(), std::back_inserter(swordImperial2), metric_to_imperial);
	print(swordImperial2);
	std::map<std::string, int> word_statistics;
	word_statistics.emplace(std::pair{"the", 1});
}

struct CurrencyRate
{
	std::string name = "";
	float value = 0.0f;
	std::string date = "";
};
void print(const std::vector<CurrencyRate>& rates, const std::string& description) {

	std::cout << description << '\n';
	for (const CurrencyRate& rate : rates)
	{
		std::cout << rate.name << " rate at the day " << rate.date << " was " << rate.value << '\n';
	}
	std::cout << "-----------------------------\n";
}

void print(const std::vector<CurrencyRate>::const_iterator begin,
           const std::vector<CurrencyRate>::const_iterator end,
           const std::string& description) {

	std::cout << description << '\n';
	for (auto it = begin; it != end; ++it)
	{
		const CurrencyRate& rate = *it;
		std::cout << rate.name << " rate at the day " << rate.date << " was " << rate.value << '\n';
	}
	std::cout << "-----------------------------\n";
}

bool operator<(const CurrencyRate& rate1, const CurrencyRate& rate2) {
	return std::tie(rate1.name, rate1.value, rate1.date) <
		std::tie(rate2.name, rate2.value, rate2.date);
}


void test_zadanie_10() {

	std::vector<CurrencyRate> currencyRates{
		{"USD", 4.5f, "2020-04-03"},
		{"USD", 4.51f, "2020-04-04"},
		{"USD", 4.51f, "2020-04-05"},
		{"USD", 4.49f, "2020-04-06"},
		{"USD", 4.34f, "2020-04-07"},
		{"USD", 4.34f, "2020-04-08"},
		{"USD", 4.51f, "2020-04-09"},
		{"EUR", 3.5f, "2020-04-03"},
		{"EUR", 3.51f, "2020-04-04"},
		{"EUR", 3.51f, "2020-04-05"},
		{"EUR", 5.49f, "2020-04-06"},
		{"EUR", 3.34f, "2020-04-07"},
		{"EUR", 3.34f, "2020-04-08"},
		{"EUR", 3.51f, "2020-04-09"},
	};
	std::vector<CurrencyRate> currencyRatesUSD;
	std::vector<CurrencyRate> currencyRatesEURO;


	std::copy_if(currencyRates.cbegin(), currencyRates.cend(),
	             std::back_inserter(currencyRatesUSD),
	             [](const CurrencyRate& rate)
	             {
		             return rate.name == "USD";
	             }
	);
	std::copy_if(currencyRates.cbegin(), currencyRates.cend(),
	             std::back_inserter(currencyRatesEURO),
	             [](const CurrencyRate& rate)
	             {
		             return rate.name == "EUR";
	             }
	);

	print(currencyRates, "ALL");
	print(currencyRatesUSD, "USD");
	print(currencyRatesEURO, "EUR");

	auto compareRates = [](const CurrencyRate& rate1, const CurrencyRate& rate2)
	{
		return rate1.value < rate2.value;
	};
	std::sort(currencyRatesUSD.begin(), currencyRatesUSD.end(), compareRates);
	std::sort(currencyRatesEURO.begin(), currencyRatesEURO.end(), compareRates);

	print(currencyRatesUSD, "USD Sorted");

	auto [firstIt, endIt] = std::equal_range(currencyRatesUSD.cbegin(), currencyRatesUSD.cend(),
	                                         CurrencyRate{"USD", 4.51f}, compareRates);

	print(firstIt, endIt, "USD = 4.51");


	std::sort(currencyRates.begin(), currencyRates.end(), compareRates);
	print(currencyRates, "ALL sorted");
	std::sort(currencyRates.begin(), currencyRates.end());
	print(currencyRates, "ALL sorted second try");


}


int main() {


	//test_lambda();
	test_zadanie_10();


}
