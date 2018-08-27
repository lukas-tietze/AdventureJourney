#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace util
{

namespace error_codes
{
    const std::string &get_message(int error_code);    
};

class exception : public std::exception
{
  private:
    std::string msg;
    int error_code;

  public:
    exception();
    exception(int);
    exception(const std::string &);
    exception(int, const std::string &);

    virtual const char *what() const throw();
    virtual const std::string &get_message() const;
    int get_error_code() const;
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

class invalid_case_exception : util::exception
{
  public:
    invalid_case_exception();
    invalid_case_exception(const std::string &which);
    invalid_case_exception(const std::string &which, const std::string &custom_msg);
};
} // namespace util

#endif /*EXCEPTION_HPP*/