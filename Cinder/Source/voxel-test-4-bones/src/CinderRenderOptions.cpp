#include "CinderRenderOptions.h"

CinderRenderOptions::CinderRenderOptions(Shader* _shader, std::vector<Light *> *_lights, Shader * _overrideShader):
	RenderOptions(_shader, _lights, _overrideShader),
	voxelPreviewMode(false),
	voxelPreviewResolution(0.1f),
	voxelPreviewSize(0.1f),
	voxelSphereRadius(0.1f),
	sphere(nullptr),
	cube(nullptr)
{
}

CinderRenderOptions::~CinderRenderOptions(){
}