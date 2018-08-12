#ifndef JSON_HPP
#define JSON_HPP

#include <string>
#include <vector>
#include <stack>
#include <iostream>

#include "data.hpp"

namespace json
{
constexpr auto ValueTrue = "true";
constexpr auto ValueFalse = "false";
constexpr auto ValueNull = "null";

enum class value_type
{
    String,
    Number,
    Object,
    Array,
    True,
    False,
    Null,
};

class formatted_printer;

class node
{
  private:
    std::string name;

  public:
    node(const std::string &name);
    node();
    virtual ~node();

    const std::string &get_name() const;
    void set_name(const std::string &name);

    virtual value_type get_type() const = 0;

    virtual const std::string &get_value_as_string() const = 0;
    virtual double get_value_as_number() const = 0;
    virtual const node *get_value_as_object() const = 0;
    virtual const std::vector<node *> &get_value_as_array() const = 0;

    virtual const node *find_child(const std::string &name) = 0;

    virtual std::ostream &operator<<(std::ostream &stream) const;
    virtual json::formatted_printer &print_formatted(json::formatted_printer &) const;
};

class object_node : public node
{
  private:
    std::unordered_map<std::string, node *> children;

  public:
    object_node(const std::string &name);
    object_node();
    ~object_node();

    value_type get_type() const;

    const std::string &get_value_as_string() const;
    double get_value_as_number() const;
    const node *get_value_as_object() const;
    const std::vector<node *> &get_value_as_array() const;

    const node *find_child(const std::string &name);

    void add_child(json::node *node);

    virtual std::ostream &operator<<(std::ostream &stream) const;
    virtual json::formatted_printer &print_formatted(json::formatted_printer &) const;
};

class array_node : public node
{
  private:
    std::vector<node *> children;

  public:
    array_node(const std::string &name);
    array_node();
    ~array_node();

    value_type get_type() const;

    const std::string &get_value_as_string() const;
    double get_value_as_number() const;
    const node *get_value_as_object() const;
    const std::vector<node *> &get_value_as_array() const;

    const node *find_child(const std::string &name);

    void add_child(json::node *node);

    virtual std::ostream &operator<<(std::ostream &stream) const;
    virtual json::formatted_printer &print_formatted(json::formatted_printer &) const;
};

class primitive_node : public node
{
  private:
    std::string string_value;
    double numeric_value;
    json::value_type type;

    void clear_values();

  public:
    primitive_node(const std::string &name);
    primitive_node();
    ~primitive_node();

    value_type get_type() const;

    const std::string &get_value_as_string() const;
    double get_value_as_number() const;
    const node *get_value_as_object() const;
    const std::vector<node *> &get_value_as_array() const;

    const node *find_child(const std::string &name);

    void set_value(bool value);
    void set_value_null();
    void set_value(const std::string &stringValue);
    void set_value(double doubleValue);
    void set_value(node *nodeValue);

    virtual std::ostream &operator<<(std::ostream &stream) const;
    virtual json::formatted_printer &print_formatted(json::formatted_printer &) const;
};

class value_exception : public util::exception
{
  public:
    value_exception();
    value_exception(const std::string &msg);
};

class operation_exception : public util::exception
{
  public:
    operation_exception();
    operation_exception(const std::string &msg);
};

enum class token_type
{
    String,
    Number,
    ArrayStart,
    ArrayEnd,
    ObjectStart,
    ObjectEnd,
    ValueAssignment,
    ValueSeperator,
    ValueTrue,
    ValueFalse,
    ValueNull,
};

struct token
{
    token_type type;
    const char *data;
    int data_len;

    friend std::ostream &operator<<(std::ostream &, const token &);
};

std::ostream &operator<<(std::ostream &, const token &);
std::ostream &operator<<(std::ostream &, const token_type &);

class tokenizer
{
  private:
    std::vector<token> tokens;
    std::stack<char> bracket_stack;
    int pos;
    int length;
    const char *data;

    bool is_start_of_number(char);
    void read_next();
    void read_number();
    void read_string();
    void skip_whitespace();
    bool can_escape(char);
    bool is_start_of_special(char);
    void read_special();
    bool is_valid_number_end(char);

  public:
    tokenizer();
    ~tokenizer();

    const std::vector<token> &tokenize(const std::string &data);
    const std::vector<token> &tokenize(const char *data, int length);
};

class parser
{
  public:
    parser();
    ~parser();

    void parse(const std::string &, node **);

    class parser_exception : public util::exception
    {
      public:
        parser_exception();
        parser_exception(const std::string &msg);
    };

  private:
    std::stack<node *> nodeStack;
    std::vector<json::token> working_set;
    std::vector<json::token>::const_iterator pos;

    bool has_next() const;
    json::token_type peek_type() const;
    node *parse(const std::vector<token> &tokens);
    json::token read_token(json::token_type type);

    node *read_start();
    node *read_value();
    node *read_object();
    node *read_array();
    node *read_item();
    std::string read_string();
    double read_number();
};

class i_json_mappable
{
  public:
    void *map(const std::string &name, json::value_type type);
};

class json_mapper : protected json::parser
{
  public:
    json_mapper();

    void map(const std::string &, i_json_mappable *);
};

class formatted_printer
{
  private:
    std::string indent;
    std::string indent_template;
    int indent_level;
    std::stringstream buf;

  public:
    formatted_printer();
    formatted_printer(bool useTabs);
    formatted_printer(int indentLength);
    formatted_printer(int indentLength, bool useTabs);
    formatted_printer(const std::string &indentTemplate);

    formatted_printer &begin_indent();
    formatted_printer &end_indent();
    formatted_printer &begin_array();
    formatted_printer &end_array();
    formatted_printer &begin_object();
    formatted_printer &end_object();
    formatted_printer &print_property(const std::string &names);
    formatted_printer &next_property();
    formatted_printer &new_line();
    formatted_printer &print(const std::string &);
    formatted_printer &print(double);
    formatted_printer &print_false();
    formatted_printer &print_true();
    formatted_printer &print_null();

    std::string to_string();

    std::ostream &operator<<(std::ostream &) const;
};
} // namespace json

#endif /*JSON_HPP*/