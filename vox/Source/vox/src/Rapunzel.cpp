#pragma once

#include <Rapunzel.h>
#include <RapunzelContactListener.h>
#include <RapunzelResourceManager.h>
#include <Castle.h>
#include <PuppetGame.h>
#include <PuppetCharacter.h>
#include <FollowCamera.h>
#include <Behaviour.h>
#include <BehaviourFollow.h>
#include <BehaviourPatrol.h>
#include <BehaviourAttack.h>
#include <Boulder.h>
#include <Catapult.h>
#include <Box2DSprite.h>
#include <Box2DWorld.h>
#include <MeshEntity.h>
#include <MeshInterface.h>
#include <MeshFactory.h>
#include <shader/BaseComponentShader.h>
#include <keyboard.h>
#include <Texture.h>
#include <TextureSampler.h>
#include <PuppetCharacterGuard.h>
#include <PuppetCharacterRapunzel.h>
#include <PuppetCharacterThief.h>
#include <PuppetTexturePack.h>
#include <PuppetController.h>
#include <Item.h>
#include <ItemFlail.h>
#include <ItemSimpleWeapon.h>
#include <ItemProjectileWeapon.h>
#include <Hair.h>
#include <Lever.h>
#include <ItemGold.h>
#include <NumberUtils.h>
#include <StructureBoxingGlove.h>

#include <glfw\glfw3.h>
#include <SoundManager.h>

Rapunzel::Rapunzel(PuppetGame* _game):
	PuppetScene(_game, 30),
	guard(new PuppetCharacterGuard(true, RAPUNZEL_GHOST_HEIGHT, world, PuppetGame::kPLAYER, -1, -20)),
	playerCharacter1(new PuppetCharacterThief(false, RAPUNZEL_GHOST_HEIGHT, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -1)),
	playerCharacter2(new PuppetCharacterThief(false, RAPUNZEL_GHOST_HEIGHT, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -2)),
	playerCharacter3(new PuppetCharacterThief(false, RAPUNZEL_GHOST_HEIGHT, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -3)),
	playerCharacter4(new PuppetCharacterRapunzel(false, RAPUNZEL_GHOST_HEIGHT, world, PuppetGame::kPLAYER, PuppetGame::kGROUND | PuppetGame::kSTRUCTURE | PuppetGame::kITEM | PuppetGame::kPLAYER | PuppetGame::kBEHAVIOUR | PuppetGame::kBOUNDARY, -4))
{
	cl = new RapunzelContactListener(this);
	populateBackground();
	TextureSampler * splashMessageTextureSampler = RapunzelResourceManager::splashMessage;
	splashMessage = new Sprite(nullptr, new Transform());
	splashMessage->transform->scale(glm::vec3(3, 3, 0));
	splashMessage->mesh->pushTexture2D(splashMessageTextureSampler->texture);
	splashMessage->setShader(shader, true);
	splashMessage->transform->scale(-1, 1, 1);

	players.push_back(playerCharacter1);
	players.push_back(playerCharacter2);
	players.push_back(playerCharacter3);
	players.push_back(playerCharacter4);

	playerCharacter1->setShader(shader, true);
	addChild(playerCharacter1, 1);
	playerCharacter1->addToLayeredScene(this, 1);
	playerCharacter1->rootComponent->maxVelocity = b2Vec2(10, NO_VELOCITY_LIMIT);
	static_cast<PuppetGame *>(game)->puppetControllers.at(0)->setPuppetCharacter(playerCharacter1);

	playerCharacter2->setShader(shader, true);
	addChild(playerCharacter2, 1);
	playerCharacter2->addToLayeredScene(this, 1);
	playerCharacter2->rootComponent->maxVelocity = b2Vec2(10, NO_VELOCITY_LIMIT);
	static_cast<PuppetGame *>(game)->puppetControllers.at(1)->setPuppetCharacter(playerCharacter2);

	playerCharacter3->setShader(shader, true);
	addChild(playerCharacter3, 1);
	playerCharacter3->addToLayeredScene(this, 1);
	playerCharacter3->rootComponent->maxVelocity = b2Vec2(10, NO_VELOCITY_LIMIT);
	static_cast<PuppetGame *>(game)->puppetControllers.at(2)->setPuppetCharacter(playerCharacter3);

	playerCharacter4->setShader(shader, true);
	addChild(playerCharacter4, 1);
	playerCharacter4->addToLayeredScene(this, 1);
	playerCharacter4->rootComponent->maxVelocity = b2Vec2(10, NO_VELOCITY_LIMIT);
	static_cast<PuppetGame *>(game)->puppetControllers.at(3)->setPuppetCharacter(playerCharacter4);

	guard->setShader(shader, true);
	addChild(guard, 0);
	guard->addToLayeredScene(this, 1);
	guard->rootComponent->maxVelocity = b2Vec2(10, NO_VELOCITY_LIMIT);
	
	/*guard->itemToPickup = new ItemFlail(world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kSTRUCTURE | PuppetGame::kGROUND, guard->groupIndex, 0, 0, -RapunzelResourceManager::itemFlailGrip->height/2.f);
	addChild(guard->itemToPickup, 1);
	guard->itemToPickup->addToLayeredScene(this, 1);
	guard->itemToPickup->setShader(shader, true);*/

	gameCam->addTarget(playerCharacter1->torso);
	gameCam->addTarget(playerCharacter2->torso);
	gameCam->addTarget(playerCharacter3->torso);
	gameCam->addTarget(playerCharacter4->torso);

	playerCharacter3->behaviourManager.addBehaviour(new BehaviourPatrol(glm::vec3(50,0,0), glm::vec3(100,0,0), playerCharacter3, 10));
	playerCharacter3->behaviourManager.addBehaviour(new BehaviourAttack(playerCharacter3, 3, PuppetGame::kPLAYER));
	playerCharacter3->ai = true;

	playerCharacter4->behaviourManager.addBehaviour(new BehaviourPatrol(glm::vec3(50, 0, 0), glm::vec3(100, 0, 0), playerCharacter4, 10));
	playerCharacter4->behaviourManager.addBehaviour(new BehaviourAttack(playerCharacter4, 3, PuppetGame::kPLAYER));
	playerCharacter4->ai = true;

	guard->behaviourManager.addBehaviour(new BehaviourPatrol(glm::vec3(50, 0, 0), glm::vec3(100, 0, 0), guard, 10));
	guard->behaviourManager.addBehaviour(new BehaviourAttack(guard, 3, PuppetGame::kPLAYER));
	guard->ai = true;

	for(PuppetCharacter * p : players){
		TextureSampler * weaponTex = RapunzelResourceManager::getRandomWeapon();
		TextureSampler * projTex = RapunzelResourceManager::getRandomWeapon();
		
		ItemProjectileWeapon * weapon = new ItemProjectileWeapon(projTex, weaponTex, world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kSTRUCTURE | PuppetGame::kBOUNDARY | PuppetGame::kGROUND, p->groupIndex, 1, 0, -weaponTex->height);
		weapon->addToLayeredScene(this, 1);
		weapon->setShader(shader, true);
		p->itemToPickup = weapon;
        addChild(weapon, 1);
	}
	
	playerCharacter1->translateComponents(glm::vec3(20.f, 35.f, 0.f));
	playerCharacter2->translateComponents(glm::vec3(40.f, 35.f, 0.f));
	playerCharacter3->translateComponents(glm::vec3(60.f, 35.f, 0.f));
	playerCharacter4->translateComponents(glm::vec3(80.f, 35.f, 0.f));
	guard->translateComponents(glm::vec3(100.f, 35.f, 0.f));

	Hair * hair = new Hair(world, PuppetGame::kGROUND, PuppetGame::kPLAYER, 0);
	addChild(hair, 1);
	hair->setShader(shader, true);
	hair->translateComponents(glm::vec3(50.f, 0.f, 0.f));
	
	lever1 = new Lever(world, PuppetGame::kSTRUCTURE, PuppetGame::kPLAYER, 0);
	addChild(lever1, 1);
	lever1->addToLayeredScene(this, 1);
	lever1->setShader(shader, true);
	lever1->translateComponents(glm::vec3(5.f, 2.f, 0));
	lever1->type = 1;
	
	lever2 = new Lever(world, PuppetGame::kSTRUCTURE, PuppetGame::kPLAYER, 0);
	addChild(lever2, 1);
	lever2->addToLayeredScene(this, 1);
	lever2->setShader(shader, true);
	lever2->translateComponents(glm::vec3(10.f, 2.f, 0));
	lever2->type = 2;

	lever3 = new Lever(world, PuppetGame::kSTRUCTURE, PuppetGame::kPLAYER, 0);
	addChild(lever3, 1);
	lever3->addToLayeredScene(this, 1);
	lever3->setShader(shader, true);
	lever3->translateComponents(glm::vec3(15.f, 2.f, 0));
	lever3->type = 3;

	glove = new StructureBoxingGlove(world);
	glove->translateComponents(glm::vec3(50.f, 25.f, 0.f));
	addChild(glove, 1);
	glove->setShader(shader, true);
	glove->addToLayeredScene(this, 1);

	playRandomBackgroundMusic();
}

Rapunzel::~Rapunzel(){
}

void Rapunzel::update(Step* _step){
	PuppetScene::update(_step);

	if(!splashSoundPlayed){
		PuppetResourceManager::splashSounds->play("Rapunzel");
		splashSoundPlayed = true;
	}
}

void Rapunzel::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions){
	PuppetScene::render(_matrixStack, renderOptions);
}

void Rapunzel::load(){
	PuppetScene::load();
}

void Rapunzel::unload(){
	PuppetScene::unload();
}