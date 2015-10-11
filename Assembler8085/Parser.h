//
//  Parser.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#ifndef Parser_h
#define Parser_h

#include <string>

namespace Assembler8085
{
    class Parser
    {
    public:
        Parser (const std::string & fileName);
        virtual ~Parser ();

        void parse ();

    private:
        std::string mFileName;
    };
}

#endif /* Parser_h */
