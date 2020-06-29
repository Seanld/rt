#include <stack>
#include "vectors.h"
#include <string>
#include <iostream>



template <typename T>
T ceiling(T value, T max) {
    if (value > max) {
        return max;
    } else {
        return value;
    }
}

template <typename T>
T flooring(T value, T min) {
    if (value < min) {
        return min;
    } else {
        return value;
    }
}

template <typename T>
T betweenify(T value, T min, T max) {
    if (value > max) {
        return max;
    } else if (value < min) {
        return min;
    } else {
        return value;
    }
}



// Color declaration.

class Color {
    public:
        int r;
        int g;
        int b;

        int* rgb;

        Color();
        Color(int, int, int);
        Color(int*);

        void set(int, int, int);
        void set(int*);

        Color operator+(const Color&);
        Color operator-(const Color&);
};

// Color definition.

Color::Color() {
    this->rgb = new int[3];

    this->r, this->g, this->b = 0;

    this->set(0, 0, 0);
}

Color::Color(int r, int g, int b) {
    this->rgb = new int[3];

    this->set(r, g, b);
}

Color::Color(int* rgb) {
    this->rgb = new int[3];

    this->set(rgb);
}

void Color::set(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;

    this->rgb[0] = r;
    this->rgb[1] = g;
    this->rgb[2] = b;
}

void Color::set(int* rgb) {
    this->r = rgb[0];
    this->g = rgb[1];
    this->b = rgb[2];

    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
}

Color Color::operator+(const Color& otherColor) {
    Color newColor = Color();

    newColor.r = betweenify<int>(this->r + otherColor.r, 0, 255);
    newColor.g = betweenify<int>(this->g + otherColor.g, 0, 255);
    newColor.r = betweenify<int>(this->r + otherColor.r, 0, 255);

    return newColor;
}

Color Color::operator-(const Color& otherColor) {
    Color newColor = Color();

    newColor.r = betweenify<int>(this->r + otherColor.r, 0, 255);
    newColor.g = betweenify<int>(this->g + otherColor.g, 0, 255);
    newColor.r = betweenify<int>(this->r + otherColor.r, 0, 255);

    return newColor;
}



// Ray declaration.

class Ray {
    public:
        Vector3 origin;
        Vector3 direction;

        Ray();
        Ray(Vector3, Vector3);

        Vector3 findT(float);
};

// Ray definition.

Ray::Ray() {
    this->origin = Vector3();
    this->direction = Vector3();
}

Ray::Ray(Vector3 _origin, Vector3 _direction) {
    this->origin = _origin;
    this->direction = _direction;
}

Vector3 Ray::findT(float t) {
    float Px = this->origin.x + (this->direction.x * t);
    float Py = this->origin.y + (this->direction.y * t);
    float Pz = this->origin.z + (this->direction.z * t);

    return Vector3(Px, Py, Pz);
}



// Object declaration.

class Object {
    public:
        Vector3 position;
        Color* color;

        std::string child_type;

        Object();
        // Positional constructor.
        Object(Vector3);

        void moveBy(Vector3);
        float* intersect(Ray);
};

// Object definition.

Object::Object() {
    this->position = Vector3(0.0f, 0.0f, 0.0f);

    this->child_type = "Object";
}

Object::Object(Vector3 _position) {
    this->position = _position;

    this->child_type = "Object";
}

void Object::moveBy(Vector3 direction) {
    this->position = this->position + direction;
}

float* Object::intersect(Ray ray) {
    // Slope of origin to direction.
    // float OyDy = ray.origin

    float* result = new float[3] {0.0f, 0.0f, -1.0f};
}



// Sphere declaration.

class Sphere : public Object {
    public:
        float radius;
        Color* color;

        Sphere();
        Sphere(Vector3, float, Color*);

        float* intersect(Ray);
};

// Sphere definition.

Sphere::Sphere() {
    this->radius = 0.0f;
    this->color = new Color();

    this->child_type = "Sphere";
}

Sphere::Sphere(Vector3 _position, float _radius, Color* _color) : Object(_position) {
    this->radius = _radius;
    this->color = _color;

    this->child_type = "Sphere";
}

float* Sphere::intersect(Ray ray) {
    Vector3 dist = this->position - ray.origin;

    float a = ray.direction.dotProduct(ray.direction);
    float b = 2 * ray.direction.dotProduct(dist);
    float c = dist.dotProduct(dist) - std::pow<float>(this->radius, 2.0f);

    float discrim = b * b - 4 * a * c;

    float* result;

    if (discrim < 0) {
        result = new float[3] {0.0f, 0.0f, -1.0f};
        
        return result;
    }

    if (discrim == 0) {
        result = new float[3] {0.0f, 0.0f, 0.0f};
        
        return result;
    }

    float t1 = (b + sqrt(discrim)) / (2 * a);
    float t2 = (b - sqrt(discrim)) / (2 * a);

    result = new float[3] {t1, t2, 1.0f};

    return result;
}



// PointLight declaration.

class PointLight : public Sphere {
    public:
        float intensity;

        PointLight();
        PointLight(Vector3, float, Color*, float);
};

// PointLight definition.

PointLight::PointLight() {
    this->intensity = 0.0f;
}

PointLight::PointLight(Vector3 _position, float _radius, Color* _color, float _intensity) : Sphere(_position, _radius, _color) {
    this->intensity = _intensity;
}