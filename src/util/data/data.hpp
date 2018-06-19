#include <stdexcept>

namespace util
{
template <class T>
class array
{
  private:
    T *m_data;
    int m_size;

  public:
    array(int length)
    {
        m_size = size;
        m_data = new T[m_size];
    }

    ~array()
    {
        delete[] m_data;
    }

    const T &first() const
    {
        return m_data[0];
    }

    const T &last() const
    {
        return m_data[m_size - 1]
    }

    int length()
    {
        return m_size;
    }

    const T &operator[](int index) const
    {
        if (index >= 0 && index < m_size)
        {
            return m_data[index];
        }
        else
        {
            throw std::exception();
        }
    }

    T &operator[](int index)
    {
        if (index >= 0 && index < m_size)
        {
            return m_data[index];
        }
        else
        {
            throw std::exception();
        }
    }
};
} // namespace util