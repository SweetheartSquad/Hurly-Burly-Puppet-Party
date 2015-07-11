#pragma once

#include "Tower.h"
#include <Box2DSprite.h>
#include "MeshInterface.h"
#include <Texture.h>
#include <TextureSampler.h>
#include "Box2DWorld.h"
#include "PuppetScene.h"
#include "SpriteSheet.h"
#include "SpriteSheetAnimation.h"
#include <iostream>

#include <RapunzelResourceManager.h>

Tower::Tower(Box2DWorld* _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex):
	Structure(_world, _categoryBits, _maskBits, _groupIndex)
{
	componentScale = 0.06f;
	
	TextureSampler * towerTex = RapunzelResourceManager::towerTower;

	rootComponent = new Box2DSprite(_world, towerTex, b2_staticBody, false, nullptr, componentScale);

	addComponent(&rootComponent);
	
	b2Filter sf;
	sf.categoryBits = categoryBits;
	if(maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}
	sf.groupIndex = groupIndex;
	for(Box2DSprite ** c : components){
		(*c)->createFixture(sf);
	}
	setUserData(this);

	rootComponent->setTranslationPhysical(0.f, rootComponent->getCorrectedHeight(), 0.f);
}