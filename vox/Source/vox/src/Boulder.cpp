#pragma once

#include <Boulder.h>
#include <Box2DSprite.h>
#include <Texture.h>
#include <PuppetCharacter.h>
#include <Box2DWorld.h>
#include <Catapult.h>
#include <RaidTheCastleResourceManager.h>

Boulder::Boulder(Box2DWorld* _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex) :
	Item(true, _world, _categoryBits, _maskBits, _groupIndex, 25.f, 50.f, 56.f),
	catapult(nullptr)
{
	componentScale = 0.032f;

	TextureSampler * boulderTexSampler = RaidTheCastleResourceManager::boulder;
	
	boulder = new Box2DSprite(_world, boulderTexSampler, b2_dynamicBody, false, nullptr, componentScale);
	rootComponent = boulder;
	addComponent(&boulder);
	
	b2Filter sf;
	sf.categoryBits = categoryBits;
	if(maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}else{
		sf.maskBits = 0;
	}
	sf.groupIndex = groupIndex;
	
	for(Box2DSprite ** c : components){
		(*c)->createFixture(sf);
	}

	boulder->body->SetBullet(true);

	setUserData(this);
}

Boulder::~Boulder(){
	if(catapult != nullptr){
		world->b2world->DestroyJoint(catapult->boulderJoint);
		catapult->boulderJoint = nullptr;
		catapult->boulder = nullptr;
	}
}

void Boulder::update(Step* _step){
	Item::update(_step);

	// in case the boulder misses
	glm::vec3 tv = rootComponent->parents.at(0)->getTranslationVector();
	if(tv.x > 200 || tv.y < 0){
		destroy = true;
	}
}