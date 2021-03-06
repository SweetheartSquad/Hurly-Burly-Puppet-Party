#pragma once

#include <vector>

#include "node/NodeLoadable.h"
#include "node/NodeRenderable.h"
#include "node/NodeUpdatable.h"

class Camera;

namespace vox{
	class MatrixStack;
}

class RenderOptions;
class Light;
class DepthMapShader;
class BaseComponentShader;
class RenderSurface;
class Keyboard;
class StandardFrameBuffer;
class DepthFrameBuffer;
class Mouse;
class Game;
class Entity;
class BlurShader;

class Scene : public virtual NodeRenderable, public virtual NodeLoadable, public virtual NodeUpdatable{
public:
	explicit Scene(Game * _game);
	virtual ~Scene(void);
	Game * game;
	/** Reference to mouse singleton */
	Mouse * mouse;
	/** Reference to keyboard singleton */
	Keyboard * keyboard;
	/** Reference to this scene's active camera */
	Camera * activeCamera;
	std::vector<Camera *> cameras;

	RenderOptions       * renderOptions;
	StandardFrameBuffer	* depthBuffer;
	StandardFrameBuffer * shadowBuffer;
	DepthMapShader		* depthShader;
	BlurShader			* shadowShader;
	RenderSurface       * shadowSurface;
	/** Reference to a list of references to entitites included in this scene */
	std::vector<Entity *> children;
	/** The lights for this scene **/
	std::vector<Light *> lights;
	/**The default matrix stack for the scene*/
	vox::MatrixStack * matrixStack;
	/** Calls update on the attached camera */
	virtual void update(Step * _step) override;
	/** Tells the RenderSystem to render the attached children to the vox::currentContext using the camera's view-projection matrix */
	virtual void render(vox::MatrixStack * _matrixStack, RenderOptions * _renderOptions) override;
	/** Adds a reference to an entity to the attached list of children */
	virtual void addChild(Entity * _child);
	/** Searches the list of children and removes _child
	(searches whole array, so if child is added more than once, removes every instance) */
	virtual void removeChild(Entity * _child);

	virtual void renderShadows(vox::MatrixStack * _matrixStack, RenderOptions * _renderOptions);

	float clearColor[4];

	virtual void load() override;
	virtual void unload() override;
};
