#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

//globals
int num_vertBox = 30, num_horzBox = 20;
int size = 16;
int w = size * num_horzBox;
int h = size * num_vertBox;

int direction, direction2, snake_length = 4;
float timer = 0, delay = .1;
//Maximum size of Snake
struct Snake
{
	int x, y;
}s[100];
struct Snake2
{
	int x, y;
}t[100];

struct Fruit
{
public:
	int x, y;
}d[100];
Fruit food;

void Tick()
{
	//Move remaining pieces of snake s[1] - s[99]
	for (int i = snake_length; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	//Head of snake depends on direction of user s[0]
	//User up
	if (direction == 3)
		s[0].y -= 1;
	//User down
	if (direction == 0)
		s[0].y += 1;
	//User left
	if (direction == 1)
		s[0].x -= 1;
	//User right
	if (direction == 2)
		s[0].x += 1;
	//if snake eats food it should grow and get faster
	if ((s[0].x == food.x) && (s[0].y == food.y))
	{
		snake_length++;
		delay /= 1.1;
		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	//Boundary Checking screen loop back on other side
	if (s[0].x > num_horzBox)
		s[0].x = 0;
	if (s[0].x < 0)
		s[0].x = num_horzBox;
	if (s[0].y > num_vertBox)
		s[0].y = 0;
	if (s[0].y < 0)
		s[0].x = num_vertBox;

	//Check if go over snake
	for (int i = 1; i < snake_length; i++)
	{
		//Cut snake in half from place eaten and slow it back down
		if (s[0].x == s[i].x && s[0].y == s[i].y)
		{
			snake_length = i;
			delay *= 2;
		}
	}




	//Move remaining pieces of snake s[1] - s[99]
	for (int i = snake_length; i > 0; --i)
	{
		t[i].x = t[i - 1].x;
		t[i].y = t[i - 1].y;
	}
	//Head of snake depends on direction of user s[0]
	//User up
	if (direction2 == 3)
		t[0].y -= 1;
	//User down
	if (direction2 == 0)
		t[0].y += 1;
	//User left
	if (direction2 == 1)
		t[0].x -= 1;
	//User right
	if (direction2 == 2)
		t[0].x += 1;
	//if snake eats food it should grow and get faster
	if ((t[0].x == food.x) && (t[0].y == food.y))
	{
		snake_length++;
		delay /= 1.1;
		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	//Boundary Checking screen loop back on other side
	if (t[0].x > num_horzBox)
		t[0].x = 0;
	if (t[0].x < 0)
		t[0].x = num_horzBox;
	if (t[0].y > num_vertBox)
		t[0].y = 0;
	if (t[0].y < 0)
		t[0].x = num_vertBox;

	//Check if go over snake
	for (int i = 1; i < snake_length; i++)
	{
		//Cut snake in half from place eaten and slow it back down
		if (t[0].x == t[i].x && t[0].y == t[i].y)
		{
			snake_length = i;
			delay *= 2;
		}
	}
}
int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game!");

	//Textures
	//load in image
	Texture t1, t2, t3;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/thumb.png");

	//Sprite
	//has physical dimensions
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);

	Sprite sprite4(t2);
	food.x = 10;
	food.y = 10;

	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something
		Event e;

		//check when window is closed
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}

		//Controls for snake movement by user1
		if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;

		//Controls for snake movement by user2
		if (Keyboard::isKeyPressed(Keyboard::W)) direction2 = 3;
		if (Keyboard::isKeyPressed(Keyboard::S)) direction2 = 0;
		if (Keyboard::isKeyPressed(Keyboard::A)) direction2 = 1;
		if (Keyboard::isKeyPressed(Keyboard::D)) direction2 = 2;

		if (timer > delay)
		{
			timer = 0;
			Tick();
		}

		//Draw
		window.clear();

		//Draw Background
		for(int i = 0; i < num_horzBox; i++)
			for (int j = 0; j < num_vertBox; j++)
			{
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}

		for (int i = 0; i < snake_length; i++)
		{
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);
		}
		


		for (int i = 0; i < snake_length; i++)
		{
			sprite4.setPosition(t[i].x*size, t[i].y*size);
			window.draw(sprite4);
		}


		//Draw Fruit
		sprite3.setPosition(food.x*size, food.y*size);
		window.draw(sprite3);

		window.display();
	}
}
