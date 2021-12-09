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

int main()
{
	//Generate graph data from named-places.txt
	//generateData();
	sf::Text textCityA;
	sf::Text textCityB;
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 455, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(900, 900), "SFML Project", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);

	sf::Font arial;
	arial.loadFromFile("arial.ttf");

	Textbox textbox1(15, 5, sf::Color::Black, true);
	textbox1.setFont(arial);
	textbox1.setLimit(true, 12);
	textbox1.setPosition({ 100,100 });

	Button btn1("Calculate", { 200,50 }, 20, sf::Color::Green, sf::Color::Black);
	btn1.setPosition({ 100,200 });
	btn1.setFont(arial);
	
	while (window.isOpen()) {
		sf::Event aEvent;
		window.clear(sf::Color(200, 255, 255));
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			textbox1.setSelected(true);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			textbox1.setSelected(false);*/
		
		while (window.pollEvent(aEvent)) {
			switch (aEvent.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				textbox1.typeOn(aEvent);
				break;
			case sf::Event::MouseMoved:
				if (btn1.isMouseOver(window))
					btn1.setBackColor(sf::Color::White);
				else
				 btn1.setBackColor(sf::Color::Green);
			}
		}
		window.clear(sf::Color(200, 255, 255));
		
		sf::RectangleShape rectangle(sf::Vector2f(120, 50));
		rectangle.setSize(sf::Vector2f((textbox1.text.str().length()+1)*10, textbox1.sizeY*5));
		rectangle.setFillColor(sf::Color(120, 120, 120));
		rectangle.setPosition({ 100,100 });
		window.draw(rectangle);
		textbox1.drawTo(window);
		btn1.drawTo(window);
		window.display();
	}
	graph* _graph = new graph();

	vector<string> path;

	populateGraph(*_graph);
	cout << _graph->BellmanFord("Orlando FL", "Lansing MI", path);
	cout << _graph->dijkstra("Orlando FL", "Lansing MI", path);
}
