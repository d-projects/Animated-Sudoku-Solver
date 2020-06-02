// class for the numbers as text
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Numbers {

	sf::Text numbers[9][9];
	sf::Font font;

public:
	Numbers() : numbers() {

		// creates a text instance for each square on the board; the text string is not set yet
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				sf::Text num;
				num.setCharacterSize(20);
				num.setFillColor(sf::Color::Red);
				num.setFont(font);
				numbers[i][j] = num;
			}
		}

		// loads the Open Sans font; SFML doesn't have direct access to fonts
		if (!font.loadFromFile("OpenSans-Regular.ttf")) {
			std::cout << "Error loading font file" << std::endl;
		}
	}

	void set_single_number(int n, int row, int col) {
		//check this !!!!
		numbers[col][row].setString(std::to_string(n));
	}

	// sets position of text number on board
	void set_position(int row, int col, sf::Vector2f v) {
		numbers[row][col].setPosition(v);
	}

	sf::Text get_num(int row, int col) {
		return numbers[row][col];
	}

};
