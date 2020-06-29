#include <math.h>

// Vector2 declaration.

class Vector2 {
    public:
        float x;
        float y;

        Vector2();
        Vector2(float, float);

        void setAll(float, float);

        float distanceTo(const Vector2&);
        float dotProduct(const Vector2&);

        Vector2 operator+(const Vector2&);
        Vector2 operator-(const Vector2&);
};

// Vector2 definition:

Vector2::Vector2() {
    this->setAll(0.0f, 0.0f);
}

Vector2::Vector2(float x, float y) {
    this->setAll(x, y);
}

void Vector2::setAll(float x, float y) {
    this->x = x;
    this->y = y;
}

float Vector2::distanceTo(const Vector2& otherVector) {
    return std::sqrt(std::pow<float>((otherVector.x - this->x), 2.0f) + std::pow<float>((otherVector.y - this->y), 2.0f));
}

float Vector2::dotProduct(const Vector2& otherVector) {
    float product = 0;

    product += ((this->x * otherVector.x) + (this->y * otherVector.y));

    return product;
}

Vector2 Vector2::operator+(const Vector2& otherVector) {
    float _x = this->x + otherVector.x;
    float _y = this->y + otherVector.y;

    Vector2 newVector = Vector2(_x, _y);

    return newVector;
}

Vector2 Vector2::operator-(const Vector2& otherVector) {
    float _x = this->x - otherVector.x;
    float _y = this->y - otherVector.y;

    Vector2 newVector = Vector2(_x, _y);

    return newVector;
}



// Vector3 declaration

class Vector3 {
    public:
        float x;
        float y;
        float z;
        
        Vector3();
        Vector3(float, float, float);

        void setAll(float, float, float);

        float distanceTo(const Vector3&);
        float dotProduct(const Vector3&);

        Vector3 operator+(const Vector3&);
        Vector3 operator-(const Vector3&);
};

// Vector3 definition.

Vector3::Vector3() {
    this->setAll(0.0f, 0.0f, 0.0f);
}

Vector3::Vector3(float x, float y, float z) {
    this->setAll(x, y, z);
}

void Vector3::setAll(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector3::distanceTo(const Vector3& otherVector) {
    return std::sqrt(std::pow<float>((otherVector.x - this->x), 2.0f) + std::pow<float>((otherVector.y - this->y), 2.0f) + std::pow<float>((otherVector.z - this->z), 2.0f));
}

float Vector3::dotProduct(const Vector3& otherVector) {
    float product = 0;

    product += ((this->x * otherVector.x) + (this->y * otherVector.y) + (this->y * otherVector.y));

    return product;
}

Vector3 Vector3::operator+(const Vector3& otherVector) {
    float _x = this->x + otherVector.x;
    float _y = this->y + otherVector.y;
    float _z = this->z + otherVector.z;

    Vector3 newVector = Vector3(_x, _y, _z);

    return newVector;
}

Vector3 Vector3::operator-(const Vector3& otherVector) {
    float _x = this->x - otherVector.x;
    float _y = this->y - otherVector.y;
    float _z = this->z - otherVector.z;

    Vector3 newVector = Vector3(_x, _y, _z);

    return newVector;
}