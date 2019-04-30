#include "Exception.hpp"

#include "Values.hpp"
#include "View.hpp"
#include "controls/ControlBase.hpp"
#include "controls/containers/FrameContainer.hpp"

#pragma region enums
std::ostream &terminal::operator<<(std::ostream &s, const terminal::InputMode value)
{
    switch (value)
    {
    case terminal::InputMode::Raw:
        s << "    RAW";
        break;
    case terminal::InputMode::Break:
        s << "    BREAK";
        break;
    case terminal::InputMode::Line:
        s << "    LINE";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::ResizeMode value)
{
    switch (value)
    {
    case terminal::ResizeMode::North:
        s << "North";
        break;
    case terminal::ResizeMode::South:
        s << "South";
        break;
    case terminal::ResizeMode::West:
        s << "West";
        break;
    case terminal::ResizeMode::East:
        s << "East";
        break;
    case terminal::ResizeMode::Horizontal:
        s << "Horizontal";
        break;
    case terminal::ResizeMode::Vertical:
        s << "Vertical";
        break;
    case terminal::ResizeMode::All:
        s << "All";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::OutputAttribute value)
{
    switch (value)
    {
    case terminal::OutputAttribute::None:
        s << "None";
        break;
    case terminal::OutputAttribute::Standout:
        s << "Standout";
        break;
    case terminal::OutputAttribute::Underline:
        s << "Underline";
        break;
    case terminal::OutputAttribute::Reverse:
        s << "Reverse";
        break;
    case terminal::OutputAttribute::Blink:
        s << "Blink";
        break;
    case terminal::OutputAttribute::Dimmed:
        s << "Dimmed";
        break;
    case terminal::OutputAttribute::Bold:
        s << "Bold";
        break;
    case terminal::OutputAttribute::Protect:
        s << "Protect";
        break;
    case terminal::OutputAttribute::Invisible:
        s << "Invisible";
        break;
    case terminal::OutputAttribute::AlternatCharset:
        s << "AlternatCharset";
        break;
    case terminal::OutputAttribute::All:
        s << "All";
        break;

    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::DefaultColors value)
{
    switch (value)
    {
    case terminal::DefaultColors::Black:
        s << "Black";
        break;
    case terminal::DefaultColors::Red:
        s << "Red";
        break;
    case terminal::DefaultColors::Green:
        s << "Green";
        break;
    case terminal::DefaultColors::Yellow:
        s << "Yellow";
        break;
    case terminal::DefaultColors::Blue:
        s << "Blue";
        break;
    case terminal::DefaultColors::Magenta:
        s << "Magenta";
        break;
    case terminal::DefaultColors::Cyan:
        s << "Cyan";
        break;
    case terminal::DefaultColors::White:
        s << "White";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::CursorMode value)
{
    switch (value)
    {

    case CursorMode::Invisible:
        s << "Invisible";
        break;
    case CursorMode::Default:
        s << "Default";
        break;
    case CursorMode::Highlighted:
        s << "Highlighted";
        break;
    default:
        throw util::InvalidCaseException();
    }
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::Key value)
{
    switch (value)
    {
    case terminal::Key::Down:
        s << "Down";
        break;
    case terminal::Key::Up:
        s << "Up";
        break;
    case terminal::Key::Left:
        s << "Left";
        break;
    case terminal::Key::Right:
        s << "Right";
        break;
    case terminal::Key::Pos1:
        s << "Pos1";
        break;
    case terminal::Key::Backspace:
        s << "Backspace";
        break;
    case terminal::Key::F0:
        s << "F0";
        break;
    case terminal::Key::F1:
        s << "F1";
        break;
    case terminal::Key::F2:
        s << "F2";
        break;
    case terminal::Key::F3:
        s << "F3";
        break;
    case terminal::Key::F4:
        s << "F4";
        break;
    case terminal::Key::F5:
        s << "F5";
        break;
    case terminal::Key::F6:
        s << "F6";
        break;
    case terminal::Key::F7:
        s << "F7";
        break;
    case terminal::Key::F8:
        s << "F8";
        break;
    case terminal::Key::F9:
        s << "F9";
        break;
    case terminal::Key::F10:
        s << "F10";
        break;
    case terminal::Key::F11:
        s << "F11";
        break;
    case terminal::Key::F12:
        s << "F12";
        break;
    case terminal::Key::DeleteLine:
        s << "DeleteLine";
        break;
    case terminal::Key::InsertLine:
        s << "InsertLine";
        break;
    case terminal::Key::Delete:
        s << "Delete";
        break;
    case terminal::Key::Insert:
        s << "Insert";
        break;
    case terminal::Key::Eic:
        s << "Eic";
        break;
    case terminal::Key::Clear:
        s << "Clear";
        break;
    case terminal::Key::ClearToEndOfScreen:
        s << "ClearToEndOfScreen";
        break;
    case terminal::Key::ClearToEndOfLine:
        s << "ClearToEndOfLine";
        break;
    case terminal::Key::ScrollForward:
        s << "ScrollForward";
        break;
    case terminal::Key::ScrollBackward:
        s << "ScrollBackward";
        break;
    case terminal::Key::PageUp:
        s << "PageUp";
        break;
    case terminal::Key::PageDown:
        s << "PageDown";
        break;
    case terminal::Key::Tab:
        s << "Tab";
        break;
    case terminal::Key::ClearTab:
        s << "ClearTab";
        break;
    case terminal::Key::ClearAllTabs:
        s << "ClearAllTabs";
        break;
    case terminal::Key::Enter:
        s << "Enter";
        break;
    case terminal::Key::Print:
        s << "Print";
        break;
    case terminal::Key::LowerLeft:
        s << "LowerLeft";
        break;
    case terminal::Key::KeypadA1:
        s << "KeypadA1";
        break;
    case terminal::Key::KeypadA3:
        s << "KeypadA3";
        break;
    case terminal::Key::KeypadB2:
        s << "KeypadB2";
        break;
    case terminal::Key::KeypadC1:
        s << "KeypadC1";
        break;
    case terminal::Key::KeypadC3:
        s << "KeypadC3";
        break;
    case terminal::Key::BackTab:
        s << "BackTab";
        break;
    case terminal::Key::Begin:
        s << "Begin";
        break;
    case terminal::Key::Cancel:
        s << "Cancel";
        break;
    case terminal::Key::Close:
        s << "Close";
        break;
    case terminal::Key::Command:
        s << "Command";
        break;
    case terminal::Key::Copy:
        s << "Copy";
        break;
    case terminal::Key::Create:
        s << "Create";
        break;
    case terminal::Key::End:
        s << "End";
        break;
    case terminal::Key::Exit:
        s << "Exit";
        break;
    case terminal::Key::Find:
        s << "Find";
        break;
    case terminal::Key::Help:
        s << "Help";
        break;
    case terminal::Key::Mark:
        s << "Mark";
        break;
    case terminal::Key::Message:
        s << "Message";
        break;
    case terminal::Key::Move:
        s << "Move";
        break;
    case terminal::Key::Next:
        s << "Next";
        break;
    case terminal::Key::Open:
        s << "Open";
        break;
    case terminal::Key::Options:
        s << "Options";
        break;
    case terminal::Key::Previous:
        s << "Previous";
        break;
    case terminal::Key::Redo:
        s << "Redo";
        break;
    case terminal::Key::Reference:
        s << "Reference";
        break;
    case terminal::Key::Refresh:
        s << "Refresh";
        break;
    case terminal::Key::Replace:
        s << "Replace";
        break;
    case terminal::Key::Restart:
        s << "Restart";
        break;
    case terminal::Key::Resume:
        s << "Resume";
        break;
    case terminal::Key::Save:
        s << "Save";
        break;
    case terminal::Key::Sbeg:
        s << "Sbeg";
        break;
    case terminal::Key::ShiftCommand:
        s << "ShiftCommand";
        break;
    case terminal::Key::ShiftCancel:
        s << "ShiftCancel";
        break;
    case terminal::Key::ShiftCopy:
        s << "ShiftCopy";
        break;
    case terminal::Key::ShiftCreate:
        s << "ShiftCreate";
        break;
    case terminal::Key::ShiftDeleteChar:
        s << "ShiftDeleteChar";
        break;
    case terminal::Key::ShiftDeleteLine:
        s << "ShiftDeleteLine";
        break;
    case terminal::Key::Select:
        s << "Select";
        break;
    case terminal::Key::ShiftEnd:
        s << "ShiftEnd";
        break;
    case terminal::Key::ShiftClearToEndOfLine:
        s << "ShiftClearToEndOfLine";
        break;
    case terminal::Key::ShiftExit:
        s << "ShiftExit";
        break;
    case terminal::Key::ShiftFind:
        s << "ShiftFind";
        break;
    case terminal::Key::ShiftHelp:
        s << "ShiftHelp";
        break;
    case terminal::Key::ShiftHome:
        s << "ShiftHome";
        break;
    case terminal::Key::ShiftInsertChar:
        s << "ShiftInsertChar";
        break;
    case terminal::Key::ShiftLeft:
        s << "ShiftLeft";
        break;
    case terminal::Key::ShiftMessage:
        s << "ShiftMessage";
        break;
    case terminal::Key::ShiftMove:
        s << "ShiftMove";
        break;
    case terminal::Key::ShiftNext:
        s << "ShiftNext";
        break;
    case terminal::Key::ShiftOptions:
        s << "ShiftOptions";
        break;
    case terminal::Key::ShiftPrevious:
        s << "ShiftPrevious";
        break;
    case terminal::Key::ShiftPrint:
        s << "ShiftPrint";
        break;
    case terminal::Key::ShiftRedo:
        s << "ShiftRedo";
        break;
    case terminal::Key::ShiftReplace:
        s << "ShiftReplace";
        break;
    case terminal::Key::ShiftRight:
        s << "ShiftRight";
        break;
    case terminal::Key::ShiftResume:
        s << "ShiftResume";
        break;
    case terminal::Key::ShiftSave:
        s << "ShiftSave";
        break;
    case terminal::Key::ShiftSuspend:
        s << "ShiftSuspend";
        break;
    case terminal::Key::ShiftUndo:
        s << "ShiftUndo";
        break;
    case terminal::Key::Suspend:
        s << "Suspend";
        break;
    case terminal::Key::Undo:
        s << "Undo";
        break;
    case terminal::Key::Mouse:
        s << "Mouse";
        break;
    case terminal::Key::Resize:
        s << "Resize";
        break;
    case terminal::Key::Event:
        s << "Event";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, MouseAction value)
{
    switch (value)
    {
    case terminal::MouseAction::Button1Pressed:
        s << "Button1Pressed";
        break;
    case terminal::MouseAction::Button1Released:
        s << "Button1Released";
        break;
    case terminal::MouseAction::Button1Clicked:
        s << "Button1Clicked";
        break;
    case terminal::MouseAction::Button1DoubleClicked:
        s << "Button1DoubleClicked";
        break;
    case terminal::MouseAction::Button1TripleClicked:
        s << "Button1TripleClicked";
        break;
    case terminal::MouseAction::Button2Pressed:
        s << "Button2Pressed";
        break;
    case terminal::MouseAction::Button2Released:
        s << "Button2Released";
        break;
    case terminal::MouseAction::Button2Clicked:
        s << "Button2Clicked";
        break;
    case terminal::MouseAction::Button2DoubleClicked:
        s << "Button2DoubleClicked";
        break;
    case terminal::MouseAction::Button2TripleClicked:
        s << "Button2TripleClicked";
        break;
    case terminal::MouseAction::Button3Pressed:
        s << "Button3Pressed";
        break;
    case terminal::MouseAction::Button3Released:
        s << "Button3Released";
        break;
    case terminal::MouseAction::Button3Clicked:
        s << "Button3Clicked";
        break;
    case terminal::MouseAction::Button3DoubleClicked:
        s << "Button3DoubleClicked";
        break;
    case terminal::MouseAction::Button3TripleClicked:
        s << "Button3TripleClicked";
        break;
    case terminal::MouseAction::Button4Pressed:
        s << "Button4Pressed";
        break;
    case terminal::MouseAction::Button4Released:
        s << "Button4Released";
        break;
    case terminal::MouseAction::Button4Clicked:
        s << "Button4Clicked";
        break;
    case terminal::MouseAction::Button4DoubleClicked:
        s << "Button4DoubleClicked";
        break;
    case terminal::MouseAction::Button4TripleClicked:
        s << "Button4TripleClicked";
        break;
    case terminal::MouseAction::ButtonShift:
        s << "ButtonShift";
        break;
    case terminal::MouseAction::ButtonCtrl:
        s << "ButtonCtrl";
        break;
    case terminal::MouseAction::ButtonAlt:
        s << "ButtonAlt";
        break;
    default:
        throw util::InvalidCaseException();
    }
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::ControlStyleColor value)
{
    switch (value)
    {
    case terminal::ControlStyleColor::ControlText:
        s << "ControlText";
        break;
    case terminal::ControlStyleColor::DisabledControlText:
        s << "DisabledControlText";
        break;
    case terminal::ControlStyleColor::ControlBorder:
        s << "ControlBorder";
        break;
    case terminal::ControlStyleColor::InactiveControlBorder:
        s << "InactiveControlBorder";
        break;
    case terminal::ControlStyleColor::DisabledControlBorder:
        s << "DisabledControlBorder";
        break;
    case terminal::ControlStyleColor::ClearColor:
        s << "ClearColor";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, terminal::AutoSizeMode value)
{
    switch (value)
    {
    case terminal::AutoSizeMode::None:
        s << "None";
        break;
    case terminal::AutoSizeMode::Fill:
        s << "Fill";
        break;
    case terminal::AutoSizeMode::FillHorizontal:
        s << "FillHorizontal";
        break;
    case terminal::AutoSizeMode::FillVertical:
        s << "FillVertical";
        break;
    default:
        throw util::InvalidCaseException::MakeException(value);
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, terminal::BorderType value)
{
    switch (value)
    {
    case terminal::BorderType::TopEdge:
        s << "TopEdge";
        break;
    case terminal::BorderType::RightEdge:
        s << "RightEdge";
        break;
    case terminal::BorderType::BottomEdge:
        s << "BottomEdge";
        break;
    case terminal::BorderType::LeftEdge:
        s << "LeftEdge";
        break;
    case terminal::BorderType::TopLeftCorner:
        s << "TopLeftCorner";
        break;
    case terminal::BorderType::TopRightCorner:
        s << "TopRightCorner";
        break;
    case terminal::BorderType::BottomRightCorner:
        s << "BottomRightCorner";
        break;
    case terminal::BorderType::BottomLeftCorner:
        s << "BottomLeftCorner";
        break;
    case terminal::BorderType::TopLine:
        s << "TopLine";
        break;
    case terminal::BorderType::BottomLine:
        s << "BottomLine";
        break;
    case terminal::BorderType::LeftLine:
        s << "LeftLine";
        break;
    case terminal::BorderType::RightLine:
        s << "RightLine";
        break;
    case terminal::BorderType::AllEdges:
        s << "AllEdges";
        break;
    case terminal::BorderType::AllCorners:
        s << "AllCorners";
        break;
    case terminal::BorderType::All:
        s << "All";
        break;
    }

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, terminal::FrameContainer::Orientation value)
{
    switch (value)
    {
    case terminal::FrameContainer::Orientation::Left:
        s << "Left";
        break;
    case terminal::FrameContainer::Orientation::Right:
        s << "Right";
        break;
    case terminal::FrameContainer::Orientation::Top:
        s << "Top";
        break;
    case terminal::FrameContainer::Orientation::Bottom:
        s << "Bottom";
        break;
    case terminal::FrameContainer::Orientation::Center:
        s << "Center";
        break;
    default:
        throw util::InvalidCaseException();
    }

    return s;
}

#pragma endregion enums
#pragma region structs

std::ostream &terminal::operator<<(std::ostream &s, const terminal::KeyInput &value)
{
    s << value.key << " (" << (value.handled ? "handled" : "unhandled") << ")";

    return s;
}

std::ostream &terminal::operator<<(std::ostream &s, const terminal::MouseInput &value)
{
    s << value.action << " [" << value.x << ", " << value.y << "] (" << (value.handled ? "handled" : "unhandled") << ")";

    return s;
}

#pragma endregion structs