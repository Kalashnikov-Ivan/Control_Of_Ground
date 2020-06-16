#include "stdHeader.hpp"

#include "Converter.h"

using namespace GUI;

float Converter::calcX(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

float Converter::calcX(const float perc, const sf::Vector2f& size_xy)
{
	return std::floor(static_cast<float>(size_xy.x) * (perc / 100.f));
}

float Converter::calcY(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

float Converter::calcY(const float perc, const sf::Vector2f& size_xy)
{
	return std::floor(static_cast<float>(size_xy.y) * (perc / 100.f));
}

sf::Vector2f Converter::calcVecf(const sf::Vector2f& perc, const sf::VideoMode& vm)
{
	return sf::Vector2f(
		std::floor(static_cast<float>(vm.width)  * (perc.x / 100.f)),
		std::floor(static_cast<float>(vm.height) * (perc.y / 100.f))
	);
}

sf::Vector2f Converter::calcVecf(const sf::Vector2f& perc, const sf::Vector2f& size_xy)
{
	return sf::Vector2f(
		std::floor(static_cast<float>(size_xy.x) * (perc.x / 100.f)),
		std::floor(static_cast<float>(size_xy.y) * (perc.y / 100.f))
	);
}
