#include "camera.hpp"
#include <iostream>

void Camera::rotate(const glm::vec2& delta) {
	transform.euler_angles.y += delta.x;
	transform.euler_angles.x += delta.y;
	front = glm::rotate(front, delta.x, up);
	front = glm::rotate(front, delta.y, right);
	right = glm::rotate(right, delta.x, up);
}