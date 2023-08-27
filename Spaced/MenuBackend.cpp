#include "MenuBackend.h"
#include <iostream>

int getVolumePercentage(int knob_pos, int window_x) {
	int vol_bar_width = 290;
	int left_gap = (window_x - vol_bar_width) / 2;
	return std::round((knob_pos - left_gap) / 2.9);
}