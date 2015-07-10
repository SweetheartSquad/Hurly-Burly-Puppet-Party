#pragma once

#include <PuppetCharacterGuard.h>
#include <PuppetTexturePack.h>
#include <BehaviourPatrol.h>
#include <BehaviourAttack.h>
#include <BehaviourManager.h>
#include <RapunzelResourceManager.h>
#include <shader\ShaderComponentTint.h>
#include <shader\ShaderComponentAlpha.h>
#include <RenderOptions.h>
#include <shader\ComponentShaderBase.h>

#include <Item.h>

PuppetCharacterGuard::PuppetCharacterGuard(bool _ai, Box2DWorld * _world, int16 _categoryBits, int16 _maskBits, int16 _groupIndex):
	PuppetCharacter(new PuppetTexturePack(
	std::rand()%2 == 0 ? RapunzelResourceManager::guard1Torso : RapunzelResourceManager::guard2Torso,
	std::rand()%2 == 0 ? RapunzelResourceManager::guard1Arm : RapunzelResourceManager::guard2Arm,
	std::rand()%2 == 0 ? RapunzelResourceManager::guard1Helmet : RapunzelResourceManager::guard2Helmet
	), _ai, _world, _categoryBits, _maskBits, _groupIndex)
{
	//itemHolder = armLeft;
	behaviourManager->addBehaviour(new BehaviourPatrol(glm::vec3(0, 0, 0), glm::vec3(70.f, 0, 0), this, 10));
	behaviourManager->addBehaviour(new BehaviourAttack(this, 3, PuppetGame::kPLAYER));
}

void PuppetCharacterGuard::render(vox::MatrixStack * _matrixStack, RenderOptions * _renderOptions){
	Shader * prev = _renderOptions->shader;
	applyShader(_renderOptions);
	// save the current shader settings
	float red = static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->getRed();
	float green = static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->getGreen();
	float blue = static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->getBlue();
	float alpha = static_cast<ShaderComponentAlpha *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(3))->getAlpha();

	static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->setRed(red + (1 - control) * 3);
	static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->setGreen(green - (1 - control) * 3);
	static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->setBlue(blue - (1 - control) * 3);

	if (dead){
		static_cast<ShaderComponentAlpha *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(3))->setAlpha(0.5f);
	}

	popsicleStick->parents.at(0)->render(_matrixStack, _renderOptions);

	whiteHead->parents.at(0)->render(_matrixStack, _renderOptions);
	whiteTorso->parents.at(0)->render(_matrixStack, _renderOptions);
	whiteArmLeft->parents.at(0)->render(_matrixStack, _renderOptions);
	whiteArmRight->parents.at(0)->render(_matrixStack, _renderOptions);


	armLeft->parents.at(0)->render(_matrixStack, _renderOptions);
	armRight->parents.at(0)->render(_matrixStack, _renderOptions);
	torso->parents.at(0)->render(_matrixStack, _renderOptions);
	head->parents.at(0)->render(_matrixStack, _renderOptions);
	face->parents.at(0)->render(_matrixStack, _renderOptions);
	handLeft->parents.at(0)->render(_matrixStack, _renderOptions);
	handRight->parents.at(0)->render(_matrixStack, _renderOptions);
	headgear->parents.at(0)->render(_matrixStack, _renderOptions);

	if (indicator != nullptr){
		indicator->parents.at(0)->render(_matrixStack, _renderOptions);
	}
	static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->setRed(red);
	static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->setGreen(green);
	static_cast<ShaderComponentTint *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(2))->setBlue(blue);
	static_cast<ShaderComponentAlpha *>(static_cast<ComponentShaderBase *>(shader)->getComponentAt(3))->setAlpha(alpha);

	_renderOptions->shader = prev;
}