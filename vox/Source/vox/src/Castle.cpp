#pragma once

#include "Castle.h"
#include <Box2DSprite.h>
#include "MeshInterface.h"
#include <Texture.h>
#include <TextureSampler.h>
#include "Box2DWorld.h"
#include "Boulder.h"
#include "PuppetScene.h"
#include "SpriteSheet.h"
#include "SpriteSheetAnimation.h"
#include <iostream>
#include <SoundManager.h>

#include <RaidTheCastleResourceManager.h>

Castle::Castle(Box2DWorld* _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex):
	StructureBreakable(100.f, _world, _categoryBits, _maskBits, _groupIndex),
	spriteSheet(new SpriteSheetAnimation(RaidTheCastleResourceManager::castleSpriteSheet, 0))
{
	componentScale = 0.03f;
	
	rootComponent = new Box2DSprite(_world, RaidTheCastleResourceManager::castleBase, b2_staticBody, false, nullptr, componentScale);
	addComponent(&rootComponent);
	
	b2Filter sf;
	sf.categoryBits = categoryBits;
	if(maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}
	sf.groupIndex = groupIndex;
	for(Box2DSprite ** c : components){
		b2Fixture * f = (*c)->createFixture(sf);
		f->SetSensor(true);
	}

	setUserData(this);
	
	// sprite sheet animation
	rootComponent->mesh->popTexture2D();
	spriteSheet->pushFramesInRange(0, 3, RaidTheCastleResourceManager::castleBase->texture->width, RaidTheCastleResourceManager::castleBase->texture->height, spriteSheet->texture->width);
	rootComponent->addAnimation("castleStates", spriteSheet, true);
	rootComponent->setTranslationPhysical(0.f, rootComponent->getCorrectedHeight(), 0.f);
	rootComponent->mesh->uvEdgeMode = GL_MIRRORED_REPEAT_ARB;

	// increase mesh size to add some padding between the sprite edge and the collider
	for(unsigned long int i = 0; i < rootComponent->mesh->vertices.size(); ++i){
		rootComponent->mesh->vertices.at(i).x *= 1.1f;
		rootComponent->mesh->vertices.at(i).y *= 1.1f;
	}
}

void Castle::takeDamage(float _damage){
	RaidTheCastleResourceManager::catapultHitSounds->playRandomSound();
	StructureBreakable::takeDamage(_damage);
	switch (state){
		default:
		case StructureBreakable::kNORMAL:
			rootComponent->currentAnimation->currentFrame = 0;
			break;
		case StructureBreakable::kDAMAGED:
			rootComponent->currentAnimation->currentFrame = 1;
			break;
		case StructureBreakable::kDEAD:
			rootComponent->currentAnimation->currentFrame = 3;
			break;
	}
}