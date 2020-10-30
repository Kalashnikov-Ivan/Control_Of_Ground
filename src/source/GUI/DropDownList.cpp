#include "stdafx.h"

#include "DropDownList.hpp"

using namespace GUI;

//Constructors
DropDownList::DropDownList(sf::Font& mainFont,
						   const sf::Vector2f& pos, const sf::Vector2f& size, size_t chSize,
						   std::vector<std::string>& list, size_t cur_elem)
	: m_activeElem { nullptr }
	, m_isOpen     { false }
{
	m_activeElem = new Button{  pos, size, mainFont, list[cur_elem], chSize,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200), cur_elem 
	};

	//Init list
	for (size_t i = 0; i < list.size(); i++)
	{
		m_list.push_back(
			new Button(
				sf::Vector2f(pos.x, pos.y + ((i+1) * size.y)), size, mainFont, list[i], chSize,
				sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200), i)
		);
	}
}

DropDownList::~DropDownList()
{
	//#TODO: Make smart_ptr
	delete m_activeElem;

	DeleteList();
}

//Accessors
size_t DropDownList::GetActiveElemIndex() const
{
	return m_activeElem->GetIndex();
}

//Support func
void DropDownList::DeleteList()
{
	for (auto& i : m_list)
		delete i;
}

//Modificators
void DropDownList::SetPosition(const sf::Vector2f& pos)
{
	m_activeElem->SetPosition(pos);

	//Update position of elements
	for (size_t i = 0; i < m_list.size(); i++)
		m_list[i]->SetPosition(sf::Vector2f(pos.x, pos.y + ((i + 1) * m_list[i]->getSize().y)));
}

//Info
std::string DropDownList::GetStringInfo()
{
	std::stringstream result;

	if (m_activeElem->GetState() == Button::States::HOVER)
		result << m_activeElem->SetStringInfo();
	else
	{
		for (auto& i : m_list)
			if (i->GetState() == Button::States::HOVER)
				result << i->SetStringInfo();
	}

	return result.str();
}

//Update
void DropDownList::UpdateList(const sf::Vector2f& mousePos, const float& dt)
{
	for (auto& elem : m_list)
	{
		elem->Update(mousePos, dt);

		if (elem->IsPressed())
		{
			m_isOpen = false;
			m_activeElem->SetTextString(elem->GetText().getString());
			m_activeElem->SetIndex(elem->GetIndex());
		}
	}
}

void DropDownList::Update(const sf::Vector2f& mousePos, const float& dt)
{
	m_activeElem->Update(mousePos, dt);

	if (m_isOpen)
		UpdateList(mousePos, dt);

	if (m_activeElem->IsPressed())
	{
		if (m_isOpen)
			m_isOpen = false;
		else
			m_isOpen = true;
	}
}

//Render
void DropDownList::RenderList(sf::RenderTarget& target)
{
	for (auto& i : m_list)
		i->Render(target);
}

void DropDownList::Render(sf::RenderTarget& target)
{
	m_activeElem->Render(target);

	if (m_isOpen)
		RenderList(target);
}

void DropDownList::Reset(const sf::Vector2f& size_wh, const sf::Vector2f& pos, const uint32_t chSize)
{
	m_activeElem->Reset(size_wh, pos, chSize);

	for (size_t i = 0; i < m_list.size(); i++)
	{
		m_list[i]->Reset(size_wh, 
			sf::Vector2f(pos.x, pos.y + ((i + 1) * size_wh.y)),
			chSize
		);
	}
}