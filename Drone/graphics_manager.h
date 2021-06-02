#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm/glm.hpp>

#include "shader.h"
#include "model.h"
#include "environment.h"

enum LeanSide {
    STRAIGHT = 0,
    RIGHT = 1,
    LEFT = 2
};

enum LeanFront {
    FORWARD = 1,
    BACKWARD = 2
};

class GraphicsManager
{
public:
    GraphicsManager(GLFWwindow* window, Environment* env);
    void Draw(Environment* env, float currentFrame);
private:
    GLFWwindow* window;

    unsigned int SCREEN_WIDTH;
    unsigned int SCREEN_HEIGHT;

    float sideLean = 0.0f;
    float frontLean = 0.0f;
    int leanSide = 0;
    int leanFront = 0;
    bool fly = false;
    float flySpeed = 0.0f;

    glm::vec3 Pos;
    glm::mat4 drone_model_t;
    glm::mat4 rotor_model_t;
    glm::mat4 hoop_model_t;

    Action action;

    Shader model_shader;

    Model drone_model;
    Model rotor_model;
    Model hoop_model;

    float side_lean_degrees = 30.0f;
    float side_lean_speed = 0.1f;

    float front_lean_degrees = 8.0f;
    float front_lean_speed = 0.1f;

    int frame_counter = 0;
    float delta_time_avg = 0;

    std::vector<glm::vec3> rotor_transformations;
};

