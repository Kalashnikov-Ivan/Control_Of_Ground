#ifndef GAME_STATE_H
#define GAME_STATE_H

namespace cog
{
class GameState : 
	public State
{
public:
	//Constructors
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	//Virtual override
	virtual void update_key_binds(const float& dt) override;
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;

	virtual void end_state() override;

private:

};
} // !namespace cog
#endif // !GAME_STATE_H
