#include "Parser.h"

double MathParser::Parser::expression(MathParser::LexemAnalyzer& lexemAnalyzer) {
	MathParser::Lexem lexem = lexemAnalyzer.next();
	if (lexem.getType() == MathParser::LexemType::EOF_EXPR) {
		return 0;
	} else {
		lexemAnalyzer.back();
		return plusMinus(lexemAnalyzer);
	}
}

double MathParser::Parser::plusMinus(MathParser::LexemAnalyzer& lexemAnalyzer) {
	double value = mulDiv(lexemAnalyzer);
	while (true) {
		MathParser::Lexem lexem = lexemAnalyzer.next();
		if (lexem.getType() == MathParser::LexemType::PLUS) {
			value += mulDiv(lexemAnalyzer);
		}
		else if (lexem.getType() == MathParser::LexemType::MINUS) {
			value -= mulDiv(lexemAnalyzer);
		}
		else {
			lexemAnalyzer.back();
			break;
		}
	}
	return value;
}

double MathParser::Parser::mulDiv(MathParser::LexemAnalyzer& lexemAnalyzer) { 
	double value = factor(lexemAnalyzer);
	while (true) {
		MathParser::Lexem lexem = lexemAnalyzer.next();
		if (lexem.getType() == MathParser::LexemType::MUL) {
			value *= factor(lexemAnalyzer);
		} else if (lexem.getType() == MathParser::LexemType::DIV) {
			value /= factor(lexemAnalyzer);
		} else {
			lexemAnalyzer.back();
			break;
		}
	}
	return value;
}

double MathParser::Parser::factor(MathParser::LexemAnalyzer& lexemAnalyzer) {
	MathParser::Lexem lexem = lexemAnalyzer.next();
	if (lexem.getType() == MathParser::LexemType::LEFT_PARENTHESIS) {
		double resExpression = expression(lexemAnalyzer);
		MathParser::Lexem lexemEnd = lexemAnalyzer.next();
		if (lexemEnd.getType() == MathParser::LexemType::RIGHT_PARENTHESIS) {
			return resExpression;
		} 
		else {
			// Error
		}
	} 
	else if (lexem.getType() == MathParser::LexemType::MINUS) {
		return -factor(lexemAnalyzer);
	}
	else if (lexem.getType() == MathParser::LexemType::NUMBER) {
		return std::stod(lexem.getValue());
	}
}
