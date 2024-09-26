#include "vectors.h"
#include <math.h>

// vec2 Addition
vec2 vec2_add(vec2 v1, vec2 v2) {
    vec2 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    return result;
}

// vec2 Subtraction
vec2 vec2_sub(vec2 v1, vec2 v2) {
    vec2 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}

// Scalar Multiplication
vec2 vec2_mul(vec2 v, float scalar) {
    vec2 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    return result;
}

// Dot Product
float vec2_dot(vec2 v1, vec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

// Length (Magnitude) of the vector
float vec2_length(vec2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

// Normalization (Unit Vector)
vec2 vec2_normalise(vec2 v) {
    float len = vec2_length(v);
    vec2 result;
    if (len != 0) {
        result.x = v.x / len;
        result.y = v.y / len;
    } else {
        result.x = result.y = 0;
    }
    return result;
}

// vec3 Addition
vec3 vec3_add(vec3 v1, vec3 v2) {
    vec3 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

// vec3 Subtraction
vec3 vec3_sub(vec3 v1, vec3 v2) {
    vec3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

// Scalar Multiplication
vec3 vec3_mul(vec3 v, float scalar) {
    vec3 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result;
}

// Dot Product
float vec3_dot(vec3 v1, vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Cross Product
vec3 vec3_cross(vec3 v1, vec3 v2) {
    vec3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

// Length (Magnitude) of the vector
float vec3_length(vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Normalization (Unit Vector)
vec3 vec3_normalise(vec3 v) {
    float len = vec3_length(v);
    vec3 result;
    if (len != 0) {
        result.x = v.x / len;
        result.y = v.y / len;
        result.z = v.z / len;
    } else {
        result.x = result.y = result.z = 0;
    }
    return result;
}

// Example usage:
// vec3 v1 = {1.0f, 2.0f, 3.0f};
// vec3 v2 = {4.0f, 5.0f, 6.0f};
// vec3 cross = vec3_cross(v1, v2);
// float dot = vec3_dot(v1, v2);
