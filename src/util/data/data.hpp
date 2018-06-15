#include <stdexcept>


namespace util
{
template <class T, uint size>
class array
{
  private:
    T m_data[size];

  public:
    int length()
    {
        return size;
    }

    const T &operator[](int index) const
    {
        if (index >= 0 && index < size)
        {
            return m_data[index];
        }
        else{
            throw std::exception();
        }
    }

    T &operator[](int index)
    {
        if (index >= 0 && index < size)
        {
            return m_data[index];
        }
        else{
            throw std::exception();
        }
    }
};
} // namespace util