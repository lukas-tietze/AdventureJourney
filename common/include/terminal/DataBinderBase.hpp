#pragma once

namespace terminal
{
template <class T>
class DataBinderBase
{
  private:
    T *data;

  protected:
    void HandleDataChanged()
    {
        if (this->data != nullptr)
            *this->data = this->GetSelectedValue();
    }

    virtual T &GetSelectedValue() = 0;

  public:
    const T *GetBoundDataTarget() const
    {
        return this->data;
    }

    void UnbindData()
    {
        this->data = nullptr;
    }

    void BindData(T *data)
    {
        this->data = data;
    }

    bool IsDataBound() const
    {
        return this->data != nullptr;
    }
};
} // namespace terminal
