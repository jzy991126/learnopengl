#include "JTool/j_camera.h"
#include <glm/gtc/quaternion.hpp>
#include "imgui.h"
#include<spdlog/spdlog.h>

JCamera::JCamera()
{

	position = glm::vec3(0, 0, 1);
	front = glm::normalize(glm::vec3(0, 0, -1));
	up = glm::vec3(0, 1, 0);
	wordup = up;


	prepos = glm::vec2(0, 0);
	nowpos = glm::vec2(0, 0);

	view = glm::lookAt(position, position + front, up);


	yaw = -90; 
	pitch = 0;
	speed = 0;
	sensitivity = 0.1;

}

glm::mat4 JCamera::getMatrix()
{
	return glm::lookAt(position, position + front, up);
}



void JCamera::pan(float x, float y, float z)
{
	/*glm::vec3 right = glm::normalize(glm::cross(front, up));

	position = position + x * right + y * glm::vec3(0, 1, 0) +z*(-front) ;*/



	glm::vec4 move(x, y, z, 0);
	glm::mat4 inverse = glm::inverse(view);
	glm::vec4 res = inverse* move;

	position = position+glm::vec3(res);

}

void JCamera::rotate(float x, float y, float z)
{
	yaw += x;
	pitch += y;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

}
glm::vec3 JCamera::getPos()
{
	return position;
}

glm::vec3 JCamera::getFront()
{
	return front;
}

void JCamera::update()
{
	glm::vec3 Front;
	Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	Front.y = sin(glm::radians(pitch));
	Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(Front);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, wordup));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));

	view = glm::lookAt(position, position + front, up);
}

void JCamera::processInput(float x, float y, float window_width, float window_height)
{
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Middle) || ImGui::IsMouseClicked(ImGuiMouseButton_Left) || ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		prepos = glm::vec2(x, y);


	//glm::vec3 move(-front * ImGui::GetIO().MouseWheel);
	//view = glm::translate(view, move);
	float speed = ImGui::GetIO().MouseWheel * 0.1;
	pan(0,0,-speed);


	if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
	{
		nowpos = glm::vec2(x, y);
		glm::vec2 move = nowpos - prepos;
		glm::vec2 window(1.0f / window_width, 1.0f / window_height);
		prepos = nowpos;
		move *= 0.01;
		pan(move.x, -move.y, 0);
	}
	if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
	{

		nowpos = glm::vec2(x, y);
		glm::vec2 move = nowpos - prepos;
		glm::vec2 window(1.0f / window_width, 1.0f / window_height);
		prepos = nowpos;

		move *= 0.1;
		rotate(move.x, -move.y, 0);
	}

	update();
}
