//
//  MnemonicParser.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#ifndef MnemonicParser_h
#define MnemonicParser_h

#include <string>
#include <vector>

#include "Parser.h"
#include "Token.h"

namespace Assembler8085
{
    class MnemonicParser
    {
    public:
        MnemonicParser (const std::string & mnemonic, Parser & parser)
        : mMnemonic(mnemonic), mParser(parser)
        { }
        
        virtual ~MnemonicParser ()
        { }

        virtual void parse (int lineLength, const Token & label, const std::vector<Token> arguments) = 0;

        std::string mnemonic ()
        {
            return mMnemonic;
        }

    private:
        std::string mMnemonic;
        Parser & mParser;
    };
}

#endif /* MnemonicParser_h */
