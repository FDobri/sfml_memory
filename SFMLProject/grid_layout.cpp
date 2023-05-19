#include "grid_layout.h"

constexpr int CHILD_WIDTH = 128;
constexpr int CHILD_HEIGHT = 128;
constexpr int CHILD_SPACING = 25;
constexpr int INITIAL_Y_OFFSET = 75;

int grid_layout::get_children_per_row_count(const uint32_t screen_width)
{
	float calculated_width = 0;
	int child_count = 0;
	do
	{
		calculated_width += CHILD_WIDTH + CHILD_SPACING;
		child_count++;
	} while (calculated_width < screen_width);

	return child_count - 1;
}

sf::Vector2<float> grid_layout::get_child_position(const uint32_t screen_width, const uint32_t screen_height, const size_t child_index)
{
	const int position_in_row = child_index % get_children_per_row_count(screen_width);
	const int position_in_col = child_index / get_children_per_row_count(screen_width);
	float x_pos = CHILD_SPACING + position_in_row * CHILD_SPACING + position_in_row * CHILD_WIDTH;
	float y_pos = INITIAL_Y_OFFSET + CHILD_SPACING + position_in_col * CHILD_SPACING + position_in_col * CHILD_HEIGHT;
	return { x_pos, y_pos };
}
