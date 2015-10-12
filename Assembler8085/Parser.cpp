//
//  Parser.cpp
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#include <fstream>

#include "Parser.h"
#include "SyntaxErrorException.h"
#include "MnemonicParser.h"

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
        int tokenColumnNumber = 0;
        string text = "";
        mLabelComplete = false;
        mMnemonicComplete = false;
        mCommaNeeded = false;
        bool stringMode = false;

        for (char & c : line)
        {
            columnNumber++;
            if (c == '"')
            {
                if (columnNumber == 1)
                {
                    string message = "Lines cannot begin with a string";
                    throw SyntaxErrorException(lineNumber, columnNumber, message);
                }
                if (!mMnemonicComplete)
                {
                    string message = "Strings must come after a mnemonic";
                    throw SyntaxErrorException(lineNumber, columnNumber, message);
                }
                if (!stringMode && !text.empty())
                {
                    string message = "Unexpected string";
                    throw SyntaxErrorException(lineNumber, columnNumber, message);
                }

                if (stringMode)
                {
                    Token token(lineNumber, tokenColumnNumber, text);
                    placeToken(token);
                    text = "";

                    stringMode = false;
                }
                else
                {
                    tokenColumnNumber = columnNumber;

                    stringMode = true;
                }
            }
            else if (isspace(c) && !stringMode)
            {
                if (!text.empty())
                {
                    Token token(lineNumber, tokenColumnNumber, text);
                    placeToken(token);
                    text = "";
                }

                // Labels must start in the first column. So any spaces
                // will always mean that the label is complete.
                mLabelComplete = true;

                continue;
            }
            else if (c == ';' && !stringMode)
            {
                if (!text.empty())
                {
                    Token token(lineNumber, tokenColumnNumber, text);
                    placeToken(token);
                    text = "";
                }
                break;
            }
            else if (c == ',' && !stringMode)
            {
                if (!text.empty())
                {
                    // A comma could come right after a parameter which means that we
                    // haven't yet placed the parameter. Do that first and then see
                    // if a comma is needed.
                    Token token(lineNumber, tokenColumnNumber, text);
                    placeToken(token);
                    text = "";
                }
                if (!mCommaNeeded)
                {
                    string message = "Unexpected comma";
                    throw SyntaxErrorException(lineNumber, columnNumber, message);
                }
                mCommaNeeded = false;
            }
            else
            {
                if (text.empty() && !stringMode)
                {
                    tokenColumnNumber = columnNumber;
                }
                text += c;
            }
        }

        // Some errors may need to reference the end of the line for missing components.
        mLineLength = columnNumber;

        if (stringMode)
        {
            string message = "End of string not found";
            throw SyntaxErrorException(lineNumber, mLineLength, message);
        }

        if (!text.empty())
        {
            Token token(lineNumber, tokenColumnNumber, text);
            placeToken(token);
            text = "";
        }

        if (!mLabel.text().empty() && !mMnemonicComplete)
        {
            string message = "Mnemonic not found";
            throw SyntaxErrorException(lineNumber, mLineLength, message);
        }

        if (mMnemonicComplete)
        {
            bool mnemonicParserFound = false;
            for (unique_ptr<MnemonicParser> & mnemonicParser : mMnemonicParsers)
            {
                if (mnemonicParser->mnemonic() == mMnemonic.text())
                {
                    mnemonicParser->parse(mLineLength, mLabel, mArguments);
                    
                    mnemonicParserFound = true;
                }
            }

            if (!mnemonicParserFound)
            {
                string message = "Unexpected mnemonic found";
                throw SyntaxErrorException(lineNumber, mMnemonic.column(), message);
            }
        }
    }

    file.close();
}

void Parser::placeToken (Token & token)
{
    if (!mLabelComplete)
    {
        mLabel = token;
        mLabelComplete = true;
    }
    else if (!mMnemonicComplete)
    {
        mMnemonic = token;
        mMnemonicComplete = true;
    }
    else
    {
        if (mCommaNeeded)
        {
            string message = "Expected comma";
            throw SyntaxErrorException(token.line(), token.column(), message);
        }
        mArguments.push_back(token);
        mCommaNeeded = true;
    }
}
