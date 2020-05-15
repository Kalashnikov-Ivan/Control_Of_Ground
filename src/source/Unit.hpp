#ifndef UNIT_H
#define UNIT_H

namespace cog
{

class Unit : public sf::Sprite
{
public:

	//Constructors
	Unit();
	Unit(std::string& name, double hp, double power, sf::Texture* texture_ptr);
	~Unit();

	//Name
	std::string get_name() const;
	void set_name(const std::string& name);

	//HP
	double get_hp() const;
	void set_hp(const double hp);

	void get_damage(double damage);

	//Power of damage
	double get_power() const;
	void set_power(const double m_power);

private:
	static size_t m_id;
	sf::Texture* m_texture_ptr;

	std::string m_name;
	double m_hp;
	double m_power;
};

} // namespace cog

#endif // !UNIT_H