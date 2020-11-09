#ifndef J_CAMERA_H
#define J_CAMERA_H

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class JCamera
{
public:
	JCamera();
	glm::mat4 getMatrix();
	void pan(float x,float y,float z);
	void rotate(float x, float y, float z);
	void processInput(float x, float y,float window_width,float window_height);
	void update();
	glm::vec3 getPos();
	glm::vec3 getFront();


private:
	glm::vec3 position,up,front,right,wordup;
	glm::mat4 view;

	glm::vec2 prepos,nowpos;

	float yaw, pitch, speed, sensitivity;



};


#endif