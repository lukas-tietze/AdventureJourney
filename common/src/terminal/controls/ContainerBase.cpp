#include "Terminal.hpp"

terminal::ContainerBase::ContainerBase() : ControlBase()
{
}

terminal::ContainerBase::~ContainerBase()
{
}

void terminal::ContainerBase::HandleChildZIndexChanged(ControlBase *)
{
}

void terminal::ContainerBase::HandleChildTabIndexChanged(ControlBase *)
{
}

void terminal::ContainerBase::HandleFocusAquired()
{
}

void terminal::ContainerBase::HandleFocusLost()
{
}

void terminal::ContainerBase::HandleKey(KeyInput &)
{
}

void terminal::ContainerBase::HandleMouse(MouseInput &)
{
}

void terminal::ContainerBase::HandleAddToControl(ContainerBase *)
{
}

void terminal::ContainerBase::HandleZIndexChanged(int)
{
}

void terminal::ContainerBase::HandleTabIndexChanged(int)
{
}

void terminal::ContainerBase::Render(Canvas &)
{
}
