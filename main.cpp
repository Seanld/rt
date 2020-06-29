#include "lib/core.h"
#include <fstream>

int main() {
    Color* backgroundColor = new Color(0, 0, 0);
    Space* space =  new Space(10);
    Camera cam = Camera(Vector3(0.0f, 0.0f, 0.0f), space, 400.0f, Vector2(100, 50), Vector2(100, 50), backgroundColor);
    
    Sphere* s1 = new Sphere(Vector3(0.0f, 600.0f, 0.0f), 200.0f, new Color(255, 0, 0));
    space->addObject(s1);

    // Ray testRay = Ray(cam.position, Vector3(-100.5, 400, 0.5));
    // float* testIntersectionResult = s1->intersect(testRay);
    // std::cout << testIntersectionResult[2] << std::endl;

    Color*** renderedBuffer = cam.render();

    // Write color data to file, 3 bytes per pixel (8 bits = 255 combos i.e. colors, 8 bits = a byte).

    // std::ofstream imageBinFile("image", std::ios::out | std::ios::binary);

    for (int a=0; a<cam.screenRes.y; a++) {
        for (int b=0; b<cam.screenRes.x; b++) {
            Color* c = renderedBuffer[a][b];

            // std::cout << c->r << ", " << c->g << ", " << c->b << std::endl;
        }
    }

    // imageBinFile.close();

    return 0;
}