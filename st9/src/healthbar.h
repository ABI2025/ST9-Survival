#pragma once
class healthbar
{
private:
	int m_health;
public:
	healthbar(int);
	~healthbar();
	void set_health(int);

	int get_health();

	void damage_input(int);
	void draw_healthbar();

};

