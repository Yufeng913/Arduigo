#pragma once

#include "ofMain.h"
#include "Game.h"
#include "Command.h"
#include "Opening.h"
#include "GameOverScreen.h"
#include "ofEvents.h"

//extern int activate;

class ofApp : public ofBaseApp{


	
	public:

		enum AppState
		{
			Uninitialized,
			Opening,
			Playing,
			GameOver
		};


		static const int BUTTON_PIN1 = 2;
		static const int BUTTON_PIN2 = 3;
		static const int BUTTON_PIN3 = 4;
		static const int BUTTON_PIN4 = 5;
		static const int DIST_PIN = 2;
		static const int FLEX_PIN = 1;
		static const int STRETCH_PIN = 3;
		static const int LED1_PIN = 10;

		float m_distVal;

		float getIRDistance(int _value);

		// Flex
		int		m_flexVal;

		
		// Stretch
		float			m_stretchVal;

		bool activateRed;
		bool activateGreen;
		bool activateDist;
		bool activateStretch;
		bool activateFlex;

		void setup();
		void update();
		void draw();

		void beginGame();
		
		AppState			m_appState;
		//int                 m_score;
		Game				m_game;
		//Command				m_command;
		OpeningScreen		m_opening;
		GameOverScreen		m_gameOverScreen;

		ofTrueTypeFont  m_font;

		ofArduino	m_arduino;
		bool		m_bArduinoSetup;			// flag variable for setting up arduino once

		 
		
		int         m_buttonValueExit;
		int			m_buttonValueStart;
		int			m_buttonValueRed;
		int			m_buttonValueGreen;

		void setupArduino(const int & _version);
		void updateArduino();

		AppState getGameState();

private:

	void updateCommand();

	AppState           m_state;
	Command				m_command;
	int                 m_score;

	// timer stuff
	float			timeSoFar;
	float			oldTime;
	float			allotedTime;
	bool			m_triggered;
	float			speedUpTimer;

};

