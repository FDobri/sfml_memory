// SFMLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SFML/Graphics.hpp"
#include "card_manager.h"
#include "grid_layout.h"
#include <iostream>
#include <vector>

constexpr int CARDS_COUNT = 10;

void set_card_positions(std::vector<std::shared_ptr<card>>& cards, const sf::RenderWindow& window)
{
	for (size_t i = 0; i < cards.size(); ++i)
	{
		cards[i]->set_sprite_position(grid_layout::get_child_position(window.getSize().x,
			window.getSize().y, i));
	}
}

void run_game_loop()
{
	//init preparation stuff
	std::vector<sf::Texture> textures;
	sf::Texture card_back_texture;
	card_manager card_manager;

	int current_click_counter = 0;
	int current_steps_counter = 0;

	// path constants
	const std::string resources_path = "..\\Resources\\";
	const std::string textures_folder = "CardTextures\\";
	const std::string fonts_folder = "Fonts\\";
	const std::string file_prefix = "card";
	const std::string back_suffix = "back";
	const std::string font_name = "SunnyspellsRegular-MV9ze.otf";

	// clock
	sf::Clock clock;
	sf::Time card_check_period = sf::seconds(0.5f); // Set the interval to 2 seconds

	bool should_check_for_cards = false;

	// create window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "hi");

	// create font
	sf::Font desired_font;
	std::string font_path = resources_path + fonts_folder + font_name;
	if (!desired_font.loadFromFile(font_path))
	{
		std::cerr << "Error loading font at path: " + font_path << std::endl;
	}

	//create title text
	sf::Text title_text("Memory, the game.", desired_font, 50);
	title_text.setPosition(25.0f, 25.0f);
	sf::Text steps_counter_text("0", desired_font, 50);
	steps_counter_text.setPosition(window.getSize().x - 100, 25.0f);

	// load textures
	for (int i = 0; i < CARDS_COUNT; i++)
	{
		sf::Texture texture;
		std::string combined_path = resources_path + textures_folder + file_prefix + std::to_string(i + 1) + ".png";
		if (texture.loadFromFile(combined_path))
		{
			textures.push_back(texture);
		}
		else
		{
			std::cerr << "Error loading texture from file path: " << combined_path << std::endl;
		}
	}

	// load card back texture
	std::string combined_path_card_bg = resources_path + textures_folder + back_suffix + ".png";
	if (!card_back_texture.loadFromFile(combined_path_card_bg))
	{
		std::cerr << "Error loading card back texture from file path: " << combined_path_card_bg << std::endl;
	}

	// init cards
	card_manager.init_cards(textures, card_back_texture);

	while (window.isOpen())
	{
		// place cards on screen using the grid_layout which feeds the position depending on the card index
		set_card_positions(card_manager.get_cards(), window);

		// handle events
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				std::cout << "Closing the window." << std::endl;
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				set_card_positions(card_manager.get_cards(), window);
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && !should_check_for_cards)
				{
					card_manager.query_mouse_click(sf::Mouse::getPosition(window), current_click_counter);
					if (current_click_counter >= 2)
					{
						should_check_for_cards = true;
						clock.restart();
					}
				}
			}
		}

		if (should_check_for_cards && clock.getElapsedTime() >= card_check_period)
		{
			card_manager.check_for_solved_cards();
			should_check_for_cards = false;
			current_click_counter = 0;
			current_steps_counter++;
			steps_counter_text.setString(std::to_string(current_steps_counter));
		}

		// clear the screen and render the sprite
		window.clear();
		for (const auto& card : card_manager.get_cards())
		{
			window.draw(card->get_sprite());
		}

		window.draw(title_text);
		window.draw(steps_counter_text);

		window.display();
	}
}

int main()
{
	run_game_loop();
	return 0;
}
