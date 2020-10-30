#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

namespace Components
{
class MovementComponent
{
public:
	enum class MovingState { NONE = -1, IDLE = 0, RIGHT, LEFT, DOWN, UP, BREAKING_RIGHT, BREAKING_LEFT};
	enum class SpeedStage  { NONE = 0, FIRST, SECOND, THIRD };

//Constructors
	MovementComponent(sf::Sprite& sprite, const float& maxSpeed, const float& acceleration, const float& deceleration);
	~MovementComponent();

//Accessors
	const float        GetMaxSpeed()   const;
	const sf::Vector2f GetSpeed()      const;
	const sf::Vector2f GetSpeedDir()   const;
	const SpeedStage   GetSpeedStage() const;

	const MovingState GetMovingState() const;

//Info
	std::string GetStringInfo();

//Functions
	void Move(const sf::Vector2f& dir_xy, const float& dt);
	void Update(const float& dt);

private:
	sf::Sprite& m_sprite;

//Speed
	float m_maxSpeed;
	float m_acceleration;
	float m_deceleration;

	sf::Vector2f m_dir_xy;
	sf::Vector2f m_speed;
	sf::Vector2f m_speedDir;
	SpeedStage   m_speedStage;
	MovingState  m_movingState;

	float m_firstSpeedStage;
	float m_secondSpeedStage;
	float m_thirdSpeedStage;

//Functions
	inline void UpdateSpeedDir();
	inline void UpdateSpeedStage();
	inline void UpdateState();

//Support functions
	//inline void acceleration(const sf::Vector2f& dir_xy);
	inline void Deceleration();

	inline void MaxSpeedCheck();
};
} // !namespace Components
#endif // !MOVEMENT_COMPONENT_H