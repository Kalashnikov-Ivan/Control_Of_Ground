#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

namespace Components
{
class MovementComponent
{
public:
	enum class MovingStates { NONE = -1, IDLE = 0, RIGHT, LEFT, DOWN, UP, BREAKING_RIGHT, BREAKING_LEFT};
	enum class SpeedStages  { NONE = 0, FIRST, SECOND, THIRD };

	//Constructors
	MovementComponent(sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration);
	~MovementComponent();

	//Accessors
		//Speed
			const float        getMaxSpeed() const;
			const sf::Vector2f getSpeed() const;
			const sf::Vector2f getSpeedDir() const;
			const SpeedStages  getSpeedStage() const;
		//State
			const MovingStates getMovingState() const;

	//Info
		std::string getStringInfo();

	//Functions
		void move(const sf::Vector2f& dir_xy, const float& dt);
		void update(const float& dt);

private:
	//Members
		sf::Sprite& m_sprite;

	//Speed
		float m_max_speed;
		float m_acceleration;
		float m_deceleration;

		sf::Vector2f m_dir_xy;
		sf::Vector2f m_speed;
		sf::Vector2f m_speed_dir;
		SpeedStages  m_speed_stage;
		MovingStates m_moving_state;

		float m_first_speed_stage;
		float m_second_speed_stage;
		float m_third_speed_stage;

	//Functions
		inline void updateSpeedDir();
		inline void updateSpeedStage();
		inline void updateState();

	//Support functions
		//inline void acceleration(const sf::Vector2f& dir_xy);
		inline void deceleration();

		inline void maxSpeedCheck();
		
};
} // !namespace Components

#endif // !MOVEMENT_COMPONENT_H