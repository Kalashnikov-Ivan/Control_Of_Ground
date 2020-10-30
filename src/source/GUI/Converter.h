#ifndef CONVERTER_H
#define CONVERTER_H

namespace GUI
{
class Converter
{
public:
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

	static float Сalc(const float perc, const float size);
	static float Сalc(const float perc, const unsigned size);

	static float СalcX(const float perc, const sf::VideoMode& vm);
	static float СalcX(const float perc, const sf::Vector2f& size_xy);

	static float СalcY(const float perc, const sf::VideoMode& vm);
	static float СalcY(const float perc, const sf::Vector2f& size_xy);

	static sf::Vector2f СalcVecf(const sf::Vector2f& perc, const sf::VideoMode& vm);
	static sf::Vector2f СalcVecf(const sf::Vector2f& perc, const sf::Vector2f& size_xy);

/*
	 * Calculates the character size for text using the current resolution and a constant.
	 *
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 * @param		unsigned modifier		Used to modify the character size in a more custom way.
	 *
	 * @return		unsigned				The calculated character size value.
*/

	static const unsigned СalcCharSize(const unsigned modifier, const sf::VideoMode& vm);
	static const unsigned СalcCharSize(const unsigned modifier, const sf::Vector2f& size_xy);
};
} // !namespace GUI
#endif // !CONVERTER_H
