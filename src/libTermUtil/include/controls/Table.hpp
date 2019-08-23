#pragma once

#include "controls/ControlBase.hpp"

namespace terminal
{
class Table : public ControlBase
{
  private:
    std::vector<std::string> content;
    int columns;
    int rows;

  public:
    Table();
    Table(int rows, int cols);
    
    virtual void HandleFocusAquired();
    virtual void HandleFocusLost();
    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void HandleAddToControl(ContainerBase *);
    virtual void HandleZIndexChanged(int);
    virtual void HandleTabIndexChanged(int);

    virtual void Render(Canvas &);
};
} // namespace terminal