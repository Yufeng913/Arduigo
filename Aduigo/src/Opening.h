#pragma once
#include "ofMain.h"

class OpeningScreen
{
public:
	OpeningScreen();
	~OpeningScreen();

	void init();
	void render();

private:
	ofImage	      m_img;
};