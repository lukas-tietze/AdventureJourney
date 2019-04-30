#include <iostream>
#include <sstream>
#include <ios>

#include "data/Json.hpp"

json::FormattedPrinter::FormattedPrinter() : FormattedPrinter(nullptr)
{
}

json::FormattedPrinter::FormattedPrinter(bool useTabs) : FormattedPrinter(nullptr, useTabs)
{
}

json::FormattedPrinter::FormattedPrinter(int indentLength) : FormattedPrinter(nullptr, indentLength)
{
}

json::FormattedPrinter::FormattedPrinter(int indentLength, bool useTabs) : FormattedPrinter(nullptr, indentLength, useTabs)
{
}

json::FormattedPrinter::FormattedPrinter(const std::string &indentTemplate) : FormattedPrinter(nullptr, indentTemplate)
{
}

json::FormattedPrinter::FormattedPrinter(std::iostream *stream) : FormattedPrinter(stream, 4)
{
}

json::FormattedPrinter::FormattedPrinter(std::iostream *stream, bool useTabs) : FormattedPrinter(stream, useTabs ? 1 : 4, useTabs)
{
}

json::FormattedPrinter::FormattedPrinter(std::iostream *stream, int indentLength) : FormattedPrinter(stream, std::string(indentLength, ' '))
{
}

json::FormattedPrinter::FormattedPrinter(std::iostream *stream, int indentLength, bool useTabs) : FormattedPrinter(stream, useTabs ? std::string(indentLength, ' ') : std::string(indentLength, '\t'))
{
}

json::FormattedPrinter::FormattedPrinter(std::iostream *stream, const std::string &indentTemplate) : indent(""),
                                                                                                       indentTemplate(indentTemplate),
                                                                                                       indentLevel(0),
                                                                                                       out(stream),
                                                                                                       outIsManaged(stream == nullptr),
                                                                                                       valueWritten(false),
                                                                                                       printCompact(false)
{
    if (this->out == nullptr)
    {
        this->out = new std::stringstream(std::ios_base::openmode::out);
    }
    else
    {
        this->out = stream;
    }
}

json::FormattedPrinter::~FormattedPrinter()
{
    if (this->outIsManaged)
    {
        delete this->out;
    }
}

json::FormattedPrinter &json::FormattedPrinter::BeginIndent()
{
    this->indentLevel++;
    this->indent.append(this->indentTemplate);
    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::EndIndent()
{
    if (this->indentLevel > 0)
    {
        this->indentLevel--;
        this->indent.erase(this->indentLevel * 2, this->indentTemplate.length());
    }

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::BeginArray()
{
    this->NextProperty();

    if (this->valueWritten && !this->printCompact)
        (*this->out) << this->indent;

    (*this->out) << '[';

    this->BeginIndent();

    if (!this->printCompact)
        (*this->out) << std::endl
                     << this->indent;

    this->valueWritten = false;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::EndArray()
{
    this->EndIndent();

    if (!this->printCompact)
        (*this->out) << std::endl
                     << this->indent;

    (*this->out) << ']';
    this->valueWritten = true;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::BeginObject()
{
    this->NextProperty();

    if (this->valueWritten && !this->printCompact)
        (*this->out) << this->indent;

    (*this->out) << '{';

    this->BeginIndent();

    if (!this->printCompact)
        (*this->out) << std::endl;

    this->valueWritten = false;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::EndObject()
{
    this->EndIndent();
    if (!this->printCompact)
        (*this->out) << std::endl
                     << this->indent;
    (*this->out) << '}';
    this->valueWritten = true;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::PrintProperty(const std::string &name)
{
    this->NextProperty();
    if (!this->printCompact)
        (*this->out) << this->indent;

    (*this->out) << '"' << name << "\":";

    if (!this->printCompact)
        (*this->out) << ' ';

    this->valueWritten = false;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::NextProperty()
{
    if (this->valueWritten)
    {
        (*this->out) << ',';

        if (!this->printCompact)
            (*this->out) << std::endl;
    }

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::IndentProperty()
{
    if (this->valueWritten && !this->printCompact)
    {
        (*this->out) << this->indent;
    }

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::Print(const std::string &s)
{
    this->NextProperty();
    this->IndentProperty();
    (*this->out) << '"' << s << '"';
    this->valueWritten = true;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::Print(double d)
{
    this->NextProperty();
    this->IndentProperty();
    (*this->out) << d;
    this->valueWritten = true;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::PrintFalse()
{
    this->NextProperty();
    this->IndentProperty();
    (*this->out) << json::ValueFalse;
    this->valueWritten = true;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::PrintTrue()
{
    this->NextProperty();
    this->IndentProperty();
    (*this->out) << json::ValueTrue;
    this->valueWritten = true;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::PrintNull()
{
    this->NextProperty();
    this->IndentProperty();
    (*this->out) << json::ValueNull;
    this->valueWritten = true;

    return *this;
}

json::FormattedPrinter &json::FormattedPrinter::Print(json::Node *n)
{
    n->PrintFormatted(*this);

    return *this;
}

std::string json::FormattedPrinter::ToString() const
{
    if (this->outIsManaged)
    {
        return (static_cast<std::stringstream *>(this->out))->str();
    }

    return std::string();
}

std::ostream &json::FormattedPrinter::operator<<(std::ostream &s) const
{
    if (this->outIsManaged)
    {
        s << (static_cast<std::stringstream *>(this->out))->str();
    }

    return s;
}

const std::string &json::FormattedPrinter::GetIndentTemplate() const
{
    return this->indentTemplate;
}

uint json::FormattedPrinter::GetIndentLength() const
{
    return this->indentTemplate.length();
}

const std::iostream *json::FormattedPrinter::GetOutput() const
{
    return this->out;
}

bool json::FormattedPrinter::IsIndependent() const
{
    return this->outIsManaged;
}

void json::FormattedPrinter::SetCompactStyle(bool printCompact)
{
    this->printCompact = printCompact;
}

bool json::FormattedPrinter::IsCompactStyle() const
{
    return this->printCompact;
}
