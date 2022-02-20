//#include "Game.h"
//#include<iostream>
//#include<chrono>
//#include<fstream>
//#include<Thread>
//CShooting::CShooting()
//{
//	InitWindow(); // initalise the window
//	InitPlayer();
//	InitGrass();
//	InitLeftBirds();
//	InitRightBirds();
//	InitVariable();
//
//
//
//
//
//}
//void CShooting::InitFire()
//{
//	m_fire.loadFromFile("fire2.png");
//	m_fireSprite.setTexture(m_fire);
//
//	m_fireSprite.setScale(0.08, 0.08);
//	m_fireSprite.setPosition(m_playerSprite.getPosition().x, m_playerSprite.getPosition().y);
//
//	m_fireVec.push_back(m_fireSprite);
//
//}
//
//void CShooting::InitVariable()
//{
//	m_font.loadFromFile("arial.ttf"); // load the ttf file so that we can set the style of text
//
//	m_PlayerScore.setFont(m_font);
//	m_PlayerScore.setCharacterSize(20);
//	m_PlayerScore.setFillColor(sf::Color::Green);
//	m_PlayerScore.setStyle(sf::Text::Bold);
//	m_PlayerScore.setPosition(1000.f, 10.f);
//}
//
//
//
//
//void CShooting::InitWindow()
//{
//	m_window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Shooting", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
//	m_window->setFramerateLimit(60);
//}
//
//void CShooting::InitBackGround1()
//{
//	m_shoot.loadFromFile("shooting.png");
//
//	sf::Vector2u size = m_shoot.getSize();
//	m_backgroundSprite.setTexture(m_shoot);
//	//m_sprite1.setOrigin(size.x/3, size.y/3);
//	m_backgroundSprite.setPosition(150.f, 100.f);
//	m_backgroundSprite.setScale(800 / m_backgroundSprite.getGlobalBounds().width, 500 / m_backgroundSprite.getGlobalBounds().height); // background will cover the whole window
//	m_window->clear();
//	m_window->draw(m_backgroundSprite);
//	m_window->display();
//	Sleep(2000);
//}
//
//
//
//void CShooting::PollEvent()
//{
//
//	// poll events to left and right paddle and save and load game 
//	while (m_window->pollEvent(m_event))
//	{
//		switch (m_event.type)
//		{
//		case sf::Event::Closed:
//			m_window->close();
//			break;
//		case sf::Event::KeyPressed: // if any key pressed this case executes
//			if (m_event.key.code == sf::Keyboard::Escape)
//			{
//				m_window->close();
//			}
//			if (m_event.key.code == sf::Keyboard::Right || m_event.key.code == sf::Keyboard::D)
//			{
//
//				m_playerSprite.move(sf::Vector2f(15.f, 0.f));
//				m_playerx++;
//				m_playerx = m_playerx % 10;
//				m_playerSprite.setTextureRect(sf::IntRect(m_playerx * 120, 910, 120, 130));
//				if (!m_music.openFromFile("walk3.wav"))
//					return; // error
//				m_music.play();
//
//
//			}
//			if (m_event.key.code == sf::Keyboard::Left || m_event.key.code == sf::Keyboard::A)
//			{
//				m_playerSprite.move(sf::Vector2f(-15.f, 0.f));
//				m_playerx++;
//				m_playerx = m_playerx % 10;
//				m_playerSprite.setTextureRect(sf::IntRect(m_playerx * 120, 650, 120, 130));
//				if (!m_music.openFromFile("walk3.wav"))
//					return; // error
//				m_music.play();
//			}
//
//			if (m_event.key.code == sf::Keyboard::Up || m_event.key.code == sf::Keyboard::W)
//			{
//				//m_sprite2.move(sf::Vector2f(0.f, -5.f));
//				m_playerx++;
//				m_playerx = m_playerx % 10;
//				m_playerSprite.setTextureRect(sf::IntRect(m_playerx * 120, 780, 120, 130));
//				if (!m_music.openFromFile("walk2.wav"))
//					return; // error
//				m_music.play();
//			}
//			//if (m_event.key.code == sf::Keyboard::Down)
//			//{
//			//	m_sprite2.move(sf::Vector2f(0.f, 5.f));
//			//	m_playerx++;
//			//	m_playerx = m_playerx % 10;
//			//	m_sprite2.setTextureRect(sf::IntRect(m_playerx * 120, 520, 120, 130));
//			//	if (!m_music.openFromFile("walk2.wav"))
//			//		return; // error
//			//	m_music.play();
//			//}
//			break;
//		case sf::Event::KeyReleased:
//			if (m_event.key.code == sf::Keyboard::Right)
//			{
//				m_music.pause();
//			}
//			break;
//		case sf::Event::MouseButtonPressed:
//			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//			{
//				InitFire();
//				if (!m_music.openFromFile("gun.wav"))
//					return; // error
//				m_music.play();
//				m_localPosition = sf::Mouse::getPosition(*m_window);
//				//std::cout << m_localPosition.x << " " << m_localPosition.y << "\n";
//				FireMove(m_localPosition);
//
//			}
//
//
//
//		}
//	}
//}
//
//void CShooting::InitGrass()
//{
//	m_grass.loadFromFile("grass.png");
//
//	sf::Vector2u size = m_grass.getSize();
//	m_grassSprite.setTexture(m_grass);
//	//m_sprite1.setOrigin(size.x/3, size.y/3);
//	m_grassSprite.setPosition(0.f, 400.f);
//	m_grassSprite.setScale(1200 / m_grassSprite.getGlobalBounds().width, 500 / m_grassSprite.getGlobalBounds().height); // background will cover the whole window
//
//}
//
//void CShooting::CheckBoundariesForPlayer()
//{
//	if (m_playerSprite.getPosition().x < 0)
//	{
//		m_playerSprite.setPosition(0.f, m_playerSprite.getPosition().y);
//	}
//	if (m_playerSprite.getPosition().x + m_playerSprite.getGlobalBounds().width > m_window->getSize().x)
//	{
//		m_playerSprite.setPosition(m_window->getSize().x - m_playerSprite.getGlobalBounds().width, m_playerSprite.getPosition().y);
//	}
//}
//
//void CShooting::InitLeftBirds()
//{
//	m_leftBird.loadFromFile("Rbird.png");
//	m_leftBirdSprite.setTexture(m_leftBird);
//	m_leftBirdSprite.setScale(1, 1);
//	m_leftBirdSprite.setPosition(0, rand() % 400);
//
//	m_bomb.loadFromFile("bomb.png");
//	m_leftbombSprite.setTexture(m_bomb);
//	m_leftbombSprite.setScale(-0.1, 0.1);
//	m_leftbombSprite.setPosition(m_leftBirdSprite.getPosition().x, m_leftBirdSprite.getPosition().y);
//	m_rightBirdCount--;
//	if (m_rightBirdCount < 0)
//	{
//		m_leftBirdSprite.setTextureRect(sf::IntRect(100, 92, 100, 92));
//		m_leftbirdsVec.push_back(std::make_pair(m_leftBirdSprite, m_leftbombSprite));
//
//		m_rightBirdCount = rand() % 60 + 40;
//	}
//
//}
//
//void CShooting::InitRightBirds()
//{
//	m_rightBird.loadFromFile("Rbird.png");
//	m_rightBirdSprite.setTexture(m_rightBird);
//	m_rightBirdSprite.setScale(-1, 1);
//	m_rightBirdSprite.setPosition(m_window->getSize().x, rand() % 400);
//
//
//	m_bomb.loadFromFile("bomb.png");
//	m_rightbombSprite.setTexture(m_bomb);
//	m_rightbombSprite.setScale(0.1, 0.1);
//	m_rightbombSprite.setPosition(m_rightBirdSprite.getPosition().x, m_rightBirdSprite.getPosition().y);
//
//
//	m_leftBirdCount--;
//
//	if (m_leftBirdCount < 0)
//	{
//
//		m_rightBirdSprite.setTextureRect(sf::IntRect(100, 92, 100, 92));
//		m_rightbirdsVec.push_back(std::make_pair(m_rightBirdSprite, m_rightbombSprite));
//		m_leftBirdCount = rand() % 40 + 50;
//
//	}
//
//}
//
//void CShooting::MoveLeftBird()
//{
//	m_leftBirdx++;
//	m_leftBirdx = m_leftBirdx % 5;
//	if (m_leftBirdx == 0)
//	{
//		m_leftBirdy++;
//		m_leftBirdy = m_leftBirdy % 3;
//	}
//
//	for (int i = 0; i < m_leftbirdsVec.size(); i++)
//	{
//		m_leftbirdsVec[i].first.setTextureRect(sf::IntRect(100 * m_leftBirdx, 92 * m_leftBirdy, 100, 92));
//
//
//
//	}
//}
//
//void CShooting::MoveRightBird()
//{
//	m_rightBirdx++;
//	m_rightBirdx = m_rightBirdx % 5;
//	if (m_rightBirdx == 0)
//	{
//		m_rightBirdy++;
//		m_rightBirdy = m_rightBirdy % 3;
//	}
//
//	for (int i = 0; i < m_rightbirdsVec.size(); i++)
//	{
//		m_rightbirdsVec[i].first.setTextureRect(sf::IntRect(100 * m_rightBirdx, 92 * m_rightBirdy, 100, 92));
//
//
//
//	}
//}
//
//void CShooting::FireMove(sf::Vector2i m_localPosition)
//{
//	m_dir = sqrt(pow((m_playerSprite.getPosition().x - m_localPosition.x), 2) + pow((m_playerSprite.getPosition().y - m_localPosition.y), 2));
//	// std::cout << m_dir << "\n";
//	// std::cout << m_localPosition.x << " " << m_localPosition.y << "\n";
//	// std::cout << m_sprite2.getPosition().x << " " << m_sprite2.getPosition().y << "\n";
//	m_x = (m_localPosition.x - m_playerSprite.getPosition().x) / m_dir;
//	m_y = (m_localPosition.y - m_playerSprite.getPosition().y) / m_dir;
//	sf::Vector2f vec;
//	vec.x = m_x;
//	vec.y = m_y;
//	m_unitVec.push_back(vec);
//	//std::cout << m_x <<" "<< m_y << "\n";
//}
//
//
//
//
//
//void CShooting::UpdateDt()
//{
//	m_dt = dtClock.restart().asSeconds(); // the the frame time in seconds
//}
//
//void CShooting::InitPlayer()
//{
//	m_player.loadFromFile("player2.png");
//
//	sf::Vector2u size = m_player.getSize();
//	m_playerSprite.setTexture(m_player);
//	m_playerSprite.setTextureRect(sf::IntRect(0, 0, 120, 130));
//	//m_sprite1.setOrigin(size.x/3, size.y/3);
//	m_playerSprite.setPosition(m_window->getSize().x / 2.f, 670.f);
//	//m_sprite2.setScale(800 / m_sprite1.getGlobalBounds().width, 500 / m_sprite1.getGlobalBounds().height); // background will cover the whole window
//
//
//}
//
//void CShooting::CheckCollisionBombWithBird()
//{
//	for (int i = 0; i < m_fireVec.size(); i++)
//	{
//		for (int j = 0; j < m_leftbirdsVec.size(); j++)
//		{
//			if (m_fireVec[i].getGlobalBounds().intersects(m_leftbirdsVec[j].first.getGlobalBounds()))
//			{
//				m_fireVec.erase(m_fireVec.begin() + i);
//				m_unitVec.erase(m_unitVec.begin() + i);
//				m_leftbirdsVec.erase(m_leftbirdsVec.begin() + j);
//				m_playerScore++;
//			}
//		}
//	}
//
//	for (int i = 0; i < m_fireVec.size(); i++)
//	{
//		for (int j = 0; j < m_rightbirdsVec.size(); j++)
//		{
//			if (m_fireVec[i].getGlobalBounds().intersects(m_rightbirdsVec[j].first.getGlobalBounds()))
//			{
//				m_fireVec.erase(m_fireVec.begin() + i);
//				m_unitVec.erase(m_unitVec.begin() + i);
//				m_rightbirdsVec.erase(m_rightbirdsVec.begin() + j);
//				m_playerScore++;
//			}
//		}
//	}
//
//}
//
//void CShooting::Update()
//{
//
//	PollEvent();
//
//	InitLeftBirds();
//	InitRightBirds();
//	MoveLeftBird();
//	MoveRightBird();
//	//InitBomb();
//	for (int i = 0; i < m_leftbirdsVec.size(); i++)
//	{
//		if (m_leftbirdsVec[i].first.getPosition().x > m_window->getSize().x + 250.f)
//		{
//			m_leftbirdsVec.erase(m_leftbirdsVec.begin() + i);
//
//		}
//	}
//	for (int i = 0; i < m_rightbirdsVec.size(); i++)
//	{
//		if (m_rightbirdsVec[i].first.getPosition().x < -250.f)
//		{
//			m_rightbirdsVec.erase(m_rightbirdsVec.begin() + i);
//		}
//	}
//
//	for (int i = 0; i < m_fireVec.size(); i++)
//	{
//		if (m_fireVec[i].getPosition().x < 0 || m_fireVec[i].getPosition().y<0 || m_fireVec[i].getPosition().x > m_window->getSize().x)
//		{
//			m_fireVec.erase(m_fireVec.begin() + i);
//			m_unitVec.erase(m_unitVec.begin() + i);
//		}
//	}
//
//	std::cout << m_leftbirdsVec.size() << " " << m_rightbirdsVec.size() << "\n";
//	//std::cout <<m_leftbombVec.size() << " "<< m_rightbombVec.size()<<"\n";
//
//	CheckBoundariesForPlayer();
//	CheckCollisionBombWithBird();
//
//
//}
//
//void CShooting::Render() // this function is to draw everything per frame happening 
//{
//	m_window->clear();
//	m_window->draw(m_grassSprite);
//	m_window->draw(m_playerSprite);
//	for (int i = 0; i < m_leftbirdsVec.size(); i++)
//	{
//		m_leftbirdsVec[i].first.move(20.f, 0.f);
//		m_leftbirdsVec[i].second.move(20.f, 0.f);
//		m_window->draw(m_leftbirdsVec[i].first);
//		m_window->draw(m_leftbirdsVec[i].second);
//	}
//	for (int i = 0; i < m_rightbirdsVec.size(); i++)
//	{
//		m_rightbirdsVec[i].first.move(-20.f, 0.f);
//		m_rightbirdsVec[i].second.move(-20.f, 0.f);
//		m_window->draw(m_rightbirdsVec[i].first);
//		m_window->draw(m_rightbirdsVec[i].second);
//	}
//
//	for (int i = 0; i < m_fireVec.size(); i++)
//	{
//		m_fireVec[i].move(200.f*m_unitVec[i].x, 200.f*m_unitVec[i].y);
//		m_window->draw(m_fireVec[i]);
//	}
//	m_PlayerScore.setString("Score : " + std::to_string(m_playerScore));
//	m_window->draw(m_PlayerScore);
//	m_window->display();
//}
//
//
//
//
//// this function will return whether window in opened or not
//const bool CShooting::isRunning() const
//{
//	return m_window->isOpen();
//}
