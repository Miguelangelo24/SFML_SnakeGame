// SFML_Test.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

//globals
int num_vertBox = 30, num_horzBox = 20;
int size = 16;// number of pixels
int w = size * num_horzBox;//Background number of pixels in width
int h = size * num_vertBox;//Background number of pixels in height

int direction, direction2, snake_length = 4, snake_length2 = 4;

//Maximum size of Snake
struct Snake
{
	int x, y;
}s[100];

struct Snake2 
{
	int x, y;
}s2[100];

struct Fruit 
{
	int x, y;
}food;

float Tick(float delay1) {
	//Move remaining pieces of snake s[1] - s[99]
	for (int i = snake_length; i > 0; i--)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	for (int j = snake_length2; j > 0; j--)
	{
		s2[j].x = s2[j - 1].x;
		s2[j].y = s2[j - 1].y;
	}

	//Head of snake depends on direction of user s[0]
	//User Up
	if (direction == 3) 
	{
		s[0].y -= 1;
	}
	//User Down
	if (direction == 0) 
	{
		s[0].y += 1;
	}
	//User Left
	if (direction == 1)
	{
		s[0].x -= 1;
	}
	//User Right
	if (direction == 2) 
	{
		s[0].x += 1;
	}

	//Head of snake depends on direction of user s2[0]
	//User Up
	if (direction2 == 3)
	{
		s2[0].y -= 1;
	}
	//User Down
	if (direction2 == 0)
	{
		s2[0].y += 1;
	}
	//User Left
	if (direction2 == 1)
	{
		s2[0].x -= 1;
	}
	//User Right
	if (direction2 == 2)
	{
		s2[0].x += 1;
	}

	//If Snake eats food it should grow
	if ((s[0].x) == food.x && (s[0].y) == food.y) 
	{
		//Increment snake
		int old_length = snake_length;
		snake_length++;

		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

		if (old_length < snake_length)
		{
			delay1 = delay1 / 1.05;
		}
		
	}

	else if ((s2[0].x) == food.x && (s2[0].y) == food.y)
	{
		//Increment snake
		int old_length2 = snake_length2;
		snake_length2++;

		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

		if (old_length2 < snake_length2)
		{
			delay1 = delay1 / 1.05;
		}

	}

	//Boundary Checking screen loop back on other side
	if (s[0].x > num_horzBox)
	{
		s[0].x = 0;
	}

	if (s[0].x < 0) 
	{
		s[0].x = num_horzBox;
	}

	if (s[0].y > num_vertBox) 
	{
		s[0].y = 0;
	}

	if (s[0].y < 0) 
	{
		s[0].y = num_vertBox;
	}

	//Boundary Checking screen loop back on other side
	if (s2[0].x > num_horzBox)
	{
		s2[0].x = 0;
	}

	if (s2[0].x < 0)
	{
		s2[0].x = num_horzBox;
	}

	if (s2[0].y > num_vertBox)
	{
		s2[0].y = 0;
	}

	if (s2[0].y < 0)
	{
		s2[0].y = num_vertBox;
	}


	//Check if go over snake
	for (int i = 1; i < snake_length; i++) 
	{
		//Cut snake in half from place eaten
		if (s[0].x == s[i].x && s[0].y == s[i].y) 
		{
			snake_length = i;
			delay1 = delay1 * 1.1;
		}
	}

	//Check if go over snake
	for (int j = 1; j < snake_length2; j++)
	{
		//Cut snake in half from place eaten
		if (s2[0].x == s2[j].x && s2[0].y == s2[j].y)
		{
			snake_length2 = j;
			delay1 = delay1 * 1.1;
		}
	}

	return delay1;
}

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game");

	//Textures
	//Load an image
	Texture t1, t2, t3, t4;
	t1.loadFromFile("image/white.png");
	t2.loadFromFile("image/red.png");
	t3.loadFromFile("image/cookie.png");
	t4.loadFromFile("image/purple.png");

	//Sprite
	//Has physical dimensions
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4);

	food.x = 10;
	food.y = 10;

	Clock clock;
	float timer = 0, delay = .1, delay1 = .1;

	while (window.isOpen()) 
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something
		Event e;

		//Check when window is closed
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) 
			{
				window.close();
			}
		}

		//Controls for Snake Movement by User
		//Player 1
		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			direction = 3;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) 
		{
			direction = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			direction = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			direction = 2;
		}

		//Player 2
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			direction2 = 3;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			direction2 = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			direction2 = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			direction2 = 2;
		}

		if (timer > delay) 
		{
			timer = 0; //reset timer
			float newDelay = Tick(delay); //Move Snake one sprite forward
			delay = newDelay;
		}

		//Draw
		window.clear();

		//Draw Background
		for (int i = 0; i < num_horzBox; i++) 
		{
			for (int j = 0; j < num_vertBox; j++) 
			{
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}
		}

		//Draw Snake 1
		for (int i = 0; i < snake_length; i++) 
		{
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);
		}

		//Draw Snake 2
		for (int j = 0; j < snake_length2; j++)
		{
			sprite4.setPosition(s2[j].x*size, s2[j].y*size);
			window.draw(sprite4);
		}

		//Draw Fruit
		sprite3.setPosition(food.x*size, food.y*size);
		window.draw(sprite3);

		window.display();

	}

	return 0;
}