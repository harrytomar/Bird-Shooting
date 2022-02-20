#include "Menu.h"
#include"Game.h"
#include<iostream>
#include<SFML/Graphics.hpp>

CMenu::CMenu(float width, float height) // this is the menu function
{
	m_Texture.loadFromFile("brick.png");

	sf::Vector2u size = m_Texture.getSize();
	m_sprite1.setTexture(m_Texture);
	m_sprite1.setScale(1200 / m_sprite1.getGlobalBounds().width, 800 / m_sprite1.getGlobalBounds().height); // background will cover the whole window
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(1150 / 2, height / (Max_INDEX + 1) * 1));


	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(1100 / 2, height / (Max_INDEX + 1) * 2));


	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(1150 / 2, height / (Max_INDEX + 1) * 3));

	selectedIndex = 0;
}


CMenu::~CMenu()
{
}

void CMenu::Draw(sf::RenderTarget &window) // draw the menu on the window
{
	window.draw(m_sprite1);
	
	for (int i = 0; i < Max_INDEX; i++)
	{
		window.draw(menu[i]);
	}
	
	
}

void CMenu::MoveUp() // if we press up key it will reach to the destination text
{
	
	if (selectedIndex - 1 >= 0)
	{
		if (!m_music.openFromFile("menuclick.wav"))
			return; // error
		m_music.play();
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setFillColor(sf::Color::Red);
	}
	else
	{
		if (!m_music.openFromFile("menuclick.wav"))
			return; // error
		m_music.play();
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex=2;
		menu[selectedIndex].setFillColor(sf::Color::Red);
	}
	
}

void CMenu::MoveDown()
{
	
	if (selectedIndex + 1 < Max_INDEX)
	{
		if (!m_music.openFromFile("menuclick.wav"))
			return; // error
		m_music.play();
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setFillColor(sf::Color::Red);
	}
	else
	{
		if (!m_music.openFromFile("menuclick.wav"))
			return; // error
		m_music.play();
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex=0;
		menu[selectedIndex].setFillColor(sf::Color::Red);
	}
}

void CMenu::PollEvent()
{
	while (game.m_window->isOpen())
	{
		sf::Event event;

		while (game.m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					//Sleep(500);
					break;

				case sf::Keyboard::Down:
					MoveDown();
					//Sleep(500);
					break;

				case sf::Keyboard::Return: // if we press enter

					switch (GetPressedItem()) // it will return the pressed item index
					{
					case 0:

						game.InitBackGround1();
						while (game.isRunning() && !game.m_isGameOver) // game will continue untill windows closed
						{

							game.UpdateDt();
							game.Update();
							game.Render();

						}
						
						break;


					case 1:
						std::cout << "*************************************\n";
						std::cout << "*************************************\n";
						std::cout << "Use F1 to save the Game\n";

						std::cout << "Use F2 to Load the Prev game\n";
						std::cout << "*************************************\n";
						std::cout << "*************************************\n";
						break;
						
					case 2:
						game.m_window->close();
						return;
					
						
					}

					break;
				}

				break;
			case sf::Event::Closed:
				game.m_window->close();
				return;
			

			}
		}

		game.m_window->clear();
		Draw(*game.m_window);

		game.m_window->display();
	}

	CMenu menu(1000.f, 800.f); // call the menu constructor which initialise the menu window

	menu.PollEvent();
}
