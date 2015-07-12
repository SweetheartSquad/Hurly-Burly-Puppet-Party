#pragma once

#include <ItemFireballLauncher.h>
#include <ItemFireball.h>
#include <PuppetScene.h>
#include <shader\ComponentShaderBase.h>

#include <SlayTheDragonResourceManager.h>
#include <PuppetResourceManager.h>
#include <PuppetCharacterDragon.h>
#include <TextureSampler.h>

ItemFireballLauncher::ItemFireballLauncher(PuppetCharacterDragon * _dragon, Box2DWorld * _world) :
	ItemProjectileWeapon(SlayTheDragonResourceManager::itemFireball, PuppetResourceManager::itemNone, _world, PuppetGame::kITEM)
{
	owner = _dragon;
}

Item * ItemFireballLauncher::getProjectile(bool _forceDrop){
	PuppetCharacterDragon * dragon = dynamic_cast<PuppetCharacterDragon *>(owner);
	if(dragon == nullptr){
		throw "not a dragon!";
	}
	ItemFireball * projectile = new ItemFireball(dragon, world);

	b2Filter sf;
	sf.categoryBits = categoryBits;
	if (projectile->maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}else{
		sf.maskBits = 0;
	}
	sf.groupIndex = groupIndex;

	for (Box2DSprite ** c : projectile->components){
		(*c)->createFixture(sf);
		(*c)->body->GetFixtureList()->SetDensity(0.01f);
		(*c)->body->ResetMassData();
	}

	projectile->setUserData(projectile);

	static_cast<PuppetScene *>(scene)->addChild(projectile, 1);
	static_cast<PuppetScene *>(scene)->items.push_back(projectile);
	projectile->addToLayeredScene(static_cast<PuppetScene *>(scene), 1);
	projectile->setShader(static_cast<PuppetScene *>(scene)->shader, true);

	projectile->snapComponents(this->rootComponent);

	return projectile;
}