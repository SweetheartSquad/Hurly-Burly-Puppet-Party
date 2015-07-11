#pragma once

#include <ItemSimpleWeapon.h>

class ItemGold : public ItemSimpleWeapon{
public:
	static MeshInterface * goldMesh;
	
	bool passed;

	explicit ItemGold (Box2DWorld * _world);
	void update(Step * _step) override;
};