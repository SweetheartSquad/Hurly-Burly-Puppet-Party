#pragma once

#include "SlayTheDragonContactListener.h"
#include "PuppetScene.h"

#include "Scene.h"
#include "Hair.h"
#include "Lever.h"
#include "PuppetCharacterArcher.h"
#include <PuppetCharacterDragon.h>
#include "Box2dWorld.h"
#include "Item.h"
#include "Box2DSprite.h"
#include "Box2DSuperSprite.h"
#include <Box2D/Box2D.h>
#include <Box2D\Dynamics\Joints\b2RevoluteJoint.h>

#include <SoundManager.h>
#include <SlayTheDragonResourceManager.h>
#include "Behaviour.h"
#include <Fortification.h>
#include <ItemFireball.h>

SlayTheDragonContactListener::SlayTheDragonContactListener(PuppetScene * _scene) :
	PuppetContactListener(_scene)
{
}

void SlayTheDragonContactListener::playerItemContact(b2Contact * _contact, b2Fixture * _playerFixture, b2Fixture * _itemFixture){
	PuppetContactListener::playerItemContact(_contact, _playerFixture, _itemFixture);
	
	PuppetCharacterArcher * player = static_cast<PuppetCharacterArcher *>( _playerFixture->GetUserData() );
    Item * item = static_cast<Item *>( _itemFixture->GetUserData() );

	ItemFireball * fb = dynamic_cast<ItemFireball *>(item);
	if(fb != nullptr){
		static_cast<PuppetCharacterDragon *>(fb->owner)->playerOnFire = player;
		player->onFire = true;
	}
}

void SlayTheDragonContactListener::structureItemContact(b2Contact * _contact, b2Fixture * _structureFixture, b2Fixture * _itemFixture){
	PuppetContactListener::structureItemContact(_contact, _structureFixture, _itemFixture);

	Structure * structure = static_cast<Structure *>( _structureFixture->GetUserData() );
    Item * item = static_cast<Item *>( _itemFixture->GetUserData() );

	Fortification * fort = dynamic_cast<Fortification *>(structure);
	if(fort != nullptr){
		fort->takeDamage(item->damage);
	}
}