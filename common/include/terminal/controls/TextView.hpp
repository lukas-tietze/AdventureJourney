#pragma once

#include <string>
#include <vector>

#include "terminal/controls/ControlBase.hpp"

namespace terminal
{
class TextView : public ControlBase
{
  private:
    std::vector<std::string> lines;
    size_t firstLine;
    bool centerVertical;
    bool centerHorizontal;

    void PrepareLines();
    void PrepareText();

  public:
    TextView();
    TextView(const std::string &);
    virtual ~TextView();

    void SetCenterHorizontal(bool);
    void SetCenterVertical(bool);

    bool IsCenterdHorizontal() const;
    bool IsCenterdVertical() const;

    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void HandleBoundsChanged();
    virtual void HandleTextChanged();

    virtual void RestoreLayout();

    virtual void Render(Canvas &);
};
} // namespace terminal
