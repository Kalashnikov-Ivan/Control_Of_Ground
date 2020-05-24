#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.hpp"
#include "Player.hpp"

namespace cog
{
class GameState : 
	public State
{
public:
	//Constructors
	GameState() = delete;
	GameState(sf::RenderWindow& window,
			  std::stack<State*>& states,
			  std::map<const std::string, sf::Font*>& supported_fonts,
			  const std::map<const std::string, int>& supported_keys);
	virtual ~GameState();

	//Update
	virtual void update_keyboard_input(const float& dt) override;
	virtual void update(const float& dt) override;

	virtual void render(sf::RenderTarget* target = nullptr) override;

private:
	//Entities
	Player* m_player;

	//----Functions
	//Init
	virtual void init_textures() override;
	virtual void init_keybinds() override;
			void init_players();
};
} // !namespace cog
#endif // !GAME_STATE_H