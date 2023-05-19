#pragma once

#include "SFML/Graphics.hpp"

class card
{
private:
	std::string card_name;
	sf::Texture card_hidden_texture;
	sf::Texture card_shown_texture;
	sf::Sprite card_sprite;
	bool card_shown = false;
	bool card_solved = false;

public:
	card() = default;
	explicit card(std::string card_name, const sf::Texture& sprite_texture, const sf::Texture& sprite_hidden_texture);
	card(const card& other);
	~card() = default;

	const sf::Sprite& get_sprite() const { return card_sprite; }
	const std::string& get_card_id() const { return card_name; }
	bool is_card_shown() const { return card_shown; }
	bool is_card_solved() const { return card_solved; } 
	void solve_card() { card_solved = true; }
	void set_sprite_position(sf::Vector2<float> position);
	void fix_sprite_size();

	void flip_card();
	void hide_card();
};
