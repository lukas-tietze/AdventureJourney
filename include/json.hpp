#ifndef JSON_HPP
#define JSON_HPP

#include <string>
#include <vector>
#include <stack>
#include "data.hpp"

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

class node
{
  private:
    const std::string name;

  public:
    node(const std::string &name);
    virtual ~node();

    const std::string &get_name();

    virtual value_type get_type() const = 0;

    virtual const std::string &get_value_as_string() const = 0;
    virtual double get_value_as_number() const = 0;
    virtual const node *get_value_as_object() const = 0;
    virtual const std::vector<node> &get_value_as_array() const = 0;

    virtual const node *find_child(const std::string &name) = 0;
};

class parser
{
  public:
    parser();
    ~parser();

    void parse(const std::string &data, node **target);

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
        ObjectSeperator,
        ValueTrue,
        ValueFalse,
        ValueNull,
    };

    struct token
    {
        token_type type;
        const char *data;
        int data_len;
    };

    class tokenizer
    {
      private:
        std::vector<token> tokens;
        std::stack<char> bracket_stack;
        int pos;
        int length;
        const char *data;      

        bool is_start_of_number(char);
        char escape_char(char);
        void read_next();
        void read_number();
        void read_string();
        void skip_whitespace();
        bool can_escape(char);
        bool is_start_of_special(char);
        void read_special();

      public:
        tokenizer();
        ~tokenizer();

        const std::vector<token> &tokenize(const char *data, int length);
    };
};
} // namespace json

#endif /*JSON_HPP*/