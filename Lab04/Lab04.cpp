// Lab04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <regex>

void zadani3() {
/*
 * Utworzono takie i takie wyra¿enie regularne:....
 *
 * 
 */
	
}

void fun1() {
	/*

	std::string text = "foo\\nb\"ar\\nbaz";
	std::string text4 = "foo"
		"bar"
		"baz";
	std::string text2 = R"(foo"\'nbar\nbaz)";
	std::string text3 = R"FFF(foo
bar
baz)FFF";

	std::cout << text << '\n';
	std::cout << text4 << '\n';
	std::cout << text2 << '\n';
	std::cout << text3 << '\n';

	*/

}

void fun2() {
	{
		const std::string inputTextSimple = R"(aaa)";

		const std::string regular_expresion = R"(a{3}?)";
		std::regex r(regular_expresion);
		std::cout << "Regex: " << regular_expresion << " " <<
			std::regex_match(inputTextSimple, r) << '\n';
	}

}

void fun3() {

	std::string inputText = R"(61-064
email@put.poznan.pl
email@google.com
777-088-00-10
aaa
aa
a)";
	const std::string emailRegex = R"(\w+@(\w+\.)+\w+)";
	std::regex r(emailRegex);

	std::cout << emailRegex << '\n';
	std::smatch emailMatch;

	auto inputText2 = inputText;

	while (std::regex_search(inputText2, emailMatch, r))
	{
		std::cout << "YAY\n";
		for (auto submatch : emailMatch)
		{
			std::cout << "Matched " << std::string{submatch.first, submatch.second} << '\n';
			std::cout << "Matched " << submatch << '\n';
		}
		std::cout << "----------\n";
		std::cout << "prefix " << emailMatch.prefix() << '\n';
		std::cout << "suffix " << emailMatch.suffix() << '\n';
		std::cout << "----------\n";
		inputText2 = emailMatch.suffix();
	}
}

std::string phone_number_normalizer(const std::string& phone_number) {


	const std::string phone_number_regex_string = R"(^((\d)[\+\(\)\- ]?)+$)";
	const std::regex phone_number_regex{ phone_number_regex_string };
	std::smatch phone_number_match;

	const bool found = std::regex_search(phone_number, phone_number_match, phone_number_regex);
	std::cout << phone_number << ": Match? " << found << '\n';

	if (found) {
		const std::string phone_number_regex_string_remove = R"(\+|\(|\)|\-| )";
		const std::regex phone_number_regex_remove{ phone_number_regex_string_remove };

		return std::regex_replace(phone_number, phone_number_regex_remove, "");
	}
	return "";

}

int main() {

	//fun1();
	//fun2();
	//fun3();


	std::cout << phone_number_normalizer("48-488-231") << '\n';
	std::cout << phone_number_normalizer("48-4a8-231") << '\n';
	std::cout << phone_number_normalizer("aa-bb--cc--dd") << '\n';
	std::cout << phone_number_normalizer("4848-823-1") << '\n';


}
