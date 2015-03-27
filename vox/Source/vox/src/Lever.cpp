#pragma once

#include <Lever.h>

#include <Box2DSprite.h>
#include <Box2DWorld.h>
#include <RapunzelResourceManager.h>

Lever::Lever(Box2DWorld* _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex):
	Structure(_world, _categoryBits, _maskBits, _groupIndex),
	NodeTransformable(new Transform()),
	NodeChild(nullptr),
	NodeRenderable()
{
	TextureSampler * baseTextureSampler = RapunzelResourceManager::leverBase;
	TextureSampler * handleTextureSampler = RapunzelResourceManager::leverHandle;

	rootComponent = base = new Box2DSprite(_world, baseTextureSampler, b2_staticBody, false, nullptr, new Transform(), componentScale);
	handle = new Box2DSprite(_world, handleTextureSampler, b2_dynamicBody, false, nullptr, new Transform(), componentScale);
	
	components.push_back(&base);
	components.push_back(&handle);
	
	b2Filter sf;
	sf.categoryBits = categoryBits;
	if(maskBits != (int16)-1){
		sf.maskBits = maskBits;
	}
	sf.groupIndex = groupIndex;

	for(Box2DSprite ** c : components){
		(*c)->createFixture(sf);
	}

	setUserData(this);

	base->setTranslationPhysical(0.f, base->getCorrectedHeight(), 0.f);
	
	handle->body->GetFixtureList()->SetDensity(10.f);

	// axel
	b2RevoluteJointDef jth;
	jth.bodyA = base->body;
	jth.bodyB = handle->body;
	jth.localAnchorA.Set(0.f, 0.9f * base->getCorrectedHeight());
	jth.localAnchorB.Set(0.f, 0.1f * handle->getCorrectedHeight());
	jth.collideConnected = false;
	jth.enableLimit = true;
	jth.referenceAngle = 0.f;
	jth.lowerAngle = glm::radians(-80.f);
	world->b2world->CreateJoint(&jth);
}

Lever::~Lever()
{
}

void Lever::render(vox::MatrixStack* _matrixStack, RenderOptions* _renderStack){
	Structure::render(_matrixStack, _renderStack);
}

void Lever::update(Step * _step){
	Structure::update(_step);

	b2RevoluteJoint * jk = (b2RevoluteJoint *)base->body->GetJointList()->joint;
	float angle = jk->GetJointAngle();
	
	if(!ready){
		if(triggered){
			handle->body->SetAngularVelocity(-20);
			if(angle <= glm::radians(-75.f)){
				handle->body->SetAngularVelocity(1);
				triggered = false;
			}
		}else if(angle >= -0.0001f){
			handle->body->SetAngularVelocity(1);
			ready = true;
		}
	}else{
		handle->body->SetAngularVelocity(1);
	}
}

void Lever::unload(){
	Structure::unload();
}

void Lever::load(){
	Structure::load();
}

void Lever::pullLever(){

}