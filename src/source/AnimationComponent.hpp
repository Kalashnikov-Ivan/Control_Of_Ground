#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "stdHeader.hpp"

namespace Components
{
class AnimationComponent
{
public:
	//Constructors
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	~AnimationComponent();

	//Accessors

	//Functions
	void addAnimation(const std::string& key, const float& animation_timer,
					   const int start_x, const int start_y, const int frames_x, const int frames_y,
					   const int width, const int height);

	void play(const std::string& key, const float& dt, const float& modifier = 1.f, const float& max_modifier = 1.f);

private:
	class Animation
	{
	public:
		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, const float& animation_timer,
				  const int start_x, const int start_y, int frames_x, int frames_y,
			      const int width, const int height);
		~Animation();

		//Functions
		void play(const float& dt, const float& modifier = 1.f, const float& max_modifier = 1.f);
		void reset();

		//------------------------------------------------
		//Members
		sf::Sprite& m_sprite;
		sf::Texture& m_texture_sheet;

		float m_animation_timer;
		float m_timer;

		//Size rect
		int m_width, m_height;

		sf::IntRect m_start_rect;
		sf::IntRect m_current_rect;
		sf::IntRect m_end_rect;
	};

	//Members
	sf::Sprite& m_sprite;
	sf::Texture& m_texture_sheet;

	std::map<std::string, Animation*> m_animations;
	Animation* m_last_animation;
};
} // !namespace Components

#endif // !ANIMATION_COMPONENT_H