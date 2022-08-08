#include <cstdio>
#include <string>

enum Token{
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,

    tok_identifier = -4,
    tok_number = -5
};

static std::string IdentifierStr; //用于填充identifier
static double NumVal; //用于填充数字

static int gettok(){
    static int LastChar = ' ';
    while(isspace(LastChar))
        LastChar = getchar();
    
    if(isalpha(LastChar)){
        IdentifierStr = LastChar;
        while(isalnum(LastChar = getchar())){
            IdentifierStr += LastChar;
        }
        if(IdentifierStr == "def"){
            return tok_def;
        }
        if(IdentifierStr == "extern"){
            return tok_extern;
        }
        return tok_identifier;
    }

    if(isdigit(LastChar) || LastChar == '.'){
        std::string NumStr;
        do{
            NumStr += LastChar;
            LastChar = getchar();
        }while(isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }

    if(LastChar == '#'){
        //一行注释
        do{
            LastChar = getchar();
        }while(LastChar != '\n' && LastChar != EOF && LastChar != '\r');
        return gettok();
    }

    if(LastChar == EOF){
        return tok_eof;
    }

    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar; //说明是未标识符号，如‘+’
}