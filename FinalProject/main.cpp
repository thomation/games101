#include "Renderer.hpp"
#include "Scene.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"
#include "global.hpp"
#include <chrono>

// In the main function of the program, we create the scene (create objects and
// lights) as well as set the options for the render (image width and height,
// maximum recursion depth, field-of-view, etc.). We then call the render
// function().
int main(int argc, char** argv)
{
    Scene scene(1024, 1024);

    std::cout << "Loading model";
    //MeshTriangle model("../models/bunny/bunny.obj");
    MeshTriangle model("../models/bunny/bunny_high.obj");
    //MeshTriangle model("../models/dragon/dragon.obj");
    scene.Add(&model);
    //scene.Add(std::make_unique<Light>(Vector3f(-20, 90, 50), Vector3f(1.0, 0.89, 0.52)));
    //scene.Add(std::make_unique<Light>(Vector3f(20, 90, 50), Vector3f(1.0, 0.89, 0.52)));
    //scene.Add(std::make_unique<Light>(Vector3f(-20, 90, 50), Vector3f(0.5, 0.8, 0.5)));
    scene.Add(std::make_unique<Light>(Vector3f(0, 90, 50), Vector3f(0.5, 0.5, 0.5)));
    scene.Add(std::make_unique<Light>(Vector3f(-20, 90, 50), Vector3f(1.0)));
    std::cout << "Building BVH" << std::endl;
    scene.buildBVH();

    Renderer r;

    auto start = std::chrono::system_clock::now();
    r.Render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";

    return 0;
}