#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include <iostream>
#include <random>
#include <thread>
#include <chrono>


enum class Button
{
	Left,
	Right
};


class Game
{
private:
	std::default_random_engine engine{ std::random_device{}() };
private:
	sf::Texture stickyTexture_;
	sf::Sprite stickySprite_;

	sf::RenderWindow& window_;

public:


	Game(sf::RenderWindow& window) : window_(window) {
		stickyTexture_.loadFromFile("data/sticky2.png");
		//stickySprite_.setSize({
		//	static_cast<float>(stickyTexture_.getSize().x),
		//	static_cast<float>(stickyTexture_.getSize().y)
		//});
		stickySprite_.setTexture(stickyTexture_);
		sf::Vector2i stickySize{ 50, 50 };
		std::vector<sf::Vector2i> coordinates{ {0, 0}, {0, 50} };
		stickySprite_.setTextureRect({ coordinates[1], stickySize });

		stickySprite_.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	}

	void Draw() {
		window_.draw(stickySprite_);

	}

	float Random(float min, float max) {
		std::uniform_real_distribution<float> dis{ min, max };
		return dis(engine);
	}

	void SetSeed(unsigned int seed) {
		engine = std::default_random_engine{ seed };
	}

	void OnMouseClick(const sf::Vector2i& mouse_position, Button button) {
		//struct Shape
		//{
		//	sf::Vector2f size;
		//	sf::Vector2f position;

		//	bool contains(const sf::Vector2i& point) {
		//		if (point.x >= position.x
		//			&& point.y >= position.y
		//			&& point.x <= position.x + size.x
		//			&& point.y <= position.y + size.y
		//			) {
		//			return true;
		//		}
		//		return false;
		//	}
		//};
		std::vector<sf::RectangleShape> rectangles{};
		for (auto rect : rectangles)
		{
			if (rect.getGlobalBounds().contains(static_cast<float>(mouse_position.x),
				static_cast<float>(mouse_position.y)))
			{
				rect.setFillColor({});
			}
		}

	}

	void Update() {

		// Animate
		// ...

	}
};


struct Foo
{
	int bar() { return 42; }


	int operator()() {
		return 42;
	}

	int operator()(int x) {
		return 42 + x;
	}

	int operator+() {
		return 42;
	}
};

class CustomRectangleShape : public sf::RectangleShape
{
	sf::Vector2f position_;
public:
	CustomRectangleShape(const sf::Vector2f& size, const sf::Vector2f& position)
		: sf::RectangleShape(size), position_(position) {
		setPosition(position_);
		/*
		size_ = size;
		position_ = position;
		*/

		// ... computations ...
	}
};

int main() {

	if constexpr (false)
	{
		{
			std::random_device rd{};
			std::uniform_int_distribution<int> dis{ 0, 100 };
			auto newRandomValue = dis(rd);
			std::cout << "Non-deterministic random value: " << newRandomValue << '\n';
		}
		{
			std::mt19937_64 mt{ 0 };
			std::uniform_int_distribution<int> dis{ 0, 100 };
			auto newRandomValue = dis(mt);
			std::cout << "Static seed equal to 0: " << newRandomValue << '\n';
		}
		{
			std::random_device rd{};
			std::mt19937_64 mt{ rd() };
			std::uniform_int_distribution<int> dis{ 0, 100 };
			auto newRandomValue = dis(mt);
			std::cout << "Deterministic random value: " << newRandomValue << '\n';
		}
	}
	if constexpr (false)
	{
		Foo foo;
		foo.bar();
		auto b1 = foo();

		Foo foo1{};
		foo1.bar();
		auto b2 = foo(4);

		auto b3 = Foo{}.bar();
		auto b4 = Foo{}();
	}

	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	if constexpr (true)
	{
		std::vector<CustomRectangleShape> rectangles;
		const int N = 10;
		for (int index = 0; index < N; ++index)
		{
			rectangles.emplace_back(CustomRectangleShape{
				{0.0f, 1.0f},
				{4.0f, index * 3.0f}
				});
		}

		for (const auto& rectangle : rectangles)
		{
			window.draw(rectangle);

		}

		sf::Vector2f size(120.0, 60.0);
		sf::Vector2f position(120.0, 60.0);
		CustomRectangleShape my_rectangle(size, position);
	}


	// create some shapes
	sf::CircleShape circle(100.0);
	//circle.setPosition(100.0, 300.0);
	circle.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	circle.setFillColor(sf::Color(100, 250, 50));

	sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
	rectangle.setPosition(500.0, 400.0);
	rectangle.setFillColor(sf::Color(100, 50, 250));

	sf::Vector2f size = { 120, 60 };
	sf::Vector2f position = { 500, 405 };
	sf::RectangleShape rectangle_rotated(size);
	rectangle_rotated.setFillColor(sf::Color(10, 250, 250));
	rectangle_rotated.setPosition(position + size / 2.0f);
	rectangle_rotated.setOrigin(rectangle_rotated.getSize() / 2.0f);

	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
	triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
	triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
	triangle.setOutlineColor(sf::Color::Red);
	triangle.setOutlineThickness(5);
	triangle.setPosition(600.0, 100.0);

	sf::ConvexShape triangle_rotated;
	triangle_rotated.setPointCount(3);
	triangle_rotated.setPoint(0, sf::Vector2f(0.0, 0.0));
	triangle_rotated.setPoint(1, sf::Vector2f(0.0, 100.0));
	triangle_rotated.setPoint(2, sf::Vector2f(140.0, 40.0));
	triangle_rotated.setOutlineColor(sf::Color::Red);
	triangle_rotated.setOutlineThickness(5);
	triangle_rotated.setPosition(
		triangle.getLocalBounds().width / 2.0f + 600.0f,
		triangle.getLocalBounds().height / 2.0f + 100.0f);
	triangle_rotated.setOrigin(
		triangle.getLocalBounds().width / 2.0f,
		triangle.getLocalBounds().height / 2.0f);


	//transform.translate(-offset);
	//transform.rotate(0.0f);
	//transform.translate(offset);
	//transform.translate(size / 2.0f);

	Game game(window);

	game.SetSeed(42);
	for (int i = 0; i < 30; ++i)
	{
		std::cout << '\r' << game.Random(0, 1);
		using namespace std::chrono_literals;
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		//std::this_thread::sleep_for(1s);
	}
	std::cout << '\n';
	game.SetSeed(42);
	for (int i = 0; i < 30; ++i)
	{
		std::cout << game.Random(1, 6) << '\n';
	}
	std::cout << '\n';
	game.SetSeed(0);
	for (int i = 0; i < 30; ++i)
	{
		std::cout << game.Random(1, 6) << '\n';
	}
	std::cout << '\n';
	game.SetSeed(std::random_device{}());
	for (int i = 0; i < 30; ++i)
	{
		std::cout << game.Random(1, 6) << '\n';
	}
	//return 0;
	/*
	{
		float x = 2.1f;
		float y = 0.3f + 0.7f + 0.4f;// +0.7f;

		float z = 0.0f;
		std::cin >> z;
		std::cout << (x == z+y) << '\n';


		return 0;
	}
	*/

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Transform transform;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
			game.OnMouseClick(mouse_position, Button::Left);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			rectangle_rotated.rotate(1);

			auto offset = position - size / 2.0f;
			triangle_rotated.rotate(1);
			transform.translate(-offset);
			transform.rotate(1.0f);

			//transform.translate(offset);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//rectangle_rotated.rotate(-1);
			triangle_rotated.rotate(-1);
			transform.rotate(-1.0f);
			//transform.translate(-offset);
		}

		game.Update();

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(circle);
		window.draw(rectangle);
		window.draw(rectangle_rotated, transform);
		window.draw(triangle);
		window.draw(triangle_rotated);

		std::cout << "straight: " << rectangle.getGlobalBounds().height << " " << rectangle.getGlobalBounds().width <<
			'\n';
		std::cout << "straight: " << rectangle_rotated.getGlobalBounds().height << " " << rectangle_rotated
			.getGlobalBounds().width <<
			'\n';
		game.Draw();


		// end the current frame
		window.display();
	}

	return 0;
}
