#pragma once

#include "PuppetScene.h"

#include <Texture.h>
#include <TextureSampler.h>
#include "Sprite.h"
#include "shader/ComponentShaderBase.h"
#include "shader/ShaderComponentTexture.h"
#include "shader/ShaderComponentHsv.h"
#include "shader/ShaderComponentTint.h"
#include "shader/ShaderComponentAlpha.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "Box2DSprite.h"
#include "Box2DWorld.h"
#include "ControllableOrthographicCamera.h"
#include "RenderOptions.h"
#include "MeshEntity.h"

#include <Box2D/Box2D.h>
#include <Box2DDebugDrawer.h>
#include "Box2DMeshEntity.h"
#include "MeshFactory.h"
#include "FollowCamera.h"
#include "MousePerspectiveCamera.h"
#include "BitmapFont.h"
#include "RaidTheCastleContactListener.h"
#include "Game.h"
#include "PuppetGame.h"
#include <Item.h>
#include <Arduino.h>
#include <AccelerometerParser.h>
#include <Accelerometer.h>
#include <FollowCamera.h>
#include <PuppetCharacter.h>
#include <PuppetController.h>
#include <RandomGround.h>

#include <RaidTheCastle.h>
#include <Rapunzel.h>
#include <SlayTheDragon.h>
#include <FightYourFriends.h>
#include <VictoryScene.h>

#include <PuppetResourceManager.h>
#include <NumberUtils.h>
#include <Resource.h>
#include <Easing.h>

#include <ParticleSystem.h>
#include <ItemGold.h>
#include <Cloud.h>
#include <RenderSurface.h>
#include <StandardFrameBuffer.h>

class SlayTheDragon;

PuppetScene::PuppetScene(PuppetGame * _game, float seconds, float _width, float _height, float _size, bool _fullCurtains) :
	LayeredScene(_game, 4),
	sceneHeight(_height),
	sceneWidth(_width),
	duration(seconds),
	currentTime(0),
	countDown(0),
	displayingSplash(false),
	splashSoundPlayed(false),
	splashMessage(nullptr),
	splashDuration(2.f),
	cl(nullptr),
	world(new Box2DWorld(b2Vec2(0.f, -98.0f))),
	drawer(nullptr),
	stageFloor(nullptr),
	stageFront(nullptr),
	background(new MeshEntity(MeshFactory::getPlaneMesh())),
	shader(new ComponentShaderBase(false)),
	soundManager(new SoundManager(-1)),
	backgroundSoundManager(new SoundManager(-1)),
	countdownSoundManager(new SoundManager(-1)),
	mouseCam(false),
	victoryTriggered(false),
	sceneStart(vox::step.time),
	screenShaderSetting(3),
	screenSurfaceShader(new Shader("../assets/RenderSurfacePlus", false, true)),
	screenSurface(new RenderSurface(screenSurfaceShader)),
	screenFBO(new StandardFrameBuffer(true)),
	ghostPosition(0),
	sun(nullptr),
	uiLayer(new UILayer(this, 0,0,0,0))
{
	screenSurfaceShader->unload();
	screenSurfaceShader->load();
	screenSurface->scaleModeMag = GL_NEAREST;
	screenSurface->load();
	screenSurface->configureDefaultVertexAttributes(screenSurfaceShader);


	world->b2world->SetContactListener(cl);
	shader->addComponent(new ShaderComponentTexture(shader));
	shader->addComponent(new ShaderComponentHsv(shader, 0.f, 1.25f, 1.25f));
	shader->addComponent(new ShaderComponentTint(shader, 0.f, 0.f, 0.f));
	shader->addComponent(new ShaderComponentAlpha(shader, 1.f));
	shader->compileShader();
	
	//Add Audio
	countdownSoundManager->addNewSound("0", "../assets/hurly-burly/audio/HighCountdown_Zero.ogg");
	countdownSoundManager->addNewSound("1", "../assets/hurly-burly/audio/silence.ogg");
	countdownSoundManager->addNewSound("2", "../assets/hurly-burly/audio/HighCountdown_One.ogg");
	countdownSoundManager->addNewSound("3", "../assets/hurly-burly/audio/HighCountdown_Two.ogg");
	countdownSoundManager->addNewSound("4", "../assets/hurly-burly/audio/HighCountdown_Three.ogg");
	countdownSoundManager->addNewSound("5", "../assets/hurly-burly/audio/HighCountdown_Four.ogg");
	countdownSoundManager->addNewSound("6", "../assets/hurly-burly/audio/HighCountdown_Five.ogg");

	//Since these are chosen randomly its easiest to just use numbers as the keys and generate a random number
	backgroundSoundManager->addNewSound("1", "../assets/hurly-burly/audio/songs/WesternSong.ogg");
	backgroundSoundManager->addNewSound("2", "../assets/hurly-burly/audio/songs/FastSong.ogg");
	backgroundSoundManager->addNewSound("3", "../assets/hurly-burly/audio/songs/MelodicaSong.ogg");
	
	if(_fullCurtains){
		Sprite * spotlight = new Sprite();
		addChild(spotlight, 2);
	
		spotlight->parents.at(0)->translate(0, 1, 5);
		spotlight->parents.at(0)->scale(sceneWidth, sceneHeight, 1);
		spotlight->mesh->pushTexture2D(PuppetResourceManager::stageSpotlight->texture);
		spotlight->setShader(shader, true);

		Sprite * curtainCenter = new Sprite();
		addChild(curtainCenter, 2);
	
		curtainCenter->parents.at(0)->translate(0, 1, 5);
		curtainCenter->parents.at(0)->scale(sceneWidth * 0.5, 30, 1);
		curtainCenter->parents.at(0)->translate((sceneWidth - curtainCenter->parents.at(0)->getScaleVector().x) * 0.8, 0, 0);
		curtainCenter->mesh->pushTexture2D(PuppetResourceManager::stageCurtainCenter->texture);
		curtainCenter->setShader(shader, true);

		Sprite * topCurtain = new Sprite();
		addChild(topCurtain, 2);
		topCurtain->parents.at(0)->translate(0, 1, 5);
		topCurtain->parents.at(0)->scale(sceneWidth, sceneHeight, 1);
		topCurtain->mesh->pushTexture2D(PuppetResourceManager::stageCurtainTop->texture);
		topCurtain->setShader(shader, true);
	}

	Sprite * curtain = new Sprite();
	addChild(curtain, 2);
	float scale = 100;
	curtain->parents.at(0)->translate(sceneWidth - 29, 1, 5);
	curtain->parents.at(0)->scale(30, sceneHeight, 1);
	curtain->mesh->pushTexture2D(PuppetResourceManager::stageCurtain->texture);
	curtain->setShader(shader, true);
	
	curtain = new Sprite();
	addChild(curtain, 2);
	curtain->parents.at(0)->translate(29, 1, 5);
	curtain->parents.at(0)->scale(-30, sceneHeight, 1);
	curtain->mesh->pushTexture2D(PuppetResourceManager::stageCurtain->texture);
	curtain->setShader(shader, true);



	boundaries.push_back(new Box2DMeshEntity(world, MeshFactory::getPlaneMesh(), b2_staticBody));
	boundaries.push_back(new Box2DMeshEntity(world, MeshFactory::getPlaneMesh(), b2_staticBody));
	boundaries.push_back(new Box2DMeshEntity(world, MeshFactory::getPlaneMesh(), b2_staticBody));
	boundaries.push_back(new Box2DMeshEntity(world, MeshFactory::getPlaneMesh(), b2_staticBody));
	for(auto b : boundaries){
		addChild(b, 2);
	}

	boundaries.at(0)->parents.at(0)->scale(_size, sceneHeight*0.5f + _size*2.f, _size);
	boundaries.at(1)->parents.at(0)->scale(_size, sceneHeight*0.5f + _size*2.f, _size);
	boundaries.at(2)->parents.at(0)->scale(sceneWidth*0.5f + _size*2.f, _size, _size);
	boundaries.at(3)->parents.at(0)->scale(sceneWidth*0.5f + _size*2.f, _size, _size);

	boundaries.at(0)->setTranslationPhysical(sceneWidth+_size, sceneHeight*0.5f, 5);
	boundaries.at(1)->setTranslationPhysical(-_size, sceneHeight*0.5f, 5);
	boundaries.at(2)->setTranslationPhysical(sceneWidth*0.5f, sceneHeight+_size, 5);
	boundaries.at(3)->setTranslationPhysical(sceneWidth*0.5f, -_size, 5);
	
	b2Filter sf;
	sf.categoryBits = PuppetGame::kBOUNDARY;
	sf.maskBits = -1;
	for(auto b : boundaries){
		b->setShader(shader, true);
		world->addToWorld(b);
		b->body->GetFixtureList()->SetFilterData(sf);
		b->mesh->pushTexture2D(PuppetResourceManager::stageFront);
	}
	sf.categoryBits = PuppetGame::kBOUNDARY | PuppetGame::kGROUND;
	boundaries.at(3)->body->GetFixtureList()->SetFilterData(sf);
	boundaries.at(3)->body->GetFixtureList()->SetFriction(1);
	boundaries.at(3)->body->GetFixtureList()->SetRestitution(0);

	addChild(background, 0);
	background->setShader(shader, true);
	background->parents.at(0)->translate(-sceneWidth/2.f, sceneHeight/2.f, -15.f/2.f);
	background->parents.at(0)->scale(sceneWidth*2.f, sceneHeight, 1);
	background->mesh->pushTexture2D(PuppetResourceManager::sky);
	background->mesh->uvEdgeMode = GL_MIRRORED_REPEAT_ARB;

	int timeOfDayOptions = PuppetResourceManager::sky->width;
	int timeOfDay = std::rand()%timeOfDayOptions;
	background->mesh->setUV(0, static_cast<float>(timeOfDay) / timeOfDayOptions, 0);
	background->mesh->setUV(1, static_cast<float>(timeOfDay) / timeOfDayOptions, 0);
	background->mesh->setUV(2, static_cast<float>(timeOfDay) / timeOfDayOptions, 1);
	background->mesh->setUV(3, static_cast<float>(timeOfDay) / timeOfDayOptions, 1);
	
	
	//Set up cameras
	Transform * t = new Transform();
	mouseCamera = new MousePerspectiveCamera();
	t->addChild(mouseCamera, false);
	cameras.push_back(mouseCamera);
	mouseCamera->farClip = 1000.f;
	t->rotate(90, 0, 1, 0, kWORLD);
	t->translate(5.0f, 1.5f, 22.5f);
	mouseCamera->yaw = 90.0f;
	mouseCamera->pitch = -10.0f;
	mouseCamera->speed = 1;

	t = new Transform();
	gameCam = new FollowCamera(15, glm::vec3(0, 0, 0), 0, 0);
	t->addChild(gameCam, false);
	cameras.push_back(gameCam);
	gameCam->farClip = 1000.f;
	t->rotate(90, 0, 1, 0, kWORLD);
	t->translate(5.0f, 1.5f, 22.5f);
	gameCam->minimumZoom = 22.5f;
	gameCam->yaw = 90.0f;
	gameCam->pitch = -10.0f;
	activeCamera = gameCam;
	
	Sprite * countDown0 = new Sprite();
	Sprite * countDownWait = new Sprite();
	Sprite * countDown1 = new Sprite();
	Sprite * countDown2 = new Sprite();
	Sprite * countDown3 = new Sprite();
	Sprite * countDown4 = new Sprite();
	Sprite * countDown5 = new Sprite();
	
	countDown0->mesh->pushTexture2D(PuppetResourceManager::countDown0->texture);
	countDownWait->mesh->pushTexture2D(PuppetResourceManager::blank);
	countDown1->mesh->pushTexture2D(PuppetResourceManager::countDown1->texture);
	countDown2->mesh->pushTexture2D(PuppetResourceManager::countDown2->texture);
	countDown3->mesh->pushTexture2D(PuppetResourceManager::countDown3->texture);
	countDown4->mesh->pushTexture2D(PuppetResourceManager::countDown4->texture);
	countDown5->mesh->pushTexture2D(PuppetResourceManager::countDown5->texture);
	
	countDownNumbers.push_back(countDown0);
	countDownNumbers.push_back(countDownWait);
	countDownNumbers.push_back(countDown1);
	countDownNumbers.push_back(countDown2);
	countDownNumbers.push_back(countDown3);
	countDownNumbers.push_back(countDown4);
	countDownNumbers.push_back(countDown5);
	countDown = countDownNumbers.size();
	
	for(Sprite * n : countDownNumbers){
		n->setShader(shader, true);
		n->childTransform->translate(1920.f*0.5, 1080.f*0.5f, 0);
    }

    particleSystem = new ParticleSystem(PuppetResourceManager::dustParticle, world, 0, 0, 0);
    particleSystem->addToLayeredScene(this, 1);
    addChild(particleSystem, 1);
	particleSystem->setShader(shader, true);
	particleSystem->emissionRate = -1;
	particleSystem->emissionAmount = 0;

	addChild(uiLayer, 3, false);
}

PuppetScene::~PuppetScene(){
	while(countDownNumbers.size() > 0){
		// just in case the scene was deleted while the countdown was going, remove them from the children list to avoid deleting them twice
		removeChild(countDownNumbers.back());
		delete countDownNumbers.back();
		countDownNumbers.pop_back();
	}
	
	deleteChildTransform();

	delete soundManager;
	delete countdownSoundManager;
	delete backgroundSoundManager;

	delete shader;

	delete world;
	delete cl;
	delete screenSurface;
	delete screenSurfaceShader;
	delete screenFBO;
}


void PuppetScene::assignControllers(){
	// standard
	//static_cast<PuppetGame *>(game)->puppetControllers.at(0)->setPuppetCharacter(players.at(0));
	//static_cast<PuppetGame *>(game)->puppetControllers.at(1)->setPuppetCharacter(players.at(1));
	//static_cast<PuppetGame *>(game)->puppetControllers.at(2)->setPuppetCharacter(players.at(2));
	//static_cast<PuppetGame *>(game)->puppetControllers.at(3)->setPuppetCharacter(players.at(3));
	
	

	// random
	std::vector<PuppetCharacter *> chars;
	for(PuppetCharacter * p : players){
		chars.push_back(p);
	}

	int c = 0;
	while(chars.size() > 0){
		int ch = vox::NumberUtils::randomInt(0, chars.size()-1);
		chars.at(ch)->id = c;
		static_cast<PuppetGame *>(game)->puppetControllers.at(c)->setPuppetCharacter(chars.at(ch));
		chars.erase(chars.begin() + ch);
		c++;
	}
}

void PuppetScene::load(){
	Scene::load();

	for(Sprite * s : countDownNumbers){
		s->load();
	}

	screenSurface->load();
	screenFBO->load();
}

void PuppetScene::unload(){
	Scene::unload();
	
	for(Sprite * s : countDownNumbers){
		s->unload();
	}

	screenSurface->unload();
	screenFBO->unload();
}

void PuppetScene::update(Step * _step){
    PuppetGame * pg = static_cast<PuppetGame *>(game);
	if(game->kc_just_active){
		screenShaderSetting = currentTime;
	}
	if(game->kc_active){
		if(currentTime > screenShaderSetting){
			screenShaderSetting = currentTime + std::rand() % 5 + 1;
			glUniform1i(glGetUniformLocation(screenSurfaceShader->getProgramId(), "distortion"), std::rand() % 6 + 1);
		}
	}else{
		glUniform1i(glGetUniformLocation(screenSurfaceShader->getProgramId(), "distortion"), 0);
	}
	glUniform1f(glGetUniformLocation(screenSurfaceShader->getProgramId(), "time"), (float)vox::lastTimestamp);

	// player controls
	if (players.size() > 0){
		if (keyboard->keyDown(GLFW_KEY_W)){
			pg->puppetControllers.at(0)->getPuppetCharacter()->jump();
		}if (keyboard->keyDown(GLFW_KEY_A)){
			pg->puppetControllers.at(0)->getPuppetCharacter()->targetRoll = glm::radians(-75.f);
		}
		if (keyboard->keyDown(GLFW_KEY_D)){
			pg->puppetControllers.at(0)->getPuppetCharacter()->targetRoll = glm::radians(75.f);
		}
		if (keyboard->keyJustDown(GLFW_KEY_T)){
			players.at(3)->action();
			players.at(2)->action();
			players.at(1)->action();
			players.at(0)->action();
		}

		if (keyboard->keyDown(GLFW_KEY_B)){
			for (PuppetCharacter * p : players){
				p->control = 0;
			}
		}
	}
	// camera controls
	if (keyboard->keyDown(GLFW_KEY_UP)){
		activeCamera->parents.at(0)->translate((activeCamera->forwardVectorRotated) * static_cast<MousePerspectiveCamera *>(activeCamera)->speed);
	}
	if (keyboard->keyDown(GLFW_KEY_DOWN)){
		activeCamera->parents.at(0)->translate((activeCamera->forwardVectorRotated) * -static_cast<MousePerspectiveCamera *>(activeCamera)->speed);
	}
	if (keyboard->keyDown(GLFW_KEY_LEFT)){
		activeCamera->parents.at(0)->translate((activeCamera->rightVectorRotated) * -static_cast<MousePerspectiveCamera *>(activeCamera)->speed);
	}
	if (keyboard->keyDown(GLFW_KEY_RIGHT)){
		activeCamera->parents.at(0)->translate((activeCamera->rightVectorRotated) * static_cast<MousePerspectiveCamera *>(activeCamera)->speed);
	}
	

	if(keyboard->keyDown(GLFW_KEY_G)){
		Item * g = new ItemGold(world);
		g->addToLayeredScene(this, 1);
		g->setShader(shader, true);
        addChild(g, 1);
		g->translateComponents(glm::vec3(vox::NumberUtils::randomFloat(0, sceneWidth), vox::NumberUtils::randomFloat(0, sceneHeight), 0));
		items.push_back(g);
	}

	LayeredScene::update(_step);
	if(splashMessage != nullptr){
		if(currentTime < splashDuration){
			if(displayingSplash){
				// the factor of 15 is only there because I can't load this thing at the correct size...
				//float scale = Easing::easeOutBack(splashDuration - currentTime, 0, 10, splashDuration);
				float easeTime = splashDuration - currentTime;
				float scale = (easeTime < splashDuration / 2.f) ? Easing::easeOutCubic(easeTime, 0, 1024, splashDuration / 2.f) : Easing::easeInElastic(easeTime - splashDuration / 2.f, 1024, -1024, splashDuration / 2.f);
				splashMessage->childTransform->scale(glm::vec3(scale, scale, 1), false);
			}else{
				//addChild(splashMessage, 2);
				uiLayer->childTransform->addChild(splashMessage, false);
				displayingSplash = true;
			}

			//splashMessage->transform->translate(activeCamera->transform->getTranslationVector(), false);
			//splashMessage->transform->translate(glm::vec3(0,0,-10));
		}else{
			// Remove previous number from scene
			uiLayer->childTransform->removeChild(splashMessage);
			delete splashMessage;
			splashMessage = nullptr;
		}
	}
	
	// destroy used up items
	for(signed long int i = items.size()-1; i >= 0; --i){
		Item * item = items.at(i);
		
		if (item->destroy){
			for (signed long int j = 0; j < std::rand() % 5 + 1; ++j){
				particleSystem->addParticle(item->rootComponent->getWorldPos(false), PuppetResourceManager::dustParticle);
			}
			destroyItem(item);
			item = nullptr;
			items.erase(items.begin() + i);
		}
	}
	
	world->update(_step);

	if(this == game->currentScene){
		currentTime += _step->deltaTime;
		if (currentTime > duration - countDownNumbers.size()){
			if(duration - currentTime < countDown){
				doCountDown();
			}
			if(countDown < countDownNumbers.size()){
				float displayTime = fmod(currentTime, 1.f);
				if(displayTime < 0.5f){
					float scale = Easing::easeOutElastic(displayTime, 0.f, 512.f, 0.5f);
					countDownNumbers.at(countDown)->childTransform->scale(glm::vec3(scale, scale, 1.f), false);
				}else{
					float scale = Easing::easeInCirc(displayTime-0.5f, 512.f, -512.f, 0.5f);
					countDownNumbers.at(countDown)->childTransform->scale(glm::vec3(scale, scale, 1.f), false);
				}
			}
			if(currentTime > duration){
				complete();
			}
		}
	}

	if(sun != nullptr){
		sun->parents.at(0)->rotate(_step->deltaTimeCorrection*0.05f, 0, 0, 1, kOBJECT);
	}

	// camera control
	if (keyboard->keyJustUp(GLFW_KEY_1)){
		mouseCam = !mouseCam;
		if (!mouseCam){
			activeCamera = gameCam;
		}else{
			activeCamera = mouseCamera;
		}
	}

	
	// trigger/speed-up countdown
	if (keyboard->keyJustUp(GLFW_KEY_ENTER)){
		if(currentTime < duration - countDownNumbers.size()){
			currentTime = duration - countDownNumbers.size();
			countDown = countDownNumbers.size();
		}else{
			currentTime += 1;
		}
    }
    if (keyboard->keyJustUp(GLFW_KEY_7)){
        if (game->currentSceneKey != "Fight Your Friends"){
            pg->puppetControllers.at(0)->unassign();
            pg->puppetControllers.at(1)->unassign();
            pg->puppetControllers.at(2)->unassign();
            pg->puppetControllers.at(3)->unassign();
            game->scenes.insert(std::make_pair("Fight Your Friends", new FightYourFriends((PuppetGame *)game)));
            complete("Fight Your Friends");
        }
    }else if (keyboard->keyJustUp(GLFW_KEY_8)){
        if (game->currentSceneKey != "Raid The Castle"){
            pg->puppetControllers.at(0)->unassign();
            pg->puppetControllers.at(1)->unassign();
            pg->puppetControllers.at(2)->unassign();
            pg->puppetControllers.at(3)->unassign();
            game->scenes.insert(std::make_pair("Raid The Castle", new RaidTheCastle((PuppetGame *)game)));
            complete("Raid The Castle");
        }
    }else if (keyboard->keyJustUp(GLFW_KEY_9)){
        if (game->currentSceneKey != "Rapunzel"){
            pg->puppetControllers.at(0)->unassign();
            pg->puppetControllers.at(1)->unassign();
            pg->puppetControllers.at(2)->unassign();
            pg->puppetControllers.at(3)->unassign();
            game->scenes.insert(std::make_pair("Rapunzel", new Rapunzel((PuppetGame *)game)));
            complete("Rapunzel");
        }
    }else if (keyboard->keyJustUp(GLFW_KEY_0)){
        if (game->currentSceneKey != "Slay The Dragon"){
            pg->puppetControllers.at(0)->unassign();
            pg->puppetControllers.at(1)->unassign();
            pg->puppetControllers.at(2)->unassign();
            pg->puppetControllers.at(3)->unassign();
            game->scenes.insert(std::make_pair("Slay The Dragon", new SlayTheDragon((PuppetGame *)game)));
            complete("Slay The Dragon");
        }
    }

	
	
	if(keyboard->keyJustUp(GLFW_KEY_F11)){
		game->toggleFullScreen();
	}
	if(keyboard->keyJustUp(GLFW_KEY_2)){
		if(drawer != nullptr){
			world->b2world->SetDebugDraw(nullptr);
			removeChild(drawer);
			delete drawer;
			drawer = nullptr;
		}else{
			drawer = new Box2DDebugDrawer(world);
			world->b2world->SetDebugDraw(drawer);
			drawer->drawing = true;
			//drawer->AppendFlags(b2Draw::e_aabbBit);
			drawer->AppendFlags(b2Draw::e_shapeBit);
			drawer->AppendFlags(b2Draw::e_centerOfMassBit);
			drawer->AppendFlags(b2Draw::e_jointBit);
			//drawer->AppendFlags(b2Draw::e_pairBit);
			addChild(drawer, 2);
		}
	}

	bool everyonesDead = true;
	for(auto p : players){
		if(!p->dead){
			everyonesDead = false;
			break;
		}
	}
	if(everyonesDead){
		triggerVictoryState();
	}
}

void PuppetScene::triggerVictoryState(){
	if(!victoryTriggered){
		if(currentTime < duration - 1){
			currentTime = duration - 1;
			countDown = 1;
			doCountDown();
		}
	}
}
void PuppetScene::complete(std::string _switchTo){
    PuppetGame * pg = static_cast<PuppetGame *>(game);
    if (_switchTo != ""){
        pg->switchScene(_switchTo, true);
    } else{
	    if(dynamic_cast<VictoryScene *>(this) != nullptr){
		    pg->puppetControllers.at(0)->unassign();
		    pg->puppetControllers.at(1)->unassign();
		    pg->puppetControllers.at(2)->unassign();
		    pg->puppetControllers.at(3)->unassign();

		    pg->loadRandomScene();
	    }else{
		    pg->scenes.insert(std::make_pair("Victory", new VictoryScene(pg, players)));
		    pg->switchScene("Victory", true);
	    }
    }
}

void PuppetScene::destroyItem(Item * _item){
	// remove the item from the children list
	removeChild(_item);

	// remove from follow cam
	gameCam->removeTarget(_item);
	for(signed long int j = _item->components.size()-1; j >= 0; --j){
		gameCam->removeTarget(*_item->components.at(j));
	}

	//maybe use something like children.erase(std::remove(children.begin(), children.end(), item), children.end());

	delete _item;
	_item = nullptr;
}

void PuppetScene::doCountDown(){
	// Remove previous number
	if (countDown <= countDownNumbers.size() - 1){
		// make things get
		static_cast<ShaderComponentHsv *>(shader->getComponentAt(1))->setSaturation(static_cast<ShaderComponentHsv *>(shader->getComponentAt(1))->getSaturation() - 0.15f);
		//static_cast<ShaderComponentHsv *>(shader->components.at(1))->setValue(static_cast<ShaderComponentHsv *>(shader->components.at(1))->getValue() + 0.2f);
		
		uiLayer->childTransform->removeChild(countDownNumbers.back());
		delete countDownNumbers.back();
		countDownNumbers.pop_back();
	}
	
	if(countDown > 0){
		// Decrease countdown
		-- countDown;

		// Display countdown
		std::cout << "=========================" << std::endl;
		std::cout << countDown << std::endl;
		std::cout << "idx: " << countDown << std::endl;
		std::cout << "=========================" << std::endl;

		countdownSoundManager->play(std::to_string(countDown));

		// Add new number to scene
		uiLayer->childTransform->addChild(countDownNumbers.at(countDown), false);
	}
}

void PuppetScene::playRandomBackgroundMusic(){
	backgroundSoundManager->playRandomSound();
}

void PuppetScene::populateBackground(){
	stageFloor = new MeshEntity(Resource::loadMeshFromObj("../assets/hurly-burly/stageFloor.vox").at(0));
	stageFront = new MeshEntity(Resource::loadMeshFromObj("../assets/hurly-burly/stageFront.vox").at(0));

	addChild(stageFloor, 0);
	addChild(stageFront, 0);

	stageFloor->setShader(shader, true);
	stageFloor->parents.at(0)->scale(1000, 100, 100);
	stageFloor->parents.at(0)->translate(50.f / 2.f, 0, -15.f / 2.f);
	stageFloor->mesh->uvEdgeMode = GL_REPEAT;
	stageFloor->mesh->pushTexture2D(PuppetResourceManager::stageFloor);
	for (Vertex & v : stageFloor->mesh->vertices){
		v.u *= 10;
		v.v *= 100;
	}
	stageFloor->mesh->dirty = true;

	stageFront->setShader(shader, true);
	stageFront->parents.at(0)->scale(1000, 100, 100);
	stageFront->parents.at(0)->translate(50.f / 2.f, 0, -15.f / 2.f);
	stageFront->mesh->uvEdgeMode = GL_REPEAT;
	stageFront->mesh->pushTexture2D(PuppetResourceManager::stageFront);
	for (Vertex & v : stageFront->mesh->vertices){
		v.u *= 10;
		v.v *= 100;
	}
	stageFront->mesh->dirty = true;
	
	sun = new MeshEntity(MeshFactory::getPlaneMesh());
	addChild(sun, 0);
	sun->setShader(shader, true);
	sun->parents.at(0)->translate(10, sceneHeight-10, -7.f);
	sun->parents.at(0)->scale(12, 12, 1);
	sun->mesh->pushTexture2D(PuppetResourceManager::sun);

	Texture * treeTex1 = PuppetResourceManager::tree1;
	Texture * treeTex2 = PuppetResourceManager::tree2;
	Texture * bushTex1 = PuppetResourceManager::bush1;
	Texture * bushTex2 = PuppetResourceManager::bush2;
	
	int numFoliage = 60;
	for(signed long int i = 0; i < numFoliage; ++i){
		float height = std::rand()%500/50.f+5.f;
		MeshEntity * foliage = new MeshEntity(MeshFactory::getPlaneMesh());
		addChild(foliage, 0);
		foliage->setShader(shader, true);
		foliage->parents.at(0)->translate((std::rand()%500/3.f)-25.f, height, max(-9, -(float)(numFoliage-i)/numFoliage)*8.f - 1.f);
		foliage->parents.at(0)->scale(height, height, 1);
		int tex = i % 4;
		switch(tex){
			case 0:
				foliage->mesh->pushTexture2D(treeTex1); break;
			case 1:
				foliage->mesh->pushTexture2D(treeTex2); break;
			case 2:
				foliage->mesh->pushTexture2D(bushTex1); break;
			case 3:
				foliage->mesh->pushTexture2D(bushTex2); break;
			default:
				break;
		}
		if(i == 3){
			RandomGround * randomGround = new RandomGround(world, 100, 0.4f, PuppetResourceManager::paper->texture, 3, 1);
			addChild(randomGround, 0);
			randomGround->setTranslationPhysical(0.0f, 0.0f, max(-9, -(float)(numFoliage-i)/numFoliage)*8.f - 1.f);
			randomGround->setShader(shader, true);
		}
	}
	
}

void PuppetScene::populateClouds(){
	int numClouds = std::rand() % 5 + 2;
	for(signed long int i = 0; i < numClouds; ++i){
		float height = vox::NumberUtils::randomFloat(sceneHeight / 4.f, sceneHeight);
		Cloud * cloud = new Cloud(shader);
		addChild(cloud, 0);
		cloud->parents.at(0)->translate(vox::NumberUtils::randomFloat(0, sceneWidth), height, max(-9, -(float)(numClouds-i)/numClouds)*8.f - 1.f);
	}
}

bool PuppetScene::comparePuppetId(PuppetCharacter * p1, PuppetCharacter * p2){
	if(p1->id < p2->id){
		return true;
	}
	return false;
}