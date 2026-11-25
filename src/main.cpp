#include "Debug.h"
#include "Scene.h"
#include "Vector2D.h"
#include "TestActor.h"

using namespace Engineering2D;
using namespace Math;

int main(int argc, char* argv[])
{
    try
    {
        Scene scene{ "SDL Test", {960, 720}, {1000, 1000} };
        
        auto a = scene.CreateTexture({ "graphics/LonerA.bmp" });
        auto b = scene.CreateTexture({ "graphics/LonerA.bmp" });
        auto c = scene.CreateTexture({ "graphics/LonerC.bmp" });

        scene.CreateActor<TestActor>(Vector2D{ 0, 0 }, c);

        //Debug::Log("AAS" + "DAdad");

        scene.Start();
    }
    catch(const std::exception& e)
    {
        Debug::LogError(e.what());
        return 1;
    }

    return 0;
}
