#include <iostream>

#include "Scene.h"
#include "TestActor.h"

using namespace Engineering2D;

int main(int argc, char* argv[])
{
    try
    {
        Scene scene{ "SDL Test", {640, 480}, {1000, 1000} };
        
        auto a = scene.CreateTexture({ "graphics/LonerA.bmp" });
        auto b = scene.CreateTexture({ "graphics/LonerA.bmp" });
        auto c = scene.CreateTexture({ "graphics/LonerC.bmp" });
        
        scene.CreateActor(new TestActor{ Vector2D{0, 0}, c });

        scene.Start();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
