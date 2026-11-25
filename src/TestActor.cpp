#include "TestActor.h"

using namespace Math;

TestActor::TestActor(Vector2D position, std::weak_ptr<Texture> texture) : Actor(position, Vector2D::zero(), texture)
{
}

void TestActor::Update(double deltaTime)
{
	
}

void TestActor::Destroy()
{
	Actor::Destroy();
}
