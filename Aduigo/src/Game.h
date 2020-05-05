#pragma once

#include "ofMain.h"
#include "ProjectConstants.h"
#include "Command.h"

class Game
{
public:
	enum GameState
	{
		NotInitialized,
		Ready,
		Playing,
		GameOver
	};

	Game();
	~Game();

	void init();
	void update();
	void render();
	void begin();

	//trigger for timer
	bool			m_triggered;
	GameState getGameState();

private:

	void updateCommand();

	GameState           m_state;
	Command				m_command;

	// timer stuff
	float			timeSoFar;
	float			oldTime;
	float			allotedTime;
	float			speedUpTimer;

	int                 m_score;

	//font
	ofTrueTypeFont	      m_font;


	
};
