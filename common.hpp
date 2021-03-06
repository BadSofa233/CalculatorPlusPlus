#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED
#include <string>
#include <stdexcept>
#include "TokenDictionary.hpp"
#include "Number.hpp"

//Mathematical constants
const double PI = 3.14159265358979323846264338327950288;
const double EULER_NUMBER = 2.71828182845904523536;

//Global settings and functions
class GlobalFormat{
public:
    GlobalFormat();
    class BitWordLength{
    public:
        BitWordLength(){
            wordLength = 32;
        }
        unsigned length() { return wordLength; }
        void setLength(unsigned l) { wordLength = l; }
    private:
        unsigned wordLength;
    };

    class ComplexNumebrFormat{ // Set the display format for complex numbers
    public:
        ComplexNumebrFormat(){
            i = 'i';
            prefix = false;
            tokenDictionary.addToken(new ImaginaryUnit(i));
            abiForm = true;
        }
        char imagUnit() const {return i;}
        void refreshImagUnit(const char& c){
            tokenDictionary.deleteWord(i);
            i = c;
            tokenDictionary.addToken(new ImaginaryUnit(i));
        }
        bool preOrPost() const {return prefix;}
        bool abiOrCis() const {return abiForm;}
        friend std::ostream& operator<<(std::ostream&, const Complex&);
    private:
        friend class Use; // only the Use class (command) has access to global settings
        char i; // imaginary unit, i by default
        bool prefix; // prefix or postfix the imaginary unit, postfix by default
        bool abiForm; // false means cis form
    };

    class AngleFormat{ // Set the output format of angles
    public:
        AngleFormat() {
            deg = true;
        }
        double r2d(const double& x) const {return deg ? x / PI * (double)180 : x;}
        double d2r(const double& x) const {return deg ? x * PI / (double)180 : x;}
        bool getDR() const {return deg;}
    private:
        friend class Use; // only the Use class (command) has access to global settings
        bool deg;
    };
    BitWordLength wordLength;
    ComplexNumebrFormat complexNumberFormat;
    AngleFormat angleFormat;
};

extern GlobalFormat globalFormat;

std::ostream& operator<<(std::ostream&, const Complex&);

//Exceptions
class invalid_character : public std::invalid_argument{
public:
    invalid_character(const char&);
    const char* what() const throw();
private:
    char errData;
};

class invalid_func_name : public std::invalid_argument{
public:
    invalid_func_name(const std::string&);
};

class invalid_func_arg : public std::invalid_argument{
public:
    invalid_func_arg(const std::string&);
};

class invalid_bracket : public std::invalid_argument{
public:
    invalid_bracket(const char&);
    const char* what() const throw();
private:
    char errData;
};

class invalid_expression : public std::invalid_argument{
public:
    invalid_expression();
};

// warning message
void print_warning(std::string);

#endif // COMMON_HPP_INCLUDED
