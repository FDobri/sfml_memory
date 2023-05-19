#include "card_manager.h"
#include <memory>
#include <random>
#include <algorithm>

void card_manager::init_cards(const std::vector<sf::Texture>& textures, const sf::Texture& card_back_texture)
{
	const std::string card_name_prefix = "card";
	int card_id = 1;
	int position_index = 0;
	for (auto&& texture : textures)
	{
		std::string card_name = card_name_prefix + std::to_string(card_id);
		cards.emplace_back(std::make_shared<card>(card_name, texture, card_back_texture));
		position_index++;
		cards.emplace_back(std::make_shared<card>(card_name, texture, card_back_texture));
		position_index++;
		card_id++;
	}

	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(cards.begin(), cards.end(), generator);
}

void card_manager::clear_cards()
{
	cards.clear();
}

void card_manager::on_card_clicked(const std::shared_ptr<card>& clicked_card, int& click_count)
{
	if (clicked_card->is_card_shown())
		return;

	clicked_card->flip_card();
	click_count++;
}

void card_manager::check_for_solved_cards() const
{
	int same_cards_flipped_count = 0;
	std::string first_flipped_card;
	std::vector<std::shared_ptr<card>> flipped_cards;
	for (auto&& card : cards)
	{
		if (card->is_card_solved() || !card->is_card_shown())
			continue;

		if (first_flipped_card._Equal(card->get_card_id()))
		{
			same_cards_flipped_count++;
		}

		if (first_flipped_card.empty())
		{
			first_flipped_card = card->get_card_id();
			same_cards_flipped_count++;
		}
		flipped_cards.push_back(card);
	}

	for (auto&& flipped_card : flipped_cards)
	{
		if (same_cards_flipped_count >= 2)
		{
			flipped_card->solve_card();
		}
		else
		{
			flipped_card->flip_card();
		}
	}
}

void card_manager::query_mouse_click(const sf::Vector2i& click_position, int& current_click_counter) const
{
	for (auto&& card : cards)
	{
		if (card->get_sprite().getGlobalBounds().contains((int)click_position.x, (int)click_position.y))
		{
			on_card_clicked(card, current_click_counter);
		}
	}
}
