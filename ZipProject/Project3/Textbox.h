using namespace std;
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <map>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
public:
	//sf::RectangleShape aRect;
	int sizeX, sizeY;
	ostringstream text;


	Textbox() {}

	Textbox(int _sizeX, int _sizeY, sf::Color color, bool sel) {
		// define a 120x50 rectangle
		 //sf::RectangleShape aRect(sf::Vector2f(120, 50));
		sizeX = _sizeX;
		sizeY = _sizeY;
		// change the size to 100x100
		
		textbox.setCharacterSize(_sizeX);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel)
			textbox.setString("_");
		else
			textbox.setString("");
	}

	void setFont(sf::Font& font) {
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f pos) {
		textbox.setPosition(pos);
	}

	void setLimit(bool ToF,int lim) {
		hasLimit = ToF;
		limit = lim-1;
	}

	void setSelected(bool sel) {
		isSelected = sel;
		if (!sel) {
			string t = text.str();
			string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}
	string getText() {
		return text.str();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(textbox);
	}

	void typeOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit) {
					if (text.str().length() <= limit)
						inputLogic(charTyped);

					else if (text.str().length() > limit && charTyped == DELETE_KEY)
						deleteLastChar();

				}
				else
					inputLogic(charTyped);
			}
		}
	}

	bool isHovered(sf::RenderWindow& window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;
		float btnPosX =textbox.getPosition().x;
		float btnPosY = textbox.getPosition().y;

		float btnxPosWidth = textbox.getPosition().x +textbox.getLocalBounds().width;
		float btnyPosHeight =textbox.getPosition().y + textbox.getLocalBounds().height;

		if (mouseX< btnxPosWidth && mouseX> btnPosX && mouseY<btnyPosHeight && mouseY>btnPosY)
			return true;

		return false;

	}
private:
	sf::Text textbox;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) 
			text << static_cast<char>(charTyped);
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");

	}

	void deleteLastChar() {
		string t = text.str();
		string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str());
	}
};

