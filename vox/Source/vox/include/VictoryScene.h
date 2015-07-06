#pragma once

#include <PuppetScene.h>

class PuppetGame;

class VictoryScene : public PuppetScene{
public:
	unsigned long int winner;
	VictoryScene(PuppetGame * _game, std::vector<PuppetCharacter *> players);

	virtual void update(Step * _step) override;
};