#ifndef RECT_ANIMATION_COMPONENT_H
#define RECT_ANIMATION_COMPONENT_H

namespace Components
{
	class RectAnimationComponent
	{
	public:
		//Constructors
		RectAnimationComponent(sf::RectangleShape& shape, sf::Texture& texture_sheet);
		~RectAnimationComponent();

		//Accessors
		bool isDone(const std::string& key);

		//Functions
		void addAnimation(const std::string& key, const float& animation_timer,
			const int start_x, const int start_y, const int frames_x, const int frames_y,
			const int width, const int height);

		bool play(const std::string& key, const float& dt, const float& modifier = 50.f, const float& max_modifier = 100.f, const bool is_priority = false);

	private:
		class Animation
		{
		public:
			Animation(sf::RectangleShape& shape, sf::Texture& texture_sheet, const float& animation_timer,
				const int start_x, const int start_y, int frames_x, int frames_y,
				const int width, const int height);
			~Animation();

			//Accessors
			bool isDone() const;

			//Functions
			bool play(const float& dt, float modif_percent, const bool is_priority = false);
			void reset();

			//------------------------------------------------
			//Members
			sf::RectangleShape& m_shape;
			sf::Texture& m_texture_sheet;

			bool m_is_done;
			float m_animation_timer;
			float m_timer;

			//Size rect
			int m_width, m_height;

			sf::IntRect m_start_rect;
			sf::IntRect m_current_rect;
			sf::IntRect m_end_rect;
		};

		//Members
		sf::RectangleShape& m_shape;
		sf::Texture& m_texture_sheet;

		std::map<std::string, Animation*> m_animations;
		Animation* m_last_animation;
		Animation* m_priority_animation;
	};
} // !namespace Components

#endif // !RECT_ANIMATION_COMPONENT_H