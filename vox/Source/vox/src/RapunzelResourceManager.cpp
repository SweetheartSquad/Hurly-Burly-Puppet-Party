#pragma once

#include <RapunzelResourceManager.h>
#include <TextureSampler.h>
#include <SoundManager.h>

Texture * RapunzelResourceManager::goldSpriteSheet    = new Texture("../assets/hurly-burly/Gold/GoldPileSpriteSheet.png", 1024, 1024, true, false);

TextureSampler * RapunzelResourceManager::splashMessage		= nullptr;
															  
TextureSampler * RapunzelResourceManager::towerBackground	= nullptr;
TextureSampler * RapunzelResourceManager::towerCatwalk		= nullptr;
TextureSampler * RapunzelResourceManager::towerTower		= nullptr;
															  
TextureSampler * RapunzelResourceManager::goldBrick			= nullptr;
TextureSampler * RapunzelResourceManager::glove				= nullptr;
TextureSampler * RapunzelResourceManager::spring			= nullptr;
TextureSampler * RapunzelResourceManager::itemSpear			= nullptr;
															  
TextureSampler * RapunzelResourceManager::leverHandle		= nullptr;
TextureSampler * RapunzelResourceManager::leverBase			= nullptr;
															  
TextureSampler * RapunzelResourceManager::hair				= nullptr;
															  
TextureSampler * RapunzelResourceManager::hairLink			= nullptr;
TextureSampler * RapunzelResourceManager::hairEnd			= nullptr;
															  
TextureSampler * RapunzelResourceManager::thiefTorso		= nullptr;
TextureSampler * RapunzelResourceManager::thiefArm			= nullptr;
TextureSampler * RapunzelResourceManager::thiefHelmet		= nullptr;
										  					  
TextureSampler * RapunzelResourceManager::rapunzelTorso		= nullptr;
TextureSampler * RapunzelResourceManager::rapunzelArm		= nullptr;
TextureSampler * RapunzelResourceManager::rapunzelHelmet	= nullptr;
										  					  
TextureSampler * RapunzelResourceManager::guard1Torso		= nullptr;
TextureSampler * RapunzelResourceManager::guard1Arm			= nullptr;
TextureSampler * RapunzelResourceManager::guard1Helmet		= nullptr;
TextureSampler * RapunzelResourceManager::guard2Torso		= nullptr;
TextureSampler * RapunzelResourceManager::guard2Arm			= nullptr;
TextureSampler * RapunzelResourceManager::guard2Helmet		= nullptr;

SoundManager * RapunzelResourceManager::gloveSounds	= new SoundManager(-1);
SoundManager * RapunzelResourceManager::spearSounds	= new SoundManager(-1);
SoundManager * RapunzelResourceManager::tauntSounds	= new SoundManager(-1);

void RapunzelResourceManager::init(){

	splashMessage		= new TextureSampler(new Texture("../assets/hurly-burly/SplashMessages/RapunzelSplash.png", 1024, 1024, true, false), 1024, 1024);
	
	towerBackground	= new TextureSampler("../assets/hurly-burly/RapCastleAssets/", "RapCastleBackground.png.def", false);
	towerCatwalk		= new TextureSampler("../assets/hurly-burly/RapCastleAssets/", "RapCastleCatwalk.png.def", false);
	towerTower		= new TextureSampler("../assets/hurly-burly/RapCastleAssets/", "RapCastleTower.png.def", false);
	
	goldBrick			= new TextureSampler("../assets/hurly-burly/Gold/", "goldBrick.png.def", false);
	glove				= new TextureSampler("../assets/hurly-burly/BoxingGlove/", "BoxingGlove.png.def", false);
	spring			= new TextureSampler("../assets/hurly-burly/RapCastleAssets/", "RapCastleSpring.png.def", false);
	itemSpear			= new TextureSampler("../assets/hurly-burly/WeaponAssets/", "arrow.png.def", false);
	
	leverHandle		= new TextureSampler("../assets/hurly-burly/Lever/", "LeverHandle.png.def", false);
	leverBase			= new TextureSampler("../assets/hurly-burly/Lever/", "LeverBase.png.def", false);
	
	hair				= new TextureSampler("../assets/hurly-burly/Hair/", "Hair.png.def", false);
	
	hairLink			= new TextureSampler("../assets/hurly-burly/RapunzelAssets/", "RapunzelHairLink.png.def", false);
	hairEnd			= new TextureSampler("../assets/hurly-burly/RapunzelAssets/", "RapunzelHairEnd.png.def", false);
	
	thiefTorso		= new TextureSampler("../assets/hurly-burly/ThiefAssets/", "ThiefTorso.png.def", false);
	thiefArm			= new TextureSampler("../assets/hurly-burly/ThiefAssets/", "ThiefArm.png.def", false);
	thiefHelmet		= new TextureSampler("../assets/hurly-burly/ThiefAssets/", "ThiefHelmet.png.def", false);
	
	rapunzelTorso		= new TextureSampler("../assets/hurly-burly/RapunzelAssets/", "RapunzelDress.png.def", false);
	rapunzelArm		= new TextureSampler("../assets/hurly-burly/RapunzelAssets/", "RapunzelArm.png.def", false);
	rapunzelHelmet	= new TextureSampler("../assets/hurly-burly/RapunzelAssets/", "RapunzelHat.png.def", false);
	
	guard1Torso		= new TextureSampler("../assets/hurly-burly/FancyKnight1/", "FK1Breastplate.png.def", false);
	guard1Arm			= new TextureSampler("../assets/hurly-burly/FancyKnight1/", "FK1Arm.png.def", false);
	guard1Helmet		= new TextureSampler("../assets/hurly-burly/FancyKnight1/", "FK1Helmet.png.def", false);
	guard2Torso		= new TextureSampler("../assets/hurly-burly/FancyKnight2/", "FK2Breastplate.png.def", false);
	guard2Arm			= new TextureSampler("../assets/hurly-burly/FancyKnight2/", "FK2Arm.png.def", false);
	guard2Helmet		= new TextureSampler("../assets/hurly-burly/FancyKnight2/", "FK2Helmet.png.def", false);


	resources.push_back(splashMessage);

	resources.push_back(leverHandle);
	resources.push_back(leverBase);

	resources.push_back(hair);
	resources.push_back(hairLink);
	resources.push_back(hairEnd);

	resources.push_back(goldSpriteSheet);
	resources.push_back(goldBrick);
	resources.push_back(glove);
	resources.push_back(spring);
	resources.push_back(itemSpear);

	resources.push_back(towerBackground);
	resources.push_back(towerCatwalk);
	resources.push_back(towerTower);

	resources.push_back(thiefTorso);
	resources.push_back(thiefArm);
	resources.push_back(thiefHelmet);
	
	resources.push_back(rapunzelTorso);
	resources.push_back(rapunzelArm);
	resources.push_back(rapunzelHelmet);
	
	resources.push_back(guard1Torso);
	resources.push_back(guard1Arm);	  
	resources.push_back(guard1Helmet);
	resources.push_back(guard2Torso);
	resources.push_back(guard2Arm);	  
	resources.push_back(guard2Helmet);
	
	gloveSounds->addNewSound("1", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_glove1.ogg");
	gloveSounds->addNewSound("2", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_glove2.ogg");
	gloveSounds->addNewSound("3", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_glove3.ogg");
	resources.push_back(gloveSounds);						  
															  
	spearSounds->addNewSound("1", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_spear1.ogg");
	spearSounds->addNewSound("2", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_spear2.ogg");
	spearSounds->addNewSound("3", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_spear3.ogg");
	resources.push_back(spearSounds);						  
															  
	tauntSounds->addNewSound("1", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_throw1.ogg");
	tauntSounds->addNewSound("2", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_throw2.ogg");
	tauntSounds->addNewSound("3", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_throw3.ogg");
	tauntSounds->addNewSound("4", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_myGold.ogg");
	tauntSounds->addNewSound("5", "../assets/hurly-burly/audio/RapunzelAudio/rapunzel_getOff.ogg");
	resources.push_back(tauntSounds);
}
