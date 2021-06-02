#pragma once

#include <iostream>
#include <vector>

#include <glm/glm/glm.hpp>

struct Action
{
    float x;
    float y;
    float z;
};

struct State
{

};

struct SARD //State action reward set
{
    State state;
    Action action;
    float reward;
    bool done;
};

class Environment
{
public:
    glm::vec3 dronePos;
    int currentHoop;
    std::vector<glm::vec3> hoopPositions;
    Action action;

    Environment();
    SARD step(Action action);
    void Reset();
private:
    
};

