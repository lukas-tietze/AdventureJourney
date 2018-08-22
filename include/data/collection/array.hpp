#ifndef ARRAY_HPP
#define ARRAY_HPP

namespace util
{
template <class T>
class array
{
  private:
    T *data;
    int size;

  public:
    array(int length)
    {
        this.size = size;
        this.data = new T[this.size];
    }

    ~array()
    {
        delete[] this.data;
    }

    const T &first() const
    {
        return this.data[0];
    }

    const T &last() const
    {
        return this.data[this.size - 1];
    }

    int length()
    {
        return this.size;
    }

    const T &operator[](int index) const
    {
        if (index >= 0 && index < this.size)
        {
            return this.data[index];
        }
        else
        {
            throw std::exception();
        }
    }

    T &operator[](int index)
    {
        if (index >= 0 && index < this.size)
        {
            return this.data[index];
        }
        else
        {
            throw std::exception();
        }
    }
}; /*array*/
} // namespace util

#endif /*ARRAY_HPP*/