#include "Scene.h"

using namespace Engineering2D;

class TestActor : Actor
{

public:

	TestActor(Vector2D position, SpriteSheet* spriteSheet);

	// Inherited via Actor
	void Update(double deltaTime) override;
	void Destroy() override;
};
