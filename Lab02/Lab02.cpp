// Lab02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "bisect.h"

std::vector<std::string> split(const std::string& text, char separator = ' ') {

	std::vector<std::string> splitted;

	size_t pos = 0;
	size_t prevPos = 0;
	while (pos != std::string::npos)
	{
		prevPos = pos;
		const bool isFirstWord = pos == 0;
		prevPos += !isFirstWord;

		pos = text.find(separator, prevPos);
		if (pos - prevPos > 0)
		{
			splitted.push_back(text.substr(prevPos, pos - (prevPos)));
		}

		//if (isFirstWord)
		//{
		//	pos = text.find(separator, prevPos);
		//	splitted.push_back(text.substr(prevPos, pos - (prevPos) ));
		//	
		//} else
		//{
		//	prevPos += 1;
		//	pos = text.find(separator, prevPos);
		//	splitted.push_back(text.substr(prevPos, pos - (prevPos) ));
		//}
	}

	return splitted;
}

void print(const std::vector<std::string>& words) {
	std::cout << "--------------------\n";
	std::cout << "Found " << words.size() << '\n';
	for (const auto& word : words)
	{
		std::cout << word << '\n';
	}
}

struct Exchange_rate
{
	std::string date;
	double usd;
	double eur;
	std::string table_id;
};


std::vector<Exchange_rate> load_data() {
	std::fstream file("kursy_usd_eur.csv");
	//plik znajduje siê w tym samym katalogu co pliki Ÿród³owe projektu, inaczej trzeba podaæ pe³n¹ œcie¿kê np. "c:/Users/nazwa_uzytkownika/Downloads/kursy_usd_eur.csv"
	std::vector<Exchange_rate> rates;
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line); // wczytuje pierwsz¹ liniê z nag³ówkiem i j¹ ignoruje
		while (std::getline(file, line))
		{
			//wczytuje kolejne linie a¿ do koñca pliku
			std::stringstream str(line); //tworzy strumieñ, którego Ÿród³em jest wczytana linia

			Exchange_rate er;
			std::getline(str, er.date, ','); //wczytuje date (pierwszy element wiersza)
			std::string double_str;
			std::getline(str, double_str, ',');  // wczytuje kurs USD (jako tekst)
			er.usd = std::stod(double_str);      //zamiana na string->double
			std::getline(str, double_str, ',');  // wczytuje kurs EUR (jako tekst)
			er.eur = std::stod(double_str);      //zamiana na string->double
			std::getline(str, er.table_id, ','); // wczytuje ostatni¹ kolumnê z numerem tabeli NBP
			rates.emplace_back(er);              //dodaje element do kolekcji
		}
	}
	else
	{
		std::cout << "Nie mo¿na by³o otworzyæ pliku\n";
	}
	return rates;
}

void print(const std::vector<Exchange_rate>& rates) {
	std::cout << "--------------------\n";
	std::cout << "Found " << rates.size() << '\n';
	for (const auto& rate : rates)
	{
		std::cout << rate.date << " " << rate.eur << " " << rate.usd << '\n';
	}
}

std::vector<Exchange_rate> bubble_sort(std::vector<Exchange_rate> rates) {

	int n = rates.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (rates[j].usd > rates[j + 1].usd)
			{
				double temp = rates[j].usd;
				rates[j].usd = rates[j + 1].usd;
				rates[j + 1].usd = temp;
			}
		}
	}

	return rates;
}

//std::string read_words(const std::string& name) {
//	std::ifstream file(name);
//	std::vector<std::string> words;
//	if (file)
//	{
//		std::string word;
//		while (file >> word)
//		{
//			words.push_back(word);
//		}
//	}
//	return words;
//}

std::string load_whole_file(const std::string& name) {
	std::ifstream file(name);
	std::ostringstream str;
	str << file.rdbuf();
	std::copy(std::istreambuf_iterator<char>(file), {},
	          std::ostreambuf_iterator<char>(str));
	return str.str();
}



int main() {
	//std::string file("kursy_usd_eur.csv");
	//auto content = load_whole_file(file);
	//std::cout << content;

	//std::vector<Exchange_rate> rates = load_data();
	//print(rates);
	//auto sorted_rates = bubble_sort(rates);
	//print(sorted_rates);

	test_bisect();


	return 0;
}
