#include "LexemAnalyzer.h"

MathParser::LexemAnalyzer::LexemAnalyzer(std::string expression) : lexemIndex(0)
{
	std::string::iterator it = expression.begin();
	while (it != expression.end()) {
		char currentExpressionCharacter = *it;
		switch (currentExpressionCharacter)
		{
		case '(':
			lexenList.push_back(Lexem(LexemType::LEFT_PARENTHESIS, std::string(1, *it)));
			break;
		case ')':
			lexenList.push_back(Lexem(LexemType::RIGHT_PARENTHESIS, std::string(1, *it)));
			break;
		case '+':
			lexenList.push_back(Lexem(LexemType::PLUS, std::string(1, *it)));
			break;
		case '-':
			lexenList.push_back(Lexem(LexemType::MINUS, std::string(1, *it)));
			break;
		case '*':
			lexenList.push_back(Lexem(LexemType::MUL, std::string(1, *it)));
			break;
		case '/':
			lexenList.push_back(Lexem(LexemType::DIV, std::string(1, *it)));
			break;
		case ' ':
			break;
		default:
			const std::string DIGITS_CHARACTERS = "0123456789";
			const std::string DECIMAL_DELIMITER = ".";
			std::string numberAccumulator = "";
			while ((DIGITS_CHARACTERS.find(currentExpressionCharacter) != std::string::npos) || 
				   (DECIMAL_DELIMITER.find(currentExpressionCharacter) != std::string::npos)) {
				numberAccumulator += currentExpressionCharacter;
				if (++it != expression.end()) {
					currentExpressionCharacter = *it;
				} else {
					break;
				}
			}
			lexenList.push_back(Lexem(LexemType::NUMBER, numberAccumulator));
			--it;
			break;
		}
		++it;
	}
	lexenList.push_back(MathParser::Lexem(MathParser::LexemType::EOF_EXPR, "eof"));
}

MathParser::Lexem& MathParser::LexemAnalyzer::next() {
	if (lexemIndex >= lexenList.size()) {
		//todo Exeption
	}
	return lexenList[lexemIndex++];
}

void MathParser::LexemAnalyzer::back() {
	--lexemIndex;
}

std::vector<MathParser::Lexem>& MathParser::LexemAnalyzer::getLexemList()
{
	return lexenList;
}

int MathParser::LexemAnalyzer::getPos() {
	return lexemIndex;
}

MathParser::Lexem::Lexem(LexemType lt, std::string v) : lexemType(lt), value(v)
{
}

bool MathParser::Lexem::operator==(const Lexem& lexem) const {
	return lexemType == lexem.lexemType && value == lexem.value;
}

MathParser::LexemType& MathParser::Lexem::getType()
{
	return lexemType;
}

std::string& MathParser::Lexem::getValue()
{
	return value;
}
