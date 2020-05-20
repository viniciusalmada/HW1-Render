#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "constants.h"
#include "model.h"
#include "object.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void clearColor(const float color[4]);

float eyeX;
float eyeY;
float eyeZ;
bool eyeInitialized = false;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    int windW = 800;
    int windH = 600;
    GLFWwindow* window = glfwCreateWindow(windW, windH, Const::WINDOW_TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, windW, windH);

    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, [](GLFWwindow*, int key, int code, int ac, int mods) -> void {
//        if (ac != GLFW_PRESS) return;
        float step = 0.25f;
        switch (key) {
            case GLFW_KEY_W:
                eyeZ -= step;
                break;
            case GLFW_KEY_S:
                eyeZ += step;
                break;
            case GLFW_KEY_A:
                eyeX -= step;
                break;
            case GLFW_KEY_D:
                eyeX += step;
                break;
            case GLFW_KEY_Q:
                eyeY -= step;
                break;
            case GLFW_KEY_E:
                eyeY += step;
                break;
            default:
                break;
        }
    });

    Object stonesObj(Const::STONES_MODEL, Const::FRAGMENT_STONES_PATH, &Const::AMBIENT_COMP_STONES, nullptr);
    Object golfObj(Const::GOLF_MODEL, Const::FRAGMENT_GOLF_PATH, &Const::AMBIENT_COMP_GOLF, &Const::DIFFUSE_COMP_GOLF);

    Object currentObj = golfObj;

    Shader shader(Const::VERTEX_PATH, currentObj.fragmentPath);
    Model model(currentObj.modelPath);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        clearColor(Color::WHITE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 modelMat = glm::mat4(1.0f);
        float maxZ;
        auto center = model.center(&maxZ);
        if (!eyeInitialized) {
            eyeX = (center + glm::vec3(0.0f, 0.0f, maxZ * 4.0f)).x;
            eyeY = (center + glm::vec3(0.0f, 0.0f, maxZ * 4.0f)).y;
            eyeZ = (center + glm::vec3(0.0f, 0.0f, maxZ * 4.0f)).z;
            eyeInitialized = true;
        }
        auto eye = glm::vec3(eyeX, eyeY, eyeZ);
        glm::mat4 viewMat = glm::lookAt(
                eye,
                center,
                glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float) windW / (float) windH, 0.1f, 100.0f);

        GLint projLoc = glGetUniformLocation(shader.mProgram, Const::UNI_PROJ_MATRIX);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
        GLint viewLoc = glGetUniformLocation(shader.mProgram, Const::UNI_VIEW_MATRIX);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
        GLint modelLoc = glGetUniformLocation(shader.mProgram, Const::UNI_MODEL_MATRIX);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

        // Light Position
        GLint lightPosLoc = glGetUniformLocation(shader.mProgram, Const::UNI_LIGHT_POSITION);
        glm::vec3 lightPos = center + glm::vec3(0.0f, 0.0f, maxZ * 4.0f);
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

        // Lights
        currentObj.setLights(shader);

        GLint lightColorLoc = glGetUniformLocation(shader.mProgram, Const::UNI_LIGHT_COLOR);
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

        model.draw(shader);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void clearColor(const float color[4]) {
    glClearColor(color[0], color[1], color[2], color[3]);
}
