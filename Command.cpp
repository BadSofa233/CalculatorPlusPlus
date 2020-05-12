
#include "common.hpp"
#include "Command.hpp"
#include "Dictionary.hpp"

Command::Command() : Token(){
    type = COMMAND;
}

Command::~Command(){}

//void Command::execute(const unsigned& argc, std::string* argv){}

Calculate::Calculate() : Command(){
    word = "calculate";
}

extern Complex * calcString(std::string &);

void Calculate::execute(const unsigned& argc, std::string* argv) {
    DEBUG_PRINT("In calculate execute()\n");
    Complex * result = calcString(argv[0]);
    std::cout << '=' << * result << "\n\n";
    delete result;
}

Use::Use() : Command(){
    word = "use";
}

void Use::execute(const unsigned& argc, std::string* argv){
    DEBUG_PRINT("Use argc: %d\n", argc);
    for(unsigned i = 0; i < argc; ++i){
        if(argv[i][0] == '-' && argv[i].length() == 2){
            switch(argv[i][1]){
            case 'a':
                setAngle(argc, argv, ++i);
                break;
            case 'i':
                setImagUnit(argc, argv, ++i);
                break;
            case 'h':
                std::cout << "Use help message not written yet...\n"; // COME ON WRITE IT PLEASE, and other help messages
                break;
            // consider -d for default settings in later dev
            default:
                goto ERR_OUT;
            }
        }
        else
            goto ERR_OUT;
    }

    return;

    ERR_OUT:
        invalid_func_arg err(word);
        throw err;
}

void Use::setAngle(const unsigned& argc, std::string* s, unsigned& pos){
    if(pos > argc - 1)
        goto ERR_OUT;

    if(s[pos] == "deg"){
        GIO.AngIO.deg = true;
        std::cout << "Angle format set to degrees.\n";
        return;
    }
    else if(s[pos] == "rad"){
        GIO.AngIO.deg = false;
        std::cout << "Angle format set to radians.\n";
        return;
    }
    else
        goto ERR_OUT;

    return;

    ERR_OUT:
        invalid_func_arg err(word);
        throw(err);
}

void Use::setImagUnit(const unsigned& argc, std::string * argv, unsigned& pos){
    if(pos == argc || argv[pos][0] == '-')
        goto ERR_OUT;
    for(; pos < argc; ++pos){
        DEBUG_PRINT("argc: %d, pos: %d, argv: %s\n", argc, pos, argv[pos]);
        if(argv[pos][0] == '-'){
            --pos;
            return;
        }
        if(argv[pos].length() == 1){
            if(argv[pos][0] != GIO.CompNumIO.i && dictionary.searchString(argv[pos]))
                goto ERR_OUT;
            GIO.CompNumIO.refreshImagUnit(argv[pos][0]);
            DEBUG_PRINT("Refreshed imaginary unit\n");
            std::cout << "Imaginary unit set to " << GIO.CompNumIO.i << ".\n";
        }
        else if(argv[pos] == "prefix" || argv[pos] == "postfix"){
            GIO.CompNumIO.prefix = (argv[pos] == "prefix");
            std::cout << "Imaginary unit is now ";
            GIO.CompNumIO.prefix ? std::cout << "prefix\n" : std::cout << "postfix\n";
        }
        else if(argv[pos] == "cis" || argv[pos] == "abi"){
            GIO.CompNumIO.abiForm = (argv[pos] == "abi");
            std::cout << "Complex number form is now ";
            GIO.CompNumIO.abiForm ? std::cout << "a+bi\n" : std::cout << "cis\n";
        }
        else
            goto ERR_OUT;
    }
    return;

    ERR_OUT:
        invalid_func_arg err(word);
        throw(err);
}

Help::Help() : Command(){ // consider moving help messages to local files or web pages
    word = "help";
    helpMsg = "";
}

Help::Help(const std::string& msg){
    word = "help";
    helpMsg = msg;
}

void Help::execute(const unsigned& argc, std::string* argv){
    FILE * fp = fopen("help.txt", "r");
    if(!fp)
        std::cout << "help.txt not found. Please download it or view online in the git repository\n";
    else{
        char c = 0;
        std::cout << '\n';
        while(c != EOF){
            c = fgetc(fp);
            std::cout << c;
        }
    }
    fclose(fp);
}

License::License(){
    word = "license";
}

void License::execute(const unsigned & argc, std::string * argv){
    if(argv[0] == "print"){
        FILE * fp = fopen("LICENSE", "r");
        if(!fp)
            std::cout << "GPL v2 License not found. Please download it from the git repository or view online at https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html\n";
        else{
            char c = 0;
            std::cout << '\n';
            while(c != EOF){
                c = fgetc(fp);
                std::cout << c;
            }
        }
        fclose(fp);
        std::cout << '\n';
    }
    else if(argc == 1){
        std::cout << "This program is licensed under GPL v2.\n"
                    << "To view its full version please type \'license print\'\n"
                    << "or visit https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html\n";
    }
    else{
        invalid_func_arg err(word);
        throw err;
    }

}

About::About(){
    word = "about";
    aboutMsg = "";
}

void About::execute(const unsigned & argc, std::string * argv){
    if(argc > 1){
        invalid_func_arg err(word);
        throw err;
    }
    std::cout << '\n';
    aboutMsg += "This software calculates a math expression with complex numbers\n";
    aboutMsg += "Author:\tYuhan Li\tWE Computer Engineering (Hardware) 2021\n";
    aboutMsg += "Email:\tyli2993@uwo.ca\n";
    std::cout << aboutMsg << '\n';
}

Donate::Donate() : Command(){
    word = "donate";
    donationList.push_back("Haopu Yao");
}

void Donate::execute(const unsigned & argc, std::string * argv){
    if(argc > 1){
        invalid_func_arg err(word);
        throw err;
    }
    std::cout << '\n'
                << "Thanks for you interest in supporting this project!\n"
                << "The donation link is:\n"
                << "https://paypal.me/YuhanLi1999\n"
                << "Your name will be listed in the donation list after a successful donation.\n"
                << "Thank you!\n"
                << "Yuhan Li\n"
                << '\n';
    std::cout << "Donation list:\n";
    for(const char * name : donationList)
        std::cout << name << '\n';
    std::cout << '\n';
}

Exit::Exit() : Command(){
    word = "exit";
}

void Exit::execute(const unsigned& argc, std::string* argv){
    std::cout << "\nThanks for using!\n";
    exit(0);
}
