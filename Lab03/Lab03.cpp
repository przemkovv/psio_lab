// Lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <algorithm>
#include <iostream>
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


int main() {

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


	std::vector<int> v{1, 2, 3, 4, 5};
	std::vector<int> v{1, 2, 3, 3, 3, 3, 4, 5};
	std::cout << v;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
