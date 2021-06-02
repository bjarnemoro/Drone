#include <iostream>
#include <iomanip>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm/glm.hpp>

#include "shader.h"
#include "model.h"
#include "environment.h"
#include "graphics_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLFWwindow* create_window();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);

unsigned int SCREEN_WIDTH = 1200;
extern unsigned int SCREEN_HEIGHT = 800;

float sideLean = 0.0f;
float frontLean = 0.0f;
int leanSide;
int leanFront;
bool fly;
float flySpeed = 0.0f;
glm::vec3 drone_pos = glm::vec3(0.0f);
int current_hoop = 0;

Environment env;
Action action;
//GraphicsManager graphicsManager;

//enum LeanSide {
//    STRAIGHT = 0,
//    RIGHT = 1,
//    LEFT = 2
//};
//
//enum LeanFront {
//    FORWARD = 1,
//    BACKWARD = 2
//};

int main()
{
    //-----------------------------------
    //   load glfw and create a window
    //-----------------------------------

    //glfwInit();
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //
    //GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Drone simulation", 0, 0);
    //
    //glfwMakeContextCurrent(window);
    //
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    std::cout << "Failed to initialize GLAD" << std::endl;
    //    return -1;
    //}
    GLFWwindow* window = create_window();

    //-----------------------------------
    //     set the main callbacks
    //-----------------------------------
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);

    env = Environment();
    action = Action();

    GraphicsManager graphicsManager = GraphicsManager(window, &env);


    //-----------------------------------
    //           load models
    //-----------------------------------

    //float points[] =
    //{
    //    -1.8f, 0.0f, 0.0f,
    //    1.8f, 0.0f, 0.0f,
    //};
    //
    //unsigned int VAO, VBO;
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //
    //glBindVertexArray(VAO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //
    //glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    //
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    

    

    //-----------------------------------
    //       start the main loop
    //-----------------------------------
    glEnable(GL_DEPTH_TEST);

    int r = rand();

    float currentFrame;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    float side_lean_degrees = 30.0f;                
    float side_lean_speed = 0.1f;

    float front_lean_degrees = 8.0f;
    float front_lean_speed = 0.1f;

    int frame_counter = 0;
    float delta_time_avg = 0;

    action.y = -0.1f;

    while (!glfwWindowShouldClose(window))
    {
        //calculate the delta time
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //draw


        env.step(action);
        graphicsManager.Draw(&env, currentFrame);

        //spheroid.Draw(model_shader);

        //glm::mat4 drone_model_t = glm::mat4(1.0f);
        //
        ////drone_model_t = glm::rotate(drone_model_t, (float)90, glm::vec3(1.0f, 0.0f, 0.0f));
        ////drone_model_t = glm::rotate(drone_model_t, currentFrame, glm::vec3(1.0f, 0.0f, 1.0f));
        //
        //
        //switch (leanSide)
        //{
        //    case STRAIGHT:   
        //        action.z = 0.0f;
        //        sideLean += abs(sideLean) * side_lean_speed * ((sideLean < 0) * 2 - 1);
        //        break;
        //    case RIGHT:
        //        drone_pos.z += 0.1;  
        //        action.z = 0.1f;
        //        sideLean += abs(sideLean - side_lean_degrees) * side_lean_speed;
        //        break;
        //    case LEFT:
        //        drone_pos.z -= 0.1;
        //        action.z = -0.1f;
        //        sideLean -= abs(sideLean + side_lean_degrees) * side_lean_speed;
        //        break;
        //}
        //
        //switch (leanFront)
        //{
        //case STRAIGHT:
        //    action.x = 0.0f;
        //    frontLean += abs(frontLean) * front_lean_speed * ((frontLean < 0) * 2 - 1);
        //    break;
        //case FORWARD:
        //    drone_pos.x += 0.2;
        //    action.x = 0.2f;
        //    frontLean -= abs(frontLean + front_lean_degrees) * front_lean_speed;
        //    break;
        //case BACKWARD:
        //    drone_pos.x -= 0.2;
        //    action.x = -0.2f;
        //    frontLean += abs(frontLean - front_lean_degrees) * front_lean_speed;
        //    break;
        //}
        //
        //env.step(action);
        //
        //if (fly)
        //{
        //    action.y = -abs(flySpeed - 20) * 0.01 + 0.1;
        //    flySpeed += abs(flySpeed - 20) * 0.1;
        //}
        //else 
        //{
        //    action.y = -0.1f;
        //    flySpeed -= abs(flySpeed) * 0.3;
        //}
        //drone_pos.y += (flySpeed * 0.01) - 0.1;
        //
        ////calculate collisions with the hoops
        //for (int i = 0; i < sizeof(hoop_positions) / sizeof(*hoop_positions); i++)
        //{
        //    if (glm::distance(env.dronePos, hoop_positions[env.currentHoop]) < 2 && abs(env.dronePos.x - hoop_positions[env.currentHoop].x) < 0.05)
        //    {
        //        current_hoop++;
        //    }
        //}
        //
        //drone_model_t = glm::translate(drone_model_t, env.dronePos);
        //drone_model_t = glm::rotate(drone_model_t, glm::radians(sideLean), glm::vec3(1.0f, 0.0f, 0.0f));
        //drone_model_t = glm::rotate(drone_model_t, glm::radians(frontLean), glm::vec3(0.0f, 0.0f, 1.0f));
        //
        //Pos = env.dronePos + glm::vec3(-8.0f, 2.5f, 0.0f);
        //model_shader.SetMat4("view", glm::lookAt(Pos, env.dronePos, glm::vec3(0.0f, 1.0f, 0.0f)));
        //model_shader.SetMat4("model", drone_model_t);
        //drone_model.Draw(model_shader);
        //
        //for (int i = 0; i < 4; i++)
        //{
        //    glm::mat4 rotor_model_t = glm::mat4(1.0f);
        //    //rotor_model_t = glm::rotate(rotor_model_t, (float)90, glm::vec3(1.0f, 0.0f, 0.0f));
        //    //rotor_model_t = glm::rotate(rotor_model_t, currentFrame, glm::vec3(1.0f, 0.0f, 1.0f));
        //    rotor_model_t = glm::translate(rotor_model_t, env.dronePos);
        //    rotor_model_t = glm::rotate(rotor_model_t, glm::radians(sideLean), glm::vec3(1.0f, 0.0f, 0.0f));
        //    rotor_model_t = glm::rotate(rotor_model_t, glm::radians(frontLean), glm::vec3(0.0f, 0.0f, 1.0f));
        //    rotor_model_t = glm::translate(rotor_model_t, rotor_transformations[i]);
        //    rotor_model_t = glm::rotate(rotor_model_t, currentFrame * flySpeed, glm::vec3(0.0f, 1.0f, 0.0f));
        //    
        //
        //    model_shader.SetMat4("model", rotor_model_t);
        //    rotor_model.Draw(model_shader);
        //}
        //
        //for (int i = 0; i < sizeof(hoop_positions) / sizeof(*hoop_positions); i++)
        //{
        //    glm::mat4 hoop_model_t = glm::mat4(1.0f);
        //    hoop_model_t = glm::translate(hoop_model_t, hoop_positions[i]);
        //    hoop_model_t = glm::scale(hoop_model_t, glm::vec3(0.5f));
        //    model_shader.SetMat4("model", hoop_model_t);
        //
        //    if (i == env.currentHoop)
        //    {
        //        hoop_model.ChangeColor(glm::vec4(0.3f, 0.524135f, 0.321252f, 1.0f));
        //        hoop_model.Draw(model_shader);
        //        hoop_model.ChangeColor(glm::vec4(0.8f, 0.024135f, 0.021252f, 1.0f));
        //    }
        //    else
        //    {
        //        hoop_model.Draw(model_shader);
        //    }
        //} 

        //if (frame_counter % 20 == 0)
        //{
        //    delta_time_avg /= 20;
        //    std::cout << std::fixed << std::setprecision(2);
        //    std::cout << "current FPS: " << 1 / delta_time_avg << "\r";
        //    frame_counter = 0;
        //    delta_time_avg = 0;
        //}
        //
        //delta_time_avg += deltaTime;
        //frame_counter++;
    }
    return 0;
}

GLFWwindow* create_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Drone simulation", 0, 0);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    return window;
}

void draw_stuff()
{

}

void key_callback(GLFWwindow* window, int key, int scancode, int key_action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && key_action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (key == GLFW_KEY_A && key_action == GLFW_PRESS)
    {
        leanSide = LEFT;
        action.z = -0.1f;
    }
    if (key == GLFW_KEY_A && key_action == GLFW_RELEASE)
    {
        leanSide = STRAIGHT;
        action.z = 0.0f;
    }
    if (key == GLFW_KEY_D && key_action == GLFW_PRESS)
    {
        leanSide = RIGHT;
        action.z = 0.1f;
    }
    if (key == GLFW_KEY_D && key_action == GLFW_RELEASE)
    {
        leanSide = STRAIGHT;
        action.z = 0.0f;
    }
    if (key == GLFW_KEY_W && key_action == GLFW_PRESS)
    {
        leanFront = FORWARD;
        action.x = 0.2f;
    }
    if (key == GLFW_KEY_W && key_action == GLFW_RELEASE)
    {
        leanFront = STRAIGHT;
        action.x = 0.0f;
    }
    if (key == GLFW_KEY_S && key_action == GLFW_PRESS)
    {
        leanFront = BACKWARD;
        action.x = -0.2f;
    }
    if (key == GLFW_KEY_S && key_action == GLFW_RELEASE)
    {
        leanFront = STRAIGHT;
        action.x = 0.0f;
    }
    if (key == GLFW_KEY_SPACE && key_action == GLFW_PRESS)
    {
        fly = true;
        action.y = 0.1f;
    }
    if (key == GLFW_KEY_SPACE && key_action == GLFW_RELEASE)
    {
        fly = false;
        action.y = -0.1f;
    }
    if (key == GLFW_KEY_R && key_action == GLFW_RELEASE)
    {
        env.Reset();
    }
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
    }
}