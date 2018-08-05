#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <string>

class entity_class
{
  private:
    std::string name;
};

class entity_subclass
{
  private:
    std::string name;
    std::string parentClassName;
};

class entity
{
  private:
    long armor;
    long attack;
    long armourPen;
};

#endif /*ENTITIES_HPP*/