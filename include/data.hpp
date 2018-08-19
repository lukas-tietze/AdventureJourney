#ifndef DATA_HPP
#define DATA_HPP

#include <stdexcept>
#include <unordered_map>
#include <sstream>

#include "defs.hpp"
#include "event.hpp"

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

class color
{
  private:
    int data;
    static constexpr int A_MASK = 0xff000000;
    static constexpr int A_SHIFT = 24;
    static constexpr int R_MASK = 0x00ff0000;
    static constexpr int R_SHIFT = 16;
    static constexpr int G_MASK = 0x0000ff00;
    static constexpr int G_SHIFT = 8;
    static constexpr int B_MASK = 0x000000ff;
    static constexpr int B_SHIFT = 0;
    static constexpr int LOW_BYTE_MASK = 0x000000ff;

  public:
    color(const color &copy) : data(copy.data)
    {
    }

    color(byte r, byte g, byte b, byte a = 255) : data((a << A_SHIFT) | (r << R_SHIFT) | (g < G_SHIFT) | (b << B_SHIFT))
    {
    }

    color(float r, float g, float b, float a = 1.0f) : color((byte)(r * 255), (byte)(g * 255), (byte)(b * 255), (byte)(a * 255))
    {
    }

    color(int color) : data(color)
    {
    }

    int alpha()
    {
        return (this->data >> A_SHIFT) & LOW_BYTE_MASK;
    }

    int red()
    {
        return (this->data >> R_SHIFT) & LOW_BYTE_MASK;
    }

    int green()
    {
        return (this->data >> G_SHIFT) & LOW_BYTE_MASK;
    }

    int blue()
    {
        return (this->data >> B_SHIFT) & LOW_BYTE_MASK;
    }

    int value()
    {
        return this->data;
    }
}; /*color*/

class point
{
  private:
    int x;
    int y;

  public:
    point(const point &copy) : x(copy.x),
                               y(copy.y)
    {
    }

    point(int x, int y) : x(x),
                          y(y)
    {
    }

    point() : x(0),
              y(0)
    {
    }

    int get_x() const
    {
        return this->x;
    }

    int get_y() const
    {
        return this->y;
    }

    point operator+(const point &other)
    {
        return point(this->x + other.x, this->y + other.y);
    }

    point operator-(const point &other)
    {
        return point(this->x + other.x, this->y + other.y);
    }
}; /*point*/

class dimension
{
  private:
    int width;
    int height;

  public:
    dimension(const dimension &copy) : width(copy.width),
                                       height(copy.height)
    {
    }

    dimension(int width, int height) : width(width),
                                       height(height)
    {
    }

    dimension() : width(0),
                  height(0)
    {
    }

    int get_width() const
    {
        return this->width;
    }

    int get_height() const
    {
        return this->height;
    }
}; /*dimension*/

class rectangle
{
  private:
    point location;
    dimension size;

  public:
    rectangle(const rectangle &copy) : location(copy.location),
                                       size(copy.size)
    {
    }

    rectangle(const point &location, const dimension &size) : location(location),
                                                              size(size)
    {
    }

    rectangle(const point &location, int width, int height) : location(location),
                                                              size(width, height)
    {
    }

    rectangle(int x, int y, const dimension &size) : location(x, y),
                                                     size(size)
    {
    }

    rectangle(int x, int y, int width, int height) : location(x, y),
                                                     size(width, height)
    {
    }

    int get_x() const
    {
        return this->location.get_x();
    }

    int get_y() const
    {
        return this->location.get_y();
    }

    int get_width() const
    {
        return this->size.get_width();
    }

    int get_height() const
    {
        return this->size.get_height();
    }

    const point &get_location() const
    {
        return this->location;
    }

    const dimension &get_size() const
    {
        return this->size;
    }
}; /*rectangle*/

enum class cache_policy
{

}; /*cache_policy*/

template <class TKey, class TData>
class cache
{
  private:
    std::unordered_map<TKey, TData> data;
    int max_size;
    util::cache_policy cache_policy;
}; /*cache*/

int hex4ToNumber(const char *);

int hexToNumber(char);

double clock_to_ms(clock_t);

double clock_to_seconds(clock_t);

std::string read_file(const std::string &file);

bool try_read_file(const std::string &file, std::string &buf);

void write_file(const std::string &file, const std::string &data);

void write_file(const std::string &path, const std::vector<std::string &> data);

bool try_write_file(const std::string &file, const std::string &data);

bool try_write_file(const std::string &path, const std::vector<std::string &> data);

template <class T>
int printr(const T &obj)
{
    std::stringstream stream;

    stream << obj << std::endl;

    return std::printf("%s", stream.str().c_str());
}

template <class T>
int printp(const T *obj)
{
    std::stringstream stream;

    obj->operator<<(stream);

    stream << std::endl;

    return std::printf("%s", stream.str().c_str());
}

class exception : public std::exception
{
  private:
    std::string msg;

  public:
    exception();
    exception(const std::string &msg);

    virtual const char *what() const throw();

    virtual const std::string &get_message() const;
};

class index_out_of_range_exception : util::exception
{
  public:
    index_out_of_range_exception();
    index_out_of_range_exception(int index, int max);
    index_out_of_range_exception(int index, int max, const std::string &custom_msg);
};

class missing_key_exception : util::exception
{
  public:
    missing_key_exception();
    missing_key_exception(const std::string &key);
    missing_key_exception(const std::string &key, const std::string &custom_msg);
};

class file_not_found_exception : util::exception
{
  public:
    file_not_found_exception();
    file_not_found_exception(const std::string &path);
    file_not_found_exception(const std::string &path, const std::string &custom_msg);
};

std::string format(const std::string &format, ...);

template <class T>
std::string to_string(const T &arg)
{
    std::stringstream s;

    s << arg;

    return s.str();
}

template <class TStruct, class TArg1>
TStruct init_struct(TArg1 arg1)
{
    TStruct res = {arg1};

    return res;
}

class args
{
  public:
    args(int argc, char **argv);

    bool next(std::string &target);
    bool next_int(int &target);
    bool next_uint(uint &target);
    const std::string &current();
    bool has_next() const;
    bool has_next_int() const;
    bool has_next_uint() const;
    bool peek(std::string &target) const;

  private:
    int m_pos;
    int m_argc;
    char **m_argv;
    std::string m_last;

    bool next();
};

std::string &to_lower(std::string &nameBuf);

std::string to_lower(const std::string &nameBuf);

std::string &to_upper(std::string &nameBuf);

std::string to_upper(const std::string &nameBuf);

// Teilt einen String zwischen den Vorkommen von Kommata auf.
std::vector<std::string> split(const std::string &str);

std::vector<std::string> split(const std::string &str, char seperator);

std::vector<std::string> split(const std::string &str, char seperator[]);

// Versucht, den gegebenen String in eine ganze Zahl umzuwandeln.
// Gibt true zurück, wenn die Umwandlung erfolgreich war, sonst false.
// Der umgewandelte Wert wird in target geschrieben.
template <typename NumT>
bool parse_integral(const std::string &text, NumT &target)
{
    try
    {
        target = (NumT)std::stol(text);
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }

    return true;
}

// Versucht, den gegebenen String in eine Gleitkommazahl umzuwandeln.
// Gibt true zurück, wenn die Umwandlung erfolgreich war, sonst false.
// Der umgewandelte Wert wird in target geschrieben.
template <typename NumT>
bool parse_float(const std::string &text, NumT &target)
{
    try
    {
        target = (NumT)std::stod(text);
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }

    return true;
}

} // namespace util

#endif /*DATA_HPP*/