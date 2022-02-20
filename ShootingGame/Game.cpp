#include "Game.h"
#include<iostream>
#include<chrono>
#include<fstream>
#include<Thread>
#include"flatbuffers/flatbuffers.h"
#include"schema_generated.h"
CShooting::CShooting() // initialise the necessary functions
{
	InitWindow(); // initalise the window
	InitPlayer1();// init the player on the screen
	InitGrass();// init the grass like platform on the screen 
	InitLeftBirds();// initialise the left bird coming from left
	InitRightBirds();// initialise the right bird coming from right
	InitVariable(); // initialise the text on the window
	InitSniper();
	InitGameOver();
	
}

void CShooting::InitSniper()
{
	m_sniper.loadFromFile("sniperscope.png");
	m_sniperSprite.setTexture(m_sniper);

	m_sniperSprite.setScale(0.1, 0.1);
	m_sniperSprite.setPosition(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);

}

void CShooting::InitGameOver()
{
	m_gameOver.loadFromFile("gameOver.png");

	sf::Vector2u size = m_gameOver.getSize();
	m_gameOverSprite.setTexture(m_gameOver);
	//m_sprite1.setOrigin(size.x/3, size.y/3);
	m_gameOverSprite.setPosition(100.f, 0.f);
	m_gameOverSprite.setScale(1000 / m_gameOverSprite.getGlobalBounds().width, 800 / m_gameOverSprite.getGlobalBounds().height); // background will cover the whole window
}

void CShooting::InitFire() // initialise the fire bomb which the player will shot
{
	m_fire.loadFromFile("fire2.png");
	m_fireSprite.setTexture(m_fire);
	
	m_fireSprite.setScale(0.08, 0.08);
	m_fireSprite.setPosition(m_playerSprite.getPosition().x,m_playerSprite.getPosition().y);

	m_fireVec.push_back(m_fireSprite);
	
}

void CShooting::InitVariable() // initialise the score,player turn number in text form  on screen 
{
	m_font.loadFromFile("arial.ttf"); // load the ttf file so that we can set the style of text

	m_Player1Score.setFont(m_font);
	m_Player1Score.setCharacterSize(20);
	m_Player1Score.setFillColor(sf::Color::Green);
	m_Player1Score.setStyle(sf::Text::Bold);
	m_Player1Score.setPosition(1000.f, 10.f);


	m_Player2Score.setFont(m_font);
	m_Player2Score.setCharacterSize(20);
	m_Player2Score.setFillColor(sf::Color::Green);
	m_Player2Score.setStyle(sf::Text::Bold);
	m_Player2Score.setPosition(1000.f, 30.f);

	m_PlayerTurn.setFont(m_font);
	m_PlayerTurn.setCharacterSize(20);
	m_PlayerTurn.setFillColor(sf::Color::Red);
	m_PlayerTurn.setStyle(sf::Text::Bold);
	m_PlayerTurn.setPosition(m_playerSprite.getPosition().x, m_playerSprite.getPosition().y-10.f);
}

void CShooting::InitLeftBomb() // initialise the bomb hold by left bird
{
	m_bomb.loadFromFile("bomb.png");
	m_bombSprite.setTexture(m_bomb);
	m_bombSprite.setScale(-0.1, 0.1);
	m_bombSprite.setPosition(m_leftBirdSprite.getPosition().x + 40.f, m_leftBirdSprite.getPosition().y + 50.f);
	m_leftbombVec.push_back(m_bombSprite);
}

void CShooting::InitRightBomb() // initialise the bomb hold by right bird
{
	m_bomb.loadFromFile("bomb.png");
	m_bombSprite.setTexture(m_bomb);
	m_bombSprite.setScale(0.1, 0.1);
	m_bombSprite.setPosition(m_rightBirdSprite.getPosition().x - 40.f, m_rightBirdSprite.getPosition().y + 50.f);
	m_rightbombVec.push_back(m_bombSprite);
}




void CShooting::InitWindow() // initialise the game window
{
	m_window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Shooting", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	m_window->setFramerateLimit(60);
}

void CShooting::InitBackGround1() // initialise the background image for 2 sec
{
	m_shoot.loadFromFile("shooting.png");

	sf::Vector2u size = m_shoot.getSize();
	m_backgroundSprite.setTexture(m_shoot);
	//m_sprite1.setOrigin(size.x/3, size.y/3);
	m_backgroundSprite.setPosition(150.f, 100.f);
	m_backgroundSprite.setScale(800 / m_backgroundSprite.getGlobalBounds().width, 500 / m_backgroundSprite.getGlobalBounds().height); // background will cover the whole window
	m_window->clear();
	m_window->draw(m_backgroundSprite);
	m_window->display();
	Sleep(2000);
}

void CShooting::SaveGame() // will svave the game state
{
	std::cout << "Saving of Data is Processing....\n";
	flatbuffers::FlatBufferBuilder builder(1024);

	//Saving paddle Positions
	auto player1 = pos(m_playerSprite.getPosition().x, m_playerSprite.getPosition().y);
	//saving paddles scores
	auto player1Score = GetPlayer1Score();
	auto player2Score = GetPlayer2Score();
	auto playerTurn = GetPlayerTurn();
	// saving ball position


	auto contents = Createcontents(builder, &player1, player1Score, player2Score, playerTurn);
	builder.Finish(contents); //Wrapping everything into a table

	// open the file and saved the data
	uint8_t* buff = builder.GetBufferPointer();
	int bufferSize = builder.GetSize();
	std::ofstream fp;
	fp.open("SavedFile.bin", std::ios::out | std::ios::binary);
	fp.write((char*)buff, bufferSize);


	std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(2));
	std::cout << "Data Saved Successfully !\n";
}

void CShooting::LoadGame() // load the prev game state which we saved earlier
{ 
	std::cout << "Loading Saved Data...\n";

	//Getting/loading the contents of the file
	std::ifstream file;
	file.open("SavedFile.bin", std::ios::binary | std::ios::in);
	file.seekg(0, std::ios::end);
	int length = file.tellg();
	file.seekg(0, std::ios::beg);
	char* data = new char[length];
	file.read(data, length);
	file.close();
	auto readContents = Getcontents(data);





	//Setting important variables to the loaded values from the saved files 
	m_playerSprite.setPosition(readContents->playerPos()->x(), readContents->playerPos()->y());
	m_player1Score = readContents->Player1Score();
	m_player2Score = readContents->Player2Score();
	m_playerTurn = readContents->PlayerTurn();

	//Incorporating delay
	std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
	std::cout << "Data Loaded Successfully!!! !\n";
}

int CShooting::GetPlayer1Score()
{
	return m_player1Score;
}

int CShooting::GetPlayer2Score()
{
	return m_player2Score;
}

int CShooting::GetPlayerTurn()
{
	return m_playerTurn;
}


void CShooting::PollEvent()
{

	// poll events to left and right paddle and save and load game 
	while (m_window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed: // if any key pressed this case executes
			if (m_event.key.code == sf::Keyboard::F1) // if player press F1 game state will be saved
			{
				SaveGame();
			}
			if (m_event.key.code == sf::Keyboard::F2)  // if player press F2 game state will be loaded
			{
				LoadGame();
			}
			if (m_event.key.code == sf::Keyboard::Escape)
			{
				m_window->close(); // if player press escape window get closed 
			}
			if (m_event.key.code == sf::Keyboard::Right || m_event.key.code == sf::Keyboard::D)
			{
				// take care of the player right movement and his feet sound
				m_playerSprite.move(sf::Vector2f(15.f, 0.f));
				m_playerx++;
				m_playerx = m_playerx % 10;
				m_playerSprite.setTextureRect(sf::IntRect(m_playerx*120,910,120,130));
				if (!m_music.openFromFile("walk3.wav"))
					return; // error
				m_music.play();
				
				
			}
			if (m_event.key.code == sf::Keyboard::Left || m_event.key.code == sf::Keyboard::A)
			{
				// take care of the player left movement and his foot sounds
				m_playerSprite.move(sf::Vector2f(-15.f, 0.f));
				m_playerx++;
				m_playerx = m_playerx % 10;
				m_playerSprite.setTextureRect(sf::IntRect(m_playerx * 120, 650, 120, 130));
				if (!m_music.openFromFile("walk3.wav"))
					return; // error
				m_music.play();
			}

			if (m_event.key.code == sf::Keyboard::Up || m_event.key.code == sf::Keyboard::W)
			{
				// will take care of the player to face upward and craete the sound
				//m_sprite2.move(sf::Vector2f(0.f, -5.f));
				m_playerx++;
				m_playerx = m_playerx % 10;
				m_playerSprite.setTextureRect(sf::IntRect(m_playerx * 120, 780, 120, 130));
				if (!m_music.openFromFile("walk2.wav"))
					return; // error
				m_music.play();
			}
			break;
		case sf::Event::KeyReleased:
			if (m_event.key.code == sf::Keyboard::Right)
			{
				// if key got released the music will stop
				m_music.pause();
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// change the player turn one after the other
				if (m_playerTurn == 1)
				{
					m_playerTurn = 2;
				}
				else
				{
					m_playerTurn = 1;
				}

				InitFire();
				if (!m_music.openFromFile("gun.wav"))
					return; // error
				m_music.play();
				m_localPosition = sf::Mouse::getPosition(*m_window);
				FireMove(m_localPosition); // will take care of the direction of the shot 
			}
		}
	}
}

void CShooting::InitGrass() // initialise the grass platform image 
{
	m_grass.loadFromFile("grass.png");

	sf::Vector2u size = m_grass.getSize();
	m_grassSprite.setTexture(m_grass);
	//m_sprite1.setOrigin(size.x/3, size.y/3);
	m_grassSprite.setPosition(0.f, 400.f);
	m_grassSprite.setScale(1200 / m_grassSprite.getGlobalBounds().width, 500 / m_grassSprite.getGlobalBounds().height); // background will cover the whole window

}

void CShooting::CheckBoundariesForPlayer() //will take care of  player can not move beyound window
{
	if (m_playerSprite.getPosition().x < 0)
	{
		m_playerSprite.setPosition(0.f, m_playerSprite.getPosition().y);
	}
	if (m_playerSprite.getPosition().x + m_playerSprite.getGlobalBounds().width > m_window->getSize().x)
	{
		m_playerSprite.setPosition(m_window->getSize().x - m_playerSprite.getGlobalBounds().width, m_playerSprite.getPosition().y);
	}
}

void CShooting::InitLeftBirds() // initialise the left bird coming from left side of window
{
	m_leftBird.loadFromFile("Rbird.png");
	m_leftBirdSprite.setTexture(m_leftBird);
	m_leftBirdSprite.setScale(1, 1);
	m_leftBirdSprite.setPosition(0, rand()%400);
	m_rightBirdCount--;
	if (m_rightBirdCount < 0)
	{
		m_leftBirdSprite.setTextureRect(sf::IntRect(100, 92, 100, 92));
		m_leftbirdsVec.push_back(m_leftBirdSprite);
		InitLeftBomb();
		m_rightBirdCount =  30;
		
	}
}

void CShooting::InitRightBirds() // initialise the right bird coming from right side of window
{
	m_rightBird.loadFromFile("Rbird.png");
	m_rightBirdSprite.setTexture(m_rightBird);
	m_rightBirdSprite.setScale(-1, 1);
	m_rightBirdSprite.setPosition(m_window->getSize().x, rand() % 400);
	m_leftBirdCount--;
	if (m_leftBirdCount <0)
	{
		m_rightBirdSprite.setTextureRect(sf::IntRect(100 , 92 , 100, 92));
		m_rightbirdsVec.push_back(m_rightBirdSprite);
		InitRightBomb();
		m_leftBirdCount = 30;
		
	}
	
}

void CShooting::MoveLeftBird() // will change the sprite of bird in each frame to add animation
{
	m_leftBirdx++;
	m_leftBirdx = m_leftBirdx % 5;
	if (m_leftBirdx == 0)
	{
		m_leftBirdy++;
		m_leftBirdy = m_leftBirdy % 3;
	}
	
	for (int i = 0; i < m_leftbirdsVec.size(); i++)
	{
		m_leftbirdsVec[i].setTextureRect(sf::IntRect(100 * m_leftBirdx, 92 * m_leftBirdy, 100, 92));
		m_leftbirdsVec[i].move(20.f, 0.f);

		
	}
}

void CShooting::MoveRightBird()  // will change the sprite of bird in each frame to add animation
{
	m_rightBirdx++;
	m_rightBirdx = m_rightBirdx % 5;
	if (m_rightBirdx == 0)
	{
		m_rightBirdy++;
		m_rightBirdy = m_rightBirdy % 3;
	}
	
	for (int i = 0; i < m_rightbirdsVec.size(); i++)
	{
		m_rightbirdsVec[i].setTextureRect(sf::IntRect(100 * m_rightBirdx, 92 * m_rightBirdy, 100, 92));
		m_rightbirdsVec[i].move(-20.f, 0.f);

		
	}
}

void CShooting::FireMove(sf::Vector2i m_localPosition) // will take care of the direction of the player shot
{
	// used unit vector to take care the direction of shot 
	 m_distance = sqrt(pow((m_playerSprite.getPosition().x - m_localPosition.x), 2) + pow((m_playerSprite.getPosition().y - m_localPosition.y), 2));
	// std::cout << m_dir << "\n";
	// std::cout << m_localPosition.x << " " << m_localPosition.y << "\n";
	// std::cout << m_sprite2.getPosition().x << " " << m_sprite2.getPosition().y << "\n";
	 m_mouseXPosition =  (m_localPosition.x - m_playerSprite.getPosition().x) / m_distance;
	 m_mouseYPosition = ( m_localPosition.y- m_playerSprite.getPosition().y) / m_distance;
	 sf::Vector2f vec;
	 vec.x = m_mouseXPosition;
	 vec.y = m_mouseYPosition;
	 m_unitVec.push_back(vec);
	//std::cout << m_x <<" "<< m_y << "\n";
}





void CShooting::UpdateDt()
{
	m_dt = dtClock.restart().asSeconds(); // the the frame time in seconds
}

void CShooting::InitPlayer1() // initialise the player 1
{
	m_player.loadFromFile("player2.png");

	sf::Vector2u size = m_player.getSize();
	m_playerSprite.setTexture(m_player);
	m_playerSprite.setTextureRect(sf::IntRect(0,130*2,120,130));
	//m_sprite1.setOrigin(size.x/3, size.y/3);
	m_playerSprite.setPosition(m_window->getSize().x/2.f-80.f, 670.f);
	//m_sprite2.setScale(800 / m_sprite1.getGlobalBounds().width, 500 / m_sprite1.getGlobalBounds().height); // background will cover the whole window
	

}

void CShooting::CheckCollisionBombWithBird() // if the shot collide with bird that bird will disappear and we will increase the player score who shot accordingly
{
	
		for (int i = 0; i < m_fireVec.size(); i++)
		{
			for (int j = 0; j < m_leftbirdsVec.size(); j++)
			{
				if (m_fireVec[i].getGlobalBounds().intersects(m_leftbirdsVec[j].getGlobalBounds()))
				{

					m_fireVec.erase(m_fireVec.begin() + i);
					m_unitVec.erase(m_unitVec.begin() + i);
					m_leftbirdsVec.erase(m_leftbirdsVec.begin() + j);
					m_leftbombVec.erase(m_leftbombVec.begin() + j);
					if (m_playerTurn == 1)
					{
						m_player1Score++;
						

					}
					else
					{
						m_player2Score++;
					}
					

				}
			}
		}

		for (int i = 0; i < m_fireVec.size(); i++)
		{
			for (int j = 0; j < m_rightbirdsVec.size(); j++)
			{
				if (m_fireVec[i].getGlobalBounds().intersects(m_rightbirdsVec[j].getGlobalBounds()))
				{
					m_fireVec.erase(m_fireVec.begin() + i);
					m_unitVec.erase(m_unitVec.begin() + i);
					m_rightbirdsVec.erase(m_rightbirdsVec.begin() + j);
					m_rightbombVec.erase(m_rightbombVec.begin() + j);
					if (m_playerTurn == 1)
					{
						m_player1Score++;


					}
					else
					{
						m_player2Score++;
					}
				}
			}
		}
}
	

void CShooting::Update() // this function is called in each frame to update the game on screen in each frame
{
	
	PollEvent();
	
	InitLeftBirds();
	InitRightBirds();
	MoveLeftBird();
	MoveRightBird();
	//InitBomb();
	for (int i = 0; i < m_leftbirdsVec.size(); i++)
	{
		if (m_leftbirdsVec[i].getPosition().x > m_window->getSize().x+250.f)
		{
			m_leftbirdsVec.erase(m_leftbirdsVec.begin() + i);
			m_leftbombVec.erase(m_leftbombVec.begin() + i);
			
		}
	}
	for (int i = 0; i < m_rightbirdsVec.size(); i++)
	{
		if (m_rightbirdsVec[i].getPosition().x  < -250.f)
		{
			m_rightbirdsVec.erase(m_rightbirdsVec.begin() + i);
			m_rightbombVec.erase(m_rightbombVec.begin() + i);
		}
	}

	for (int i = 0; i < m_fireVec.size(); i++)
	{
		if (m_fireVec[i].getPosition().x < 0 || m_fireVec[i].getPosition().y<0 || m_fireVec[i].getPosition().x > m_window->getSize().x)
		{
			m_fireVec.erase(m_fireVec.begin() + i);
			m_unitVec.erase(m_unitVec.begin() + i);
		}
	}

	//std::cout << m_leftbirdsVec.size() << " " << m_rightbirdsVec.size() << "\n";
	//std::cout <<m_leftbombVec.size() << " "<< m_rightbombVec.size()<<"\n";
	
	CheckBoundariesForPlayer();
	CheckCollisionBombWithBird();

	
	

}

void CShooting::Render() // this function is to draw everything per frame happening 
{
	m_dropCount++;
	m_window->clear();
	m_window->draw(m_grassSprite);
	m_window->draw(m_playerSprite);
	m_sniperSprite.setPosition(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
	m_window->draw(m_sniperSprite);
	for (int i = 0; i < m_leftbirdsVec.size(); i++)
	{
		
		m_leftbombVec[i].move(20.f, 0.f);
		m_window->draw(m_leftbombVec[i]);
		m_window->draw(m_leftbirdsVec[i]);
	}
	for (int i = 0; i < m_rightbirdsVec.size(); i++)
	{
		m_rightbombVec[i].move(-20.f, 0.f);
		m_window->draw(m_rightbombVec[i]);
		m_window->draw(m_rightbirdsVec[i]);
	}
	
	for (int i = 0; i < m_fireVec.size(); i++)
	{
		m_fireVec[i].move(100.f*m_unitVec[i].x, 100.f*m_unitVec[i].y);
		m_window->draw(m_fireVec[i]);
	}
	
	m_Player1Score.setString("Player 1 Score : " + std::to_string(m_player1Score));
	m_Player2Score.setString("Player 2 Score : " + std::to_string(m_player2Score));
	if (m_playerTurn == 1) // display the player turn text
	{
		m_PlayerTurn.setFillColor(sf::Color::Blue);
		m_PlayerTurn.setPosition(m_playerSprite.getPosition().x, m_playerSprite.getPosition().y-10.f);
		m_PlayerTurn.setString("Player 2  ");
		m_window->draw(m_PlayerTurn);
	}
	else
	{
		m_PlayerTurn.setFillColor(sf::Color::Red);
		m_PlayerTurn.setPosition(m_playerSprite.getPosition().x, m_playerSprite.getPosition().y-10.f);
		m_PlayerTurn.setString("Player 1");
		m_window->draw(m_PlayerTurn);
	}
	if (m_player1Score == 10)
	{
		m_Player1Score.setPosition(500.f, 400.f);
		m_Player2Score.setCharacterSize(30);
		m_Player1Score.setString("****Player 1 Win!**** ");
		m_window->clear();
		m_window->draw(m_gameOverSprite);
		m_window->draw(m_Player1Score);
		m_window->display();
		Sleep(3000);
		m_window->close();
	}
	if(m_player2Score == 10)
	{
		m_Player2Score.setPosition(500.f, 400.f);
		m_Player2Score.setCharacterSize(30);
		m_Player2Score.setString("****Player 2 Win!**** ");
		m_window->clear();
		m_window->draw(m_gameOverSprite);
		m_window->draw(m_Player2Score);
		m_window->display();
		Sleep(3000);
		m_window->close();
	}
	m_window->draw(m_Player1Score);
	m_window->draw(m_Player2Score);
	//std::cout << m_fireVec.size() << " " << m_leftbirdsVec.size() << " " << m_rightbirdsVec.size() << " "<<m_leftbombVec.size()<<" "<<m_rightbombVec.size()<<"\n";
	m_window->display();
}
// this function will return whether window in opened or not
const bool CShooting::isRunning() const
{
	return m_window->isOpen();
}

