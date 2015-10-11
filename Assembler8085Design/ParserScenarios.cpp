//
//  ParserScenarios.cpp
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Assembler8085/Parser.h"
#include "../Assembler8085/SyntaxErrorException.h"

using namespace std;
using namespace MuddledManaged;
using namespace Assembler8085;

DESIGNER_SCENARIO( GeneralParser, "Construction/Normal", "Parser can be constructed." )
{
    Parser parser("");
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Normal", "Parser can parse empty file." )
{
    Parser parser("Empty.s");
    parser.parse();
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Normal", "Parser can parse file with comments." )
{
    Parser parser("Comments.s");
    parser.parse();
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Undefined", "Parser cannot parse file with undefined content." )
{
    Parser parser("Org.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(8, e.line());
        verifyEqual(13, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser does not allow string at column one." )
{
    Parser parser("StringColumnOne.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(1, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser does not allow empty string at column one." )
{
    Parser parser("StringColumnOneEmpty.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(1, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser does not allow string before mnemonic." )
{
    Parser parser("StringBeforeMnemonic.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(5, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser does not allow string with no end." )
{
    Parser parser("StringNoEnd.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(39, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser does not allow unexpected string." )
{
    Parser parser("StringUnexpected.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(26, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser does not allow comma before argument." )
{
    Parser parser("CommaBeforeArgument.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(21, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser does not allow multiple commas." )
{
    Parser parser("CommaMultiple.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(27, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser enforces comma between arguments." )
{
    Parser parser("CommaMissing.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(25, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Error", "Parser enforces mnemonic exists." )
{
    Parser parser("MnemonicMissing.s");

    bool exceptionCaught = false;
    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(1, e.line());
        verifyEqual(5, e.column());
        exceptionCaught = true;
    }

    verifyTrue(exceptionCaught);
}

