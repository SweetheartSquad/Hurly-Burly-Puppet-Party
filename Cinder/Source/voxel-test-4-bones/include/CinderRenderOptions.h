#pragma once 

#include "RenderOptions.h"
#include <cinder\gl\GlslProg.h>

#include <vector>
//#include "GL/glew.h"
#include <glm/glm.hpp>

#include <cinder\Camera.h>
#include <cinder\gl\Vbo.h>

class Shader;
class Light;

class CinderRenderOptions : public RenderOptions{
	
public:

	CinderRenderOptions(Shader * _shader, std::vector<Light *> * _lights, Shader * _overrideShader = nullptr);

	~CinderRenderOptions();

	const ci::Camera * ciCam;
	ci::gl::GlslProg * ciShader;
	ci::gl::VboMesh * sphere;
	ci::gl::VboMesh * cube;

	// Whether to draw the voxels as voxels
	bool voxelPreviewMode;
	// Grid resolution for voxel preview
	float voxelPreviewResolution;
	// Cube size for voxel preview
	float voxelPreviewSize;
	// Sphere radius for voxel placing
	float voxelSphereRadius;
    // Whether to display the voxels
    bool viewJointsOnly;
};