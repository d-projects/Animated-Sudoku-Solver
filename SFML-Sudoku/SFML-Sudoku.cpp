#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Zones.h"
#include "Numbers.h"
#include "Sudoku.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(450, 450), "Sudoku", sf::Style::Close | sf::Style::Resize);

	Zones sudoku_zones(450, 3, 5);
	Zones sudoku_zones_small(450, 9);
	sf::Font font;
	std::vector<std::vector<int>> changes;

	Numbers text_nums;
	// initalizes numbers as 0
	int initial_nums[9][9] = {
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,}
	};

	Sudoku board1(&text_nums, &sudoku_zones_small);

	text_nums.set_all_numbers(initial_nums);


	sudoku_zones_small.set_text_positions(text_nums);


	for (int i = 0; i < 9; i++) {
		sudoku_zones.push_zone(font);
	}
	for (int i = 0; i < 81; i++) {
		sudoku_zones_small.push_zone(font);
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

					if (event1.text.unicode <= 57 && event1.text.unicode >= 49) {
						if (indices[0] >= 0 && indices[1] >= 0) {
							text_nums.set_single_number((event1.text.unicode - 48), indices[0], indices[1]);
							board1.set_value((event1.text.unicode - 48), indices[0], indices[1]);
						}
					}

					else if (event1.text.unicode == 115 ) {
						changes = board1.solve();
					}
					break;
			}

			if (event1.type == event1.Closed) {
				window.close();
			}
		}

		if (!changes.empty()) {
			text_nums.set_single_number(changes[0][0], changes[0][1], changes[0][2]);
			sudoku_zones_small.highlight_zone(changes[0][1], changes[0][2]);
			changes.erase(changes.begin());
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
			indices = sudoku_zones_small.highlight_zone(mouse_pos);
			
		}

		std::vector<sf::RectangleShape> major_zones = sudoku_zones.get_major_zones();
		std::vector<sf::RectangleShape> minor_zones = sudoku_zones_small.get_major_zones();

		window.clear(sf::Color::White);
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
