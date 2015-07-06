#include "PuppetGame.h"
#include "RaidTheCastle.h"
#include <SlayTheDragon.h>
#include <FightYourFriends.h>
#include <StartupScene.h>
#include <Rapunzel.h>

#include <NumberUtils.h>

#include <cstdlib>
#include <ctime>
#include <AccelerometerParser.h>
#include <Accelerometer.h>
#include <PuppetController.h>

PuppetGame::PuppetGame(bool _running):
	Game(_running, std::pair<std::string, Scene *>("Startup", new StartupScene(this))),
	arduino(new AccelerometerParser("COM4")),
	lastScene(-1)
{
	std::srand((unsigned long int)std::time(0));

	//Arduino stuff must be setup before the first scene is intiailized
	puppetControllers.push_back(new PuppetController(arduino->addAccelerometer()));
	puppetControllers.push_back(new PuppetController(arduino->addAccelerometer()));
	puppetControllers.push_back(new PuppetController(arduino->addAccelerometer()));
	puppetControllers.push_back(new PuppetController(arduino->addAccelerometer()));
}

PuppetGame::~PuppetGame(){
	while(puppetControllers.size() > 0){
		delete puppetControllers.back();
		puppetControllers.pop_back();
	}

	delete arduino;
}

void PuppetGame::update(Step * _step){
	arduino->update(_step);
	for (PuppetController * pc : puppetControllers){
		pc->update(_step);
	}

	Game::update(_step);
}

void PuppetGame::draw(){
	Game::draw();
}

void PuppetGame::loadRandomScene(){
	int r;
	do{
		r = vox::NumberUtils::randomInt(0, 3);
	}while(r == lastScene);

	switch(r) {
	case 0:
		scenes.insert(std::make_pair("Raid The Castle", new RaidTheCastle(this)));
		switchScene("Raid The Castle", true);
		break;
	case 1:
		scenes.insert(std::make_pair("Rapunzel", new Rapunzel(this)));
		switchScene("Rapunzel", true);
		break;
	case 2:
		scenes.insert(std::make_pair("Slay The Dragon", new SlayTheDragon(this)));
		switchScene("Slay The Dragon", true);
		break;
	case 3:
		scenes.insert(std::make_pair("Fight Your Friends", new FightYourFriends(this)));
		switchScene("Fight Your Friends", true);
		break;
	}
	lastScene = r;
}