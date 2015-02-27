#pragma once

#include "RaidTheCastle.h"
#include "Boulder.h"
#include "Catapult.h"
#include "Box2DSprite.h"
#include "Box2DWorld.h"
#include "shader/BaseComponentShader.h"
#include "keyboard.h"

#include <glfw\glfw3.h>

RaidTheCastle::RaidTheCastle(Game* _game):
	PuppetScene(_game)
{
	loadCatapult();
}

RaidTheCastle::~RaidTheCastle(){
}

void RaidTheCastle::update(Step* _step){
	PuppetScene::update(_step);
	if(catapult->ready && !catapult->boulderLoaded){
		loadCatapult();
	}

	if(keyboard->keyDown(GLFW_KEY_F)){
		catapult->fireCatapult();
	}
	if(catapult->fireBoulder){
		catapult->fireBoulder = false;
		catapult->boulderLoaded = false;
		if(catapult->boulderJoint != nullptr){
			world->b2world->DestroyJoint(catapult->boulderJoint);
			catapult->boulderJoint = nullptr;
			catapult->boulder = nullptr;
		}
	}
}

void RaidTheCastle::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderStack){
	PuppetScene::render(_matrixStack, renderOptions);
}

void RaidTheCastle::load(){
	PuppetScene::load();
}

void RaidTheCastle::unload(){
	PuppetScene::unload();
}

void RaidTheCastle::loadCatapult(){
	Boulder * boulder = new Boulder(world, PuppetScene::ITEM, PuppetScene::PLAYER | PuppetScene::STRUCTURE | PuppetScene::ITEM, catapult->groupIndex);
	boulder->setShader(shader, true);
	addChild(boulder);
	boulder->addToScene(this);
	//boulder->boulder->body->SetTransform(catapult->arm->body->GetPosition(), std::rand());
	boulder->translateComponents(glm::vec3(-36, 6, 0)); // this is hard-coded, should not be
	//boulder->boulder->body->SetTransform(b2Vec2(-36, 6), 0);
	catapult->cooldownCnt = 0.f;
	catapult->ready = true;
	catapult->boulderLoaded = true;
	catapult->boulder = boulder;

	// axel
	b2WeldJointDef abpj;
	abpj.bodyA = catapult->arm->body;
	abpj.bodyB = boulder->boulder->body;
	abpj.localAnchorA.Set(-0.7f * catapult->arm->getCorrectedWidth(), 0.0f * catapult->arm->getCorrectedHeight());
	abpj.localAnchorB.Set(0.0f * boulder->boulder->getCorrectedWidth(), 0.f * boulder->boulder->getCorrectedHeight());
	abpj.collideConnected = false;
	abpj.referenceAngle = 0.f;
	catapult->boulderJoint = (b2WeldJoint *)world->b2world->CreateJoint(&abpj);
}