#include<iostream>
#include "Gameclass.h"

using namespace sf;

int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	Gameclass mygame;

	while (mygame.running())
	{
		
		//Update
		mygame.update();

		//Render
		mygame.render();
	}


	return 0;
}