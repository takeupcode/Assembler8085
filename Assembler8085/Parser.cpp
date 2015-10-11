//
//  Parser.cpp
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#include <fstream>

#include "Parser.h"
#include "SyntaxErrorException.h"

using namespace std;
using namespace Assembler8085;

Parser::Parser (const string & fileName)
: mFileName(fileName)
{
}

Parser::~Parser ()
{
}

void Parser::parse ()
{
    ifstream file;
    file.open(mFileName);
    if (!file.is_open())
    {
        throw logic_error("Source file could not be opened.");
    }

    int lineNumber = 0;
    std::string line;
    while (getline(file, line))
    {
        lineNumber++;
        int columnNumber = 0;
        for (char & c : line)
        {
            columnNumber++;
            if (isspace(c))
            {
                continue;
            }
            else if (c == ';')
            {
                break;
            }
            else
            {
                string message = "Unexpected character: ";
                message += c;
                throw SyntaxErrorException(lineNumber, columnNumber, message);
            }
        }
    }

    file.close();
}
