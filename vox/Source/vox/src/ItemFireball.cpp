#pragma once

#include <ItemFireball.h>
#include <PuppetCharacterDragon.h>
#include <SlayTheDragonResourceManager.h>

ItemFireball::ItemFireball(PuppetCharacterDragon * _dragon, Box2DWorld * _world) :
	Item(true, _world, PuppetGame::kITEM, PuppetGame::kPLAYER | PuppetGame::kSTRUCTURE | PuppetGame::kBOUNDARY | PuppetGame::kGROUND, 0, 25)
{
	owner = _dragon;
	groupIndex = owner->groupIndex;
	setGroupIndex(owner->groupIndex);

	thrown = true;
	held = false;
	
	Box2DSprite ** test = new Box2DSprite*[1];
	test[0] = rootComponent = new Box2DSprite(world, SlayTheDragonResourceManager::itemFireball, b2_dynamicBody, false, nullptr, componentScale);

	addComponent(test);
}

ItemFireball::~ItemFireball(){
	PuppetCharacterDragon * dragon = dynamic_cast<PuppetCharacterDragon *>(owner);
	if(dragon == nullptr){
		throw "not a dragon!";
	}
	dragon->fireball = nullptr;
}