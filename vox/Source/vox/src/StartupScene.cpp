#pragma once

#include <StartupScene.h>
#include <PuppetGame.h>
#include <PuppetResourceManager.h>
#include <Sprite.h>
#include <MeshInterface.h>
#include <shader\ComponentShaderBase.h>
#include <SoundManager.h>
#include <PuppetController.h>
#include <FollowCamera.h>
#include <PuppetCharacterKnight.h>
#include <Box2DSprite.h>

StartupScene::StartupScene(PuppetGame * _game) :
	PuppetScene(_game, 20.f, 30.f, 20.f, 100.f, true),
	playerCharacter1(new PuppetCharacterKnight(false, 0, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -1)),
	playerCharacter2(new PuppetCharacterKnight(false, 1, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -2)),
	playerCharacter3(new PuppetCharacterKnight(false, 2, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -3)),
	playerCharacter4(new PuppetCharacterKnight(false, 3, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -4))
{
	splashMessage->mesh->pushTexture2D(PuppetResourceManager::startupSplash);

	populateBackground();
	
	players.push_back(playerCharacter1);
	players.push_back(playerCharacter2);
	players.push_back(playerCharacter3);
	players.push_back(playerCharacter4);

	for(unsigned long int i = 0; i < players.size(); ++i){
		PuppetCharacter * p = players.at(i);
		p->ai = true;
		addChild(p, 1);
		p->addToLayeredScene(this, 1);
		p->setShader(shader, true);

		p->translateComponents(glm::vec3((i+0.5f) * sceneWidth*0.25f, 35, 0.f));
	}

	gameCam->offset = glm::vec3(sceneWidth*0.5f, sceneHeight*0.5f, 0);
}
void StartupScene::complete(std::string _switchTo){
	if (_switchTo == ""){
		PuppetGame * pg = static_cast<PuppetGame *>(game);
		pg->loadRandomScene();
	}else{
		PuppetScene::complete(_switchTo);
	}
}

void StartupScene::update(Step * _step){
	PuppetScene::update(_step);
	if(!splashSoundPlayed){
		PuppetResourceManager::splashSounds->play("Startup-alt");
		splashSoundPlayed = true;
	}
}
void StartupScene::triggerVictoryState(){
	// intentionally left blank: since there are no players, this function will be called automatically at the start of the scene
}

void StartupScene::populateBackground(){

}