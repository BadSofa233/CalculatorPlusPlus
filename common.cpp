#include <exception>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdarg.h>
#include "common.hpp"
#include "Complex.hpp"

GlobalFormat globalFormat;

GlobalFormat::GlobalFormat(){}

std::ostream& operator<<(std::ostream & os, const Complex & z){
    if(globalFormat.complexNumberFormat.abiForm){
        if(z.getReal())
            os << std::setprecision(OUTPUT_PRECISION) << z.getReal(); // the number has a real part, output the real part directly
        if(z.getReal() && z.getImag() > 0)
            os << '+';
        else if(z.getImag() < 0)
            os << '-';
        if(z.getImag()){
            if(globalFormat.complexNumberFormat.prefix)
                os << globalFormat.complexNumberFormat.i;
            if(abs(z.getImag()) != ((double)1 + VERY_SMALL_DOUBLE - VERY_SMALL_DOUBLE)) // 1.00000000000000000000
                os << std::setprecision(OUTPUT_PRECISION) << abs(z.getImag());
            if(!globalFormat.complexNumberFormat.prefix)
                os << globalFormat.complexNumberFormat.i;
        }
        if(z.getMagn() == 0)
            os << '0';
    }
    else {
        if(abs(z.getAngl() - PI) < VERY_SMALL_DOUBLE) {
            os << '-';
            os << std::setprecision(OUTPUT_PRECISION) << z.getMagn();
        }
        else if(z.getMagn()) {
            os << std::setprecision(OUTPUT_PRECISION) << z.getMagn(); // the number has magnitude, output the magnitude part directly
            if(z.getAngl()){
                os << "cis(";
                os << std::setprecision(OUTPUT_PRECISION) << globalFormat.angleFormat.r2d(z.getAngl());
                os << ")";
            }
        }
        else
            os << '0';
    }
    return os;
}

invalid_character::invalid_character(const char& c) :
    std::invalid_argument("Invalid character: "){
    errData = c;
}

const char* invalid_character::what() const throw(){
    std::cout << std::invalid_argument::what();
    std::cout << errData;
    return nullptr;
}

invalid_func_name::invalid_func_name(const std::string& str) :
    std::invalid_argument("Invalid string: \'" + str + '\'')
{}

invalid_func_arg::invalid_func_arg(const std::string& str) :
    std::invalid_argument("Invalid arguments for " + str)
{}

invalid_bracket::invalid_bracket(const char& br) :
    std::invalid_argument("Unmatched bracket: "){
    errData = br;
}

const char * invalid_bracket::what() const throw(){
    std::cout << std::invalid_argument::what();
    std::cout << errData;
    return nullptr;
}

invalid_expression::invalid_expression() : std::invalid_argument("Invalid math expression")
{}

void print_warning(std::string msg) {
    std::cout << "Warning: " << msg << std::endl;
}

void debug_print(const char * str, ...){
    va_list printVar;
    va_start(printVar, str);
    for(int i = 0; str[i] != 0; ++i){
        if(str[i] == '%'){
            switch(str[++i]){
            case COMPLEX_PRINT:
                std::cout << va_arg(printVar, Complex);
                continue;
            case 'd':
                std::cout << va_arg(printVar, int);
                continue;
            case 'f':
                std::cout << va_arg(printVar, double);
                continue;
            case 'c':
                std::cout << (char)va_arg(printVar, int);
                continue;
            case 's':
                std::cout << va_arg(printVar, std::string);
                continue;
            default:
                std::invalid_argument("Invalid Argument(s) in DEBUG_PRINT");
            }
        }
        std::cout << str[i];
    }
}
