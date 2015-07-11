#pragma once

#include <PuppetContactListener.h>

class b2Contact;
class b2Fixture;
class PuppetScene;

//main collision call back function
class RaidTheCastleContactListener : public PuppetContactListener{
public:
	RaidTheCastleContactListener(PuppetScene * _scene);

	virtual void BeginContact(b2Contact* contact) override;
	void structureItemContact(b2Contact * _contact, b2Fixture * _structureFixture, b2Fixture * _itemFixture) override;
};
