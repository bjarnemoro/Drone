#include "graphics_manager.h"

GraphicsManager::GraphicsManager(GLFWwindow* _window, Environment* env)
    : model_shader(Shader("model_shader.vs", "model_shader.fs")),
    drone_model(Model("C:/Users/bjarn/source/resources/models/drone/drone.obj")),
    rotor_model(Model("C:/Users/bjarn/source/resources/models/drone/rotor.obj")),
    hoop_model(Model("C:/Users/bjarn/source/resources/models/drone/hoop.obj"))
{
    window = _window;
    SCREEN_WIDTH = 1200;
    SCREEN_HEIGHT = 800;

    Pos = glm::vec3(-5.0f, 3.0f, 0.0f);
    drone_model_t = glm::mat4(1.0f);
    rotor_model_t = glm::mat4(1.0f);
    hoop_model_t = glm::mat4(1.0f);

    model_shader = Shader("model_shader.vs", "model_shader.fs");
    model_shader.use();
    model_shader.SetMat4("projection", glm::perspective(45.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.3f, 300.0f));
    //model_shader.SetMat4("view", glm::lookAt(Pos, Pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    model_shader.SetMat4("view", glm::lookAt(Pos, env->dronePos, glm::vec3(0.0f, 1.0f, 0.0f)));
    model_shader.SetMat4("model", drone_model_t);
    model_shader.SetVec3("viewPos", Pos);

    drone_model = Model("C:/Users/bjarn/source/resources/models/drone/drone.obj");
    rotor_model = Model("C:/Users/bjarn/source/resources/models/drone/rotor.obj");
    hoop_model = Model("C:/Users/bjarn/source/resources/models/drone/hoop.obj");

    rotor_transformations = {
       glm::vec3(1.0f, 0.08f, 0.7f),
       glm::vec3(-1.0f, 0.08f, 0.7f),
       glm::vec3(1.0f, 0.08f, -0.7f),
       glm::vec3(-1.0f, 0.08f, -0.7f)
    };
}

void GraphicsManager::Draw(Environment* env, float currentFrame)
{
    glClearColor(0.45f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sideLean += ((double)env->action.z * 200 - sideLean) * 0.1;
    frontLean += ((double)-env->action.x * 50 - frontLean) * 0.1;
    
    drone_model_t = glm::mat4(1.0f);
    drone_model_t = glm::translate(drone_model_t, env->dronePos);
    drone_model_t = glm::rotate(drone_model_t, glm::radians(sideLean), glm::vec3(1.0f, 0.0f, 0.0f));
    drone_model_t = glm::rotate(drone_model_t, glm::radians(frontLean), glm::vec3(0.0f, 0.0f, 1.0f));
    
    Pos = env->dronePos + glm::vec3(-8.0f, 2.5f, 0.0f);
    model_shader.SetMat4("view", glm::lookAt(Pos, env->dronePos, glm::vec3(0.0f, 1.0f, 0.0f)));
    model_shader.SetMat4("model", drone_model_t);
    drone_model.Draw(model_shader);

    flySpeed = env->action.y + 0.1f;
    
    for (int i = 0; i < 4; i++)
    {
        rotor_model_t = glm::mat4(1.0f);
        //rotor_model_t = glm::rotate(rotor_model_t, (float)90, glm::vec3(1.0f, 0.0f, 0.0f));
        //rotor_model_t = glm::rotate(rotor_model_t, currentFrame, glm::vec3(1.0f, 0.0f, 1.0f));
        rotor_model_t = glm::translate(rotor_model_t, env->dronePos);
        rotor_model_t = glm::rotate(rotor_model_t, glm::radians(sideLean), glm::vec3(1.0f, 0.0f, 0.0f));
        rotor_model_t = glm::rotate(rotor_model_t, glm::radians(frontLean), glm::vec3(0.0f, 0.0f, 1.0f));
        rotor_model_t = glm::translate(rotor_model_t, rotor_transformations[i]);
        rotor_model_t = glm::rotate(rotor_model_t, currentFrame * (flySpeed*100), glm::vec3(0.0f, 1.0f, 0.0f));
        
    
        model_shader.SetMat4("model", rotor_model_t);
        rotor_model.Draw(model_shader);
    }
    
    for (int i = 0; i < env->hoopPositions.size(); i++)
    {
        hoop_model_t = glm::mat4(1.0f);
        hoop_model_t = glm::translate(hoop_model_t, env->hoopPositions[i]);
        hoop_model_t = glm::scale(hoop_model_t, glm::vec3(0.5f));
        model_shader.SetMat4("model", hoop_model_t);

        if (i == env->currentHoop)
        {
            hoop_model.ChangeColor(glm::vec4(0.3f, 0.524135f, 0.321252f, 1.0f));
            hoop_model.Draw(model_shader);
            hoop_model.ChangeColor(glm::vec4(0.8f, 0.024135f, 0.021252f, 1.0f));
        }
        else
        {
            hoop_model.Draw(model_shader);
        }
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}