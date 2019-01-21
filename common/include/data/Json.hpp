#pragma once

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <unordered_map>

#include "Defs.hpp"
#include "Exception.hpp"

namespace json
{
constexpr auto ValueTrue = "true";
constexpr auto ValueFalse = "false";
constexpr auto ValueNull = "null";

enum class ValueType
{
    String,
    Number,
    Object,
    Array,
    True,
    False,
    Null,
};

std::ostream &operator<<(std::ostream &, const ValueType &);

class FormattedPrinter;

class Node
{
  public:
    virtual ~Node();

    virtual ValueType GetType() const = 0;

    virtual std::ostream &operator<<(std::ostream &stream) const;
    virtual json::FormattedPrinter &PrintFormatted(json::FormattedPrinter &) const = 0;

    virtual bool operator==(const Node &other) const = 0;
    virtual bool operator!=(const Node &other) const = 0;
};

class ObjectNode final : public Node
{
  private:
    std::vector<std::pair<std::string, Node *>> children;
    std::unordered_map<std::string, int> quickAccess;

  public:
    ObjectNode();
    ~ObjectNode();

    ValueType GetType() const;

    void Put(const std::string &, const std::string &);
    void Put(const std::string &, const char *);
    void Put(const std::string &, double);
    void Put(const std::string &, int);
    void Put(const std::string &, bool);
    void Put(const std::string &, json::Node *);
    void PutNull(const std::string &);

    bool HasChild(const std::string &name) const;
    int GetChildCount() const;
    json::Node *Get(const std::string &name);
    const json::Node *Get(const std::string &name) const;
    bool TryGet(const std::string &name, json::Node *&) const;

    template <class T>
    bool TryGetAs(const std::string &name, T *&out) const
    {
        Node *item;

        return this->TryGet(name, item) &&
               item != nullptr &&
               (out = dynamic_cast<T *>(item)) != nullptr;
    }

    template <class T>
    bool TryGetAs(const std::string &name, T *&out, ValueType exactType) const
    {
        Node *item;

        return this->TryGet(name, item) &&
               item != nullptr &&
               item->GetType() == exactType &&
               (out = dynamic_cast<T *>(item)) != nullptr;
    }

    typedef std::vector<std::pair<std::string, Node *>>::iterator ChildIterator;
    typedef std::vector<std::pair<std::string, Node *>>::const_iterator ConstChildIterator;

    ChildIterator begin();
    ConstChildIterator begin() const;

    ChildIterator end();
    ConstChildIterator end() const;

    std::ostream &operator<<(std::ostream &stream) const;
    json::FormattedPrinter &PrintFormatted(json::FormattedPrinter &) const;

    bool operator==(const Node &other) const;
    bool operator!=(const Node &other) const;
};

class ArrayNode final : public Node
{
  private:
    std::vector<Node *> children;

  public:
    ArrayNode();
    ~ArrayNode();

    ValueType GetType() const;

    void Put(const std::string &);
    void Put(const char *);
    void Put(double);
    void Put(int);
    void Put(bool);
    void Put(json::Node *);
    void PutNull();
    void Insert(uint at, const std::string &);
    void Insert(uint at, const char *);
    void Insert(uint at, double);
    void Insert(uint at, int);
    void Insert(uint at, bool);
    void Insert(uint at, json::Node *);
    void InsertNull(uint at);

    int GetChildCount() const;
    json::Node *Get(uint index);
    const json::Node *Get(uint index) const;
    bool TryGet(uint index, json::Node *&) const;

    template <class T>
    bool TryGetAs(uint index, T *&out) const
    {
        Node *item;

        return this->TryGet(index, item) &&
               item != nullptr &&
               (out = dynamic_cast<T *>(item)) != nullptr;
    }

    template <class T>
    bool TryGetAs(uint index, T *&out, ValueType exactType) const
    {
        Node *item;

        return this->TryGet(index, item) &&
               item != nullptr &&
               item->GetType() == exactType &&
               (out = dynamic_cast<T *>(item)) != nullptr;
    }

    typedef std::vector<Node *>::const_iterator ConstChildIterator;
    typedef std::vector<Node *>::iterator ChildIterator;

    ChildIterator begin();
    ConstChildIterator begin() const;

    ChildIterator end();
    ConstChildIterator end() const;

    std::ostream &operator<<(std::ostream &stream) const;
    json::FormattedPrinter &PrintFormatted(json::FormattedPrinter &) const;

    bool operator==(const Node &other) const;
    bool operator!=(const Node &other) const;
};

class PrimitiveNode final : public Node
{
  private:
    std::string stringValue;
    double numericValue;
    json::ValueType type;

    void ClearValues();

  public:
    PrimitiveNode(const std::string &);
    PrimitiveNode(const char *);
    PrimitiveNode(bool);
    PrimitiveNode(double);
    PrimitiveNode(int);
    PrimitiveNode();
    ~PrimitiveNode();

    ValueType GetType() const;

    const std::string &GetValueAsString() const;
    double GetValueAsNumber() const;
    bool GetValueAsBool() const;
    bool IsValueNull() const;

    bool TryGetValueAsString(std::string &) const;
    bool TryGetValueAsNumber(double &) const;
    bool TryGetValueAsBool(bool &) const;

    bool TryGetValueAsStringOrDefault(std::string &, const std::string &defaultValue = "") const;
    bool TryGetValueAsNumberOrDefault(double &, double defaultValue = 0) const;
    bool TryGetValueAsBoolOrDefault(bool &, bool defaultValue = false) const;

    void SetValue(bool value);
    void SetValue(const std::string &stringValue);
    void SetValue(double doubleValue);
    void SetValueNull();

    std::ostream &operator<<(std::ostream &stream) const;
    json::FormattedPrinter &PrintFormatted(json::FormattedPrinter &) const;

    bool operator==(const Node &other) const;
    bool operator!=(const Node &other) const;
};

class IJsonSerializable
{
  public:
    virtual ~IJsonSerializable();

    virtual Node *Serialize() = 0;
    virtual void Deserialize(const Node *) = 0;
};

class ValueException : public util::Exception
{
  public:
    ValueException();
    ValueException(const std::string &msg);
};

class OperationException : public util::Exception
{
  public:
    OperationException();
    OperationException(const std::string &msg);
};

enum class TokenType
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

struct Token
{
    TokenType type;
    const char *data;
    int dataLen;
};

std::ostream &operator<<(std::ostream &, const json::Token &);
std::ostream &operator<<(std::ostream &, const json::TokenType &);
std::ostream &operator<<(std::ostream &, const json::ValueType &);

class Tokenizer
{
  private:
    std::vector<Token> tokens;
    std::stack<char> bracketStack;
    int pos;
    int length;
    const char *data;

    bool IsStartOfNumber(char);
    void ReadNext();
    void ReadNumber();
    void ReadString();
    void SkipWhitespace();
    bool CanEscape(char);
    bool IsStartOfSpecial(char);
    void ReadSpecial();
    bool IsValidNumberEnd(char);

  public:
    Tokenizer();
    ~Tokenizer();

    int GetPos() const;
    const char *GetData() const;
    int GetLength() const;

    const std::vector<Token> &Tokenize(const std::string &data);
    const std::vector<Token> &Tokenize(const char *data, int length);
};

class TokenizerException : public util::Exception
{
  public:
    TokenizerException();
    TokenizerException(const Tokenizer &);
    TokenizerException(const Tokenizer &, const std::string &message);
};

class ParserException : public util::Exception
{
  public:
    ParserException();
    ParserException(const std::string &msg);
};

class Parser
{
  public:
    Parser();
    ~Parser();

    void parse(const std::string &, Node *&);

  private:
    std::vector<json::Token> workingSet;
    std::vector<json::Token>::const_iterator pos;

    bool HasNext() const;
    json::TokenType PeekType() const;
    Node *Parse(const std::vector<Token> &tokens);
    json::Token ReadToken(json::TokenType type);

    Node *ReadStart();
    Node *ReadValue();
    Node *ReadObject();
    Node *ReadArray();
    Node *ReadItem();
    std::string ReadString();
    double ReadNumber();
};

class FormattedPrinter
{
  private:
    std::string indent;
    std::string indentTemplate;
    int indentLevel;
    std::iostream *out;
    bool outIsManaged;
    bool printCompact;

    bool valueWritten;

    FormattedPrinter &BeginIndent();
    FormattedPrinter &EndIndent();
    FormattedPrinter &NextProperty();
    FormattedPrinter &IndentProperty();

  public:
    FormattedPrinter();
    FormattedPrinter(bool useTabs);
    FormattedPrinter(int indentLength);
    FormattedPrinter(int indentLength, bool useTabs);
    FormattedPrinter(const std::string &indentTemplate);
    FormattedPrinter(std::iostream *);
    FormattedPrinter(std::iostream *, bool useTabs);
    FormattedPrinter(std::iostream *, int indentLength);
    FormattedPrinter(std::iostream *, int indentLength, bool useTabs);
    FormattedPrinter(std::iostream *, const std::string &indentTemplate);

    ~FormattedPrinter();

    FormattedPrinter &BeginArray();
    FormattedPrinter &EndArray();
    FormattedPrinter &BeginObject();
    FormattedPrinter &EndObject();
    FormattedPrinter &PrintProperty(const std::string &names);
    FormattedPrinter &Print(const std::string &);
    FormattedPrinter &Print(double);
    FormattedPrinter &PrintFalse();
    FormattedPrinter &PrintTrue();
    FormattedPrinter &PrintNull();

    FormattedPrinter &Print(json::Node *);

    const std::string &GetIndentTemplate() const;
    uint GetIndentLength() const;
    const std::iostream *GetOutput() const;

    void SetCompactStyle(bool);
    bool IsCompactStyle() const;

    bool IsIndependent() const;
    std::string ToString() const;
    std::ostream &operator<<(std::ostream &) const;
};
} // namespace json