#ifndef GAME_STATE_H
#define GAME_STATE_H

namespace cog
{
//class Entity;

class GameState : 
	public State
{
public:
	//Constructors
	GameState(sf::RenderWindow* window, std::map<const std::string, int>* supported_keys);
	virtual ~GameState();

	//Virtual override
	virtual void update_input(const float& dt) override;
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;

	virtual void end_state() override;

private:
	//Entities
	Entity m_player;

	//----Functions
	//Init
	virtual void init_keybinds() override;
};
} // !namespace cog
#endif // !GAME_STATE_H