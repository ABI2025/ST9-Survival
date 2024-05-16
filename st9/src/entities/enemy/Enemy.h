#pragma once
#include "entities/entity/Entity.h"
#include "Utils/Utils.h"

class Enemy :
    public Entity
   {
   private:
       
       std::vector<glm::vec3> m_movements;
       Utils::Priority m_priority;
       size_t prev_size{};
       double m_id = 0;
       bool can_be_removed = false;
       bool currently_dying = false;
       friend class EnemyManager;
   public:
       Enemy();
       void die();
       void attack();
       void update();
       bool is_alive() const ;
       Utils::Priority get_priority() const { return m_priority; }
};

