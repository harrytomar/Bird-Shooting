#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include<windows.h>
enum direction // used enum to take care of the direction of the ball
{
	LEFT = 0, RIGHT, UPDIAGONAL, DOWNDIAGONAL, BACKWARDDOWNDIAGONAL, BACKWARDUPDIAGONAL
};

class CShooting
{
public:


	sf::RenderWindow *m_window;
	sf::Music m_music;  // will take care of the music
	sf::Event m_event; // will take care of the events
	bool m_isGameOver = false; // will take care of the game
	int m_playerTurn; // will take care of the which player turns next
	int m_playerx, m_playery;// used for next player sprites
	int m_leftBirdx, m_leftBirdy;// used for next bird sprite coming from left
	int m_rightBirdx, m_rightBirdy; // used for next bird sprite coming from right
	int m_leftBirdCount=-1, m_rightBirdCount=-1;
	sf::Texture m_shoot,m_player,m_grass,m_leftBird,m_rightBird,m_fire,m_bomb,m_sniper,m_gameOver;
	sf::Sprite m_backgroundSprite,m_playerSprite,m_grassSprite,m_leftBirdSprite,m_rightBirdSprite,m_fireSprite,m_bombSprite,m_sniperSprite,m_gameOverSprite;
	sf::Text m_Player1Score,m_Player2Score,m_PlayerTurn;
	sf::Font m_font;
	int m_player1Score,m_player2Score;
	std::vector<sf::Sprite>m_leftbirdsVec,m_rightbirdsVec,m_fireVec,m_leftbombVec,m_rightbombVec; // vector to hold birds and bombssprites
	CShooting();
	void InitWindow(); // initialise the window
	void InitBackGround1(); // init the initial background
	~CShooting() {}
	void UpdateDt();
	void InitPlayer1(); // initialize the player
	void Update(); // update the poll events,collisions
	void Render(); // draw things in every frame
	void PollEvent();
	void InitGrass(); // initialise the grass platforn
	void CheckBoundariesForPlayer(); // will check the player collision with boundary
	void InitLeftBirds(); // initialise left bird
	void InitRightBirds(); // initialise right bird
	void MoveLeftBird();
	void MoveRightBird();
	void FireMove(sf::Vector2i m_localPosition); // will throw the bomb in mose direction
	void InitFire();// initialise the 
	void CheckCollisionBombWithBird();
	void InitVariable();// initialise the  text on the screen
	void InitLeftBomb(); // initialise the left bomb holding by left bird
	void InitRightBomb();// initialise the right bomb holding by right bird
	void SaveGame(); // will save the game state
	void LoadGame();// will load the prev ggame state
	int GetPlayer1Score();
	int GetPlayer2Score();
	int GetPlayerTurn();
	float m_distance;// will get the distance bw the player and the mouse point on the window and find the distance and then unit vector of that
	std::vector<sf::Vector2f>m_unitVec; // hold the unit vector of all the bombs
	float m_mouseXPosition, m_mouseYPosition; // will hold the mouse x and y pos
	sf::Vector2i m_localPosition; // local positions of mouse where ever clicked on the window
	const bool isRunning() const; // return the window status
	float m_dt;
	sf::Clock dtClock;
	int m_dropCount; // when the bomb will drop by the bird
	void InitSniper();
	void InitGameOver();

private:

};

