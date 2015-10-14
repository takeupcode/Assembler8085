//
//  ParserEquScenarios.cpp
//  Assembler8085
//
//  Created by Wahid Tanner on 10/12/15.
//

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Assembler8085/Parser.h"
#include "../Assembler8085/SyntaxErrorException.h"
#include "../Assembler8085/MnemonicParserEqu.h"

using namespace std;
using namespace MuddledManaged;
using namespace Assembler8085;

DESIGNER_SCENARIO( GeneralParser, "Construction/Normal", "MnemonicParserEqu can be constructed." )
{
    Parser parser("");
    MnemonicParserEqu parserEqu("equ", parser);
}

DESIGNER_SCENARIO( GeneralParser, "Parsing/Normal", "ParserEqu can parse file." )
{
    Parser parser("Equ.s");
    shared_ptr<MnemonicParserEqu> parserEqu(new MnemonicParserEqu("equ", parser));
    parser.addParser(parserEqu);
    parser.parse();

    string symbol;
    verifyTrue(parser.getSymbol("addr1", symbol));
    verifyEqual("2020h", symbol);

    verifyTrue(parser.getSymbol("addr2", symbol));
    verifyEqual("2040h", symbol);
}
