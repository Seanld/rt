#include <math.h>
#include <typeinfo>
#include "objects.h"
#include <vector>



// ImagePlane declaration.

class ImagePlane : Object {
    public:
        Vector3 position;
        Vector2 size;
        Vector2 resolution;
        Vector2 pixelSize;

        ImagePlane();
        ImagePlane(Vector3, Vector2);
        ImagePlane(Vector3, Vector2, Vector2);

        Vector3** getPixelPositions();
};

// ImagePlane definition.

ImagePlane::ImagePlane() {
    this->position = Vector3(0.0f, 0.0f, 0.0f);

    this->size = Vector2(100.0f, 100.0f);
    this->resolution = Vector2(100.0f, 100.0f);

    this->pixelSize = Vector2(this->size.x / this->resolution.x, this->size.y / this->resolution.y);
}

ImagePlane::ImagePlane(Vector3 _position, Vector2 _size) {
    this->position = _position;

    this->size = _size;
    this->resolution = _size;

    this->pixelSize = Vector2(this->size.x / this->resolution.x, this->size.y / this->resolution.y);
}

ImagePlane::ImagePlane(Vector3 _position, Vector2 _size, Vector2 _resolution) {
    this->position = _position;

    this->size = _size;
    this->resolution = _resolution;

    this->pixelSize = Vector2(this->size.x / this->resolution.x, this->size.y / this->resolution.y);
}

Vector3** ImagePlane::getPixelPositions() {
    float Y = (this->position.y - (this->size.x / 2)) + (this->pixelSize.x / 2);
    float Z = (this->position.z + (this->size.y / 2)) - (this->pixelSize.y / 2);
    Vector3 startingPoint = Vector3(this->position.x, Y, Z);

    Vector3** pixelPositions = new Vector3*[(int)this->resolution.y];

    for (int z=0; z<(int)this->resolution.y; z++) {
        Vector3* row = new Vector3[(int)this->resolution.x];

        for (int y=0; y<(int)this->resolution.x; y++) {
            Vector3 temp = Vector3(this->position.x, startingPoint.y + (y * this->pixelSize.x), startingPoint.z - (z * this->pixelSize.y));

            float clone = temp.y;
            temp.y = temp.x;
            temp.x = clone;

            temp.y = this->position.y;

            row[y] = temp;
        }

        pixelPositions[z] = row;
    }

    return pixelPositions;
}



// Space declaration.

class Space {
    public:
        int maxObjects;
        
        Object** objects;
        int totalObjects;
        PointLight** lights;
        int totalLights;

        Space();
        Space(int);

        void addObject(Object*);
        void addObject(PointLight*);

        Color* calculateColorWithLight(Object*, Vector3);
};

// Space definition.

Space::Space() {
    totalObjects = 0;
    totalLights = 0;

    this->maxObjects = 1000;

    this->objects = new Object*[this->maxObjects];
    this->lights = new PointLight*[this->maxObjects];
}

Space::Space(int _maxObjects) {
    totalObjects = 0;
    totalLights = 0;

    this->maxObjects = _maxObjects;

    this->objects = new Object*[this->maxObjects];
    this->lights = new PointLight*[this->maxObjects];
}

void Space::addObject(PointLight* newLightPtr) {
    this->lights[totalLights] = newLightPtr;

    this->totalLights++;
}

void Space::addObject(Object* newObjectPtr) {
    this->objects[totalObjects] = newObjectPtr;

    this->totalObjects = this->totalObjects + 1;
}

Color* Space::calculateColorWithLight(Object* objectToCalculatePtr, Vector3 origin) {
    // Implement later.
}



// Camera declaration.

class Camera : public Object {
    private:
        // Decided to use vectors instead of arrays since
        // dynamic sizes of arrays isn't allowed. It sucks,
        // but so does C++. Just kidding.
        Color*** buffer;

    public:
        Space* space;
        float screenDistance;
        Vector2 screenRes;
        ImagePlane* screen;
        Color* bg;

        Camera();
        Camera(Vector3, Space*, float, Vector2, Vector2, Color*);

        Color*** render();
};

// Camera definition.

Camera::Camera() {

}

Camera::Camera(Vector3 _position, Space* _space, float _screenDistance, Vector2 _screenSize, Vector2 _screenRes, Color* _bg) {
    this->position = _position;

    this->space = _space;
    this->screenDistance = _screenDistance;
    this->screenRes = _screenRes;
    this->bg = _bg;

    this->screen = new ImagePlane(Vector3(this->position.x, this->position.y + this->screenDistance, this->position.z), _screenSize, _screenRes);

    const int screenResX = this->screenRes.x;
    const int screenResY = this->screenRes.y;
    
    this->buffer = new Color**[screenResY];
}

Color*** Camera::render() {
    Vector3** pixelPositions = this->screen->getPixelPositions();

    int screenResX = this->screenRes.x;
    int screenResY = this->screenRes.y;

    Color*** newBuffer = new Color**[screenResY];

    int counter = 0;

    for (int c=0; c<screenResY; c++) {
        Color** pixRow = new Color*[screenResX];

        for (int r=0; r<screenResX; r++) {
            Vector3 pixPos = pixelPositions[c][r];

            // Create a ray originated at the camera position, and heading
            // towards the position of the current pixel to test, to see if
            // the pixel needs to be recorded.
            Ray ray = Ray(this->position, pixPos);

            int totalObjectsTemp = this->space->totalObjects;
            // std::cout << "TOTAL " << totalObjectsTemp << std::endl;

            // Check all objects in space for intersection.
            for (int o=0; o<totalObjectsTemp; o++) {
                Object* obj = this->space->objects[o];

                // std::cout << static_cast<Sphere*>(obj)->color << std::endl;

                // std::cout << "SCREEN POS: " << this->screen->position.x << ", " << this->screen->position.y << ", " << this->screen->position.z << std::endl;
                // std::cout << "CAMERA POS: " << this->position.x << ", " << this->position.y << ", " << this->position.z << std::endl;
                // std::cout << "SPHERE POS: " << obj->position.x << ", " << obj->position.y << ", " << obj->position.z << std::endl;
                // std::cout << "PIXELS POS: " << pixPos.x << ", " << pixPos.y << ", " << pixPos.z << std::endl;
                // std::cout << "---------" << std::endl;

                float* intersects;

                if (obj->child_type == "Sphere") {
                    intersects = static_cast<Sphere*>(obj)->intersect(ray);
                } else {
                    intersects = obj->intersect(ray);
                }

                std::cout << intersects[0] << ", " << intersects[1] << ", " << intersects[2] << std::endl;

                if (intersects[2] == 1.0f) {
                    // Intersection! Record color data of object.
                    if (obj->child_type == "Sphere") {
                        pixRow[r] = static_cast<Sphere*>(obj)->color;
                    } else {
                        pixRow[r] = obj->color;
                    }

                    std::cout << "INTERSECTION!" << std::endl;

                    break; // Don't continue looping through objects if we already found one.
                } else {
                    pixRow[r] = this->bg;

                    // std::cout << "MISS!" << std::endl;
                }
            }
        }

        newBuffer[c] = pixRow;
    }

    // Return the new buffer.
    // Because this returns the same buffer pointer that is
    // stored privately, any modifications made outside will
    // affect the private version too.
    // Need to fix this by copying array separately.
    return newBuffer;
}