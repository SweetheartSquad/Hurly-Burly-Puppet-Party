#pragma once

#include <PuppetContactListener.h>

class b2Contact;
class b2Fixture;
class PuppetScene;

//main collision call back function
class RapunzelContactListener : public PuppetContactListener{
public:
	RapunzelContactListener(PuppetScene * _scene);
};