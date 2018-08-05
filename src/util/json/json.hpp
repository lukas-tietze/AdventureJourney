#ifndef JSON_HPP
#define JSON_HPP

#include <string>
#include <vector>
#include "util/util.hpp"

namespace json
{
enum class value_type
{
    String,
    Number,
    Object,
    Array,
    BOOL_TRUE,
    BOOL_FALSE,
    EMPTY,
};

class parser
{
  public:
    parser();
    ~parser();

    node parse(const std::string &data);

  private:
    enum class token_type
    {
        String,
        Number,
        ArrayStart,
        ArrayEnd,
        ObjectStart,
        ObjectEnd,
        ObjectAssignment,
    };

    struct token
    {
        token_type type;
        char *data;
        int data_len;
    };

    class tokenizer
    {
      private:
        std::vector<token> tokens;
        std::stack<char> bracket_stack;
        int pos;
        int length;
        char *data;      

        bool is_start_of_number(char);
        char escape_char(char);
        void read_next();
        void read_number();
        void read_string();
        void skip_whitespace();

      public:
        tokenizer();
        ~tokenizer();

        const std::vector<token> &tokenize(const char *data, int length);
    };
};

class node
{
  private:
    const std::string name;

  public:
    node(const std::string &name);
    virtual ~node();

    const std::string &name();

    virtual value_type type() const = 0;

    virtual const std::string &value_as_string() const = 0;
    virtual double value_as_number() const = 0;
    virtual node value_as_object() const = 0;
    virtual const std::vector<node> &value_as_array() const = 0;

    virtual const node *find_child(const std::string &name) = 0;
};
} // namespace json

#endif /*JSON_HPP*/