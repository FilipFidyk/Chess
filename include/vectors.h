#ifndef VECTORS_H
#define VECTORS_H

typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    float x;
    float y;
    float z;
} vec3;

vec2 vec2_add(vec2, vec2);
vec2 vec2_sub(vec2, vec2);
vec2 vec2_mul(vec2, float);
float vec2_dot(vec2, vec2);
float vec2_length(vec2);
vec2 vec2_normalise(vec2);

vec3 vec3_add(vec3, vec3);
vec3 vec3_sub(vec3, vec3);
vec3 vec3_mul(vec3, float);
float vec3_dot(vec3, vec3);
vec3 vec3_cross(vec3, vec3);
float vec3_length(vec3);
vec3 vec3_normalise(vec3);

#endif //VECTORS_H