
#include "JTool/j_window.h"
#include <cstdio>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

JWindow& JWindow::getInstance()
{
	static JWindow instance;
	return instance;
}

GLFWwindow* JWindow::getWindow()
{
	return window;

}

void JWindow::run()
{
	while (!glfwWindowShouldClose(window)) {
		prepare.run();
		jobs.run();
		after.run();
	}
}

void JWindow::addPrepare(JOp& op)
{
	prepare << op;
}

void JWindow::addJob(JOp& op)
{
	jobs << op;
}

JWindow::JWindow()
{
	window = nullptr;
	width = 800, height = 600;
}

void JWindow::setWindowSize(int width, int height)
{
	glfwSetWindowSize(window, width, height);
}
int JWindow::getHeight()
{
	return height;
}

int JWindow::getWidth()
{
	return width;
}

void JWindow::addAfter(JOp& op)
{
	after << op;
}
void JWindow::cleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}


void JWindow::init()
{
	if (window != nullptr)
		return;

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		throw "glfw init error";

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	

	window = glfwCreateWindow(width, height, "J window", NULL, NULL);

	if (!window)
		throw "create window error";

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	int  err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0;
	ImGui::CreateContext();

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	prepare<<JOp(
        []() {
            glfwPollEvents();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }
    );

	after<<JOp(
		[&]() {
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
		}
	);
}