#pragma once
#include "entities/entity/Entity.h"
#include "Utils/Utils.h"

class Enemy :
    public Entity
   {
   private:
       
       std::vector<glm::vec3> m_movements;
       Utils::Priority m_priority;
       size_t prev_size;
       double m_id = 0;
       friend class EnemyManager;
   public:
       Enemy() { m_health = 2; }
       void die();
       void update();
       bool is_alive() const ;
       void take_damage(double damage);
       double get_hp() const;
       Utils::Priority get_priority() const { return m_priority; }
};

