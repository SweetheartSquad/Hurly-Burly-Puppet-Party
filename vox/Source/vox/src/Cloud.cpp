#pragma once

#include <Cloud.h>
#include <PuppetResourceManager.h>
#include <MeshFactory.h>
#include <NumberUtils.h>
#include <MeshInterface.h>

Cloud::Cloud(Shader * _shader) :
	MeshEntity(MeshFactory::getPlaneMesh())
{
	setShader(_shader, true);

	float scale = vox::NumberUtils::randomFloat(0.5, 1.5)*10.f;
	childTransform->scale(scale, scale, 1);
	int tex = std::rand() % 4;
	switch (tex){
	case 0:
		mesh->pushTexture2D(PuppetResourceManager::cloud1); break;
	case 1:
		mesh->pushTexture2D(PuppetResourceManager::cloud2); break;
	case 2:
		mesh->pushTexture2D(PuppetResourceManager::cloud3); break;
	case 3:
		mesh->pushTexture2D(PuppetResourceManager::cloud4); break;
	default:
		break;
	}
}

void Cloud::update(Step * _step){
	MeshEntity::update(_step);

	parents.at(0)->translate(sin(_step->time) / (10*parents.at(0)->getScaleVector().x), 0, 0);
}