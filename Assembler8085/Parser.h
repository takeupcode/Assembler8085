//
//  Parser.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#ifndef Parser_h
#define Parser_h

#include <string>
#include <vector>

#include "Token.h"

namespace Assembler8085
{
    class Parser
    {
    public:
        Parser (const std::string & fileName);
        virtual ~Parser ();

        void parse ();

    private:
        void placeToken (Token & token);

        std::string mFileName;
        Token mLabel;
        Token mMnemonic;
        std::vector<Token> mArguments;
        bool mLabelComplete;
        bool mMnemonicComplete;
        int mLineLength;
    };
}

#endif /* Parser_h */
