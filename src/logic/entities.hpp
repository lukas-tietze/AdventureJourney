#pragma once

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