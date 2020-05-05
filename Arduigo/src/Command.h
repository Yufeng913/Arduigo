#pragma once
#include "ofMain.h"

class Command
{
public:
	Command();
	~Command();

    void init();
	void update();
	void render();

	int getCommand();


private:
	ofImage     m_pressRed;
	ofImage     m_pressGreen;
	ofImage     m_poke;
	ofImage     m_stretch;
	ofImage		m_bend;

	int			m_command;
};