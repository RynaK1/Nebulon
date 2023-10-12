#include "Movement.h"

Equation::Equation(float pt, float xt, float yt, float m_xt, float m_yt, float x_max, float speed, bool reverse, bool fhd) {
	this->pt = pt;
	this->xt = xt;
	this->yt = yt;
	this->m_xt = m_xt;
	this->m_yt = m_yt;
	this->x_max = x_max;
	this->speed = speed;
	this->negative = reverse;
	if (fhd == true) {
		if (this->pt == 2) {
			this->m_yt *= 0.66667f;
		}
		else if (this->pt == 3) {
			this->m_yt *= 0.4433f;
		}
		this->xt *= 1.5f;
		this->yt *= 1.5f;
		this->x_max *= 1.5f;
		this->speed *= 1.5f;
	}
}



Movement::Movement(float x, bool fhd) {
	eq_curr = 0;
	this->x = x;
	if (fhd == true) {
		this->x *= 1.5f;
	}
}


void Movement::push_back(Equation eq) {
	eqs.push_back(eq);
}


sf::Vector2f Movement::update(float time) {
	float r;

	if (eqs[eq_curr].negative == true) {
		x -= eqs[eq_curr].speed * time;
	}
	else {
		x += eqs[eq_curr].speed * time;
	}

	if ((eqs[eq_curr].negative == false && x >= eqs[eq_curr].x_max) ||
		(eqs[eq_curr].negative == true && x <= eqs[eq_curr].x_max)) {
		eq_curr += 1;
	};

	r = (pow((eqs[eq_curr].m_xt * x) + eqs[eq_curr].xt, eqs[eq_curr].pt) * eqs[eq_curr].m_yt) + eqs[eq_curr].yt;
	return sf::Vector2f(x, r);
}
