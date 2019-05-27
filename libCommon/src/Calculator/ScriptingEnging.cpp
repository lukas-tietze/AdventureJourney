#include "Calculator.hpp"

#include <unordered_map>

#include "data/String.hpp"
#include "datetime/Timer.hpp"

util::ScriptingEngine::Action::Action()
{
}

util::ScriptingEngine::Action::Action(const std::string &name,
                                      const std::string &alias,
                                      const std::string &description,
                                      action_t action) : name(name),
                                                         alias(alias),
                                                         description(description),
                                                         action(action)
{
}

bool util::ScriptingEngine::Action::HasDesciption() const
{
    return this->description.empty();
}

bool util::ScriptingEngine::Action::HasAlias() const
{
    return !this->alias.empty();
}

std::vector<util::ScriptingEngine::Action> util::ScriptingEngine::uniqeActions =
    {
        Action("tokenize", "t", "Prints the list of tokens of the expression.", &util::ScriptingEngine::Tokenize),
        Action("parse", "p", "Parses the expression and prints the created postfix expression.", &util::ScriptingEngine::Parse),
        Action("def", "d", "Evaluates the given expression and defines a variable, which value is the result of the evaluation.", &util::ScriptingEngine::DefineVar),
        Action("exp", "e", "Defines a variable that contains the given expression.", &util::ScriptingEngine::DefineExp),
        Action("undef", "ud", "Removes a variable.", &util::ScriptingEngine::Undefine),
        Action("quit", "q", "Quit the application.", &util::ScriptingEngine::Quit),
        Action("solve", "s", "Evaluates the expression and prints the result.", &util::ScriptingEngine::Solve),
        Action("load", "ld", "load a file from the specified path and interpret each line as a command.", &util::ScriptingEngine::LoadFile),
        Action("err", "|", "Changes the error stream to the specified file. Use :err <std> to print to console.", &util::ScriptingEngine::OpenErr),
        Action("out", ">", "Changes the output stream to the specified file. Use :out <std> to print to console.", &util::ScriptingEngine::OpenOut),
        Action("in", "<", "Changes the input stream. Use :in <std> to use the console.", &util::ScriptingEngine::OpenIn),
        Action("dir", "cd", "Changes the to specified directory and prints the current directory.", &util::ScriptingEngine::ChangeDir),
        Action("echo", "#", "Use on, off to enable or disable echoing of commands", &util::ScriptingEngine::SetEcho),
        Action("useAns", "ans", " use on, off to enable or disable the ANS-Variable. If enablad the result of the last calculation will be saved in a variable named ANS", &util::ScriptingEngine::UseAns),
        Action("clear", "cl", "Clears the screen.", &util::ScriptingEngine::ClearOut),
        Action("files", "ls", "List all Files and directories in the current directory.", &util::ScriptingEngine::ListFiles),
        Action("clearvars", "clv", "Delete all variables, except e and pi. Use :clearvars all to also delete e and pi.", &util::ScriptingEngine::ClearVars),
        Action("help", "h", "Prints the help.", &util::ScriptingEngine::ShowHelp),
        Action("diagnostic", "dg", "Set diagnostic-Output to the specified stream.", &util::ScriptingEngine::SetDiagnosticOut),
};

util::ScriptingEngine::ScriptingEngine()
{
    //TODO: Nicht Threadsafe -> Threadsafe wird an dieser Stelle aber auch nicht unbedingt benötigt!
    if (ScriptingEngine::actions.empty())
    {
        for (const auto &action : ScriptingEngine::uniqeActions)
        {
            ScriptingEngine::actions.insert(std::make_pair(action.name, action));

            if (action.HasAlias())
                ScriptingEngine::actions.insert(std::make_pair(action.alias, action));
        }
    }
}

void util::ScriptingEngine::Eval(const std::string &input)
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

            auto actionKvp = ScriptingEngine::actions.find(command.substr(1));

            if (actionKvp == ScriptingEngine::actions.end())
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

void util::ScriptingEngine::ShowHelp(const std::string &expression)
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
    else if (this->calculator.GetConfig().GetOperator(expression) != nullptr)
    {
        this->out.WriteLine("% is an operator: %", expression, this->calculator.GetConfig().GetOperator(expression));
    }
    else if (ScriptingEngine::actions.find(expression) != ScriptingEngine::actions.end())
    {
        this->out.WriteLine("% is an command: %", expression, actions[expression].description);
    }
    else
    {
        this->out.WriteLine("There is no help topic for %. Use :help for general help and check your spelling.", expression);
    }
}

int util::ScriptingEngine::FindSimilarCommands(const std::string &command, std::vector<std::string> &out)
{
    int size = 0;

    for (const auto &kvp : ScriptingEngine::actions)
    {
        const auto &existingCommand = kvp.first;

        if (existingCommand.find(command) != std::string::npos ||
            command.find(existingCommand) != std::string::npos ||
            OsaDistance(existingCommand, command) < 3)
        {
            out.push_back(existingCommand);
            size++;
        }
    }

    return size;
}

void util::ScriptingEngine::HandleUndefinedCommand(const std::string &command)
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

void util::ScriptingEngine::ListFiles(const std::string &)
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

void util::ScriptingEngine::ChangeDir(const std::string &expression)
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

void util::ScriptingEngine::HandleException(const std::exception &e)
{
    //TODO
}

void util::ScriptingEngine::HandleException(const util::Exception &e)
{
    //TODO
}

void util::ScriptingEngine::Undefine(const std::string &expression)
{
    if (expression.empty())
    {
        this->out.WriteLine("Requiring argument!");
    }

    this->calculator.GetConfig().RemoveVariable(util::ToLower(util::Strip(expression)));
}

void util::ScriptingEngine::DefineVar(const std::string &expression)
{
    this->Define(expression, true);
}

void util::ScriptingEngine::DefineExp(const std::string &expression)
{
    this->Define(expression, false);
}

void util::ScriptingEngine::Define(const std::string &expression, bool compress)
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

    this->out.WriteLine("Defined % as {1}.", key, res->GetValueDescription());
}

void util::ScriptingEngine::Solve(const std::string &expression)
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

void util::ScriptingEngine::Parse(const std::string &expression)
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

void util::ScriptingEngine::Tokenize(const std::string &expression)
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

void util::ScriptingEngine::LoadFile(const std::string &path)
{
    //TODO: richtigen Pfad bestimmenn
    this->EvalScript(util::ReadFile(this->workingDirectory + util::Strip(path)));
}

void util::ScriptingEngine::EvalScript(const std::string &script)
{
    //TODO: string parsen, zeilenweise auswerten -> //Kommentar & \\=multiline
}
