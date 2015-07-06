#pragma once

#include "Fortification.h"
#include <Box2DSprite.h>
#include "MeshInterface.h"
#include <Texture.h>
#include "Box2DWorld.h"
#include "Boulder.h"
#include "PuppetScene.h"
#include "SpriteSheet.h"
#include "SpriteSheetAnimation.h"
#include <iostream>
#include <SoundManager.h>

#include <SlayTheDragonResourceManager.h>

Fortification::Fortification(Box2DWorld* _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex) :
	StructureBreakable(250.f, _world, _categoryBits, _maskBits, _groupIndex)
{
	componentScale = 0.025f;

	TextureSampler * roofTex = SlayTheDragonResourceManager::fortStructure;

	rootComponent = new Box2DSprite(_world, roofTex, b2_staticBody, false, nullptr, componentScale);

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
	
	for(unsigned long int i = 0; i < rootComponent->mesh->vertices.size(); ++i){
		rootComponent->mesh->vertices.at(i).y *= 1.4f;
		rootComponent->mesh->vertices.at(i).x *= 1.4f;
	}
	rootComponent->mesh->dirty = true;

	setUserData(this);
	
	// sprite sheet animation
	rootComponent->mesh->popTexture2D();
	
	spriteSheet = new SpriteSheetAnimation(SlayTheDragonResourceManager::fortificationSpriteSheet, 0);

	spriteSheet->pushFramesInRange(0, 3, 1024, 188, 1024);
	rootComponent->addAnimation("fortStates", spriteSheet, true);
	rootComponent->mesh->uvEdgeMode = GL_MIRRORED_REPEAT_ARB;
}

Fortification::~Fortification(){
	delete spriteSheet;
}

void Fortification::takeDamage(float _damage){
	StructureBreakable::takeDamage(_damage);
	//glm::vec3 sv = rootComponent->parents.at(0)->getScaleVector();
	unsigned long int lastFrame = rootComponent->currentAnimation->currentFrame;
	switch (state){
	default:
	case StructureBreakable::kNORMAL:
		rootComponent->currentAnimation->currentFrame = 0;
		break;
	case StructureBreakable::kDAMAGED:
		if(lastFrame != 2){
			rootComponent->currentAnimation->currentFrame = 2;
			SlayTheDragonResourceManager::miscSounds->play("damaged");
		}
		break;
	case StructureBreakable::kDEAD:
		if(lastFrame != 3){
			rootComponent->currentAnimation->currentFrame = 3;
			SlayTheDragonResourceManager::miscSounds->play("broken");
			b2Filter sf;
			sf.groupIndex = groupIndex;
			sf.categoryBits = PuppetGame::kSTRUCTURE;
			sf.maskBits = 0;
			for(Box2DSprite ** c : components){
				(*c)->body->GetFixtureList()->SetFilterData(sf);
			}
		}
		break;
	}

	//rootComponent->parents.at(0)->scale(sv, false);
}