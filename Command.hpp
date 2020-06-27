#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include "Token.hpp"

class Command : public Token{
public:
    Command();
    Command(const unsigned&);
    virtual ~Command();
    //virtual void execute(const unsigned&, std::string *);
    void printHelp();
protected:
    std::string helpMsg;
};

class Calculate : public Command{
public:
    Calculate();
    void execute(const unsigned&, std::string *);
};

class Use : public Command{
public:
    Use();
    void execute(const unsigned&, std::string *);
private:
    void setAngle(const unsigned&, std::string *, unsigned&);
    void setImagUnit(const unsigned&, std::string *, unsigned&);
    void setForm(const unsigned&, std::string *, unsigned&);
};

class Help : public Command{
public:
    Help();
    Help(const std::string&);
    void execute(const unsigned&, std::string *);
private:
    std::string helpMsg;
};

class License : public Command{
public:
    License();
    void execute(const unsigned&, std::string *);
};

class About : public Command{
public:
    About();
    void execute(const unsigned&, std::string *);
private:
    std::string aboutMsg;
};

class Exit : public Command{
public:
    Exit();
    void execute(const unsigned&, std::string*);
};

#endif // COMMAND_H_INCLUDED
