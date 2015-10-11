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

    try
    {
        parser.parse();
    }
    catch (SyntaxErrorException & e)
    {
        verifyEqual(8, e.line());
        verifyEqual(13, e.column());
    }
}

