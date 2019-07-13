#include "Calculator.hpp"

#include <unordered_map>
#include <iostream>

#include "data/String.hpp"
#include "datetime/Timer.hpp"

namespace
{
bool AsTruthValue(const std::string &s)
{
    auto lower = util::ToLower(s);

    return lower == "yes" || lower == "y" || lower == "on";
}
} // namespace

calculator::ScriptingEngine::Action::Action()
{
}

calculator::ScriptingEngine::Action::Action(const std::string &name,
                                            const std::string &alias,
                                            const std::string &description,
                                            action_t action) : name(name),
                                                               alias(alias),
                                                               description(description),
                                                               action(action)
{
}

bool calculator::ScriptingEngine::Action::HasDesciption() const
{
    return this->description.empty();
}

bool calculator::ScriptingEngine::Action::HasAlias() const
{
    return !this->alias.empty();
}

calculator::ScriptingEngine::ScriptingEngine() : uniqeActions{
                                                     Action("tokenize", "t", "Prints the list of tokens of the expression.", &calculator::ScriptingEngine::Tokenize),
                                                     Action("parse", "p", "Parses the expression and prints the created postfix expression.", &calculator::ScriptingEngine::Parse),
                                                     Action("def", "d", "Evaluates the given expression and defines a variable, which value is the result of the evaluation.", &calculator::ScriptingEngine::DefineVar),
                                                     Action("exp", "e", "Defines a variable that contains the given expression.", &calculator::ScriptingEngine::DefineExp),
                                                     Action("undef", "ud", "Removes a variable.", &calculator::ScriptingEngine::Undefine),
                                                     Action("quit", "q", "Quit the application.", &calculator::ScriptingEngine::Quit),
                                                     Action("solve", "s", "Evaluates the expression and prints the result.", &calculator::ScriptingEngine::Solve),
                                                     Action("load", "ld", "load a file from the specified path and interpret each line as a command.", &calculator::ScriptingEngine::LoadFile),
                                                     Action("err", "|", "Changes the error stream to the specified file. util :err <std> to print to console.", &calculator::ScriptingEngine::OpenErr),
                                                     Action("out", ">", "Changes the output stream to the specified file. Use :out <std> to print to console.", &calculator::ScriptingEngine::OpenOut),
                                                     Action("in", "<", "Changes the input stream. Use :in <std> to use the console.", &calculator::ScriptingEngine::OpenIn),
                                                     Action("dir", "cd", "Changes the to specified directory and prints the current directory.", &calculator::ScriptingEngine::ChangeDir),
                                                     Action("echo", "#", "Use on, off to enable or disable echoing of commands", &calculator::ScriptingEngine::SetEcho),
                                                     Action("useAns", "ans", " use on, off to enable or disable the ANS-Variable. If enablad the result of the last calculation will be saved in a variable named ANS", &calculator::ScriptingEngine::UseAns),
                                                     Action("clear", "cl", "Clears the screen.", &calculator::ScriptingEngine::ClearOut),
                                                     Action("files", "ls", "List all Files and directories in the current directory.", &calculator::ScriptingEngine::ListFiles),
                                                     Action("clearvars", "clv", "Delete all variables, except e and pi. Use :clearvars all to also delete e and pi.", &calculator::ScriptingEngine::ClearVars),
                                                     Action("help", "h", "Prints the help.", &calculator::ScriptingEngine::ShowHelp),
                                                     Action("diagnostic", "dg", "Set diagnostic-Output to the specified stream.", &calculator::ScriptingEngine::SetDiagnosticOut),
                                                 }
{
    //TODO: Nicht Threadsafe -> Threadsafe wird an dieser Stelle aber auch nicht unbedingt benötigt!
    for (const auto &action : ScriptingEngine::uniqeActions)
    {
        this->actions.insert(std::make_pair(action.name, action));

        if (action.HasAlias())
            this->actions.insert(std::make_pair(action.alias, action));
    }
}

void calculator::ScriptingEngine::Quit(const std::string &)
{
    this->loop = false;
}

void calculator::ScriptingEngine::Eval(const std::string &input)
{
    if (input.empty())
    {
        this->diagnostic.WriteLine("Empty Input.");
        return;
    }

    if (this->echo)
    {
        this->out.WriteLine(input);
    }

    util::Timer timer;
    timer.Start();

    try
    {
        if (util::StartsWith(input, ":"))
        {
            std::string command;
            std::string expression;

            util::SplitKeyValue(input, command, expression);

            auto actionKvp = this->actions.find(command.substr(1));

            if (actionKvp == this->actions.end())
                this->HandleUndefinedCommand(command);
            else
                ((*this).*(actionKvp->second.action))(expression);
        }
        else
        {
            this->Solve(input);
        }
    }
    catch (util::Exception &e)
    {
        this->HandleException(e);
    }
    catch (std::exception &e)
    {
        this->HandleException(e);
    }

    timer.Stop();
    this->diagnostic.WriteLine("Evaluation of <%> took %ms.", input, timer.Elapsed());
}

void calculator::ScriptingEngine::ShowHelp(const std::string &expression)
{
    if (expression.empty())
    {
        this->out.WriteLine("---- Help ----");
        this->out.WriteLine("Type the expression you want to Calculate and press enter.");
        this->out.WriteLine("Lines with the syntax");
        this->out.WriteLine("\t:<command> <arg>");
        this->out.WriteLine("will be interpreted as commands, instead of calculations. (Not all commands require an argument)");
        this->out.WriteLine();
        this->out.WriteLine("Possible Commands are:");

        for (const auto &action : ScriptingEngine::uniqeActions)
        {
            if (action.HasAlias())
                this->out.WriteLine(action.alias);

            this->out.WriteLine("% - %", action.name, action.description);
        }
    }
    else if (this->calculator.GetConfig().GetVariable(expression) != nullptr)
    {
        this->out.WriteLine("% is a variable: %", expression, this->calculator.GetConfig().GetVariable(expression));
    }
    else if (this->calculator.GetConfig().GetFunction(expression) != nullptr)
    {
        this->out.WriteLine("% is a function: %", expression, this->calculator.GetConfig().GetFunction(expression));
    }
    // else if (this->calculator.GetConfig().GetOperator(expression) != nullptr)
    // {
    //     this->out.WriteLine("% is an operator: %", expression, this->calculator.GetConfig().GetOperator(expression));
    // }
    else if (this->actions.find(expression) != this->actions.end())
    {
        this->out.WriteLine("% is an command: %", expression, actions[expression].description);
    }
    else
    {
        this->out.WriteLine("There is no help topic for %. Use :help for general help and check your spelling.", expression);
    }
}

int calculator::ScriptingEngine::FindSimilarCommands(const std::string &command, std::vector<std::string> &out)
{
    int size = 0;

    for (const auto &kvp : this->actions)
    {
        const auto &existingCommand = kvp.first;

        if (existingCommand.find(command) != std::string::npos ||
            command.find(existingCommand) != std::string::npos ||
            util::OsaDistance(existingCommand, command) < 3)
        {
            out.push_back(existingCommand);
            size++;
        }
    }

    return size;
}

void calculator::ScriptingEngine::HandleUndefinedCommand(const std::string &command)
{
    if (command.empty())
    {
        this->out.WriteLine("Please enter a command! Or use :help to show a list of all commmands.");
    }
    else
    {
        this->out.WriteLine("Undefined command \"{0}\"", command);

        std::vector<std::string> similarCommands;

        if (FindSimilarCommands(command, similarCommands))
        {
            this->out.WriteLine("Possible similar commands:");

            for (const auto &match : similarCommands)
            {
                this->out.WriteLine("\t%", match);
            }
        }
    }
}

void calculator::ScriptingEngine::ListFiles(const std::string &)
{
    // TODO!
    // auto directories = Directory.GetDirectories(workingDirectory);
    // auto files = Directory.GetFiles(workingDirectory);

    // Array.Sort(directories);
    // Array.Sort(files);

    // foreach (auto directory in directories)
    // {
    //     this->out.WriteLine(Path.GetFileName(directory) + "/");
    // }

    // foreach (auto file in files)
    // {
    //     this->out.WriteLine(Path.GetFileName(file));
    // }
}

void calculator::ScriptingEngine::ChangeDir(const std::string &expression)
{
    if (!expression.empty())
    {
        // auto newDir = Path.GetFullPath(Path.Combine(workingDirectory, expression));

        // if (Directory.Exists(newDir))
        // {
        //     workingDirectory = newDir;
        // }
        // else
        // {
        //     context.Err.WriteLine("Can'tchange to {0}, Directory {1} doesn't exist", expression, newDir);
        // }
    }

    this->out.WriteLine("current directory is \"{0}\"", this->workingDirectory);
}

void calculator::ScriptingEngine::HandleException(const std::exception &e)
{
    util::err.WriteLine("!> Exception ocurred: %", e.what());
}

void calculator::ScriptingEngine::HandleException(const util::Exception &e)
{
    util::err.WriteLine("!> Exception ocurred: %", e.GetMessage());
}

void calculator::ScriptingEngine::UseAns(const std::string &expression)
{
    this->useAns = AsTruthValue(expression);
}

void calculator::ScriptingEngine::SetEcho(const std::string &expression)
{
    this->echo = AsTruthValue(expression);
}

void calculator::ScriptingEngine::ClearOut(const std::string &expression)
{
    //TODO...
}

void calculator::ScriptingEngine::SetDiagnosticOut(const std::string &expression)
{
    //TODO...
}

void calculator::ScriptingEngine::ClearVars(const std::string &expression)
{
    this->calculator.GetConfig().ClearVariables();
}

void calculator::ScriptingEngine::Undefine(const std::string &expression)
{
    if (expression.empty())
    {
        this->out.WriteLine("Requiring argument!");
    }

    this->calculator.GetConfig().RemoveVariable(util::ToLower(util::Strip(expression)));
}

void calculator::ScriptingEngine::DefineVar(const std::string &expression)
{
    this->Define(expression, true);
}

void calculator::ScriptingEngine::DefineExp(const std::string &expression)
{
    this->Define(expression, false);
}

void calculator::ScriptingEngine::Define(const std::string &expression, bool compress)
{
    std::string key;
    std::string value;

    util::SplitKeyValue(expression, key, value);

    if (value.empty())
    {
        this->out.WriteLine("> Missing value!");
        return;
    }

    IValue *res;

    if (compress)
        res = this->calculator.Evaluate(value);
    else
        res = new LazyValue(value);

    this->calculator.GetConfig().AddVariable(key, res);

    this->out.WriteLine("Defined % as %.", key, res);
}

void calculator::ScriptingEngine::Solve(const std::string &expression)
{
    if (expression.empty())
    {
        this->err.WriteLine("No input!");
        return;
    }

    auto res = this->calculator.Evaluate(expression);

    if (this->useAns)
    {
        this->calculator.GetConfig().AddVariable("ANS", res);
    }

    this->out.WriteLine("> %", *res);
}

void calculator::ScriptingEngine::Parse(const std::string &expression)
{
    if (expression.empty())
    {
        this->err.WriteLine("No input!");
        return;
    }

    std::vector<parsing::ExpressionBase *> expressions;

    tokenizing::Tokenizer tokenizer;
    tokenizer.Tokenize(expression, &this->calculator.GetConfig());
    parsing::CreatePostFixExpression(tokenizer.GetTokens(), expressions, this->calculator.GetConfig());

    for (auto i = 0; i < expressions.size(); i++)
    {
        this->out.Write("(%)", expressions[i]);

        if (i != expressions.size() - 1)
        {
            this->out.Write(", ");
        }
        else
        {
            this->out.WriteLine();
        }
    }
}

void calculator::ScriptingEngine::Tokenize(const std::string &expression)
{
    if (expression.empty())
    {
        this->err.WriteLine("No input!");
        return;
    }

    tokenizing::Tokenizer tokenizer;
    tokenizer.Tokenize(expression, &this->calculator.GetConfig());
    const auto &tokens = tokenizer.GetTokens();

    if (tokens.size() > 0)
    {
        for (auto i = 0; i < tokens.size(); i++)
        {
            this->out.Write("(%:%)", tokens[i].GetType(), tokens[i].GetValue());

            if (i != tokens.size() - 1)
                this->out.Write(", ");
            else
                this->out.WriteLine();
        }
    }
}

void calculator::ScriptingEngine::LoadFile(const std::string &path)
{
    //TODO: richtigen Pfad bestimmenn
    // this->EvalScript(calculator::ReadFile(this->workingDirectory + calculator::Strip(path)));
}

void calculator::ScriptingEngine::EvalScript(const std::string &script)
{
    auto stream = std::stringstream();

    util::dbg.WriteLine("Evaluating script \"%\"", script);

    stream.str(script);

    this->EvalStream(stream);
}

void calculator::ScriptingEngine::EvalFromStdIn()
{
    this->EvalStream(std::cin);
}

void calculator::ScriptingEngine::EvalStream(std::istream &in)
{
    std::string buf;
    std::string line;
    bool append = false;
    bool loop = false;

    this->loop = true;

    while (!in.eof() && this->loop)
    {
        std::getline(in, buf);

        if (util::StartsWith(buf, "//"))
            continue;

        if (append)
            line.append(buf);
        else
            line.assign(buf);

        append = util::EndsWith(line, "\\\\");

        if (!append)
            this->Eval(line);
    }
}

void calculator::ScriptingEngine::OpenErr(const std::string &) {}
void calculator::ScriptingEngine::OpenOut(const std::string &) {}
void calculator::ScriptingEngine::OpenIn(const std::string &) {}