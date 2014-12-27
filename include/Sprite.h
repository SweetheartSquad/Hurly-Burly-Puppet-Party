#pragma once 

#include "MeshEntity.h"
#include "MeshInterface.h"
#include <map>
#include <utility>

class SpriteSheetAnimation;
class Rectangle;
class SpriteMesh;

class Sprite : public MeshEntity{
public:
	std::map<std::string, SpriteSheetAnimation *> animations;
	SpriteSheetAnimation * currentAnimation;
	bool playAnimation;

	explicit Sprite(Shader * _shader = nullptr, Transform * _transform = new Transform());
	virtual ~Sprite();

	Vertex * getTopLeft();
	Vertex * getTopRight();
	Vertex * getBottomLeft();
	Vertex * getBottomRight();

	void setUvs(float _topLeftU, float _topLeftV, float _topRightU, float _topRightV, 
		float _bottomLeftU, float _bottomLeftV, float _bottomRightU, float _bottomRightV);
	void setUvs(Rectangle _rect);
	void update(Step* _step) override;
	void addAnimation(std::string _name, SpriteSheetAnimation * _animation, bool _makeCurrent);
	void setCurrentAnimation(std::string _name);
};