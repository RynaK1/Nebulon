#pragma once

#include<SFML\Graphics.hpp>
#include <iostream>

struct Equation {
	float pt;
	float xt;
	float yt;
	float m_xt;
	float m_yt;
	float x_max;
	bool reverse;
	float speed;
	Equation() : pt(0), xt(0), yt(0), m_xt(0), m_yt(0), x_max(0), speed(0), reverse(false) {};
	Equation(float pt, float xt, float yt, float m_xt, float m_yt, float x_max, float speed, bool reverse, bool fhd);
};



class Movement {
private:
	int eq_curr;
	float x;
	bool leave;
	std::vector<Equation> eqs;
public:
	Movement() : eq_curr(0), x(0), leave(true) {};
	Movement(float x, bool leave, bool fhd);
	void push_back(Equation eq);
	sf::Vector2f update(float time);
};