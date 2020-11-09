// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include<vector>
#include<functional>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include "JTool/j_window.h"
#include "JTool/j_opqueue.h"
#include "JTool/j_op.h"
#include "JTool/j_texture.h"
#include <glm/glm.hpp>
#include "JTool/shader.h"
#include "JTool/j_polygen.h"
#include "JTool/j_frambuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "JTool/j_camera.h"
#include "JTool/model.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;






int main(int, char**)
{
    spdlog::info("start!");
    // Setup window
    JWindow jwindow = JWindow::getInstance();
    jwindow.init();
    GLFWwindow* window = jwindow.getWindow();
    JCamera jcamera;
    

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
       glm::vec3(0.7f,  0.2f,  2.0f),
       glm::vec3(2.3f, -3.3f, -4.0f),
       glm::vec3(-4.0f,  2.0f, -12.0f),
       glm::vec3(0.0f,  0.0f, -3.0f)
    };

    Shader shader("../shaders/test.vert", "../shaders/test.frag");
    Shader screenShader("../shaders/screen.vert", "../shaders/screen.frag");
    Shader lightShader("../shaders/notex.vert", "../shaders/notex.frag");
    Shader objectShader("../shaders/muiltylight.vert", "../shaders/muiltylight.frag");
    Shader modelShader("../shaders/model.vert", "../shaders/model.frag");


    JTexture texture1("../textures/awesomeface.png");
    JTexture texture2("../textures/container2.png");
    JTexture texture3("../textures/container2_specular.png");
    //shader.use();
    //

    Model ourModel("../res/obj/test.fbx");


    JPolygen triagle(vertices,sizeof(vertices),36);
    triagle.setAttrib(0, 3, 8, 0);
    triagle.setAttrib(1, 3, 8, 3);

    JPolygen light(vertices, sizeof(vertices), 36);
    light.setAttrib(0, 3, 8, 0);
    glm::vec3 lightPos(1.1, 2, 2);

    JPolygen object(vertices, sizeof(vertices), 36);
    object.setAttrib(0, 3, 8, 0);
    object.setAttrib(1, 3, 8, 3);
    object.setAttrib(2, 2, 8, 6);


    JFrambuffer jframbuffer(SCR_WIDTH,SCR_HEIGHT);


    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    float trans_vec[] = { 0,0,0 };
    float rotate[] = {0,0,0};
    float scale[] = { 1,1,1 };
    float pan[] = { 0,0 };
    char title[50];
    glEnable(GL_DEPTH_TEST);
    JOp show(
        [&](){
            sprintf(title, "%.2f", ImGui::GetIO().Framerate);
            glfwSetWindowTitle(window, title);
            ImGui::Begin("console");
            {
                ImGui::SliderFloat3("position", trans_vec, -2, 2);
                ImGui::SliderFloat3("rotate", rotate,-360.0f,360.0f);
                
                ImGui::SliderFloat3("scale",scale, 0, 10);
            }
            ImGui::End();

            
            jframbuffer.bind();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.use();



            glm::mat4 model(1.0f);


            glm::mat4 projection(1.0f);
            projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);


            objectShader.use();
            objectShader.setVec3("viewPos", jcamera.getPos());
            objectShader.setFloat("material.shininess", 32.0f);

            /*
               Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
               the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
               by defining light types as classes and set their values in there, or by using a more efficient uniform approach
               by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
            */
            // directional light
            objectShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
            objectShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
            objectShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            objectShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
            // point light 1
            objectShader.setVec3("pointLights[0].position", pointLightPositions[0]);
            objectShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
            objectShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
            objectShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
            objectShader.setFloat("pointLights[0].constant", 1.0f);
            objectShader.setFloat("pointLights[0].linear", 0.09);
            objectShader.setFloat("pointLights[0].quadratic", 0.032);
            // point light 2
            objectShader.setVec3("pointLights[1].position", pointLightPositions[1]);
            objectShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
            objectShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
            objectShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
            objectShader.setFloat("pointLights[1].constant", 1.0f);
            objectShader.setFloat("pointLights[1].linear", 0.09);
            objectShader.setFloat("pointLights[1].quadratic", 0.032);
            // point light 3
            objectShader.setVec3("pointLights[2].position", pointLightPositions[2]);
            objectShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
            objectShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
            objectShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
            objectShader.setFloat("pointLights[2].constant", 1.0f);
            objectShader.setFloat("pointLights[2].linear", 0.09);
            objectShader.setFloat("pointLights[2].quadratic", 0.032);
            // point light 4
            objectShader.setVec3("pointLights[3].position", pointLightPositions[3]);
            objectShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
            objectShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
            objectShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
            objectShader.setFloat("pointLights[3].constant", 1.0f);
            objectShader.setFloat("pointLights[3].linear", 0.09);
            objectShader.setFloat("pointLights[3].quadratic", 0.032);
            // spotLight
            objectShader.setVec3("spotLight.position", jcamera.getPos());
            objectShader.setVec3("spotLight.direction",jcamera.getFront());
            objectShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            objectShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            objectShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            objectShader.setFloat("spotLight.constant", 1.0f);
            objectShader.setFloat("spotLight.linear", 0.09);
            objectShader.setFloat("spotLight.quadratic", 0.032);
            objectShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            objectShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


            glm::mat4 model2 = glm::translate(model, lightPos);
            model2 = glm::scale(model2, glm::vec3(0.2));
            lightShader.use();
            lightShader.setMat4("model", model2);
            lightShader.setMat4("view", jcamera.getMatrix());
            lightShader.setMat4("projection", projection);

            
            light.draw(lightShader);

            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture2.getID());
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture3.getID());
            objectShader.use();
            objectShader.setInt("material.diffuse", 0);
            objectShader.setInt("material.specular", 1);
            objectShader.setMat4("view", jcamera.getMatrix());
            objectShader.setMat4("projection", projection);
            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model3(1.0);
                model3 = glm::translate(model3, cubePositions[i]);
                float angle = 20.0f * i;
                model3 = glm::rotate(model3, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                objectShader.setMat4("model", model3);
                object.draw(objectShader);
                /*glDrawArrays(GL_TRIANGLES, 0, 36);*/
            }

            /*object.draw(objectShader);*/

            /*triagle.draw(shader);*/

            modelShader.use();

            modelShader.setVec3("viewPos", jcamera.getPos());
            modelShader.setFloat("material.shininess", 32.0f);

            modelShader.setMat4("view", jcamera.getMatrix());
            modelShader.setMat4("projection", projection);


            modelShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
            modelShader.setVec3("dirLight.ambient", 0.5f, 0.5f, 0.5f);
            modelShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            modelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

            modelShader.setVec3("pointLights[0].position", pointLightPositions[0]);
            modelShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
            modelShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
            modelShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
            modelShader.setFloat("pointLights[0].constant", 1.0f);
            modelShader.setFloat("pointLights[0].linear", 0.09);
            modelShader.setFloat("pointLights[0].quadratic", 0.032);

            modelShader.setVec3("pointLights[1].position", pointLightPositions[1]);
            modelShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
            modelShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
            modelShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
            modelShader.setFloat("pointLights[1].constant", 1.0f);
            modelShader.setFloat("pointLights[1].linear", 0.09);
            modelShader.setFloat("pointLights[1].quadratic", 0.032);

            modelShader.setVec3("pointLights[2].position", pointLightPositions[2]);
            modelShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
            modelShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
            modelShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
            modelShader.setFloat("pointLights[2].constant", 1.0f);
            modelShader.setFloat("pointLights[2].linear", 0.09);
            modelShader.setFloat("pointLights[2].quadratic", 0.032);

            modelShader.setVec3("pointLights[3].position", pointLightPositions[3]);
            modelShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
            modelShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
            modelShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
            modelShader.setFloat("pointLights[3].constant", 1.0f);
            modelShader.setFloat("pointLights[3].linear", 0.09);
            modelShader.setFloat("pointLights[3].quadratic", 0.032);

            modelShader.setVec3("spotLight.position", jcamera.getPos());
            modelShader.setVec3("spotLight.direction", jcamera.getFront());
            modelShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            modelShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            modelShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            modelShader.setFloat("spotLight.constant", 1.0f);
            modelShader.setFloat("spotLight.linear", 0.09);
            modelShader.setFloat("spotLight.quadratic", 0.032);
            modelShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            modelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
            modelShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
            // view/projection transformations



            // render the loaded model
            glm::mat4 model5=glm::mat4(1.0f);
            model5 = glm::translate(model5, glm::vec3(0.5f, -5.0f, -0.5f)); // translate it down so it's at the center of the scene
            model5 = glm::scale(model5, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model5);
            ourModel.Draw(modelShader);

            
            // render the triangle
            jframbuffer.unbind();
            //glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
            // clear all relevant buffers
            //glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
            //glClear(GL_COLOR_BUFFER_BIT);

            ImGui::Begin("GameWindow");
            {
                // Using a Child allow to fill all the space of the window.
                // It also alows customization
                // Get the size of the child (i.e. the whole draw size of the windows).

                ImGui::BeginChild("gamerender");
                ImVec2 wsize = ImGui::GetWindowSize();
                // Because I use the texture from OpenGL, I need to invert the V from the UV.
                ImGui::Image((ImTextureID)jframbuffer.getTexturebuffer(), wsize, ImVec2(0, 1), ImVec2(1, 0));
                ImVec2 now = ImGui::GetMousePos();
                ImVec2 window_size = ImGui::GetWindowSize();
                if (ImGui::IsWindowHovered())
                    jcamera.processInput(now.x,now.y,window_size.x,window_size.y);

                ImGui::EndChild();

            }
            ImGui::End();
        }
    );
    


    jwindow.addJob(show);
    // Main loop
    jwindow.run();

    // Cleanup
    jwindow.cleanUp();

    return 0;
}
