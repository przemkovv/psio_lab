#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Game
{
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
		sf::Vector2i stickySize{50, 50};
		std::vector<sf::Vector2i> coordinates{{0, 0}, {0, 50}};
		stickySprite_.setTextureRect({coordinates[1], stickySize});

		stickySprite_.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	}

	void Draw() {
		window_.draw(stickySprite_);

	}
};

int main() {
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	// create some shapes
	sf::CircleShape circle(100.0);
	//circle.setPosition(100.0, 300.0);
	circle.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	circle.setFillColor(sf::Color(100, 250, 50));

	sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
	rectangle.setPosition(500.0, 400.0);
	rectangle.setFillColor(sf::Color(100, 50, 250));

	sf::Vector2f size = {120, 60};
	sf::Vector2f position = {500, 405};
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


		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(circle);
		window.draw(rectangle);
		window.draw(rectangle_rotated, transform);
		window.draw(triangle);
		window.draw(triangle_rotated);

		game.Draw();

		// end the current frame
		window.display();
	}

	return 0;
}
