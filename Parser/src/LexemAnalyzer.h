#pragma once

#include <string>
#include <vector>

namespace MathParser {
	enum class LexemType
	{
		LEFT_PARENTHESIS,	// '(' 
		RIGHT_PARENTHESIS,	// ')'
		PLUS,				// '+'
		MINUS,				// '-'
		MUL,				// '*'
		DIV,				// '/'
		NUMBER,
		EOF_EXPR
	};

	class Lexem {
	private:
		LexemType lexemType;
		std::string value;
	public:
		Lexem(LexemType lexemType, std::string value);
		bool operator==(const Lexem& lexem) const;
		LexemType& getType();
		std::string& getValue();
	};

	class LexemAnalyzer {
	private:
		std::vector<Lexem> lexenList;
		int lexemIndex;
	public:
		LexemAnalyzer(std::string expression);
		Lexem& next();
		void back();
		int getPos();
		std::vector<Lexem>& getLexemList();
	};
}