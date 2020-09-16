#pragma once
#include <string>
#include "LexemAnalyzer.h"

namespace MathParser {
	
	class Parser {
	public:
		double expression(MathParser::LexemAnalyzer& lexemAnalyzer);
		double plusMinus(MathParser::LexemAnalyzer& lexemAnalyzer);
		double mulDiv(MathParser::LexemAnalyzer& lexemAnalyzer);
		double factor(MathParser::LexemAnalyzer& lexemAnalyzer);
	};

}