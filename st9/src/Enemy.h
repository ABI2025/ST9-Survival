#pragma once
#include "Entity.h"

class Enemy :
    public Entity
   {
   private:
       std::vector<glm::vec3> m_movements;
       double hp = 1;
       double id = 0;
       friend class Enemymanager;
   public:
       void die(){}
       void update();
};

