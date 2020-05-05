#include "Command.h"
#include "ProjectConstants.h"

Command::Command()
{
}

Command::~Command() {
}


void Command::init() {
	m_pressRed.load(ProjectConstants::IMG_PATH_PRESS_RED);
	m_pressGreen.load(ProjectConstants::IMG_PATH_PRESS_GREEN);
	m_poke.load(ProjectConstants::IMG_PATH_POKE);
	m_stretch.load(ProjectConstants::IMG_PATH_STRETCH );
	m_bend.load(ProjectConstants::IMG_PATH_BEND);
	

	m_command = ofRandom(1,6);
}


void Command::update() {
	m_command = ofRandom(1, 6);
}

void Command::render() {
	ofSetRectMode(OF_RECTMODE_CORNER);

	if (m_command == 1) {
		m_pressRed.draw(0, 0);
	}
	if (m_command == 2) {
		m_pressGreen.draw(0, 0);
	}
	if (m_command == 3) {
		m_poke.draw(0, 0);
	}
	if (m_command == 4) {
		m_stretch.draw(0, 0);
	}
	if (m_command == 5) {
		m_bend.draw(0, 0);
	}
}

int Command::getCommand() {
	return m_command;
}