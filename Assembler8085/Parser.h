//
//  Parser.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#ifndef Parser_h
#define Parser_h

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Token.h"

namespace Assembler8085
{
    class MnemonicParser;

    class Parser
    {
    public:
        Parser (const std::string & fileName);
        virtual ~Parser ();

        void parse ();

        void addParser (const std::shared_ptr<MnemonicParser> & parser);

        bool addSymbol (const std::string & name, const std::string & value);
        bool getSymbol (const std::string & name, std::string & value) const;

    private:
        void placeToken (Token & token);

        std::string mFileName;
        Token mLabel;
        Token mMnemonic;
        std::vector<Token> mArguments;
        bool mLabelComplete;
        bool mMnemonicComplete;
        bool mCommaNeeded;
        int mLineLength;
        std::vector<const std::shared_ptr<MnemonicParser>> mMnemonicParsers;
        std::unordered_map<std::string, std::string> mSymbols;
    };
}

#endif /* Parser_h */
