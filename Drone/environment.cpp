#include "environment.h"

Environment::Environment()
{
    dronePos = glm::vec3(0.0f);
    currentHoop = 0;

    hoopPositions = {
        glm::vec3(10.0f, -3.0f, 1.0f),
        glm::vec3(20.0f, 1.0f, -2.0f),
        glm::vec3(30.0f, -5.0f, 4.0f),
        glm::vec3(40.0f, 2.0f, 4.0f),
        glm::vec3(50.0f, -2.0f, 7.0f),
        glm::vec3(60.0f, 3.0f, 10.0f),
        glm::vec3(70.0f, 1.0f, 6.0f),
        glm::vec3(80.0f, -2.0f, 1.0f),
        glm::vec3(90.0f, -4.0f, -1.0f),
        glm::vec3(100.0f, 2.0f, 0.0f),
    };
};

void Environment::Reset()
{
    dronePos = glm::vec3(0.0f);
    currentHoop = 0;
}


SARD Environment::step(Action _action)
{
    SARD sardSet;
    sardSet.state = State();
    //sardSet.action = action;
    sardSet.reward = 1;
    sardSet.done = false;

    action = _action;

    dronePos.x += _action.x;
    dronePos.y += _action.y;
    dronePos.z += _action.z;

    //std::cout << hoopPositions.size() << std::endl;

    for (int i = 0; i < hoopPositions.size(); i++)
    {
        if (glm::distance(dronePos, hoopPositions[currentHoop]) < 2 && abs(dronePos.x - hoopPositions[currentHoop].x) < 0.05)
        {
            currentHoop = (currentHoop + 1) % hoopPositions.size();
        }
    }

    return sardSet;
}