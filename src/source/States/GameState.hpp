#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.hpp"
#include "GUI/PauseMenu.hpp"

#include "TileMap.hpp"

#include "Entities/Player.hpp"

namespace States
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

	//Tech info
	virtual std::string getStringInfo() override;

	//Update
	virtual void updateEvent(const sf::Event& event) override;
	virtual void update(const float& dt) override;

	virtual void render(sf::RenderTarget& target) override;

private:
	//TileMap
	TileMap m_tile_map;

	//GUI
	GUI::PauseMenu m_pause_menu;

	//Entities
	Entities::Player* m_player;

	//----Functions
	//Init
	virtual void initTextures() override;
	virtual void initKeybinds() override;
			void initPlayers();

	//Update
	virtual void updateInput(const float& dt) override;
			void updatePauseInput(const float& dt);
			void updatePlayerInput(const float& dt);
};
} // !namespace cog
#endif // !GAME_STATE_H