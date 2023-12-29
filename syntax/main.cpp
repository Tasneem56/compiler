#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


using namespace std;



//check a punctuator or not
bool isPunct(char m)
{
    if (m == ' ' || m == '+' || m == '-' || m == '*' || m == '/' || m == ',' || m == ';' || m == '>' ||
        m == '<' || m == '=' || m == '(' || m == ')' ||m == '[' || m == ']' || m == '{' || m == '}' ||
        m == '&' || m == '|')
        {
            return true;
        }
    return false;
}



//check identifier is valid or not
bool trueIdent(char* idn)
{
    //if first character of string is a digit or a special character, identifier is not valid
    if (idn[0] == '0' || idn[0] == '1' || idn[0] == '2' ||idn[0] == '3' || idn[0] == '4' || idn[0] == '5' ||
        idn[0] == '6' || idn[0] == '7' || idn[0] == '8' ||idn[0] == '9' || isPunct(idn[0]) == true)
        {
            return false;
        }
    int i,len = strlen(idn);

    //if length is one, validation is already completed, hence return true
    if (len == 1)
    {
        return true;
    }
    else
    {
        //identifier cannot contain special characters
    for (i = 1 ; i < len ; i++)
    {
        if (isPunct(idn[i]) == true)
        {
            return false;
        }
    }
    }
    return true;
}



//check if the given character is an operator or not
bool isOpera(char opera)
{
    if (opera == '+' || opera == '-' || opera == '*' ||
        opera == '/' || opera == '>' || opera == '<' ||
        opera == '=' || opera == '|' || opera == '&')
    {
        return true;
    }
    return false;
}


bool isKeyword(char *str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||  !strcmp(str, "continue")
        || !strcmp(str, "int") || !strcmp(str, "double")
        || !strcmp(str, "float") || !strcmp(str, "return")
        || !strcmp(str, "char") || !strcmp(str, "case")
        || !strcmp(str, "long") || !strcmp(str, "short")
        || !strcmp(str, "typedef") || !strcmp(str, "switch")
        || !strcmp(str, "unsigned") || !strcmp(str, "void")
        || !strcmp(str, "static") || !strcmp(str, "struct")
        || !strcmp(str, "sizeof") || !strcmp(str,"long")
        || !strcmp(str, "volatile") || !strcmp(str, "typedef")
        || !strcmp(str, "enum") || !strcmp(str, "const")
        || !strcmp(str, "union") || !strcmp(str, "extern")
        || !strcmp(str,"bool"))
        {
            return true;
        }
    else
    {
        return false;
    }
}



//check if the given substring is a number or not

bool isNumber(char* str)
{
    int i, len = strlen(str),numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0 ; i < len ; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return false;
        } else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            {
                return false;
            }
    }
    return true;
}

char* subString(char* realStr, int l, int r)
{
    int i;

    char* str = (char*) malloc(sizeof(char) * (r - l + 2));

    for (i = l; i <= r; i++)
    {
        str[i - l] = realStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}



//parse the expression
void parse(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);
    while (right <= len && left <= right) {

        if (isPunct(str[right]) == false)//if character is a digit or an alphabet
            {
                right++;
            }

        if (isPunct(str[right]) == true && left == right)//if character is a punctuator
            {
            if (isOpera(str[right]) == true)
            {
                std::cout<< str[right] <<" IS AN OPERATOR\n";
            }
            right++;
            left = right;
            } else if (isPunct(str[right]) == true && left != right
                   || (right == len && left != right))
            {
            char* sub = subString(str, left, right - 1);//extract substring

             //check if parsed substring is a keyword or identifier or number
            if (isKeyword(sub) == true)
                        {
                            cout<< sub <<" IS A KEYWORD\n";
                        }
            else if (isNumber(sub) == true)
                        {
                            cout<< sub <<" IS A NUMBER\n";
                        }
            else if (trueIdent(sub) == true
                     && isPunct(str[right - 1]) == false)
                     {
                         cout<< sub <<" IS A VALID IDENTIFIER\n";
                     }
            else if (trueIdent(sub) == false
                     && isPunct(str[right - 1]) == false)
                     {
                         cout<< sub <<" IS NOT A VALID IDENTIFIER\n";
                     }

            left = right;
            }
    }
    return;
}



int main()
{
    char expression[100] = "i want to apply lexical to int x=8+12m";
    parse(expression);
    return 0;
}
