//
//  Token.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#ifndef Token_h
#define Token_h

#include <string>

namespace Assembler8085
{
    class Token
    {
    public:
        Token (int line = 0, int column = 0, const std::string & text = std::string(""))
        : mLine(line), mColumn(column), mText(text)
        { }

        virtual ~Token ()
        { }

        void parse ();

        int line ()
        {
            return mLine;
        }

        int column ()
        {
            return mColumn;
        }

        std::string text ()
        {
            return mText;
        }

    protected:
        std::string mText;
        int mLine;
        int mColumn;
    };
}

#endif /* Token_h */
