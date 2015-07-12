#pragma once

#include <vector>

#include <node\NodeUpdatable.h>
#include <node\NodeChild.h>

class Behaviour;
class PuppetCharacter;

class BehaviourManager : public NodeUpdatable, public NodeChild{
public:
	PuppetCharacter * target;

	std::vector<Behaviour * > behaviours;

	void addBehaviour(Behaviour * _behaviour);

	void update(Step * _step) override;

	explicit BehaviourManager(PuppetCharacter * _target);
	~BehaviourManager();
};