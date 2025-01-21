#include "camera.hpp"
#include <iostream>

void Camera::rotate(const glm::vec2& delta) {
	transform.euler_angles.y += delta.x;
	transform.euler_angles.x += delta.y * 2.0f;
	front = glm::rotate(front, delta.x, up);
	front = glm::rotate(front, delta.y * 2.0f, right);
	right = glm::rotate(right, delta.x, up);
}