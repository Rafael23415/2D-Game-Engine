#pragma once

#include "Scene.h"

#include <memory>

using namespace Engineering2D;

class TestActor : public Actor
{

public:

	TestActor(Math::Vector2D position, std::weak_ptr<Texture> texture);

	// Inherited via Actor
	void Update(double deltaTime) override;
	void Destroy() override;
};
