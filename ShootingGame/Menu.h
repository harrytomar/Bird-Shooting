#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Game.h"
#define Max_INDEX 3

class CMenu
{
public:
	sf::Texture m_Texture;
	sf::Music m_music;
	sf::Sprite m_sprite1, m_sprite2;
	/*void InitGame();
	void InitGameOver();*/
	
	CMenu(float width, float height);
	CShooting game;
	~CMenu();
	void Draw(sf::RenderTarget &m_window);
	void MoveUp(); // on pressing up key option will change
	void MoveDown();
	void PollEvent();
	int GetPressedItem()
	{
		return selectedIndex; // index of particular option opted
	}


private:

	int selectedIndex;
	sf::Font font;
	sf::Text menu[Max_INDEX];

};

