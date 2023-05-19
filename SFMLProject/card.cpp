#include "card.h"

card::card(std::string card_name, const sf::Texture& sprite_texture, const sf::Texture& sprite_hidden_texture) :
	card_name(std::move(card_name)),
	card_hidden_texture(sprite_hidden_texture),
	card_shown_texture(sprite_texture)
{
	card_sprite.setTexture(sprite_hidden_texture);
}

card::card(const card& other) :
	card_name(other.card_name),
	card_hidden_texture(other.card_hidden_texture),
	card_shown_texture(other.card_shown_texture)
{
	card_sprite.setTexture(*other.card_sprite.getTexture());
	card_sprite.setPosition(other.card_sprite.getPosition());
}

void card::set_sprite_position(const sf::Vector2<float> position)
{
	card_sprite.setPosition(position);
}

void card::fix_sprite_size()
{
	card_sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
}

void card::flip_card()
{
	card_shown = !card_shown;
	card_sprite.setTexture(card_shown ? card_shown_texture : card_hidden_texture);
}

void card::hide_card()
{
	card_sprite.setTexture(card_hidden_texture);
}
