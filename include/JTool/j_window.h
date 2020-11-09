#ifndef J_WINDOW_H
#define J_WINDOW_H

#include <glad/glad.h> 
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include<functional>
#include<vector>
#include"JTool/j_opqueue.h"
#include "JTool/j_op.h"
class JWindow {
private:
	JWindow();

private:
	GLFWwindow* window;
	JOpQueue prepare,jobs,after;
	int width, height;

public:
	static JWindow& getInstance();
	GLFWwindow* getWindow();
	void addJob(JOp&);
	void addPrepare(JOp&);
	void addAfter(JOp&);
	void run();
	void init();
	void cleanUp();
	void setWindowSize(int width, int height);
	int getWidth();
	int getHeight();

};


static void glfw_error_callback(int error, const char* description);

#endif // !1
