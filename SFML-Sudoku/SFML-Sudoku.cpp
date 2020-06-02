#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Zones.h"
#include "Numbers.h"
#include "Sudoku.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(450, 450), "Sudoku", sf::Style::Close | sf::Style::Resize);

	// creates the instances of the squares on the board (one for the large 3x3 grid, the other for the 9x9 grid)
	Zones sudoku_zones(450, 3, 5);
	Zones sudoku_zones_small(450, 9);
	
	// used to store all the moves when the puzzle is solved
	std::vector<std::vector<int>> changes;

	// the object where the numbers will be stored as text
	Numbers text_nums;

	// creates the algorithm board
	Sudoku board1(&text_nums, &sudoku_zones_small);

	// allows the text to be placed with respect to the 9x9 grid
	sudoku_zones_small.set_text_positions(text_nums);


	for (int i = 0; i < 9; i++) {
		sudoku_zones.push_zone();
	}
	for (int i = 0; i < 81; i++) {
		sudoku_zones_small.push_zone();
	}

	std::vector<int> indices = { -1,-1 };

	while (window.isOpen()) {
		sf::Event event1;
		while (window.pollEvent(event1)) {

			switch (event1.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					break;
				case sf::Event::TextEntered:

					// checks if a number from 1 to 9 is pressed
					if (event1.text.unicode <= 57 && event1.text.unicode >= 49) {
						if (indices[0] >= 0 && indices[1] >= 0) {
							text_nums.set_single_number((event1.text.unicode - 48), indices[0], indices[1]);
							board1.set_value((event1.text.unicode - 48), indices[0], indices[1]);
						}
					}

					// "changes" is a 2-dimensional vector with all the moves to solve the inital board
					// needed so that the moves can be displayed visually
					else if (event1.text.unicode == 115 ) {
						changes = board1.solve();
					}
					break;
			}

			if (event1.type == event1.Closed) {
				window.close();
			}
		}

		// used to iterate through each "move" element of the vector of moves
		if (!changes.empty()) {
			text_nums.set_single_number(changes[0][0], changes[0][1], changes[0][2]);
			sudoku_zones_small.highlight_zone(changes[0][1], changes[0][2]);
			changes.erase(changes.begin());
		}

		// allows a user to enter a value by pressing on  a square
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
			indices = sudoku_zones_small.highlight_zone(mouse_pos);
			
		}

		// gets the textual
		std::vector<sf::RectangleShape> major_zones = sudoku_zones.get_major_zones();
		std::vector<sf::RectangleShape> minor_zones = sudoku_zones_small.get_major_zones();

		window.clear(sf::Color::White);

		// the following for loops display the text data on the window
		for (auto z : minor_zones) {
			window.draw(z);

		}
		for (auto z : major_zones) {
			window.draw(z);

		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				window.draw(text_nums.get_num(i,j));
			}
			
		}
		window.display();
	}

	return 0;
}
