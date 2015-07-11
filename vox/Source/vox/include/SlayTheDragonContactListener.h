#pragma once

#include <PuppetContactListener.h>

class b2Contact;
class b2Fixture;
class PuppetScene;

//main collision call back function
class SlayTheDragonContactListener : public PuppetContactListener{
public:
	SlayTheDragonContactListener(PuppetScene * _scene);

	void playerItemContact(b2Contact * contact, b2Fixture * playerFixture, b2Fixture * itemFixture) override;
	void structureItemContact(b2Contact * _contact, b2Fixture * _structureFixture, b2Fixture * _itemFixture) override;
};
