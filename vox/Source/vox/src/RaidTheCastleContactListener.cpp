#include "RaidTheCastleContactListener.h"
#include "PuppetScene.h"

#include "Scene.h"
#include "Castle.h"
#include "Boulder.h"
#include "Catapult.h"
#include "PuppetCharacter.h"
#include "Box2dWorld.h"
#include "Item.h"
#include "Box2DSprite.h"
#include "Box2DSuperSprite.h"
#include <Box2D/Box2D.h>
#include <Box2D\Dynamics\Joints\b2RevoluteJoint.h>

#include "Behaviour.h"

RaidTheCastleContactListener::RaidTheCastleContactListener(PuppetScene * _scene) :
	PuppetContactListener(_scene)
{
}

void RaidTheCastleContactListener::structureItemContact(b2Contact * _contact, b2Fixture * _structureFixture, b2Fixture * _itemFixture){
	PuppetContactListener::structureItemContact(_contact, _structureFixture, _itemFixture);

	Structure * structure = static_cast<Structure *>( _structureFixture->GetUserData() );
    Item * item = static_cast<Item *>( _itemFixture->GetUserData() );
	Castle * castle = dynamic_cast<Castle *>(structure);
	if(castle != nullptr){
		castle->takeDamage(item->damage);
		if(item->owner != nullptr){
			item->owner->score += item->damage;
		}
		Boulder * boulder = dynamic_cast<Boulder *>(item);
		if(boulder != nullptr){
			if(castle->state == StructureBreakable::kDEAD){
				boulder->owner->score += 100000;
				boulder->owner->lastUpdateScore = boulder->owner->score;
			}
		}
	}
}