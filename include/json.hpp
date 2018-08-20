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

std::ostream &operator<<(std::ostream &, const value_type &);

class formatted_printer;

class i_json_mappable
{
  public:
    virtual ~i_json_mappable();

    virtual void *map(const std::string &name, json::value_type type) = 0;
};

class node
{
  public:
    virtual ~node();

    virtual value_type get_type() const = 0;

    virtual std::ostream &operator<<(std::ostream &stream) const;
    virtual json::formatted_printer &print_formatted(json::formatted_printer &) const = 0;
};

class object_node : public node
{
  private:
    std::unordered_map<std::string, node *> children;

  public:
    object_node();
    ~object_node();

    value_type get_type() const;

    void put(const std::string &, const std::string &);
    void put(const std::string &, double);
    void put(const std::string &, bool);
    void put(const std::string &, json::node *);
    void put_null(const std::string &);

    bool has_child(const std::string &name) const;
    int get_child_count() const;
    json::node *get(const std::string &name);
    const json::node *get(const std::string &name) const;
    bool try_get(const std::string &name, json::node *&) const;

    typedef std::unordered_map<std::string, json::node *>::const_iterator const_child_iterator;
    typedef std::unordered_map<std::string, json::node *>::iterator child_iterator;

    child_iterator begin();
    const_child_iterator begin() const;

    child_iterator end();
    const_child_iterator end() const;

    virtual std::ostream &operator<<(std::ostream &stream) const;
    virtual json::formatted_printer &print_formatted(json::formatted_printer &) const;
};

class array_node : public node
{
  private:
    std::vector<node *> children;

  public:
    array_node();
    ~array_node();

    value_type get_type() const;

    void put(const std::string &);
    void put(double);
    void put(bool);
    void put(json::node *);
    void put_null();
    void insert(uint at, const std::string &);
    void insert(uint at, double);
    void insert(uint at, bool);
    void insert(uint at, json::node *);
    void insert_null(uint at);

    int get_child_count();
    json::node *get(uint index);
    const json::node *get(uint index) const;
    bool try_get(uint index, json::node *&) const;

    typedef std::vector<node *>::const_iterator const_child_iterator;
    typedef std::vector<node *>::iterator child_iterator;

    child_iterator begin();
    const_child_iterator begin() const;

    child_iterator end();
    const_child_iterator end() const;

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
    primitive_node(const std::string &value);
    primitive_node(bool value);
    primitive_node(double value);
    primitive_node();
    ~primitive_node();

    value_type get_type() const;

    const std::string &get_value_as_string() const;
    double get_value_as_number() const;
    bool get_value_as_bool() const;
    bool is_value_null() const;

    void set_value(bool value);
    void set_value(const std::string &stringValue);
    void set_value(double doubleValue);
    void set_value_null();

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

class parser_exception : public util::exception
{
  public:
    parser_exception();
    parser_exception(const std::string &msg);
};

class parser
{
  public:
    parser();
    ~parser();

    void parse(const std::string &, node *&);

  private:
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

class formatted_printer
{
  private:
    std::string indent;
    std::string indent_template;
    int indent_level;
    std::iostream *out;
    bool out_is_managed;
    bool value_written;

    formatted_printer &begin_indent();
    formatted_printer &end_indent();
    formatted_printer &next_property();
    formatted_printer &indent_property();

  public:
    formatted_printer();
    formatted_printer(bool useTabs);
    formatted_printer(int indentLength);
    formatted_printer(int indentLength, bool useTabs);
    formatted_printer(const std::string &indentTemplate);
    formatted_printer(std::iostream *);
    formatted_printer(std::iostream *, bool useTabs);
    formatted_printer(std::iostream *, int indentLength);
    formatted_printer(std::iostream *, int indentLength, bool useTabs);
    formatted_printer(std::iostream *, const std::string &indentTemplate);

    ~formatted_printer();

    formatted_printer &begin_array();
    formatted_printer &end_array();
    formatted_printer &begin_object();
    formatted_printer &end_object();
    formatted_printer &print_property(const std::string &names);
    formatted_printer &print(const std::string &);
    formatted_printer &print(double);
    formatted_printer &print_false();
    formatted_printer &print_true();
    formatted_printer &print_null();

    formatted_printer &print(json::node *);

    const std::string &get_indent_template() const;
    uint get_indent_length() const;
    const std::iostream *get_output() const;

    bool is_independent() const;
    std::string to_string() const;
    std::ostream &operator<<(std::ostream &) const;
};
} // namespace json

#endif /*JSON_HPP*/