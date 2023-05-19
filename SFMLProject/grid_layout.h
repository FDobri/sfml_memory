#pragma once

#include "SFML/Graphics.hpp"

class grid_layout
{
public:
	static int get_children_per_row_count(uint32_t screen_width);
	static sf::Vector2<float> get_child_position(uint32_t screen_width, uint32_t screen_height, size_t child_index);
};
