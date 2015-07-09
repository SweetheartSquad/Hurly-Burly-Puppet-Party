#pragma once

#include <SlayTheDragonResourceManager.h>
#include <TextureSampler.h>
#include <SoundManager.h>

Texture * SlayTheDragonResourceManager::fortificationSpriteSheet	= new Texture("../assets/hurly-burly/Fortification/FortSpriteSheet.png", 1024, 1024, true, false);

TextureSampler * SlayTheDragonResourceManager::splashMessage	= nullptr;
																  
TextureSampler * SlayTheDragonResourceManager::fortBackground	= nullptr;
TextureSampler * SlayTheDragonResourceManager::fortForeground	= nullptr;
TextureSampler * SlayTheDragonResourceManager::fortStructure	= nullptr;
TextureSampler * SlayTheDragonResourceManager::archerTorso		= nullptr;
TextureSampler * SlayTheDragonResourceManager::archerArm		= nullptr;
TextureSampler * SlayTheDragonResourceManager::archerHat		= nullptr;
																  
TextureSampler * SlayTheDragonResourceManager::dragonHead		= nullptr;
TextureSampler * SlayTheDragonResourceManager::dragonMouth		= nullptr;
TextureSampler * SlayTheDragonResourceManager::dragonTorso		= nullptr;
TextureSampler * SlayTheDragonResourceManager::dragonUpperWing	= nullptr;
TextureSampler * SlayTheDragonResourceManager::dragonLowerWing	= nullptr;
																  
TextureSampler * SlayTheDragonResourceManager::itemBow			= nullptr;
TextureSampler * SlayTheDragonResourceManager::itemArrow		= nullptr;
TextureSampler * SlayTheDragonResourceManager::itemFireball		= nullptr;
TextureSampler * SlayTheDragonResourceManager::itemFireParticle	= nullptr;

SoundManager * SlayTheDragonResourceManager::dragonSounds = new SoundManager(-1);
SoundManager * SlayTheDragonResourceManager::fireSounds = new SoundManager(-1);
SoundManager * SlayTheDragonResourceManager::miscSounds = new SoundManager(-1);

void SlayTheDragonResourceManager::init(){
	
	splashMessage	= new TextureSampler(new Texture("../assets/hurly-burly/SplashMessages/SlayTheDragon.png", 1024, 1024, true, false), 1024, 1024);
	
	fortBackground	= new TextureSampler(new Texture("../assets/hurly-burly/Fortification/FortBackground.png", 1024, 1024, true, false), 453, 307);
	fortForeground	= new TextureSampler(new Texture("../assets/hurly-burly/Fortification/FortForeground.png", 1024, 1024, true, false), 1024, 413);
	fortStructure	= new TextureSampler(new Texture("../assets/hurly-burly/Fortification/FortStructure.png", 1024, 1024, true, false), 683, 127);
	archerTorso		= new TextureSampler(new Texture("../assets/hurly-burly/ArcherAssets/ArcherTorso.png", 1024, 1024, true, false), 275, 765);
	archerArm		= new TextureSampler(new Texture("../assets/hurly-burly/ArcherAssets/ArcherArm.png", 1024, 1024, true, false), 64, 228);
	archerHat		= new TextureSampler(new Texture("../assets/hurly-burly/ArcherAssets/ArcherHat.png", 1024, 1024, true, false), 191, 275);
	
	dragonHead		= new TextureSampler("../assets/hurly-burly/DragonAssets/", "DragonHead.png.def", false);
	dragonMouth		= new TextureSampler("../assets/hurly-burly/DragonAssets/", "DragonMouth.png.def", false);
	dragonTorso		= new TextureSampler("../assets/hurly-burly/DragonAssets/", "DragonTorso.png.def", false);
	dragonUpperWing	= new TextureSampler("../assets/hurly-burly/DragonAssets/", "DragonUpperWing.png.def", false);
	dragonLowerWing	= new TextureSampler("../assets/hurly-burly/DragonAssets/", "DragonLowerWing.png.def", false);
	
	itemBow			= new TextureSampler("../assets/hurly-burly/WeaponAssets/", "Bow.png.def", false);
	itemArrow		= new TextureSampler("../assets/hurly-burly/WeaponAssets/", "Arrow.png.def", false);
	itemFireball		= new TextureSampler("../assets/hurly-burly/DragonAssets/", "Fireball.png.def", false);
	itemFireParticle	= new TextureSampler("../assets/hurly-burly/DragonAssets/", "FireParticle.png.def", false);


	resources.push_back(splashMessage);
	
	resources.push_back(fortBackground);
	resources.push_back(fortForeground);
	resources.push_back(fortStructure);
	resources.push_back(fortificationSpriteSheet);

	resources.push_back(archerTorso);
	resources.push_back(archerArm);
	resources.push_back(archerHat);
	
	resources.push_back(dragonHead);
	resources.push_back(dragonMouth);
	resources.push_back(dragonTorso);
	resources.push_back(dragonUpperWing);
	resources.push_back(dragonLowerWing);

	resources.push_back(itemBow);
	resources.push_back(itemArrow);
	resources.push_back(itemFireball);
	resources.push_back(itemFireParticle);

	
	dragonSounds->addNewSound("1", "../assets/hurly-burly/audio/dragon/dragonSound1.ogg");
	dragonSounds->addNewSound("2", "../assets/hurly-burly/audio/dragon/dragonSound2.ogg");
	dragonSounds->addNewSound("3", "../assets/hurly-burly/audio/dragon/dragonSound3.ogg");
	dragonSounds->addNewSound("4", "../assets/hurly-burly/audio/dragon/dragonSound4.ogg");
	dragonSounds->addNewSound("5", "../assets/hurly-burly/audio/dragon/dragonSound5.ogg");
	dragonSounds->addNewSound("6", "../assets/hurly-burly/audio/dragon/dragonSound6.ogg");
	dragonSounds->addNewSound("7", "../assets/hurly-burly/audio/dragon/dragonSound7.ogg");
	dragonSounds->addNewSound("8", "../assets/hurly-burly/audio/dragon/dragonSound8.ogg");
	dragonSounds->addNewSound("9", "../assets/hurly-burly/audio/dragon/dragonSound9.ogg");
	dragonSounds->addNewSound("10", "../assets/hurly-burly/audio/dragon/dragonSound10.ogg");
	dragonSounds->addNewSound("11", "../assets/hurly-burly/audio/dragon/dragonSound11.ogg");
	dragonSounds->addNewSound("12", "../assets/hurly-burly/audio/dragon/dragonSound12.ogg");
	dragonSounds->addNewSound("13", "../assets/hurly-burly/audio/dragon/dragonSound13.ogg");
	dragonSounds->addNewSound("14", "../assets/hurly-burly/audio/dragon/dragonSound14.ogg");
	dragonSounds->addNewSound("15", "../assets/hurly-burly/audio/puppetDialog_Dragon/fire1.ogg");
	dragonSounds->addNewSound("16", "../assets/hurly-burly/audio/puppetDialog_Dragon/lookOut1.ogg");
	dragonSounds->addNewSound("17", "../assets/hurly-burly/audio/puppetDialog_Dragon/lookOut2.ogg");
	dragonSounds->addNewSound("18", "../assets/hurly-burly/audio/puppetDialog_Dragon/ohNo1.ogg");
	dragonSounds->addNewSound("19", "../assets/hurly-burly/audio/puppetDialog_Dragon/ohNo2.ogg");
	dragonSounds->addNewSound("20", "../assets/hurly-burly/audio/puppetDialog_Dragon/ohNo3.ogg");
	resources.push_back(dragonSounds);

	fireSounds->addNewSound("1", "../assets/hurly-burly/audio/puppetDialog_Dragon/onFire1.ogg");
	fireSounds->addNewSound("2", "../assets/hurly-burly/audio/puppetDialog_Dragon/onFire2.ogg");
	fireSounds->addNewSound("3", "../assets/hurly-burly/audio/puppetDialog_Dragon/onFire3.ogg");
	fireSounds->addNewSound("4", "../assets/hurly-burly/audio/puppetDialog_Dragon/onFire4.ogg");
	fireSounds->addNewSound("5", "../assets/hurly-burly/audio/puppetDialog_Dragon/onFire5.ogg");
	fireSounds->addNewSound("6", "../assets/hurly-burly/audio/puppetDialog_Dragon/onFire6.ogg");
	resources.push_back(fireSounds);

	miscSounds->addNewSound("damaged", "../assets/hurly-burly/audio/puppetDialog_Dragon/castleAboutToBreak.ogg");
	miscSounds->addNewSound("broken", "../assets/hurly-burly/audio/puppetDialog_Dragon/castleBroken.ogg");
	resources.push_back(miscSounds);
}
