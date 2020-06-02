#pragma once
#include "AnimatedSprite.h"


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <random>

enum class Button
{
	Left,
	Right
};


class Game
{
private:
	std::default_random_engine engine{std::random_device{}()};
private:
	sf::Texture stickyTexture_;
	sf::Sprite stickySprite_;

	AnimatedSprite hero_ = {"data/Character/character.png"};


	sf::RenderWindow& window_;
	sf::Clock clock_;
	const int frames_per_second_ = 30;

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

		sf::Vector2i hero_size = {50, 37};
		sf::Vector2i frame_position = {0, 0};
		for (int frame_index = 0; frame_index < 9; ++frame_index)
		{
			hero_.add_animation_frame(sf::IntRect{frame_position, hero_size});
			frame_position.x += hero_size.x;
		}


		clock_.restart();
	}

	void Draw() {
		window_.draw(stickySprite_);
		window_.draw(hero_);

	}

	void Update() {
		const sf::Time elapsed_time = clock_.getElapsedTime();

		//auto frame_duration = sf::milliseconds(1000.0f / frames_per_second_);
		const auto frame_duration = sf::seconds(1.0f / frames_per_second_);

		if (elapsed_time > frame_duration)
		{
			hero_.step(true);

			clock_.restart();
		}


		// Animate
		// ...

	}

	void MoveCharacter() {
		hero_.stop();

	}

	float Random(float min, float max) {
		std::uniform_real_distribution<float> dis{min, max};
		return dis(engine);
	}

	void SetSeed(unsigned int seed) {
		engine = std::default_random_engine{seed};
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
};
