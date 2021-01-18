// class for the squares on the board
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Numbers.h"

class Zones {

	std::vector<sf::RectangleShape> major_zones;

	float size;
	int zones;
	float thickness;
	int last_clicked_row;
	int last_clicked_col;

	sf::Font font;

public:
	Zones(float s, int z, float t = 0.5) : major_zones(), size(s / z), zones(z), thickness(t), last_clicked_row(0), last_clicked_col(0) {
		if (!font.loadFromFile("OpenSans-Regular.ttf")) {
			std::cout << "Error loading font file" << std::endl;
		}
	}

	// creates squares, determines their position on the sudoku grid, formats them, and stores them in a vector
	void push_zone() {
		if (major_zones.size() > zones * zones) {
			return;
		}

		sf::RectangleShape new_major_zone(sf::Vector2f(size, size));
		new_major_zone.setFillColor(sf::Color::Transparent);
		new_major_zone.setOutlineColor(sf::Color::Black);
		new_major_zone.setOutlineThickness(thickness);

		int num_major_zones = major_zones.size();

		sf::Vector2f zone_position(static_cast<float>((num_major_zones / zones) * size), static_cast<float>((num_major_zones % zones)) * size);
		new_major_zone.move(zone_position);
		major_zones.push_back(new_major_zone);

	}

	// sets the text (number) on top of each sqaure
	void set_text_positions(Numbers& nums) {
		int count = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				nums.set_position(i, j, sf::Vector2f(static_cast<float>((count / zones) * size + size / 2), static_cast<float>((count % zones)) * size + size / 4));
				count++;
			}
		}
	}

	// highlights a square  as blue when it is clicked
	std::vector<int> highlight_zone(sf::Vector2i pos) {
		int row = pos.y / (size);
		int col = pos.x / (size);
		// changes previously highlighted square to white
		major_zones[last_clicked_col * zones + last_clicked_row].setFillColor(sf::Color::White);
		// changes new clicked sqaure to blue
		major_zones[col * zones + row].setFillColor(sf::Color::Cyan);
		last_clicked_row = row;
		last_clicked_col = col;

		std::vector<int> indices = { row, col };
		return indices;
	}

	void highlight_zone(int row, int col) {

		// changes previously highlighted square to white
		major_zones[last_clicked_col * zones + last_clicked_row].setFillColor(sf::Color::White);
		// changes new clicked sqaure to blue
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;

		major_zones[col * zones + row].setFillColor(sf::Color(r, g, b));
		last_clicked_row = row;
		last_clicked_col = col;
	}

	// CHANGE NAME To zone!
	std::vector<sf::RectangleShape> get_major_zones() { return major_zones; }

};