#include "RapunzelContactListener.h"
#include "PuppetScene.h"

#include "Scene.h"
#include "Hair.h"
#include "Lever.h"
#include "PuppetCharacter.h"
#include <PuppetCharacterRapunzel.h>
#include <PuppetCharacterGuard.h>
#include "Box2dWorld.h"
#include "Item.h"
#include "Box2DSprite.h"
#include "Box2DSuperSprite.h"
#include <Box2D/Box2D.h>
#include <Box2D\Dynamics\Joints\b2RevoluteJoint.h>

#include "Behaviour.h"
#include <StructureGoldPile.h>
#include <ItemGold.h>
#include <Rapunzel.h>
#include <vector>

RapunzelContactListener::RapunzelContactListener(PuppetScene * _scene) :
	PuppetContactListener(_scene)
{
}