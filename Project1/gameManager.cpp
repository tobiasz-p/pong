#include <gameManager.h>
#include <time.h>
#include <random>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <memory>

#define THICKNESS 10
#define FONTSIZE 64 
#define sizeX 15
#define sizeY 150
using namespace std;

gameManager::gameManager(int w, int h)
{
	srand(time(NULL));
	score1 = score2 = 0;
	scoreSpace = 100;
	windowWidth = w; windowHeight = h;
	ball = new Ball(windowWidth/2, (windowHeight + scoreSpace - THICKNESS)/2);
	player1 = new Paddle(THICKNESS + 10, (h + scoreSpace)/2- sizeY/2, sizeX, sizeY);
	player2 = new Paddle(w - 25 - THICKNESS, (h + scoreSpace) / 2 - sizeY / 2, sizeX, sizeY);
	player1->setEnemy(player2);
	player2->setEnemy(player1);
	item1 = new sizeUp(80, 30, sf::Color(255, 0, 0, 255), player1);
	item2 = new sizeUp(windowWidth - 80 - 50, 30, sf::Color(255, 0, 0, 255), player2);
	sf::Text text, timer, pressStartKey;
	sf::RectangleShape table, middle;
	std::clock_t start, itemUseTime = 0;
	menu = new Menu(400, 400, (windowWidth / 2) - 200, (windowHeight / 2) - 200);
	quit = false;
	run = true;
	koniecgry = false;
	runZasady = true;
	pressStart = true;
	runScoreBoard = true;
	lastRandomized = 0;
	fstream plikLoad;
}
gameManager::~gameManager()
{
	delete ball, player1, player2, menu;
}
void gameManager::Logic()
{
	sf::FloatRect ballPos = ball->getPosition();
	sf::FloatRect player1Pos = player1->getPosition();
	sf::FloatRect player2Pos = player2->getPosition();
	float size = ballPos.width;

	//kolizja z rakietk¹
	if (ballPos.intersects(player1->getPosition()) or (ballPos.intersects(player2->getPosition())))
	{
		ball->negateXv();

		try {
			if (abs(ball->getxV()) < 0.9f && abs(ball->getyV()) < 0.9f)
			{
				if (ball->getxV() > 0 && ball->getyV() > 0)
				ball->setSpeed(ball->getxV() + .05f, ball->getyV() + .05f);
				else if (ball->getxV() > 0 && ball->getyV() < 0)
				ball->setSpeed(ball->getxV() + .05f, ball->getyV() - .05f);
				else if (ball->getxV() < 0 && ball->getyV() > 0)
				ball->setSpeed(ball->getxV() - .05f, ball->getyV() + .05f);
				else if (ball->getxV() < 0 && ball->getyV() < 0)
				ball->setSpeed(ball->getxV() - .05f, ball->getyV() - .05f);
			}
			else throw string ("Maksymalna predkosc osiagnieta");
		}
		catch(string e){
			ball->setSpeed(0.5f, 0.5f);
			cout << e <<endl;

		}
	}
	//obicie od góry

	else if (ballPos.top < scoreSpace) {
		ball->negateYv();
	}
	//odbicie od do³u
	else if (ballPos.top > windowHeight - size - THICKNESS) {
		ball->negateYv();

	}
	else if (ballPos.left <= THICKNESS) {
		ScoreUp(player2);
		ball->setSpeed(.4f, .4f);

	}
	else if (ballPos.left + size >= windowWidth - THICKNESS) {
		ScoreUp(player1);
		ball->setSpeed(-.4f, -.4f);
	}

	checkItem(item1);
	checkItem(item2);
	randomizeItems();
}

void gameManager::ScoreUp(Paddle* player)
{
	if (player == player1)
		score1++;
	else if (player == player2)
		score2++;
	std::cout << score1 << " : " << score2 << endl;

	ball->Reset();
	player1->Reset();
	player2->Reset();
}

void gameManager::checkItem(Item *item) {
		if (item->getUsed() and (std::clock() - item->getUseTime()) / 1000 >= 5) {
			item->reset();
		}
}


void gameManager::saveToFile()
{

	std::string tmp;
	fstream tmpFile;
	fstream plikLoad;
	tmpFile.open("./resources/tmpfile.txt", std::ios::in | std::ios::out);
	plikLoad.open("./resources/scores.txt", std::ios::in | std::ios::out);
	tmpFile << plikLoad.rdbuf();
	tmpFile.close();
	plikLoad.close();
	plikLoad.open("./resources/scores.txt", std::ios::in | std::ios::out);
	tmpFile.open("./resources/tmpfile.txt", std::ios::in | std::ios::out);
	if (tmpFile.good()) {
		for (int i = 0; i < 3; i++) {
			getline(tmpFile, tmp);
			plikLoad << tmp << endl;
		}
		plikLoad <<std::setw(6) << score1 << std::setfill(' ') << "    |" << std::setw(6) << score2 << std::setfill(' ') << "    |" <<std::setw(3)<< min << 
			std::setfill(' ')<<":" << std::setw(2) << std::setfill('0') << sec  << endl;
		for (int i = 0; i < 9; i++) {
			getline(tmpFile, tmp);
			plikLoad << tmp << endl;
		}
		plikLoad.close();
		tmpFile.close();

	}
	else
	plikLoad.close();
	tmpFile.close();
}

void gameManager::randomizeItems() {
	if ((std::clock() - lastRandomized)/1000 >= 15) {
		printf("randomize!\n");
		item1->reset();
		item2->reset();
		sf::FloatRect item1Pos = item1->getPosition();
		sf::FloatRect item2Pos = item2->getPosition();
		Paddle* whos1=item1->whos(); 
		Paddle* whos2=item2->whos(); 	
		delete item1;
		delete item2;
		
		int r = rand() % 2;
		lastRandomized = std::clock();
		if (!r) {

			item1 = new sizeUp(item1Pos.left, item1Pos.top, sf::Color(255, 0, 0, 255), whos1);
			item2 = new sizeUp(item2Pos.left, item2Pos.top, sf::Color(255, 0, 0, 255), whos2);
		}
		else{
			item1 = new sizeDown(item1Pos.left, item1Pos.top, sf::Color(0, 255, 0, 255), whos1);
			item2 = new sizeDown(item2Pos.left, item2Pos.top, sf::Color(0, 255, 0, 255), whos2);
		}
	}
}

void gameManager::Win(sf::RenderWindow& window) {
	if (score1 == 11 || score2 == 11)
	{
		koniecgry = true;

		win.setSize(sf::Vector2f(800, 200));
		win.setOrigin(400, 100);
		win.setPosition(windowWidth/2, windowHeight/2);
		win.setOutlineColor(sf::Color(28, 84, 045));

		
			if (score1 == 11)
			{
				if (!texture_player1.loadFromFile("./resources/images/player1.png"))
				{
					// error...
				}
				win.setTexture(&texture_player1);
			}
			else
			{
				if (!texture_player2.loadFromFile("./resources/images/player2.png"))
				{
					// error...
				}
				win.setTexture(&texture_player2);
			}
		
		
		window.draw(win);
		window.display();
		if (koniecgry) {
			saveToFile();
			score1 = 0;
			score2 = 0;
		}
		while (koniecgry) {
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				koniecgry = false;
				pressStart = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				koniecgry = false;;
				run = false;
			}
		}
		
	}
}

void gameManager::Run()
{
	
	start = std::clock();
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Ping Pong");

	fontRetro.loadFromFile("./resources/fonts/retro.ttf");
	fontCourier.loadFromFile("./resources/fonts/cour.ttf");

	text.setCharacterSize(FONTSIZE);
	timer.setCharacterSize(40);
	text.setFont(fontRetro);
	timer.setFont(fontRetro);
	text.setOutlineThickness(1);
	timer.setOutlineThickness(1);

	table.setSize(sf::Vector2f(windowWidth - 2 * THICKNESS, windowHeight - scoreSpace - THICKNESS));
	table.setPosition(sf::Vector2f(THICKNESS, scoreSpace));
	table.setOutlineColor(sf::Color::White);
	table.setFillColor(sf::Color(0, 115, 59, 255));
	table.setOutlineThickness(THICKNESS);
	middle.setSize(sf::Vector2f(10, windowHeight - THICKNESS - scoreSpace));
	sf::FloatRect middleBounds = middle.getLocalBounds();
	middle.setOrigin(sf::Vector2f(middleBounds.left + middleBounds.width / 2.0f, middleBounds.top + middleBounds.height / 2.0f));
	middle.setPosition(sf::Vector2f(windowWidth / 2.0f, (windowHeight + scoreSpace) / 2.0f - THICKNESS / 2.0f));
	player1->setColor(0, 0, 0, 255); //zmiana koloru rakietki na czarny

	pressStartKey.setFont(fontRetro);
	pressStartKey.setCharacterSize(90);
	pressStartKey.setOutlineThickness(5);
	pressStartKey.setString("Nacisnij spacje, aby zagrac!");
	sf::FloatRect startBounds = pressStartKey.getLocalBounds();
	pressStartKey.setOrigin(sf::Vector2f(startBounds.left + startBounds.width / 2.0f, startBounds.top));
	pressStartKey.setPosition(windowWidth / 2, windowHeight / 2);

	playerText.setPosition(60, 300);
	playerText.setFont(fontRetro);
	playerText.setCharacterSize(40);

	while (window.isOpen())
	{
		
		//sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu->MoveUp();
					break;

				case sf::Keyboard::Down:
					menu->MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu->GetPressedItem())
					{
					case 0:
						run = true;
						start = std::clock();
						pressStart = true;
						while (run)
						{
							
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
							{
								if (player2->getY() > scoreSpace)
									player2->moveUp();
							}
							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
							{
								if (player2->getY() < windowHeight - player2->getPosition().height - THICKNESS)
									player2->moveDown();
							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
							{
								if (player1->getY() > scoreSpace)
									player1->moveUp();
							}
							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
							{
								if (player1->getY() < windowHeight - player1->getPosition().height - THICKNESS)
									player1->moveDown();
							}

							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
							{
								if (!item1->getUsed()) {
									item1->use();
									item1->setColor(0, 0, 0, 255);
									item1->setUseTime(std::clock());
								}
							}
							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
							{
								if (!item2->getUsed()) {
									item2->use();
									item2->setColor(0, 0, 0, 255);
									item2->setUseTime(std::clock());
								}
							}
							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Event::Closed)
							{
								// quit...
								// Someone closed the window- bye
								run = false;
								window.close();
							}

							Win(window);
							if (!koniecgry)
							{
								Logic();
								sec = (std::clock() - start) / 1000;
								min = sec / 60;
								sec -= min * 60;
								std::stringstream ss, time;
								ss << score1 << " : " << score2;
								time << min << ":" << std::setw(2) << sec << std::setfill('0');
								text.setString(ss.str());
								timer.setString(time.str());
								sf::FloatRect textBounds = text.getLocalBounds();
								sf::FloatRect timerBounds = timer.getLocalBounds();
								//sf::FloatRect timerBounds = text.getLocalBounds();
								text.setOrigin(sf::Vector2f(textBounds.left + textBounds.width / 2.0f, textBounds.top));
								timer.setOrigin(sf::Vector2f(timerBounds.left + timerBounds.width / 2.0f, timerBounds.top));
								
								text.setPosition(sf::Vector2f(windowWidth / 2.0f, 10));
								timer.setPosition(sf::Vector2f(windowWidth / 2.0f, 60));
								ball->Move();
								player1->update();
								player2->update();
								ball->update();
								window.clear(sf::Color(26, 128, 182, 255));
								window.draw(table);
								window.draw(middle);
								window.draw(player1->getShape());
								window.draw(player2->getShape());
								window.draw(ball->getShape());
								window.draw(text);
								window.draw(timer);
								window.draw(item1->getShape());
								window.draw(item2->getShape());
							}
	
								if (pressStart) {
									window.draw(pressStartKey);	
								}
								window.display();
								while (pressStart) {
									
									if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
									{
										Sleep(500);
										pressStart = false;
										start = std::clock();
										lastRandomized = clock();
									}
										
								}
						}
						break;

					case 1:
						while (runZasady)
						{
							menu->DisplayZasady(window);
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
							{
								runZasady = false;
							}
						}
						runZasady = true;
						break;
					case 2:
						while (runScoreBoard) {
							menu->displayScores(window, fontCourier);
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
							{
								runScoreBoard = false;
							}
						}
						runScoreBoard = true;
						break;
					case 3:
						window.close();
						break;
						}

						break;
					}

					break;
				case sf::Event::Closed:
					window.close();

					break;

				}
			}

			window.clear(sf::Color(26, 128, 182, 255));
			menu->draw(window);
			window.display();
		}
	}
