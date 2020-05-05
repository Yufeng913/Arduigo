#include "ofApp.h"
#include "ProjectConstants.h"
#include "Game.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(
		ProjectConstants::PROJ_WINDOW_RES_X,
		ProjectConstants::PROJ_WINDOW_RES_Y);

	ofSetFrameRate(ProjectConstants::PROJ_FRAMERATE);

	// Initialize screens
	m_opening.init();
	m_gameOverScreen.init();

	// Initialize the game
	m_game.init();

	// start out on the title screen
	m_appState = AppState::Opening;

	//
	//
	// Arduino Integration
	//
	//

	ofSetFrameRate(15);

	m_font.load("franklinGothic.otf", 16 );

	m_arduino.connect("COM3", 57600);

	ofAddListener(m_arduino.EInitialized, this, &ofApp::setupArduino);
	m_bArduinoSetup = false;	// flag so we setup arduino when its ready, you don't need to touch this :)

	m_buttonValueExit = 0;
	m_buttonValueStart = 0;
	m_buttonValueRed = 0;
	m_buttonValueGreen = 0;

	activateRed = false;
	activateGreen = false;
	activateDist = false;
	activateStretch = false;
	activateFlex = false;

	m_distVal = 0;

	m_stretchVal = 0;

	m_flexVal = 0;
}

//--------------------------------------------------------------

void ofApp::beginGame() {
	m_game.begin();
	m_appState = AppState::Playing;
}

void ofApp::update(){

	// Arduino Integration
	if (ofGetElapsedTimeMillis() > 5000 && !m_bArduinoSetup)
	{
		setupArduino(0);
	}

	updateArduino();

	switch (m_appState)
	{
	case AppState::Opening:
		if (m_bArduinoSetup)
		{
			//exit game
				m_buttonValueExit = m_arduino.getDigital(BUTTON_PIN1);
				if (ARD_LOW == m_buttonValueExit)
				{
					quick_exit(0);
				}
				else
				{
				}
			//exit the game
				m_buttonValueStart = m_arduino.getDigital(BUTTON_PIN2);
				if (ARD_LOW == m_buttonValueStart)
				{
					beginGame();
				}

				m_buttonValueGreen = m_arduino.getDigital(BUTTON_PIN2);
				if (ARD_LOW == m_buttonValueGreen)
				{
					activateGreen = true;
				}
				else
				{
					activateGreen = false;
				}

				m_buttonValueRed = m_arduino.getDigital(BUTTON_PIN1);
				if (ARD_LOW == m_buttonValueRed)
				{
					activateRed = true;
				}
				else
				{
					activateRed = false;
				}

			}

	case AppState::Playing:
		m_game.update();

		if (m_bArduinoSetup)
		{
			m_buttonValueGreen = m_arduino.getDigital(BUTTON_PIN2);
			if (ARD_LOW == m_buttonValueGreen)
			{
				activateGreen = true;
			}
			else
			{
				activateGreen = false;
			}

			m_buttonValueRed = m_arduino.getDigital(BUTTON_PIN1);
			if (ARD_LOW == m_buttonValueRed)
			{
				activateRed = true;
			}
			else
			{
				activateRed = false;
			}

		}
		if (m_game.getGameState() == Game::GameState::GameOver)
		{
			m_appState = AppState::GameOver;
		}
		break;

	case AppState::GameOver:
		if (m_bArduinoSetup)
		{

			m_buttonValueExit = m_arduino.getDigital(BUTTON_PIN1);
			if (ARD_LOW == m_buttonValueExit)
			{
				//m_arduino.sendDigital(LED2_PIN, ARD_HIGH);
				quick_exit(0);
				//activate = true;
			}
			else
			{
				//activate = false;
			}

			m_buttonValueStart = m_arduino.getDigital(BUTTON_PIN2);
			if (ARD_LOW == m_buttonValueStart)
			{
				//m_arduino.sendDigital(LED2_PIN, ARD_HIGH);
				beginGame();
			}

			m_buttonValueGreen = m_arduino.getDigital(BUTTON_PIN2);
			if (ARD_LOW == m_buttonValueGreen)
			{
				activateGreen = true;
			}
			else
			{
				activateGreen = false;
			}

			m_buttonValueRed = m_arduino.getDigital(BUTTON_PIN1);
			if (ARD_LOW == m_buttonValueRed)
			{
				activateRed = true;
			}
			else
			{
				activateRed = false;
			}

		}
		break;
	default:
		break;
	}
	
}

void ofApp::setupArduino(const int & _version)
{
	// remove listener because we don't need it anymore
	ofRemoveListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

	// it is now safe to send commands to the Arduino
	m_bArduinoSetup = true;

	// print firmware name and version to the console
	ofLogNotice() << m_arduino.getFirmwareName();
	ofLogNotice() << "firmata v" << m_arduino.getMajorFirmwareVersion() << "." << m_arduino.getMinorFirmwareVersion();

	m_arduino.sendDigitalPinMode(BUTTON_PIN1, ARD_INPUT);
	m_arduino.sendDigitalPinMode(BUTTON_PIN2, ARD_INPUT);
	m_arduino.sendDigitalPinMode(BUTTON_PIN3, ARD_INPUT);
	m_arduino.sendDigitalPinMode(BUTTON_PIN4, ARD_INPUT);

	// Distance
	m_arduino.sendAnalogPinReporting(DIST_PIN, ARD_ANALOG);

	// Flex
	m_arduino.sendAnalogPinReporting(FLEX_PIN, ARD_ANALOG);

	m_arduino.sendAnalogPinReporting(STRETCH_PIN, ARD_ANALOG);

	m_arduino.sendDigitalPinMode(LED1_PIN, ARD_OUTPUT);

}

void ofApp::updateArduino() {

	m_arduino.update();

	if (m_bArduinoSetup)
	{
		// for sensors flex, distance, stretch
		m_flexVal = m_arduino.getAnalog(FLEX_PIN);
		if (m_flexVal > 320)
		{
			activateFlex = true;
		}
		else {
			activateFlex = false;
		}

		m_distVal = getIRDistance(m_arduino.getAnalog(DIST_PIN));
		if (m_distVal < 4.0f)
		{
			activateDist = true;
		}
		else {
			activateDist = false;
		}

		m_stretchVal = m_arduino.getAnalog(STRETCH_PIN);
		if (m_stretchVal < 520.0f)
		{
			activateStretch = true;
		}
		else {
			activateDist = false;
		}

		if (((Game*)ofGetAppPtr())->m_triggered == true)
		{
			m_arduino.sendDigital(LED1_PIN, ARD_LOW); // turn LED on
		}

		else
		{
			m_arduino.sendDigital(LED1_PIN, ARD_HIGH); // turn LED off
		}
		
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofClear(ofFloatColor(0.0f, 0.0f, 0.0f, 1.0f));

	
	if (!m_bArduinoSetup)
	{
		m_font.drawString("Arduino not ready...", 530, 40);
	}


	switch (m_appState)
	{
	case AppState::Opening:
		m_opening.render();
		break;

	case AppState::Playing:
		m_game.render();		
		break;

	case AppState::GameOver:
		m_game.render();
		m_gameOverScreen.render();
		break;

	default:
		break;
	}	

}

//--------------------------------------------------------------
float ofApp::getIRDistance(int _value)
{
	if (_value < 16)
	{
		_value = 16;
	}

	return 2076.0f / (_value - 11.0f);
}

