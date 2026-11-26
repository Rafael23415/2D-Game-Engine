#include "TestActor.h"

using namespace Math;

TestActor::TestActor(std::string name, Vector2D position) : Actor(name, position, Vector2D::one())
{
}

void TestActor::Update(double deltaTime)
{
	
}

void TestActor::Destroy()
{
	Actor::Destroy();
}
