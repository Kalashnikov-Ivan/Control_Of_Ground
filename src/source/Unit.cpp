#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Unit.hpp"

using namespace cog;

size_t Unit::m_id = 0;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Unit::Unit()
{
}

Unit::~Unit()
{
}


////////////////////////////////////////////////////////////
// Name
////////////////////////////////////////////////////////////
std::string Unit::get_name() const
{
	return m_name;
}
void Unit::set_name(const std::string& name)
{
	m_name = name;
}


////////////////////////////////////////////////////////////
// HP
////////////////////////////////////////////////////////////
double Unit::get_hp() const
{
	return m_hp;
}
void Unit::set_hp(const double hp)
{
	m_hp = hp;
}
void Unit::get_damage(double damage)
{
	m_hp -= damage;
}


////////////////////////////////////////////////////////////
// Power of damage
////////////////////////////////////////////////////////////
double Unit::get_power() const
{
	return m_power;
}
void Unit::set_power(const double power)
{
	m_power = power;
}