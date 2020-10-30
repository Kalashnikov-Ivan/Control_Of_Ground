#ifndef RECT_ANIMATION_COMPONENT_H
#define RECT_ANIMATION_COMPONENT_H

namespace Components
{
class RectAnimationComponent
{
public:
	//Constructors
	RectAnimationComponent(sf::RectangleShape& shape, sf::Texture& textureSheet);
	~RectAnimationComponent();

	//Accessors
	bool IsDone(const std::string& key);

	//Functions
	void AddAnimation(const std::string& key, const float& animationTimer,
		const int start_x, const int start_y, const int frames_x, const int frames_y,
		const int width, const int height);

	bool Play(const std::string& key, const float& dt, const float& modifier = 50.f, const float& maxModifier = 100.f, const bool isPriority = false);

private:
	class Animation
	{
	public:
		Animation(sf::RectangleShape& shape, sf::Texture& textureSheet, const float& animationTimer,
			const int start_x, const int start_y, int frames_x, int frames_y,
			const int width, const int height);
		~Animation();

		//Accessors
		bool IsDone() const;

		//Functions
		bool Play(const float& dt, float modifPercent, const bool isPriority = false);
		void Reset();

		//Members
		sf::RectangleShape& m_shape;
		sf::Texture& m_textureSheet;

		bool  m_isDone;
		float m_animationTimer;
		float m_timer;

		//Size rect
		int m_width, m_height;

		sf::IntRect m_startRect;
		sf::IntRect m_currentRect;
		sf::IntRect m_endRect;
	};

	//Members
	sf::RectangleShape& m_shape;
	sf::Texture& m_textureSheet;

	std::map<std::string, Animation*> m_animations;
	Animation* m_lastAnimation;
	Animation* m_priorityAnimation;
};
} // !namespace Components
#endif // !RECT_ANIMATION_COMPONENT_H