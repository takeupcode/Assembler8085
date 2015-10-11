//
//  ParserScenarios.cpp
//  Assembler8085
//
//  Created by Wahid Tanner on 10/11/15.
//

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Assembler8085/Parser.h"

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
