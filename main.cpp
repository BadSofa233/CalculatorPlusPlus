/**

    A calculator that calculates complex number. Author: Yuhan Li, email: yli2993@uwo.ca
    Copyright (C) <2019> <Yuhan Li>

    This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*/

/*
 * To do:
 *      - fix not, add variable word length
 *      - Use addWord() distributively
 *      - Better log format
 *      - Try parse tree
 */

#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <exception>
#include "config.hpp"
#include "Complex.hpp"
#include "Dictionary.hpp"
#include "Token.hpp"
#include "Command.hpp"
#include "Calculation.hpp"
#include "common.hpp"

void fetchArgs(unsigned&, std::string **, std::string &);

int main(){
    DEBUG_PRINT("Program initiated, print header.\n");
    std::cout << "\nCalculator++ V1.7\n"
                << "Copyright (C) 2019 Yuhan Li\n"
                << "This software comes with ABSOLUTELY NO WARRANTY.\n"
                << "This is free software, and you are welcome to redistribute it under certain conditions; type 'license' for details.\n"
                << '\n'
                << "If you find any bugs, or you have any suggestions, or you want any new features on this calculator,\n"
                << "please contact the author by email: yli2993@uwo.ca\n"
                << '\n'
                << "Imaginary unit is \'i\' and angles are calculated as degrees by default,\n"
                << "you can set the imaginary unit and angle format by the \'use\' command\n"
                << "\n\n";
    std::string input;
    while(1){
        std::getline(std::cin, input);
        DEBUG_PRINT("Received user input: \'%s\'\n", input);
        if(input.length() == 0){
            DEBUG_PRINT("User input empty, continue.\n");
            continue;
        }
        unsigned argc = 0;
        std::string * argv = nullptr;
        std::string * cmdArgv = nullptr;
        try{
            fetchArgs(argc, &argv, input);
            DEBUG_PRINT("fetch args complete\n");
            cmdArgv = argv;
            Token * cmd = dictionary.searchString("calculate");
            DEBUG_PRINT("Fetched 'calculate' command\n");
            Token * op = dictionary.searchString(argv[0]);
            if(op != nullptr && op->getType() == COMMAND){
                cmd = op;
                DEBUG_PRINT("Fetched '%s' command\n", cmd->getWord());
                if(argc > 1){
                    cmdArgv = argv + 1;
                    --argc;
                }
            }
            DEBUG_PRINT("Execute '%s' command\n", cmd->getWord());
            cmd->execute(argc, cmdArgv);
        }
        catch(std::invalid_argument& err){
            const char * errMsg = err.what();
            if(errMsg != nullptr)
                std::cout << errMsg;
            std::cout << '\n';
        }
        std::cout << '\n';
        delete[] argv;
    }
    return 0;
}

void fetchArgs(unsigned& argc, std::string ** argv, std::string & input){
    for(unsigned i = 0; i < input.length(); ++i){
        if(input[i] >= 'A' && input[i] <= 'Z') input[i] += 32;
        if(i == 0 || input[i - 1] == ' ')
            ++argc;
    }
    DEBUG_PRINT("argc: %d\n", argc);
    (*argv) = new std::string[argc]{""};
    unsigned j = 0;
    for(unsigned i = 0; i < input.length(); ++i){
        if(input[i] == ' '){
            if((*argv)[j].length() == 0){
                invalid_func_name err(input);
                throw err;
            }
            DEBUG_PRINT("argv[%d]: %s\n", j, (*argv)[j]);
            ++i; ++j;
        }
        (*argv)[j] += input[i];
    }
    DEBUG_PRINT("argv[%d]: %s\n", j, (*argv)[j]);
}
