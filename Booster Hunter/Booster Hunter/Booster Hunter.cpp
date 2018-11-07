#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <ctime>

#define SC_WIDTH 1200
#define SC_HEIGHT 800

int main()
{
	// tp = Tiles position in y axis, (ra1, ra2, ra3, ra4, ra5, cra) = random number, k's = triggers, g = gravity;
	int ra1, ra2, ra3, ra4, ra5, cra;
	int j, x, y, up = 1, jump;
	int tp = 0, k = 0, tp2 = 0, k2 = 0, tp3 = 0, k3 = 0, tp4 = 0, k4 = 0, tp5 = 0, k5 = 0;
	int y1 = 0, y2 = 0, y3 = 0, y4 = 0, y5 = 0;
	unsigned i;
	int g = 5;
	int xPos = 0, yPos = 0;

	// Random Generators :
	ra1 = rand(); // These are for random tiles generate
	ra2 = rand();
	ra3 = rand();
	ra4 = rand();
	ra5 = rand();
	cra = rand(); // These are for random coin generate

	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(SC_WIDTH, SC_HEIGHT), "Booster Hunter ... ...");
	window.setFramerateLimit(60);

	// Background :
	sf::RectangleShape background(sf::Vector2f(SC_WIDTH, SC_HEIGHT));
	sf::Texture backgroundTexture;
	sf::Texture backgroundTexture2;
	sf::Texture backgroundTexture3;
	backgroundTexture.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Backgrounds\\Background1.png");
	backgroundTexture2.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Backgrounds\\Background2.png");
	backgroundTexture3.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Backgrounds\\Background3.png");

	// Lifebar:
	sf::Texture lifeHeadTexture;
	sf::Texture lifeTexture;
	lifeHeadTexture.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Hero\\HeroHead.png");
	lifeTexture.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Hero\\Life.jpg");
	sf::Sprite lifeHead;
	lifeHead.setScale(0.16, 0.16);
	lifeHead.setTexture(lifeHeadTexture);
	sf::Sprite life;
	life.setTexture(lifeTexture);
	life.setScale(0.07, 0.07);
	std::vector <sf::Sprite> lifeSprite(10, sf::Sprite(lifeTexture));

	// Hero :
	sf::Texture heroTexture;
	heroTexture.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Hero\\Hero.png");
	sf::Sprite hero;
	hero.setScale(1.3, 1.3);
	hero.setTexture(heroTexture);
	sf::Vector2u hTextureSize = heroTexture.getSize();
	hTextureSize.x /= 6;
	hTextureSize.y /= 6;
	hero.setTextureRect(sf::IntRect(hTextureSize.x * 0, hTextureSize.y * 1, hTextureSize.x, hTextureSize.y));

	// Trap :
	sf::Texture trapTexture;
	trapTexture.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Trap\\Trap.png");
	sf::Sprite trap;
	trap.setScale(2, 2);
	trap.setTexture(trapTexture);
	std::vector <sf::Sprite> trapSprite(120, sf::Sprite(trapTexture));

	// Coin :
	sf::Texture coinTexture;
	coinTexture.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Collectibles\\Coin.png");
	sf::Sprite coin;
	coin.scale(0.12, 0.12);
	coin.setTexture(coinTexture);
	std::vector <sf::Sprite> coinSprite((cra % 5 + 1), sf::Sprite(coinTexture));

	// Tile :
	sf::Texture tileTexture;
	sf::Texture tileTexture2;
	sf::Sprite tile;
	tileTexture.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Tiles\\Tile.png");
	tileTexture2.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Tiles\\Tile2.png");

	// Villain :
	sf::Texture villainTexture;
	sf::Texture villainTexture2;
	sf::Texture villainTexture3;
	sf::Texture villainPowerTex;
	sf::Texture villainPowerTex2;
	sf::Texture villainPowerTex3;
	sf::Sprite villain;
	sf::Sprite villainPower;
	villainTexture.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Villains\\BlueFox.png");
	villainTexture2.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Villains\\HellHound.png");
	villainTexture3.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Villains\\Boss Dragon.png");
	villainPowerTex.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Villains\\BlueFox'sPower.png");
	villainPowerTex2.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Villains\\HellHoun'sPower.png");
	villainPowerTex3.loadFromFile("D:\\My Programs\\In SFML\\In Visual Studio\\Booster Hunter\\Booster Hunter\\Textures\\Villains\\BossDragon'sPower.png");

	
	sf::Clock clock;
	sf::Event event;

	// Game Loop :
	while (window.isOpen())
	{
		// Handeling Times:
		sf::Time time = clock.getElapsedTime();
		if (time.asSeconds() > 16) clock.restart();

		// Setting up the Background:
		if (time.asSeconds() > 5 && time.asSeconds() < 10) background.setTexture(&backgroundTexture2);
		else if (time.asSeconds() > 10) background.setTexture(&backgroundTexture3);
		else background.setTexture(&backgroundTexture);

		// Setting up the Tiles:
		if (time.asSeconds() > 5 && time.asSeconds() < 10) tile.setTexture(tileTexture2);
		else if (time.asSeconds() > 10) tile.setTexture(tileTexture);
		else tile.setTexture(tileTexture);

		// Setting up the Villains:
		villain.setPosition(200, 200);
		villainPower.setPosition(100, 200);
		if (time.asSeconds() > 3 && time.asSeconds() < 5) {
			villainPower.setScale(0.5, 0.5);
			villainPower.setTexture(villainPowerTex);
		}
		else if (time.asSeconds() > 5 && time.asSeconds() < 8) {
			villainPower.setScale(0.5, 0.5);
			villainPower.setTexture(villainPowerTex2);
		}
		else if (time.asSeconds() > 8 && time.asSeconds() < 12) {
			villainPower.setScale(0.5, 0.5);
			villainPower.setTexture(villainPowerTex3);
		}
		if (time.asSeconds() > 3 && time.asSeconds() < 5) {
			villain.setScale(0.8, 0.8);
			villain.setTexture(villainTexture);
		}
		else if (time.asSeconds() > 5 && time.asSeconds() < 8) {
			villain.setScale(1.5, 1.5);
			villain.setTexture(villainTexture2);
		}
		else if (time.asSeconds() > 8 && time.asSeconds() < 12) {
			villain.setScale(3, 3);
			villain.setTexture(villainTexture3);
		}

		hero.setPosition(xPos, yPos);
		yPos = yPos + g;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				window.close();
			if (event.type == sf::Event::EventType::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					hero.move(5, 0);
					xPos = xPos - 5;
					if (up > 5) up = 1;
					hero.setTextureRect(sf::IntRect(hTextureSize.x*up, hTextureSize.y * 1, hTextureSize.x, hTextureSize.y));
					up++;
				}
				if (event.key.code == sf::Keyboard::Right) {
					hero.move(5, 0);
					xPos = xPos + 5;
					if (up > 5) up = 1;
					hero.setTextureRect(sf::IntRect(hTextureSize.x*up, hTextureSize.y * 1, hTextureSize.x, hTextureSize.y));
					up++;
				}
				if (event.key.code == sf::Keyboard::Space) {
					jump = 0;
					hero.move(jump + 30, -60);
					xPos = xPos + jump + 30;
					yPos = yPos - 60;
					hero.setTextureRect(sf::IntRect(hTextureSize.x * jump, hTextureSize.y * 3, hTextureSize.x, hTextureSize.y));
					jump++;

				}
			}
		}


		// Tiles movement :
		tp += 5;
		if (y1 > 700 || k == 1) {
			tp -= 10;
			k = 1;
			if (y1 < 150) k = 0;
		}
		tp2 += 5;
		if (y2 > 700 || k2 == 1) {
			tp2 -= 10;
			k2 = 1;
			if (y2 < 150) k2 = 0;
		}
		tp3 += 5;
		if (y3 > 700 || k3 == 1) {
			tp3 -= 10;
			k3 = 1;
			if (y3 < 150) k3 = 0;
		}
		tp4 += 5;
		if (y4 > 700 || k4 == 1) {
			tp4 -= 10;
			k4 = 1;
			if (y4 < 150) k4 = 0;
		}
		tp5 += 5;
		if (y5 > 700 || k5 == 1) {
			tp5 -= 10;
			k5 = 1;
			if (y5 < 150) k5 = 0;
		}

		window.clear();
		window.draw(background);

		// Drawing Tiles :
		for (i = 1; i <= 5; i++) {
			switch (i) {
			case 1:
				tile.setScale(((ra5 % 3) / 10.0) + 1, 0.6);
				y1 = (ra1 % 320 + 80) + tp;
				tile.setPosition(0, y1);
				break;
			case 2:
				tile.setScale(((ra4 % 3) / 10.0) + 1, 0.6);
				y2 = (ra2 % 320 + 80) + tp2;
				tile.setPosition(250, y2);
				break;
			case 3:
				tile.setScale(((ra3 % 3) / 10.0) + 1, 0.6);
				y3 = (ra3 % 320 + 80) + tp3;
				tile.setPosition(500, y3);
				break;
			case 4:
				tile.setScale(((ra2 % 3) / 10.0) + 1, 0.6);
				y4 = (ra4 % 320 + 80) + tp4;
				tile.setPosition(740, y4);
				break;
			case 5:
				tile.setScale(((ra1 % 3) / 10.0) + 1, 0.6);
				y5 = (ra5 % 320 + 80) + tp5;
				tile.setPosition(975, y5);
				break;
			}
			window.draw(tile);
		}

		// Drawing Coin :
		for (j = 1; j <= 5; j++) {
			switch (j) {
			case 1:
				x = 10;
				y = (ra1 % 320 + 50) + tp;
				break;
			case 2:
				x = 260;
				y = (ra2 % 320 + 50) + tp2;
				break;
			case 3:
				x = 510;
				y = (ra3 % 320 + 50) + tp3;
				break;
			case 4:
				x = 750;
				y = (ra4 % 320 + 50) + tp4;
				break;
			case 5:
				x = 985;
				y = (ra5 % 320 + 50) + tp5;
				break;
			}
			for (i = 0; i < coinSprite.size(); i++) {
				coin.setPosition(x + 20 + (i * 30), y);
				window.draw(coin);
			}
		}

		// Drawing Trap:
		for (i = 0; i < trapSprite.size(); i++) {
			trap.setPosition(-50 + ((signed)i * 30), 720);
			window.draw(trap);
		}

		// Drawing Life:
		for (i = 0; i < lifeSprite.size(); i++) {
			life.setPosition(50 + ((signed)i * 30), 5);
			window.draw(life);
		}

		//window.draw(villain);
		//window.draw(villainPower);

		window.draw(lifeHead);
		window.draw(hero);
		window.display();
	}

	return 0;
}
