/*
	This "game" was made with SFML which's documentation is: https://www.sfml-dev.org/documentation/2.5.1/

	This is just an example of how SFML works. This is far from perfect/clean code, the purpose is to introduce you to SFML.

	As you might notice this "game" doesn't have any level generation algorithm or a score counter, simply because this is not a SFML
	tutorial. This is just an introduction to glance at, not learn from.

	You might have noticed the Debug & SFML folder that comes with this project. The debug folder must remain intact. You have to open the
        SFML folder and read the instructions I left there. If the game crashes after completing my instructions, replace the files in the
        Debug folder with the "bin" files that are found in the SFML downloaded folder.

	You are free to use this in any shape or form. This was made for educational purposes not financial.

	Thanks for checking my stuff out :)
*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Window
float WND_WIDTH = 800.0f;
float WND_HEIGHT = 600.0f;
std::string WND_TITLE = "Flappy Bird using SFML";
sf::RenderWindow window(sf::VideoMode(WND_WIDTH, WND_HEIGHT), WND_TITLE, sf::Style::Close | sf::Style::Titlebar);
sf::Event eVent;
sf::View view;

// Shapes & objects
sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
sf::RectangleShape ground(sf::Vector2f(WND_WIDTH * 1000, 50.0f));
sf::RectangleShape roof(sf::Vector2f(WND_WIDTH * 1000, 50.0f));
sf::RectangleShape obstacle1up(sf::Vector2f(100.0f, 50.0f));
sf::RectangleShape obstacle1down(sf::Vector2f(100.0f, 325.0f));
sf::RectangleShape obstacle2up(sf::Vector2f(100.0f, 175.0f));
sf::RectangleShape obstacle2down(sf::Vector2f(100.0f, 200.0f));
sf::RectangleShape obstacle3up(sf::Vector2f(100.0f, 325.0f));
sf::RectangleShape obstacle3down(sf::Vector2f(100.0f, 50.0f));
std::vector<sf::RectangleShape> upobstacles;
std::vector<sf::RectangleShape> downobstacles;

// Conditions
bool canFall = true;

void initialize()
{
	window.setFramerateLimit(100);
	view.setCenter(sf::Vector2f(WND_WIDTH / 2, WND_HEIGHT / 2));
	view.setSize(sf::Vector2f(WND_WIDTH, WND_HEIGHT));

	player.setFillColor(sf::Color::Red);
	player.setOrigin(sf::Vector2f(player.getSize().x / 2, player.getSize().y / 2));
	player.setPosition(sf::Vector2f(WND_WIDTH / 2, WND_HEIGHT / 2));

	ground.setFillColor(sf::Color::Blue);
	ground.setOrigin(ground.getSize().x / 2, ground.getSize().y / 2);
	ground.setPosition(sf::Vector2f(ground.getSize().x / 2, WND_HEIGHT));

	roof.setFillColor(sf::Color::Blue);
	roof.setOrigin(roof.getSize().x / 2, roof.getSize().y / 2);
	roof.setPosition(sf::Vector2f(roof.getSize().x / 2, 0.0f));

	/* AS I MENTIONED BEOFRE, I HAVE NOT FOCUSED ON LEVEL GENERATION IN THIS "GAME" */
	obstacle1up.setOrigin(sf::Vector2f(obstacle1up.getSize().x / 2, obstacle1up.getSize().y / 2));
	obstacle1up.setPosition(sf::Vector2f(WND_WIDTH, roof.getSize().y / 2 + obstacle1up.getSize().y / 2));

	obstacle1down.setOrigin(sf::Vector2f(obstacle1down.getSize().x / 2, obstacle1down.getSize().y / 2));
	obstacle1down.setPosition(sf::Vector2f(WND_WIDTH, WND_HEIGHT - ground.getSize().y / 2 - obstacle1down.getSize().y / 2));

	obstacle2up.setOrigin(sf::Vector2f(obstacle2up.getSize().x / 2, obstacle2up.getSize().y / 2));
	obstacle2up.setPosition(sf::Vector2f(WND_WIDTH * 1.5, roof.getSize().y / 2 + obstacle2up.getSize().y / 2));

	obstacle2down.setOrigin(sf::Vector2f(obstacle2down.getSize().x / 2, obstacle2down.getSize().y / 2));
	obstacle2down.setPosition(sf::Vector2f(WND_WIDTH * 1.5, WND_HEIGHT - ground.getSize().y / 2 - obstacle2down.getSize().y / 2));

	obstacle3up.setOrigin(sf::Vector2f(obstacle3up.getSize().x / 2, obstacle3up.getSize().y / 2));
	obstacle3up.setPosition(sf::Vector2f(WND_WIDTH * 2, roof.getSize().y / 2 + obstacle3up.getSize().y / 2));

	obstacle3down.setOrigin(sf::Vector2f(obstacle3down.getSize().x / 2, obstacle3down.getSize().y / 2));
	obstacle3down.setPosition(sf::Vector2f(WND_WIDTH * 2, WND_HEIGHT - ground.getSize().y / 2 - obstacle3down.getSize().y / 2));

	// I initialize the vector here, because initializing it with the declaration will have problems when you try to edit the properties of its elements.
	upobstacles = { obstacle1up, obstacle2up, obstacle3up };
	downobstacles = { obstacle1down, obstacle2down, obstacle3down };
}

void Gravity()
{
	if (player.getPosition().y + player.getSize().y / 2 < ground.getPosition().y - ground.getSize().y / 2 && canFall)
	{
		player.move(sf::Vector2f(0.0f, 5.0f));
	}
}

void Jump()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && player.getPosition().y - player.getSize().y / 2 > roof.getPosition().y + roof.getSize().y / 2)
	{
		canFall = false;
		player.move(0.0f, -5.0f);
	}
	else
	{
		canFall = true;
	}
}

void Push()
{
	player.move(sf::Vector2f(3.5f, 0.0f));
	view.move(3.5f, 0.0f);
}

void CheckCollisions()
{
	for (sf::RectangleShape shape : upobstacles)
		if (player.getPosition().x + player.getSize().x / 2 >= shape.getPosition().x - shape.getSize().x / 2 && player.getPosition().x - player.getSize().x / 2 <= shape.getPosition().x + shape.getSize().x / 2)
			if (player.getPosition().y - player.getSize().y / 2 < shape.getPosition().y + shape.getSize().y / 2)
				initialize();

	for (sf::RectangleShape shape : downobstacles)
		if (player.getPosition().x + player.getSize().x / 2 >= shape.getPosition().x - shape.getSize().x / 2 && player.getPosition().x - player.getSize().x / 2 <= shape.getPosition().x + shape.getSize().x / 2)
			if (player.getPosition().y + player.getSize().y / 2 > shape.getPosition().y - shape.getSize().y / 2)
				initialize();
}

void Render()
{
	window.clear();
	window.draw(player);
	window.draw(ground);
	window.draw(roof);
	for (sf::RectangleShape shape : upobstacles)
		window.draw(shape);
	for (sf::RectangleShape shape : downobstacles)
		window.draw(shape);
	window.display();
}

int main()
{
	// Initialize shapes and their properties
	initialize();

	// Game loop
	while (window.isOpen())
	{
		while (window.pollEvent(eVent))
		{
			if (eVent.type == sf::Event::Closed)
				window.close();
		}

		// Player gravity
		Gravity();

		// Player jump
		Jump();

		// Right side push
		Push();

		// Check for collisions
		CheckCollisions();

		// Render
		Render();
	}
}
