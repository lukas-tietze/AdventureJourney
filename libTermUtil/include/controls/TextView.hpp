#pragma once

#include <string>
#include <vector>

#include "controls/ControlBase.hpp"

namespace terminal
{
class TextView : public ControlBase
{
  private:
    std::vector<std::string> lines;
    size_t firstLine;
    bool centerVertical;
    bool centerHorizontal;
    bool scrollAllowed;
    bool trimLines;
    bool multiLine;

    void PrepareLines();
    void PrepareText();

  public:
    TextView();
    TextView(const std::string &);
    virtual ~TextView();

    void SetCenterVertical(bool);
    bool IsCenterdVertical() const;

    void SetCenterHorizontal(bool);
    bool IsCenterdHorizontal() const;

    void SetScrollingEnabeld(bool);
    bool IsScrollingEnabled() const;

    void SetTrimLinesEnabeld(bool);
    bool IsTrimLinesEnabled() const;

    void SetMultiLineEnabled(bool);
    bool IsMultiLineEnabled() const;

    virtual void HandleKey(KeyInput &);
    virtual void HandleMouse(MouseInput &);
    virtual void HandleBoundsChanged();
    virtual void HandleTextChanged();

    virtual void RestoreLayout();

    virtual void Render(Canvas &);
};
} // namespace terminal
