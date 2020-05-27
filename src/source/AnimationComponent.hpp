#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "stdHeader.hpp"

namespace cog
{
class AnimationComponent
{
public:
	//Constructors
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Accessors

	//Functions
	void update(const float& dt);

	void start_animation(const std::string& animation);
	void pause_animation(const std::string& animation);
	void reset_animation(const std::string& animation);

private:
	class Animation
	{
	public:
		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, const float& animation_timer,
				  sf::Vector2i& start_xy, sf::Vector2i& end_xy, sf::Vector2i& size_rect);
		~Animation();

		//Functions
		void update(const float& dt);

		void play();
		void pause();
		void reset();

		//Members
		sf::Sprite& m_sprite;
		sf::Texture& m_texture_sheet;

		float m_animation_timer;
		float m_timer;

		sf::IntRect m_start_rect;
		sf::IntRect m_current_rect;
		sf::IntRect m_end_rect;
		sf::Vector2i m_size_rect;

	private:
	};

	//Members
	sf::Sprite& m_sprite;
	sf::Texture& m_texture_sheet;

	std::map<std::string, Animation*> m_animations;
};
} // !namespace cog

#endif // !ANIMATION_COMPONENT_H