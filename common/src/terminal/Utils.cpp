#include "terminal/Values.hpp"

bool terminal::IsSpecialKey(int key)
{
    return key > KEY_MIN && key < KEY_MAX;
}