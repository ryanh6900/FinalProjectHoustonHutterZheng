//Files
#include "LinkedList.h"
#include "MapProject.h"
#include "place.h"
#include "graph.h"
#include "dataGeneration.h"
#include "Textbox.h"

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

	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 455, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(900, 900), "SFML Project", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);
	Textbox textbox1(15, sf::Color::White, true);

	textbox1.setPosition({ 100,100 });

	while (window.isOpen()) {
		sf::Event Event;
		while (window.pollEvent(Event)) {
			switch (Event.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				textbox1.typeOn(Event);
			}
		}
		window.clear();
		textbox1.drawTo(window);
		window.display();
	}
	graph* _graph = new graph();

	vector<string> path;

	populateGraph(*_graph);
	cout << _graph->BellmanFord("Orlando FL", "Lansing MI", path);
	cout << _graph->dijkstra("Orlando FL", "Lansing MI", path);
}
