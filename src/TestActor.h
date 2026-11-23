#include "Scene.h"

using namespace Engineering2D;

class TestActor : Actor
{

public:

	TestActor(Vector2D position, std::weak_ptr<Texture> texture);

	// Inherited via Actor
	void Update(double deltaTime) override;
	void Destroy() override;
};
