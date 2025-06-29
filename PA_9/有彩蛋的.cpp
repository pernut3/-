#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>






#include "menu.hpp"
#include "player.hpp"
#include "background.hpp"
#include "Book.hpp"
#include "Windows.h"
#include "MiscFunctions.hpp"
#include <vector>
#include <string>
#include "pencil.hpp"
#include "GameOverScreen.hpp"
#include "testCases.hpp"

////set false if you dont want to run tests
#define RUN_TESTS true


enum class gameStateClass {

	gameStateDefault,
	mainMenu,
	play,
	levels,
	exit,
	rules
};

enum class levelsClass {

	levelsDefault,
	level1,
	level2,
	level3,
	level4,
	level5,
	rules,
	exit
};

int main()
{



	    //Seed random time
	    std::srand(static_cast<unsigned>(std::time(nullptr)));
	
	
	    //Open window and return dimensions
	     sf::RenderWindow window = initWindow();  
	    //sf::RenderWindow window(sf::VideoMode({ 1800,900 }), "sfml");
	     sf::Vector2u windowSize = window.getSize();
	
	
	    //load menu background music
	    sf::Music menuMusic;
	    menuMusic.openFromFile("danceWeapon4.mp3");
	    menuMusic.setVolume(10);
	    menuMusic.play();
	    menuMusic.setLooping(true);
	
	
	    //load in-game background music
	    sf::Music gameMusic;
	    gameMusic.openFromFile("track1.mp3");
	    gameMusic.setVolume(15);
	
	
	    //load player
	    Player player = loadPlayer(window);
	
	
	    //load background
	    Background background = loadBackground();
	
	
	    //track gamescore
	    int score = 0;
	
	    
	 
	    //load laser sound
	    sf::Music laserSound;
	    laserSound.openFromFile("LaserGunPew.wav");
	
	    //load collision sounds
	    sf::Music hitSound;
	    hitSound.openFromFile("pencil_hit.mp3");
	
	
	    //load book textures
	    sf::Texture bookTextures[3];
	    bookTextures[0].loadFromFile("Book.png");
	    bookTextures[1].loadFromFile("Book2.png");
	    bookTextures[2].loadFromFile("Book3.png");
	
	
	    //vectors to store books and pencils
	    std::vector<Book> balls;
	    std::vector<Pencil> pencils;
	
	
	    //first book
	    Book firstBook(bookTextures[std::rand() % 3]);
	    float scale = 0.1f + ((float)(std::rand() % 5 + 1) / 60); // Between 0.1 and .15
	    firstBook.setScale({ scale, scale });
	    balls.push_back(firstBook);
	
	    //load first pencil in
	    sf::Texture pencilTex;
	    pencilTex.loadFromFile("pencil.png");
	    Pencil pencil(pencilTex, player.getPosition());
	    pencils.push_back(pencil);
	
	
	    //initialize clocks to keep track of spawn times
	    sf::Clock ball_spawn_clock;
	    sf::Clock pencil_spawn_clock;
	    sf::Clock hitRestrictor;
	
	
	    //load font
	    sf::Font font;
	    font.openFromFile("PressStart2P-Regular.ttf");
	    sf::Text scoreLabel(font);
	    sf::Text healthLabel(font);
	    sf::Text highScoreLable(font);
	
	    //set text settings
	    loadTexts(window, font, scoreLabel, healthLabel, highScoreLable);
	
	    //defines starting spawn rate of balls. decreases down to 3 seconds for difficulty increase
	    float bookSpawnRate = 4;
	    float pencilSpawnRate = 50.f;
	
	
	    //Start game in the menu
	    Menu menu(background.getTexture(), player.getTexture(), font, windowSize);
	  //  menu.startMenu(window);
		menu.startMenu(window);
	    menuMusic.stop();
	
	    gameMusic.play();
	    gameMusic.setLooping(true);
	
	
	
	    //run test cases before gameloop begins
	    if (RUN_TESTS)
	    {
	        TestCases test;
	        test.testAll();
	    }
	
	
























	//sf::Clock clock;
	//sf::Font font("OpenSans-Regular.ttf");
	//const float tolerance = 10.f;


	//sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "SMPG");
	//window.setFramerateLimit(60);
	//window.setKeyRepeatEnabled(false);




	////load menu background music
	//sf::Music menuMusic;
	//menuMusic.openFromFile("danceWeapon4.mp3");
	//menuMusic.setVolume(10);
	//menuMusic.play();
	//menuMusic.setLooping(true);


	////load in-game background music
	//sf::Music gameMusic;
	//gameMusic.openFromFile("track1.mp3");
	//gameMusic.setVolume(15);


	////load player
	//Player player = loadPlayer(window);


	////load background
	//Background background = loadBackground();









	//int score = -1;
	sf::Text scoreText(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);

	int highScore = 0;
	sf::Text highScoreText(font);
	highScoreText.setCharacterSize(70);
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setPosition({ 460.f, 100.f });

	// Main menu variables
	sf::Text playText(font);
	playText.setCharacterSize(80);
	playText.setString("Play");
	playText.setPosition({ 560.f, 340.f });

	sf::Text levelsText(font);
	levelsText.setCharacterSize(80);
	levelsText.setString("Rules");
	levelsText.setPosition({ 560.f, 430.f });

	sf::Text exitText(font);
	exitText.setCharacterSize(80);
	exitText.setString("Exit");
	exitText.setPosition({ 560.f, 520.f });


	int selectedOptionMainMenu = 0; // mainMenu = 0, play = 1, levels = 2, exit = 3
	const int totalOptionsMainMenu = 3;
	gameStateClass gameState = gameStateClass::mainMenu;


	sf::Text level1Text(font);
	level1Text.setCharacterSize(60);
	level1Text.setString("Level 1");
	level1Text.setPosition({ 560.f, 100.f });

	sf::Text level2Text(font);
	level2Text.setCharacterSize(60);
	level2Text.setString("Level 2");
	level2Text.setPosition({ 560.f, 200.f });

	sf::Text level3Text(font);
	level3Text.setCharacterSize(60);
	level3Text.setString("Level 3");
	level3Text.setPosition({ 560.f, 300.f });

	sf::Text level4Text(font);
	level4Text.setCharacterSize(60);
	level4Text.setString("Level 4");
	level4Text.setPosition({ 560.f, 400.f });

	sf::Text level5Text(font);
	level5Text.setCharacterSize(60);
	level5Text.setString("Use WASD to move DinZheng\nPress the space to destory the Da");
	level5Text.setPosition({ 60.f, 200.f });



	sf::Text levelsExitText(font);
	levelsExitText.setCharacterSize(60);
	levelsExitText.setString("Exit");
	levelsExitText.setPosition({ 560.f, 600.f });

	sf::Text rulesText(font);
	rulesText.setCharacterSize(60);
	rulesText.setString("Rules");
	rulesText.setPosition({ 560.f, 60.f });

	int selectedOptionLevelsMenu = 0;
	const int totalOptionsLevelsMenu = 5;
	levelsClass level = levelsClass::levelsDefault;

	int levelsScore = -1;

	// HighScore code for writing
	std::ifstream inFileHighScore("highScore.txt");
	if (inFileHighScore.is_open()) {

		if (!(inFileHighScore >> highScore)) {

			highScore = 0;
		}

		inFileHighScore.close();
	}
	else {

		// std::cout << "Failed to open highScore.txt for writing." << std::endl;
	}


	while (window.isOpen())
	{


		while (std::optional event = window.pollEvent()) {

			if (event->is<sf::Event::Closed>()) {

				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				            {
				                std::cout << "ºÈµãÀÏÊóÒ©";
				                window.close();
				            }
				

			if (gameState == gameStateClass::mainMenu) {

				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
					if (keyPressed->scancode == sf::Keyboard::Scan::Up) {
						if (selectedOptionMainMenu == 0) {
							selectedOptionMainMenu = 1;
						}
						else if (selectedOptionMainMenu == 1) {
							selectedOptionMainMenu = totalOptionsMainMenu;
						}
						else {
							selectedOptionMainMenu -= 1;
						}
					}
					else if (keyPressed->scancode == sf::Keyboard::Scan::Down) {
						if (selectedOptionMainMenu == 0) {
							selectedOptionMainMenu = 1;
						}
						else {
							selectedOptionMainMenu = (selectedOptionMainMenu % totalOptionsMainMenu) + 1;
						}
					}
					else if (keyPressed->scancode == sf::Keyboard::Scan::Enter) {
						if (selectedOptionMainMenu == 1) {
							gameState = gameStateClass::play;
						}
						else if (selectedOptionMainMenu == 2) {
							gameState = gameStateClass::levels;
						}
						else if (selectedOptionMainMenu == 3) {
							gameState = gameStateClass::exit;
						}
					}
				}
			}



			else if (gameState == gameStateClass::levels) {

				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
					if (keyPressed->scancode == sf::Keyboard::Scan::Up) {
						if (selectedOptionLevelsMenu <= 0) {
							selectedOptionLevelsMenu = totalOptionsLevelsMenu;
						}
						else {
							selectedOptionLevelsMenu -= 1;
						}
					}
					else if (keyPressed->scancode == sf::Keyboard::Scan::Down) {
						if (selectedOptionLevelsMenu == 5) {
							selectedOptionLevelsMenu = 0;
						}
						else {
							selectedOptionLevelsMenu = (selectedOptionLevelsMenu % totalOptionsLevelsMenu) + 1;
						}
					}
					else if (keyPressed->scancode == sf::Keyboard::Scan::Enter) {
						if (selectedOptionLevelsMenu == 1) {
							level = levelsClass::level1;
						}
						else if (selectedOptionLevelsMenu == 2) {
							level = levelsClass::level2;
						}
						else if (selectedOptionLevelsMenu == 3) {
							level = levelsClass::level3;
						}
						else if (selectedOptionLevelsMenu == 4) {
							level = levelsClass::level4;
						}
						else if (selectedOptionLevelsMenu == 5) {
							level = levelsClass::level5;
						}
						else if (selectedOptionLevelsMenu == 0) {
							level = levelsClass::exit;
						}
					}
				}
			}

		}

		if (gameState == gameStateClass::mainMenu) {

			// std::cout << "Main menu state activated" << std::endl;
			// std::cout << "Player position (" << playerPosition.x << ", " << playerPosition.y << ")" << std::endl;

			if (selectedOptionMainMenu == 1) {

				playText.setFillColor(sf::Color::Red);
			}
			else {

				playText.setFillColor(sf::Color::White);
			}

			if (selectedOptionMainMenu == 2) {

				levelsText.setFillColor(sf::Color::Red);
			}
			else {

				levelsText.setFillColor(sf::Color::White);
			}

			if (selectedOptionMainMenu == 3) {

				exitText.setFillColor(sf::Color::Red);
			}
			else {

				exitText.setFillColor(sf::Color::White);
			}
	
			/*if (selectedOptionMainMenu == 4) {

				level5Text.setFillColor(sf::Color::Red);
			}
			else {

				level5Text.setFillColor(sf::Color::White);
			}*/

			// HighScore code
			highScoreText.setString("HighScore: " + std::to_string(highScore));

			window.clear();
			window.draw(background);
			window.draw(playText);
			window.draw(levelsText);
			window.draw(exitText);
			window.draw(highScoreText);
			//window.draw(level5Text);
			window.display();

		}


		else if (gameState == gameStateClass::levels) {

			// std::cout << "Levels state activated." << std::endl;

			// Level menu buttons coloring
			if (selectedOptionLevelsMenu == 1) {
				level1Text.setFillColor(sf::Color::Red);
			}
			else {
				level1Text.setFillColor(sf::Color::White);
			}

			if (selectedOptionLevelsMenu == 2) {
				level2Text.setFillColor(sf::Color::Red);
			}
			else {
				level2Text.setFillColor(sf::Color::White);
			}

			if (selectedOptionLevelsMenu == 3) {
				level3Text.setFillColor(sf::Color::Red);
			}
			else {
				level3Text.setFillColor(sf::Color::White);
			}

			if (selectedOptionLevelsMenu == 4) {
				level4Text.setFillColor(sf::Color::Red);
			}
			else {
				level4Text.setFillColor(sf::Color::White);
			}

			if (selectedOptionLevelsMenu == 5) {
				level5Text.setFillColor(sf::Color::Red);
			}
			else {
				level5Text.setFillColor(sf::Color::White);
			}

			if (selectedOptionLevelsMenu == 0) {
				levelsExitText.setFillColor(sf::Color::Red);

			}
			else {
				levelsExitText.setFillColor(sf::Color::White);
			}

			if (level == levelsClass::exit) {

				// std::cout << "Levels exit activated." << std::endl;

				gameState = gameStateClass::mainMenu;
				level = levelsClass::levelsDefault;
			}

			window.clear();
			window.draw(background);
			window.draw(rulesText);
			//window.draw(level2Text);
			//window.draw(level3Text);
			//window.draw(level4Text);
			window.draw(level5Text);
			window.draw(levelsExitText);
			window.display();
		}




        

		else if (gameState == gameStateClass::play)
		{
                     
			
				//spawn a new ball every spawnRate seconds
				if (ball_spawn_clock.getElapsedTime().asSeconds() >= bookSpawnRate)
				{
					Book newBall(bookTextures[std::rand() % 3]);
					float scale = 0.1f + ((float)(std::rand() % 5 + 1) / 60); // Between 0.1 and .15
					newBall.setScale({ scale, scale });
					balls.push_back(newBall);
					ball_spawn_clock.restart();
					if (bookSpawnRate > 1) bookSpawnRate -= 0.1f; // Decrease spawn rate to increase difficulty
					std::cout << "Number of balls: " << balls.size() << std::endl;
				}

				//spawn in a new pencil if pencil is shot
				if (pencils[pencils.size() - 1].getIsShooting() == true && pencil_spawn_clock.getElapsedTime().asMilliseconds() >= pencilSpawnRate)
				{
					Pencil newPencil(pencilTex, player.getPosition());
					pencils.push_back(newPencil);
					pencil_spawn_clock.restart();
				}


				//update all objects//


				//update all balls
				for (auto& ball : balls)
				{
					ball.update(window.getSize());
					if (ball.getHealth() <= 0)
					{
						score += ball.getOriginalHealth() * 8;
						//remove the ball from the vector if destoryed
						ball.setHealth(0);
						balls.erase(std::remove_if(balls.begin(), balls.end(), [](const Book& b) { return b.getHealth() <= 0; }), balls.end());
						scoreLabel.setString("Score: " + std::to_string(score));
					}
				}



				//update all pencils
				for (auto& pencil : pencils)
				{
					pencil.update(window, laserSound, player);
					if ((pencil.getIsHit() || pencil.getPosition().y < 0) && pencils.size() > 2)
					{
						//remove the pencil from the vector if it hits a book
						pencils.erase(std::remove_if(pencils.begin(), pencils.end(), [](const Pencil& p) { return p.getIsHit() || p.getPosition().y < 0; }), pencils.end());
					}
				}


				//check if pencils have hit a ball and if balls have hit the player
				for (auto& ball : balls)
				{
					if (checkIfPlayerIsHit(player, ball) && hitRestrictor.getElapsedTime().asSeconds() >= 1)
					{
						player.setHealth(player.getHealth() - 1);
						healthLabel.setString(std::to_string(player.getHealth()) + " HP");
						hitRestrictor.restart();
						player.setColor(sf::Color::Red);
					}
					for (auto& pencil : pencils)
					{
						if (checkShotHit(pencil, ball)) hitSound.play();
					}
					if (player.getColor() == sf::Color::Red && hitRestrictor.getElapsedTime().asSeconds() >= .5)
					{
						player.setColor(sf::Color::White);
					}
				}

				//update player location & check hit
				player.movePlayer(window.getSize());

				//clear screen between frames
				window.clear();


				//draw all objects back to screen//


				window.draw(background);
				window.draw(scoreLabel);
				window.draw(healthLabel);
				window.draw(highScoreLable);

				//draw all balls
				for (const auto& ball : balls)
				{
					window.draw(ball);
				}

				//draw all pencils
				for (const auto& pencil : pencils)
				{
					window.draw(pencil);
				}
				window.draw(player);

				//display window to screen
				window.display();

				//check if player has died
				if (player.getHealth() <= 0)
				{
					std::cout << "Game Over!" << std::endl;

					//reset player position and stats and go to game over screen
					player.setPosition({ (float)windowSize.x / 2.f, (float)windowSize.y / 1.5f });
					window.clear();
					GameOverScreen gameOverScreen(background.getTexture(), player.getTexture(), font, windowSize);
					gameOverScreen.run(window);
					bookSpawnRate = 5;
					highScoreLable.setString("High Score: " + std::to_string(checkHighScore(score)));
					score = 0;
					scoreLabel.setString("Score: 0");
					player.setHealth(5);
					healthLabel.setString("5 HP");
					balls.clear();
				}
			
			    }

		

		else if (gameState == gameStateClass::exit) {

			// std::cout << "Exit state activated" << std::endl;
			// std::cout << "HighScore: " << highScore << std::endl;

			window.close();
		}











		//window.clear();
		//window.draw(food);
		//window.draw(player);
		//window.draw(smartEnemy);
		//window.draw(enemy);
		//window.draw(bullet);
		//window.draw(scoreText);
		//window.display();


	}



	return 0;


}
