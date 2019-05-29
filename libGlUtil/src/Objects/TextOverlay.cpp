#include "Objects.hpp"

void glutil::TextOverlay::TransferFrom(TextOverlay &other)
{
    //TODO!!
    // this->mesh = other.mesh;
    this->meshDirty = other.meshDirty;
    this->enabled = other.enabled;
    this->text = other.text;

    other.meshDirty = true;
}

glutil::TextOverlay::TextOverlay()
{
}

glutil::TextOverlay::TextOverlay(TextOverlay &&other)
{
    this->TransferFrom(other);
}

void glutil::TextOverlay::SetEnabled(bool enabled)
{
    this->enabled = enabled;
}

bool glutil::TextOverlay::IsEnabled() const
{
    return this->enabled;
}

void glutil::TextOverlay::SetText(const std::string &text)
{
    this->text = text;
    this->meshDirty = true;
}

void glutil::TextOverlay::Render()
{
    if (this->meshDirty)
        this->Update();

    this->mesh.Draw();
}

void glutil::TextOverlay::Update()
{
}

glutil::TextOverlay &glutil::TextOverlay::operator=(TextOverlay &&other)
{
    this->TransferFrom(other);

    return *this;
}
