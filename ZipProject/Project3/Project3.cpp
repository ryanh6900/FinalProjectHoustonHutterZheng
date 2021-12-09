//Files
#include "LinkedList.h"
#include "MapProject.h"
#include "place.h"
#include "graph.h"
#include "dataGeneration.h"
#include "Textbox.h"
#include "Button.h"

//Includes
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <map>

//Defines
#define TAB_SIZE 25375;

using namespace std;

bool isMouseOver(sf::RenderWindow& window, sf::RectangleShape rect) {
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;
	float rectPosX = rect.getPosition().x;
	float rectPosY =rect.getPosition().y;

	float rectxPosWidth = rect.getPosition().x + rect.getLocalBounds().width;
	float rectyPosHeight = rect.getPosition().y + rect.getLocalBounds().height;

	if (mouseX< rectxPosWidth && mouseX> rectPosX && mouseY<rectyPosHeight && mouseY>rectPosY)
		return true;

	return false;
}
int main()
{
	//Generate graph data from named-places.txt
	//generateData();
	graph* _graph = new graph();
	vector<string> path;
	

	
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 455, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(900, 900), "", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);
	/*::RenderWindow loadingScreen;
	sf::Vector2i laodingWindow((sf::VideoMode::getDesktopMode().width / 2) - 455, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	loadingScreen.create(sf::VideoMode(900, 900), "LoadingScreen", sf::Style::Titlebar | sf::Style::Close);
	loadingScreen.setPosition(centerWindow);
	loadingScreen.setKeyRepeatEnabled(true);*/
	
	
	

	sf::Font arial;
	arial.loadFromFile("arial.ttf");

	Textbox textbox1(15, 5, sf::Color::Black,true);
	textbox1.setFont(arial);
	textbox1.setLimit(true, 12);
	textbox1.setPosition({ 300,105 });

	Textbox textbox2(15, 5, sf::Color::Black, false);
	textbox2.setFont(arial);
	textbox2.setLimit(true, 12);
	textbox2.setPosition({ 100,150 });


	sf::RectangleShape rectA(sf::Vector2f(120, 50));
	rectA.setSize(sf::Vector2f((textbox1.sizeX) * 10, textbox1.sizeY * 5)); //(textbox1.text.str().length() + 1) * 10
	rectA.setFillColor(sf::Color(120, 120, 120));
	rectA.setPosition({ 300,105 });

	sf::RectangleShape rectB(sf::Vector2f(120, 50));
	rectB.setSize(sf::Vector2f(textbox2.sizeX * 10, textbox2.sizeY * 5)); //(textbox2.text.str().length() + 1) * 10
	rectB.setFillColor(sf::Color(120, 120, 120));
	rectB.setPosition({ 300,155 });

	sf::Text labelCityA, labelCityB;
	labelCityA.setString("City A: ");
	labelCityA.setFont(arial);
	labelCityA.setFillColor(sf::Color::Black);
	labelCityA.setPosition({200,100 });

	labelCityB.setString("City B: ");
	labelCityB.setFont(arial);
	labelCityB.setFillColor(sf::Color::Black);
	labelCityB.setPosition({200,150 });
	

	Button calcBtn("Calculate", { 200,50 }, 20, sf::Color::Green, sf::Color::Black);
	calcBtn.setPosition({ 250,200 });
	calcBtn.setFont(arial);
	sf::Text loadText;
	loadText.setString("Loading Data for all US Cities...");
	loadText.setFont(arial);
	loadText.setCharacterSize(60);
	loadText.setFillColor(sf::Color::Black);
	loadText.setPosition({ 50,100 });

	bool firstTime = true;

	while (window.isOpen()) {
		sf::Event aEvent;
		
		if(firstTime) {
			sf::RectangleShape Loading(sf::Vector2f(120, 50));
			
			Loading.setSize({ 900,200 }); //(textbox1.text.str().length() + 1) * 10
			Loading.setFillColor(sf::Color::Yellow);
			Loading.setPosition({ 0,0 });
			Loading.move(0, 50);
			window.clear(sf::Color(200, 255, 255));

			window.draw(labelCityA);
			window.draw(labelCityB);

			window.draw(rectA);
			window.draw(rectB);
			textbox1.drawTo(window);
			calcBtn.drawTo(window);
			window.draw(Loading);
			window.draw(loadText);
			window.display();

			
			//populateGraph(*_graph);
			firstTime = false;
		}
		else {
			/*if (isMouseOver(window, rectA)) {
				textbox1.setSelected(true);
				textbox2.setSelected(false);
			}*/

			/*if (isMouseOver(window, rectB)) {
				textbox2.setSelected(true);
				textbox1.setSelected(false);
			}*/
			//else if (!textbox1.isHovered(window))
				//textbox1.setSelected(false);
			sf::String textCityA = textbox1.getText();
			sf::String textCityB = textbox2.getText();

			while (window.pollEvent(aEvent)) {
				switch (aEvent.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::TextEntered:
					textbox1.typeOn(aEvent);
					break;
				case sf::Event::MouseMoved:
					if (calcBtn.isMouseOver(window))
						calcBtn.setBackColor(sf::Color::White);
					else
						calcBtn.setBackColor(sf::Color::Blue);
					break;
				case sf::Event::MouseButtonReleased:
					if (calcBtn.isMouseOver(window)) {
						cout << _graph->BellmanFord(textCityA, textCityB, path);
						//cout << _graph->dijkstra("Orlando FL", "Lansing MI", path);
					}


				}
			}


			window.clear(sf::Color(200, 255, 255));

			window.draw(labelCityA);
			window.draw(labelCityB);

			window.draw(rectA);
			window.draw(rectB);
			textbox1.drawTo(window);
			textbox2.drawTo(window);
			calcBtn.drawTo(window);

			window.display();

		}		
		
	}
	
}
