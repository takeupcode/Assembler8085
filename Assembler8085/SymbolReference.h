//
//  SymbolReference.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/14/15.
//

#ifndef SymbolReference_h
#define SymbolReference_h

#include <string>

namespace Assembler8085
{
    class SymbolReference
    {
    public:
        SymbolReference (unsigned int position, const std::string & symbol)
        : mPosition(position), mSymbol(symbol)
        { }

        virtual ~SymbolReference ()
        { }

        unsigned int position () const
        {
            return mPosition;
        }

        std::string symbol () const
        {
            return mSymbol;
        }

    protected:
        unsigned int mPosition;
        std::string mSymbol;
    };
}

#endif /* SymbolReference_h */
