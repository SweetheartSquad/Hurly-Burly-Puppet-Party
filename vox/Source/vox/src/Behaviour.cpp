#pragma once

#include <Behaviour.h>
#include <PuppetCharacter.h>

Behaviour::Behaviour(PuppetCharacter * _source, float _radius, PuppetGame::BOX2D_CATEGORY _filter) :
	source(_source),
	radius(_radius),
	filter(_filter),
	active(false),
	fixture(nullptr)
{
	b2CircleShape behaviourShape;
	behaviourShape.m_radius = radius;

	fixture = source->torso->body->CreateFixture(&behaviourShape, 0);
	fixture->SetSensor(true);
	fixture->SetUserData(this);
	b2Filter f;
	f.categoryBits = PuppetGame::kBEHAVIOUR;
	f.maskBits = filter;
	f.groupIndex = source->groupIndex;
	fixture->SetFilterData(f);
}

Behaviour::~Behaviour(){
	if(fixture != nullptr && source->torso != nullptr){
		source->torso->body->DestroyFixture(fixture);
	}
}

void Behaviour::evaluateBeginContact(b2Fixture * _target){
	active = true;
}

void Behaviour::evaluateEndContact(b2Fixture * _target){
	
}