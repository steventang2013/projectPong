#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>

using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong game!");
	window.setFramerateLimit(60);
	bool play = true;
    sf::Event event;

	//Images
	sf::Texture background;
	if (background.loadFromFile("images/background.png") == 0)
		return 1;
	sf::RectangleShape back;
	back.setSize(sf::Vector2f(800,600));
	back.setPosition(0,0);
	back.setTexture(&background);

	sf::Font font;
	if (font.loadFromFile("BuxtonSketch.ttf") == 0)
		return 1;
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setColor(sf::Color::Red);
	score.setPosition(380, 20);
	score.setString("0 : 0");
	//Sounds
	sf::SoundBuffer buffHit;
	if (buffHit.loadFromFile("sound effects/Blip.wav") == 0)
		return -1;
	sf::Sound hit;
	hit.setBuffer(buffHit);

	//States
	bool upButton = false;
	bool downButton = false;

	//Variables
	int yVelocityrect1 = 0;
	int yVelocityrect2 = 0;
	int xVelocityball = -4;
	int yVelocityball = -4;
	int pad1score = 0;
	int pad2score = 0;

	//Shape
	sf::RectangleShape rect1;
	rect1.setSize(sf::Vector2f(20,100));
	rect1.setFillColor(sf::Color::Green);
	rect1.setPosition(20, 300);

	sf::RectangleShape rect2;
	rect2.setSize(sf::Vector2f(20,100));
	rect2.setFillColor(sf::Color::Green);
	rect2.setPosition(760, 300);

	sf::CircleShape circ;
	circ.setRadius(15);
	circ.setFillColor(sf::Color::Yellow);
	circ.setPosition(400,300);
	
	//game loop

	while (play == true){
		
		while (window.pollEvent(event)){

			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Up)
					upButton = true;
				if (event.key.code == sf::Keyboard::Down)
					downButton = true;
			}
			if (event.type == sf::Event::KeyReleased){
				if (event.key.code == sf::Keyboard::Up)
					upButton = false;
				if (event.key.code == sf::Keyboard::Down)
					downButton = false;
			}
			

			
			if (event.type == sf::Event::Closed)
				play = false;
		}
		//Ball
		circ.move(xVelocityball,yVelocityball);
		
		
		//movement
		if (upButton == true)
			yVelocityrect1 = -4;
		if (downButton == true)
			yVelocityrect1 = 4;
		if (upButton == true && downButton == true)
			yVelocityrect1 = 0;
		if (upButton == false && downButton == false)
			yVelocityrect1 = 0;
		if (circ.getPosition().y < rect2.getPosition().y)
			yVelocityrect2 = -3;
		if (circ.getPosition().y > rect2.getPosition().y)
			yVelocityrect2 = 3;
		rect2.move(0,yVelocityrect2);
		//Move
		rect1.move(0,yVelocityrect1);
		
		//Out of Bounds
		if (rect1.getPosition().y < 0)
			rect1.setPosition(20, 0);
		if (rect1.getPosition().y > 500)
			rect1.setPosition(20, 500);
		if (circ.getPosition().y < 0)
			yVelocityball = -yVelocityball;
		if (circ.getPosition().y > 570)
			yVelocityball = -yVelocityball;
	
		//ball contact
		if (circ.getGlobalBounds().intersects(rect1.getGlobalBounds()) == true){
			xVelocityball = -xVelocityball;
			hit.play();
		}
		if (circ.getGlobalBounds().intersects(rect2.getGlobalBounds()) == true){
			xVelocityball = -xVelocityball;
			hit.play();
		}
		stringstream text;
		text << pad1score << " : " << pad2score;
		score.setString(text.str());
		if (circ.getPosition().x < 0){
			pad2score++;
			circ.setPosition(400,300);
		}
		if (circ.getPosition().x > 800){
			pad1score++;
			circ.setPosition(400,300);
		}

		window.clear();
		window.draw(back);
		window.draw(rect1);
		window.draw(rect2);
		window.draw(circ);
		window.draw(score);
		window.display();
	}
	window.close();
    return 0;
}