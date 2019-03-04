#include "terminal/Size.hpp"
#include "data/Math.hpp"

terminal::Size::Size() : rel(0.f)
{
}

terminal::Size::Size(float f) : rel(0.f)
{
    if (f > 1.f)
        f = 1.f;
    else if (f < 0.f)
        f = 0.f;

    this->rel = f;
}

terminal::Size::Size(int i) : rel(0.f)
{
    if (i < 0)
        i = 0;

    this->rel = i;
}

int terminal::Size::operator[](int total)
{
    return this->rel <= 1.0 ? this->rel * total : static_cast<int>(this->rel);
}
