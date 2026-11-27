#include "Debug.h"
#include "Scene.h"
#include "Vector2D.h"
#include "TestActor.h"

#include <exception>

using namespace Engineering2D;
using namespace Math;

int main(int argc, char* argv[])
{
    try
    {
        Scene scene{ "Test Game", {960, 720}, {1000, 1000} };
        
        auto& player = scene.CreateActor<TestActor>("Player", Vector2D{-0.5, 0.5});
        auto& enemy1 = scene.CreateActor<TestActor>("Loner1", Vector2D{0.5, 0.5});
        auto& enemy2 = scene.CreateActor<TestActor>("Rusher", Vector2D{-0.5, -0.5});
        auto& enemy3 = scene.CreateActor<TestActor>("Loner2", Vector2D{0.5, -0.5});
        
        player.SetTexture(scene.CreateTexture({ "assets/Ship1.bmp" }));
        enemy1.SetTexture(scene.CreateTexture({ "assets/LonerA.bmp" }));
        enemy2.SetTexture(scene.CreateTexture({ "assets/LonerB.bmp" }));
        enemy3.SetTexture(scene.CreateTexture({ "assets/LonerA.bmp" }));
        
        scene.Start();
    }
    catch(const std::exception& e)
    {
        Debug::LogError(e.what());
        return 1;
    }

    return 0;
}
