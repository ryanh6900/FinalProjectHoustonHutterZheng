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
	graph* _graph = new graph();
	
	//map<int, Textbox> mp;
	
	
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 455, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(900, 1000), "US Trip Calculator", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);
	/*::RenderWindow loadingScreen;
	sf::Vector2i laodingWindow((sf::VideoMode::getDesktopMode().width / 2) - 455, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	loadingScreen.create(sf::VideoMode(900, 900), "LoadingScreen", sf::Style::Titlebar | sf::Style::Close);
	loadingScreen.setPosition(centerWindow);
	loadingScreen.setKeyRepeatEnabled(true);*/
	
	
	

	sf::Font arial;
	arial.loadFromFile("arial.ttf");
	sf::RectangleShape rectA(sf::Vector2f(120, 20));
	rectA.setSize(sf::Vector2f(400,20 )); //(textbox1.text.str().length() + 1) * 10
	rectA.setFillColor(sf::Color(200,200, 200));
	rectA.setPosition({ 300,60 });

	sf::RectangleShape rectB(sf::Vector2f(120, 20));
	rectB.setSize(sf::Vector2f(400, 20)); //(textbox2.text.str().length() + 1) * 10
	rectB.setFillColor(sf::Color(200,200,200));
	rectB.setPosition({300,110 });

	Textbox textbox1(15, 5, sf::Color::Black,false,rectA);
	textbox1.setFont(arial);
	textbox1.setLimit(true, 50);
	textbox1.setPosition({300,60 });
	//mp[1] = textbox1;

	Textbox textbox2(15, 5, sf::Color::Black, false,rectB);
	textbox2.setFont(arial);
	textbox2.setLimit(true, 50);
	textbox2.setPosition({300,110 });
	//mp[2] = textbox2;

	


	sf::Text labelCityA, labelCityB;
	labelCityA.setString("City A: ");
	labelCityA.setFont(arial);
	labelCityA.setFillColor(sf::Color::Black);
	labelCityA.setPosition({200,50 });

	labelCityB.setString("City B: ");
	labelCityB.setFont(arial);
	labelCityB.setFillColor(sf::Color::Black);
	labelCityB.setPosition({200,100 });
	
	sf::Text Note;
	Note.setString("Note: All calculated total distances DO NOT include the distance added by changing elevation.");
	Note.setFont(arial);
	Note.setFillColor(sf::Color::Black);
	Note.setCharacterSize(20);
	Note.setPosition(30, 400);

	sf::Text loadText;
	loadText.setString("Loading Data for all US Cities...");
	loadText.setFont(arial);
	loadText.setCharacterSize(60);
	loadText.setFillColor(sf::Color::Black);
	loadText.setPosition({ 50,200 });

	Button calcBtn("Calculate", { 250,75 }, 60, sf::Color::White, sf::Color::Black);
	/*Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);
		button.setSize(size);
		button.setFillColor(bgColor);
	}*/
	calcBtn.setFont(arial);
	calcBtn.setPosition({300,150});
	

	Button Solving("Solving...", { 350,75 }, 60, sf::Color::Green, sf::Color::Black);
	 //(textbox1.text.str().length() + 1) * 10
	Solving.setFont(arial);
	Solving.setPosition({350,150});


	Button SolvingD("Solving Dijkstra...", {500,75 }, 60, sf::Color::Red, sf::Color::Black);
	//(textbox1.text.str().length() + 1) * 10
	SolvingD.setFont(arial);
	SolvingD.setPosition({ 200,150 });

	Button SolvingB("Solving Bellman-Ford...", { 625,75 }, 60, sf::Color::Yellow, sf::Color::Black);
	//(textbox1.text.str().length() + 1) * 10
	SolvingB.setFont(arial);
	SolvingB.setPosition({ 200,150 });

	/*sf::Text SolveText;
	SolveText.setString("Solving...");
	SolveText.setFont(arial);
	SolveText.setCharacterSize(60);
	SolveText.setFillColor(sf::Color::Black);
	SolveText.setPosition({ 250,200 });*/

	bool firstTime = true;
	bool currA,currB;

	sf::Text column1;
	column1.setFont(arial);
	column1.setCharacterSize(32);
	column1.setFillColor(sf::Color::Black);
	column1.setPosition(43, 240);
	

	sf::Text column2;
	column2.setFont(arial);
	column2.setCharacterSize(32);
	column2.setFillColor(sf::Color::Black);
	column2.setPosition(468, 240);
	
	
	sf::Text resultBellman;
	resultBellman.setFont(arial);
	resultBellman.setCharacterSize(28);
	resultBellman.setFillColor(sf::Color::Black);
	resultBellman.setPosition(75, 280);

	sf::Text resultDijkstra;
	resultDijkstra.setFont(arial);
	resultDijkstra.setCharacterSize(28);
	resultDijkstra.setFillColor(sf::Color::Black);
	resultDijkstra.setPosition(500, 280);

	while (window.isOpen()) {
		sf::Event anEvent;
		if(firstTime) {
			sf::RectangleShape Loading(sf::Vector2f(120, 50));
			
			Loading.setSize({900,200 }); //(textbox1.text.str().length() + 1) * 10
			Loading.setFillColor(sf::Color::Yellow);
			Loading.setPosition({ 0,0 });
			Loading.move(0, 150);
			window.clear(sf::Color(200, 255, 255));
			window.draw(Loading);
			window.draw(loadText);
			window.draw(Note);
			window.display();

			
			populateGraph(*_graph);
			firstTime = false;
		}
		else {
			
			window.clear(sf::Color(200, 255, 255));
			window.draw(labelCityA);
			window.draw(labelCityB);
			window.draw(rectA);
			window.draw(rectB);
			textbox1.drawTo(window);
			textbox2.drawTo(window);
			calcBtn.drawTo(window);
			
			
			
			sf::String textCityA = textbox1.getText();
			sf::String textCityB = textbox2.getText();

			//sf::RectangleShape rectA(sf::Vector2f(120, 50));
			//rectA.setSize(sf::Vector2f((textbox1.text.str().length() + .8) * 10, textbox1.sizeY * 5)); //(textbox1.text.str().length() + 1) * 10
			//rectA.setFillColor(sf::Color(120, 120, 120));
			//rectA.setPosition({ 300,105 });

			//sf::RectangleShape rectB(sf::Vector2f(120, 50));
			//rectB.setSize(sf::Vector2f((textbox2.text.str().length() + .8) * 10, textbox2.sizeY * 5)); //(textbox2.text.str().length() + 1) * 10
			//rectB.setFillColor(sf::Color(120, 120, 120));
			//rectB.setPosition({ 300,155 });

	   if(textbox1.isMouseOver(window) && !(textbox2.isMouseOver(window)) && sf::Event::MouseButtonReleased) {
			   textbox1.setSelected(true);
			   textbox2.setSelected(false);
			   currA = true;
			   currB = false;
			}

		if(textbox2.isMouseOver(window) && !(textbox1.isMouseOver(window)) && sf::Event::MouseButtonReleased) {
					textbox1.setSelected(false);
					textbox2.setSelected(true);
					currB = true;
					currA = false;
			}
			//else if (!textbox1.isHovered(window))
				//textbox1.setSelected(false);
			

			while (window.pollEvent(anEvent)) {
				switch (anEvent.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::TextEntered:
					if(currA && !currB)
					textbox1.typeOn(anEvent);
					else if(currB && !currA)
					textbox2.typeOn(anEvent);
					break;

				case sf::Event::MouseMoved:
					if (calcBtn.isMouseOver(window))
						calcBtn.setBackColor(sf::Color::Cyan);
					else
						calcBtn.setBackColor(sf::Color::White);
					break;

				case sf::Event::MouseButtonReleased:
					if (calcBtn.isMouseOver(window)) {
						currA = false;
						currB = false;
						column2.setString("Using Dijkstra:");
						column1.setString("Using Bellman-Ford:");
						
						std::string ansBellman = "Total Distance includes elevation\n";
						//window.draw(resultBellman);
						std::string ansDijkstra = "";
						resultBellman.setString(ansBellman);
						resultDijkstra.setString(ansDijkstra);
						vector<string> pathBell;
						vector<string> pathDijk;
						//Solving.drawTo(window);
						window.display();
						//window.draw(SolveText);
						
						/*cout << _graph->BellmanFord(textbox1.getText(), textbox2.getText(), path);*/
						
						SolvingB.drawTo(window);
						window.display();
						ansBellman = "Total Distance: " + to_string(_graph->BellmanFord(textbox1.getText(), textbox2.getText(), pathBell)) + "km" + "\n";
						//ansBellman +=  _graph->BellmanFord("Orlando FL", "LansBellmaning MI", path) +"km";
						ansBellman += "Stops: \n";
						for (int i = pathBell.size()-2; i>0; i--)
							ansBellman += pathBell[i] + "\n";
						SolvingD.drawTo(window);
						window.display();

						ansDijkstra = "Total Distance: " + to_string(_graph->dijkstra(textbox1.getText(), textbox2.getText(), pathDijk)) + "km" + "\n";
						ansDijkstra += "Stops: \n";
						for (int i = pathDijk.size()-2; i > 0; i--)
							ansDijkstra += pathDijk[i] + "\n";
						/*for (int i = 0; i < path.size()-1; i++)
							cout<< path[i] << "\n";*/
						//cout << _graph->dijkstra(textCityA, textCityB, path);
						//resultBellman.setString(to_string(_graph->BellmanFord(textCityA, textCityB, path)));
						
						resultBellman.setString(ansBellman);
						resultDijkstra.setString(ansDijkstra);
						//cout << _graph->BellmanFord("Orlando FL", "LansBellmaning MI", path);
						
						

						//resultBellman.setString(to_string(_graph->dijkstra(textCityA, textCityB, path)));
					}
					

					
				}
				
			}


			

			window.draw(labelCityA);
			window.draw(labelCityB);

			window.draw(rectA);
			window.draw(rectB);
			textbox1.drawTo(window);
			textbox2.drawTo(window);
			
			window.draw(column1);
			window.draw(column2);

			window.draw(resultBellman);
			window.draw(resultDijkstra);
			window.display();

		}		
		
	}
	
}
