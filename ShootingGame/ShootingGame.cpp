#include"Game.h"
#include"Menu.h"
#include <iostream>
#include<ctime>

int main()
{

	srand(time(0));
	CMenu menu(1000.f, 800.f); // call the menu constructor which initialise the menu window

	menu.PollEvent(); // this will take care of all events for paddle,save and load state
	/*CPingPong game;


	while (game.isRunning())
	{


	}*/
}
