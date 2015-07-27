#pragma once

#include "FightYourFriendsResourceManager.h"
#include <TextureSampler.h>
#include <SoundManager.h>

TextureSampler * FightYourFriendsResourceManager::arena2Fg		= nullptr;
TextureSampler * FightYourFriendsResourceManager::splashMessage	= nullptr;
Texture * FightYourFriendsResourceManager::arena1	= new Texture("assets/hurly-burly/fyfArenas/arena1.png", true, false);
Texture * FightYourFriendsResourceManager::arena2Bg	= new Texture("assets/hurly-burly/fyfArenas/arena2-bg.png", true, false);

void FightYourFriendsResourceManager::init(){
	arena2Fg		= new TextureSampler("assets/hurly-burly/fyfArenas/", "arena2-fg.png.def", false);
	splashMessage	= new TextureSampler(new Texture("assets/hurly-burly/SplashMessages/FYFSplash.png", true, false), 1024, 1024);

	resources.push_back(splashMessage);
	resources.push_back(arena1);
	resources.push_back(arena2Bg);
	resources.push_back(arena2Fg);
}