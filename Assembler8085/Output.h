//
//  Output.h
//  Assembler8085
//
//  Created by Wahid Tanner on 10/14/15.
//

#ifndef Output_h
#define Output_h

#include <stdexcept>
#include <memory>
#include <string>

#include "Parser.h"

namespace Assembler8085
{
    class Output
    {
    public:
        Output (unsigned int size, Parser & parser)
        : mSize(size), mPosition(0), mParser(parser), mNext(nullptr)
        {
            if (size == 0)
            {
                throw std::invalid_argument("Size must be greater than zero.");
            }
        }

        Output (std::shared_ptr<Output> next)
        : mSize(next->size()), mPosition(next->position()), mParser(next->parser()), mNext(next)
        { }

        virtual ~Output ()
        { }

        unsigned int size () const
        {
            return mSize;
        }

        virtual void addByte (unsigned char byte)
        {
            if (position == size())
            {
                throw std::out_of_range("Cannot add bytes past size.");
            }
            ++mPosition;

            if (mNext)
            {
                mNext->addByte(byte);
            }
        }

        virtual void addSymbolByte (const std::string & symbol)
        {
            if (position == size())
            {
                throw std::out_of_range("Cannot add bytes past size.");
            }
            ++mPosition;

            if (mNext)
            {
                mNext->addSymbolByte(symbol);
            }
        }

        virtual void addSymbolWord (const std::string & symbol)
        {
            if (position >= size() - 1)
            {
                throw std::out_of_range("Cannot add bytes past size.");
            }
            ++mPosition;
            ++mPosition;

            if (mNext)
            {
                mNext->addSymbolWord(symbol);
            }
        }

        unsigned int position () const
        {
            return mPosition;
        }

        virtual void setPosition (unsigned int position)
        {
            if (position >= size())
            {
                throw std::out_of_range("Position must be less than size.");
            }
            mPosition = position;

            if (mNext)
            {
                mNext->setPosition(position);
            }
        }

        virtual Parser & parser () const
        {
            return mParser;
        }

    private:
        unsigned int mSize;
        unsigned int mPosition;
        Parser & mParser;
        std::shared_ptr<Output> mNext;
    };
}

#endif /* Output_h */
