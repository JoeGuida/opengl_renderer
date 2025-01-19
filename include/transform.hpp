#ifndef OPENGL_RENDERER_TRANSFORM_HPP
#define OPENGL_RENDERER_TRANSFORM_HPP

#include <glm/vec3.hpp>

struct Transform {
    glm::vec3 position;
    glm::vec3 euler_angles;
    glm::vec3 scale;

    Transform(const glm::vec3& position,
        const glm::vec3& euler_angles,
        const glm::vec3& scale) :
        position(position),
        euler_angles(euler_angles),
        scale(scale) {
    }
    Transform(const glm::vec3& position, const glm::vec3& euler_angles) :
        position(position),
        euler_angles(euler_angles),
        scale(glm::vec3(1.0f)) {
    }
    Transform(const glm::vec3& position) :
        position(position),
        euler_angles(glm::vec3(0.0f)),
        scale(glm::vec3(1.0f)) {
    }
    Transform() :
        position(glm::vec3(0.0f)),
        euler_angles(glm::vec3(0.0f)),
        scale(glm::vec3(1.0f)) {
    }
    Transform(const Transform&) = default;
    Transform(Transform&&) = default;
    virtual ~Transform() = default;
};

#endif