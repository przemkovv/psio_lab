#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <array>


//\<a href\=\"([a-z]+:\/{2}[a-z\d\.\/\-]+)\".+?(?=\. (((|0048|\+48|\+48 )?((\d){1}[\(\)\- ]?){9})+)|((\(\d{3}\) )\d{7}))
//\. ((\+48 |\+48|0048)?((\d{2}(\-| )?){3}\d{3})|(\d{2}(\-| )\d{3}(\-| )?(\d{2}(\-| )?){2})|(\d{3}(\-| )?(\d{2}(\-| )?){3}))|(\(\d{3}\) ?\d{7})


std::map<std::string, std::string> load(std::map<std::string, std::string>& loaded,
                                        std::fstream& plik) {
	if (plik.is_open())
	{
		std::stringstream str_stream;
		str_stream << plik.rdbuf();
		std::string full_text = str_stream.str();

		std::regex Re(
			R"(\<a href\=\"([a-z]+:\/{2}[a-z\d\.\/\-]+)\".+?(?=\. (((|0048|\+48|\+48 )?((\d){1}[\(\)\- ]?){9})+)|((\(\d{3}\) )\d{7})))");
		std::smatch m;
		while (std::regex_search(full_text, m, Re))
		{
			//std::regex_search(full_text, m, Re);
			std::cout << m[1] << " " << m[2] << '\n';
			loaded.emplace(m[1], m[2]);
			full_text = m.suffix();
		}
	}
	else
	{
		std::cout << "Nie uda³o siê otworzyæ pliku.\n";
	}

	plik.close();

	return loaded;
}


void print_m(std::map<std::string, std::string>& map_) {
	for (auto it = map_.begin(); it != map_.end(); it++)
	{
		std::cout << "FILIA: " << it->first << " NUMER: " << it->second << std::endl;
	}
}


std::map<std::string, std::string> phone_normalizer(std::map<std::string, std::string>& map_) {

	const std::string phone_number_string_remove = R"((\+|\(|\)|\-| ))";
	const std::regex phone_numeber_reg_remove{phone_number_string_remove};


	for (auto it = map_.begin(); it != map_.end(); it++)
	{
		it->second = std::regex_replace(it->second, phone_numeber_reg_remove, "");
	}

	return map_;
}


std::string href_trim(std::string& href_full) {

	std::string to_trim_b = R"((http|https)\:\/{2}(www\.)?)";
	std::regex to_trim_b_re{to_trim_b};

	href_full = std::regex_replace(href_full, to_trim_b_re, "");

	std::string to_trim_p = R"(\/.+)";
	std::regex to_trim_p_reg{to_trim_p};

	href_full = std::regex_replace(href_full, to_trim_p_reg, "");


	return href_full;
}


void print_vp(std::vector<std::pair<std::string, std::string>> vec) {
	for (auto it = vec.begin(); it != vec.end(); it++)
		std::cout << "FILIA: " << it->first << " NUMER: " << it->second << std::endl;
}


void save_to_csv(std::vector<std::pair<std::string, std::string>> to_save) {
	std::ofstream csv("dane.csv");
	if (csv.is_open())
	{
		for (auto it = to_save.begin(); it != to_save.end(); it++)
		{
			csv << it->first << ";" << it->second << "\n";
		}

		csv.close();
	}
}


int main() {
	std::map<std::string, std::string> loaded;
	std::fstream plik1("../data/numery1.html", std::ios::in);
	//std::fstream plik2("numery2.html", std::ios::in);
	//std::fstream plik3("numery3.html", std::ios::in);
	//std::fstream plik4("numery4.html", std::ios::in);

	loaded = load(loaded, plik1);
	//loaded = load(loaded, plik2);
	//loaded = load(loaded, plik3);
	//loaded = load(loaded, plik4);
	print_m(loaded);

	loaded = phone_normalizer(loaded);
	std::cout << "\nznormalizowane:\n";
	print_m(loaded);

	int i = 0;
	int size = loaded.size();
	std::vector<std::string> firsts(size);
	std::vector<std::string> seconds(size);

	{
		/*

		const int tabSize = 10;
		int tab[10];
		int tab2[tabSize];
		std::array<int, 10> tabArray;
		std::array<int, tabSize> tabArray2;


		int tabSizeFromUser = rand();
		//int tabFromUser[tabSizeFromUser]; // roszerzenie GCC/MinGW niezgodne ze standardem c++
		std::vector<int> tabFromUserVector(tabSizeFromUser);


		
		*/
	}
	for (auto it = loaded.begin(); it != loaded.end(); it++)
	{
		firsts[i] = it->first;
		seconds[i] = it->second;
		firsts[i] = href_trim(firsts[i]);

		i++;
	}


	std::map<std::string, std::string> numery_filie;
	for (auto i = 0; i < size; i++)
	{
		numery_filie.emplace(firsts[i], seconds[i]);
	}

	std::cout << "\nWyodrebniona witryna:\n";
	print_m(numery_filie);


	std::vector<std::pair<std::string, std::string>> copied;
	copy(numery_filie.begin(), numery_filie.end(), std::back_inserter(copied));
	std::vector<std::pair<std::string, std::string>> copied2;

	std::unique_copy(copied.begin(), copied.end(), std::back_inserter(copied2),
	                 [](std::pair<std::string, std::string>& pair1, std::pair<std::string, std::string>& pair2)
	                 {
		                 return pair1.second == pair2.second;
	                 });


	std::cout << "\nSKOPIOWANE:\n";
	print_vp(copied2);

	save_to_csv(copied2);


	return 0;
}
