#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.hpp"
#include "Tiles/TileMap.hpp"

#include "GUI/PauseMenu.hpp"

#include "Entities/Player.hpp"

namespace States
{
class GameState : 
	public State
{
public:
//Constructors
	GameState() = delete;
	explicit GameState(StateContext& ctx);
	~GameState();

//Tech info
	std::string GetStringInfo() override;

//Functions
	void UpdateEvent(const sf::Event& event) override;
	void Update(const float& dt) override;

	void Render(sf::RenderTarget& target) override;

	void Reset(const sf::VideoMode& vm) override;

private:
//TileMap
	Tiles::TileMap m_tileMap;

//GUI
	GUI::PauseMenu m_pauseMenu;

//Entities
	std::unique_ptr<Entities::Player> m_player;

//Init
	void InitTextures() override;
	void InitKeybinds() override;
	void InitPlayers();

//Update
	void UpdateInput(const float& dt) override;
	void updatePauseInput(const float& dt);
	void updatePlayerInput(const float& dt);
};
} // !namespace cog
#endif // !GAME_STATE_H