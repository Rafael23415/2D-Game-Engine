#pragma once

#include "Actor.h"

#include <memory>
#include <string>

using namespace Engineering2D;

class TestActor : public Actor
{

public:
	TestActor(std::string name, Math::Vector2D position);

	// Inherited via Actor
	void Update(double deltaTime) override;
	void Destroy() override;
};
