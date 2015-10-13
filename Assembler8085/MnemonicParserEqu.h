//
//  MnemonicParserEqu.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#ifndef MnemonicParserEqu_h
#define MnemonicParserEqu_h

#include "MnemonicParser.h"
#include "SyntaxErrorException.h"

using namespace std;

namespace Assembler8085
{
    class MnemonicParserEqu : public MnemonicParser
    {
    public:
        MnemonicParserEqu (const std::string & mnemonic, Parser & parser)
        : MnemonicParser(mnemonic, parser)
        { }

        virtual ~MnemonicParserEqu ()
        { }

        virtual void parse (int lineLength, const Token & label, const std::vector<Token> arguments) const
        {
            if (label.text().empty())
            {
                string message = "Expected label";
                throw SyntaxErrorException(label.line(), 1, message);
            }
            if (arguments.size() != 1)
            {
                string message = "Expected a single argument";
                throw SyntaxErrorException(label.line(), lineLength, message);
            }

            if (!mParser.addSymbol(label.text(), arguments[0].text()))
            {
                string message = "Unable to add symbol";
                throw SyntaxErrorException(label.line(), 1, message);
            }
        }
    };
}

#endif /* MnemonicParserEqu_h */
