//
//  SyntaxErrorException.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#ifndef SyntaxErrorException_h
#define SyntaxErrorException_h

#include <stdexcept>
#include <string>
#include <sstream>

namespace Assembler8085
{
    class SyntaxErrorException : public std::logic_error
    {
    public:
        SyntaxErrorException (int line, int column, const std::string & message = std::string(""))
        : std::logic_error("")
        {
            std::ostringstream stringStream;
            stringStream << "Syntax error at line:" << line << " column:" << column;
            mMessage = stringStream.str();

            if (message.size() != 0)
            {
                mMessage += " (" + message + ")";
            }
        }

        virtual ~SyntaxErrorException ()
        { }

        virtual const char * what () const noexcept
        {
            return mMessage.c_str();
        }

    protected:
        SyntaxErrorException ()
        : std::logic_error("")
        { }

        std::string mMessage;
    };
}

#endif /* SyntaxErrorException_h */
