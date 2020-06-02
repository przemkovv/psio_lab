#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


#include <iostream>
#include <string>

class AnimatedSprite : public sf::Sprite
{
	sf::Texture texture_;
	std::string texture_filename_;
	std::vector<sf::IntRect> frames_cooridnates_;
	std::size_t current_frame_index_ = 0;

public:
	AnimatedSprite(const std::string& texture_filename) : texture_filename_(texture_filename) {
		texture_.loadFromFile(texture_filename);
		setTexture(texture_);


	}

	void add_animation_frame(const sf::IntRect& frame_coordinates) {
		frames_cooridnates_.push_back(frame_coordinates);
		if (frames_cooridnates_.size() == 1)
		{
			setTextureRect(frame_coordinates);
		}

	}

	void step(bool continous_run) {
		{
			++current_frame_index_;
			if (current_frame_index_ == frames_cooridnates_.size())
			{
				if (continous_run) {
					current_frame_index_ = 3;
				}
				else {
					current_frame_index_ = 0;
				}
			}
		}
		if (false)
		{
			current_frame_index_ = (current_frame_index_ + 1) % frames_cooridnates_.size();
		}
		auto nextFrame = frames_cooridnates_[current_frame_index_];

		setTextureRect(nextFrame);


	}

	void  stop() {
		current_frame_index_ = 0;
	}
};
