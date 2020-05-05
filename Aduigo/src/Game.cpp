#include "Game.h"
#include "ofApp.h"
#include "ProjectConstants.h"

Game::Game()
	: m_state(GameState::NotInitialized)
	, m_score(0)
{
}

Game::~Game() {
}


void Game::init() {
	m_font.load(ProjectConstants::FONT_PATH_RETRO, 16, false, true);
	// game in one of four states:
	// NotInitialized, Ready, Playing, GameOver
	m_command.init();
	m_state = GameState::Ready;	
	m_score = 0;
}


void Game::update() {
	
	// playing = then update our objects
	if (m_state == GameState::Playing)
	{


		if (m_command.getCommand() == 1 && ((ofApp*)ofGetAppPtr())->activateRed == true) {
			m_triggered = true;
			((ofApp*)ofGetAppPtr())->activateRed == false;

		}
		if (m_command.getCommand() == 2 && ((ofApp*)ofGetAppPtr())->activateGreen == true) {
			m_triggered = true;
			((ofApp*)ofGetAppPtr())->activateGreen == false;

		}
		if (m_command.getCommand() == 3 && ((ofApp*)ofGetAppPtr())->activateDist == true) {
			m_triggered = true;
			((ofApp*)ofGetAppPtr())->activateDist == false;

		}
		if (m_command.getCommand() == 4 && ((ofApp*)ofGetAppPtr())->activateStretch == true) {
			m_triggered = true;
			((ofApp*)ofGetAppPtr())->activateStretch == false;

		}
		if (m_command.getCommand() == 5 && ((ofApp*)ofGetAppPtr())->activateFlex == true) {
			m_triggered = true;
			((ofApp*)ofGetAppPtr())->activateFlex == false;

		}


		if (m_triggered) {
			m_score++;
			oldTime = ofGetElapsedTimef();
			updateCommand();
			m_triggered = false;
		}
		
		timeSoFar = ofGetElapsedTimef();
		// if too much time has passed, end game
		if (((timeSoFar-oldTime) > allotedTime)) {
			oldTime = timeSoFar;
			m_state = GameState::GameOver;
		}

		
		if (timeSoFar > (speedUpTimer + 3.0f)) {
			allotedTime = allotedTime - 1.0f;
			speedUpTimer = timeSoFar;
		}
	

	}
}

void Game::render() {

	m_command.render();


	// render score
	ofFill();
	ofSetColor(ofColor::black);
	m_font.drawString("Score: " + ofToString(m_score), 40, 80);
	m_font.drawString("Allowed Time: " + ofToString(allotedTime - (timeSoFar - oldTime)), 40, 100);
	ofSetColor(ofColor::white);
}

// begin game
void Game::begin() {

	// reset score
	m_score = 0;

	//initialize every timer
	timeSoFar = ofGetElapsedTimef();
	oldTime = ofGetElapsedTimef();
	allotedTime = 10.0f;
	speedUpTimer = ofGetElapsedTimef();

	// We're now playing the game - set state to Playing
	m_state = GameState::Playing;
}        

void Game::updateCommand() {
	m_command.update();
}

// Gets the game's current game state
Game::GameState Game::getGameState() {
	return m_state;
}