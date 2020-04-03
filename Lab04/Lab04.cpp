// Lab04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <regex>

int main() {

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

	std::string inputText = R"(61-064
email@put.poznan.pl
email@google.com
777-088-00-10
aaa
aa
a)";
	{
		const std::string inputTextSimple = R"(aaa)";

		const std::string regular_expresion = R"(a{3}?)";
		std::regex r(regular_expresion);
		std::cout << "Regex: " << regular_expresion << " " <<
			std::regex_match(inputTextSimple, r) << '\n';
	}
	{
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


}
