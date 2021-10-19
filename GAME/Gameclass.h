#pragma once

#include<iostream>
#include<vector>
#include<ctime>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace sf;
using namespace std;

class Gameclass
{
private:
	//Variables
	//Window
	RenderWindow* window;
	VideoMode video;
	Event ev;

	//Mouse positions
	Vector2i mousePosWindow;

	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//Game objects
	vector<RectangleShape> enemies;
	RectangleShape enemy;

	//Private Functions
	void initVariable();
	void initWindow();
	void initEnemy();

public:
	//Constructor - Destructor
	Gameclass();
	virtual ~Gameclass();

	//Accessors
	const bool running() const;

	//Functions
	void spawnEnemies();

	void pollEvent();
	void updateMouse();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
};
