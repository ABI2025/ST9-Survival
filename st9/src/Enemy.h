#pragma once
#include "Entity.h"

class Enemy :
    public Entity
   {
   private:
       std::vector<glm::vec3> m_movements;
       size_t prev_size;
       double hp = 2;
       double id = 0;
       friend class Enemymanager;
   public:
       void die(){}
       void update();
};

