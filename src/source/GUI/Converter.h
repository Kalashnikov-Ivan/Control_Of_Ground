#ifndef CONVERTER_H
#define CONVERTER_H

namespace GUI
{
class Converter
{
	Converter() = delete;
	~Converter()
	{}

/*
		 * Converts a percentage value to pixels relative to the current resolution (container size) in the x-axis.
		 *
		 * @param		float perc												The percentage value.
		 * @param		<sf::VideoMode& vm> or <sf::Vector2f& size_xy>			The current videomode of the window (resolution).
		 *
		 * @return		<const float perc> or <const sf::Vector2f& perc>		The calculated pixel value.
 */

	static float calcX(const float perc, const sf::VideoMode& vm);
	static float calcX(const float perc, const sf::Vector2f& size_xy);

	static float calcY(const float perc, const sf::VideoMode& vm);
	static float calcY(const float perc, const sf::Vector2f& size_xy);

	static sf::Vector2f calcVecf(const sf::Vector2f& perc, const sf::VideoMode& vm);
	static sf::Vector2f calcVecf(const sf::Vector2f& perc, const sf::Vector2f& size_xy);
};
} // !namespace GUI
#endif // !CONVERTER_H
