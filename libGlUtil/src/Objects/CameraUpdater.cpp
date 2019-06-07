#include "ScreenUtils.hpp"

#include "GLFW/glfw3.h"

namespace
{
constexpr int FORWARD = 0;
constexpr int BACK = 1;
constexpr int LEFT = 2;
constexpr int RIGHT = 3;
constexpr int UP = 4;
constexpr int DOWN = 5;

constexpr int HORIZONTAL = 0;
constexpr int VERTICAL = 1;
} // namespace

glutil::CameraUpdater::CameraUpdater() : keys{GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT},
                                         moveSpeed{2.f, 2.f, 2.f, 2.f, 2.f, 2.f}, //TODO nicht implemntiert
                                         rotateSpeed{1.f, 1.f},                   //TODO nicht implemntiert
                                         flattenMove(true),                       //TODO nicht implemntiert
                                         enabled(true),
                                         invertVerticalRotation(false), //TODO, nicht implementiert
                                         camera(nullptr)
{
}

void glutil::CameraUpdater::Update(double delta)
{
    if (!this->enabled || !this->camera)
        return;

    int x = 0;
    int y = 0;
    int z = 0;

    if (glutil::IsKeyDown(this->keys[FORWARD]))
        x++;
    if (glutil::IsKeyDown(this->keys[BACK]))
        x--;
    if (glutil::IsKeyDown(this->keys[RIGHT]))
        z++;
    if (glutil::IsKeyDown(this->keys[LEFT]))
        z--;
    if (glutil::IsKeyDown(this->keys[UP]))
        y++;
    if (glutil::IsKeyDown(this->keys[DOWN]))
        y--;

    auto viewFlat = this->camera->GetViewDirection();
    viewFlat.y = 0;

    auto viewCross = glm::cross(viewFlat, this->camera->GetUp());
    viewCross.y = 0;

    this->camera->MoveBy(viewFlat * static_cast<float>(delta * x) +
                         this->camera->GetUp() * static_cast<float>(delta * y) +
                         viewCross * static_cast<float>(delta * z));

    this->camera->Rotate(static_cast<float>(glutil::GetMouseDeltaX() * -1), glutil::AXIS_Y);
    this->camera->Rotate(static_cast<float>(glutil::GetMouseDeltaY() * -1), viewCross);

    if (glutil::WasWindowResized())
        this->camera->SetAspectRation(glutil::GetAspectRatio());

    this->camera->UpdateMatrices();
}

void glutil::CameraUpdater::SetKeyForward(int key)
{
    this->keys[FORWARD] = key;
}

void glutil::CameraUpdater::SetKeyBack(int key)
{
    this->keys[BACK] = key;
}

void glutil::CameraUpdater::SetKeyLeft(int key)
{
    this->keys[LEFT] = key;
}

void glutil::CameraUpdater::SetKeyRight(int key)
{
    this->keys[RIGHT] = key;
}

void glutil::CameraUpdater::SetKeyUp(int key)
{
    this->keys[UP] = key;
}

void glutil::CameraUpdater::SetKeyDown(int key)
{
    this->keys[DOWN] = key;
}

void glutil::CameraUpdater::SetKeys(int f, int b, int l, int r, int u, int d)
{
    this->keys[FORWARD] = f;
    this->keys[BACK] = b;
    this->keys[LEFT] = l;
    this->keys[RIGHT] = r;
    this->keys[UP] = u;
    this->keys[DOWN] = d;
}

void glutil::CameraUpdater::SetRotateSpeed(float h, float v)
{
    this->rotateSpeed[VERTICAL] = v;
    this->rotateSpeed[HORIZONTAL] = h;
}

void glutil::CameraUpdater::SetVerticalRotateSpeed(float value)
{
    this->rotateSpeed[VERTICAL] = value;
}

void glutil::CameraUpdater::SetHorizontalSpeed(float value)
{
    this->rotateSpeed[HORIZONTAL] = value;
}

void glutil::CameraUpdater::SetMovementSpeed(float value)
{
    this->moveSpeed[0] = value;
    ///TODO unterschiedliche Geschwindigkeiten für jede Richtung
}

void glutil::CameraUpdater::SetFlattenMove(bool value)
{
    this->flattenMove = value;
}

void glutil::CameraUpdater::Enable()
{
    this->enabled = true;
}

void glutil::CameraUpdater::Disable()
{
    this->enabled = false;
}

void glutil::CameraUpdater::SetEnabled(bool value)
{
    this->enabled = value;
}

void glutil::CameraUpdater::SetCamera(glutil::Camera *camera)
{
    this->camera = camera;
}

glutil::Camera *glutil::CameraUpdater::GetCamera()
{
    return this->camera;
}

const glutil::Camera *glutil::CameraUpdater::GetCamera() const
{
    return this->camera;
}
