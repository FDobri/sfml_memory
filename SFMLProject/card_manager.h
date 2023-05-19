#pragma once
#include "card.h"

constexpr int CARD_COUNT = 10;

class card_manager
{
private:
	std::vector<std::shared_ptr<card>> cards;

public:
	std::vector<std::shared_ptr<card>>& get_cards() { return cards; }

	void init_cards(const std::vector<sf::Texture>& textures, const sf::Texture& card_back_texture);
	void clear_cards();
	void check_for_solved_cards() const;
	void query_mouse_click(const sf::Vector2i& click_position, int& current_click_counter) const;
	static void on_card_clicked(const std::shared_ptr<card>& clicked_card, int& click_count);
};
