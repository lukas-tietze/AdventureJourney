#pragma once

#include "Objects.hpp"
#include "GlUtils.hpp"

namespace glutil
{
class SceneViewBase : public glutil::Screen
{
protected:
    Scene scene;

public:
    SceneViewBase();

    virtual ~SceneViewBase();
};
} // namespace glutil