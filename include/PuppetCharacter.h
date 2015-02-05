#pragma once

#include <Box2D/Box2D.h>

#include "Character.h"

class CharacterComponent;
class Box2DWorld;

class PuppetCharacter : public Character{
public:

	std::vector<CharacterComponent * > components;

	PuppetCharacter(Box2DWorld * _world, int16 _categoryBits, int16 _maskBits = -1, bool _ai = true);
	~PuppetCharacter();	
	
	void render(vox::MatrixStack* _matrixStack, RenderOptions* _renderStack) override;
	void update(Step* _step) override;
	void unload() override;
	void load() override;

};