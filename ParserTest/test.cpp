#include "pch.h"
#include "../Parser/src/LexemAnalyzer.h"
#include "../Parser/src/Parser.h"

TEST(LexemAnalyzer, Constructor) {
  MathParser::LexemAnalyzer lexemAnalyzer("(334.22 + 33 - 44 * 55 / 66 + (2 + 22 * 3))");
  std::vector<MathParser::Lexem> lexems = lexemAnalyzer.getLexemList();
  std::vector<MathParser::Lexem> expected { 
      MathParser::Lexem(MathParser::LexemType::LEFT_PARENTHESIS, "("),
      MathParser::Lexem(MathParser::LexemType::NUMBER, "334.22"),
      MathParser::Lexem(MathParser::LexemType::PLUS, "+"),
      MathParser::Lexem(MathParser::LexemType::NUMBER, "33"),
      MathParser::Lexem(MathParser::LexemType::MINUS, "-"),
      MathParser::Lexem(MathParser::LexemType::NUMBER, "44"),
      MathParser::Lexem(MathParser::LexemType::MUL, "*"),
      MathParser::Lexem(MathParser::LexemType::NUMBER, "55"),
      MathParser::Lexem(MathParser::LexemType::DIV, "/"),
      MathParser::Lexem(MathParser::LexemType::NUMBER, "66"),
      MathParser::Lexem(MathParser::LexemType::PLUS, "+"),
      MathParser::Lexem(MathParser::LexemType::LEFT_PARENTHESIS, "("),
      MathParser::Lexem(MathParser::LexemType::NUMBER, "2"),
      MathParser::Lexem(MathParser::LexemType::PLUS, "+"),
      MathParser::Lexem(MathParser::LexemType::NUMBER, "22"),
      MathParser::Lexem(MathParser::LexemType::MUL, "*"),
      MathParser::Lexem(MathParser::LexemType::NUMBER, "3"),
      MathParser::Lexem(MathParser::LexemType::RIGHT_PARENTHESIS, ")"),
      MathParser::Lexem(MathParser::LexemType::RIGHT_PARENTHESIS, ")"),
      MathParser::Lexem(MathParser::LexemType::EOF_EXPR, "eof")
  };
  ASSERT_EQ(lexems.size(), expected.size()) << "Vectors x and y are of unequal length";
  for (int i = 0; i < lexems.size(); ++i) {
      EXPECT_EQ(lexems[i], expected[i]) << "Vectors x and y differ at index " << i;
  }
  EXPECT_TRUE(true);
}

TEST(LexemAnalyzer, Number) {
    MathParser::LexemAnalyzer lexemAnalyzer("334");
    std::vector<MathParser::Lexem> lexems = lexemAnalyzer.getLexemList();
    std::vector<MathParser::Lexem> expected{
        MathParser::Lexem(MathParser::LexemType::NUMBER, "334"),
        MathParser::Lexem(MathParser::LexemType::EOF_EXPR, "eof")
    };
    ASSERT_EQ(lexems.size(), expected.size());
    for (int i = 0; i < lexems.size(); ++i) {
        EXPECT_EQ(lexems[i], expected[i]);
    }
    EXPECT_TRUE(true);
}

TEST(LexemAnalyzer, Next) {
    MathParser::LexemAnalyzer lexemAnalyzer("(334.22 + 33 - 44 * 55 / 66 + (2 + 22 * 3))");
    MathParser::Lexem expected = MathParser::Lexem(MathParser::LexemType::NUMBER, "22");
    for (int i = 0; i < 14; i++) {
        lexemAnalyzer.next();
    }
    EXPECT_EQ(lexemAnalyzer.next(), MathParser::Lexem(MathParser::LexemType::NUMBER, "22"));
    EXPECT_TRUE(true);
}

TEST(LexemAnalyzer, Prev) {
    MathParser::LexemAnalyzer lexemAnalyzer("(334.22 + 33 - 44 * 55 / 66 + (2 + 22 * 3))");
    MathParser::Lexem expected = MathParser::Lexem(MathParser::LexemType::NUMBER, "22");
    for (int i = 0; i < 14; i++) {
        lexemAnalyzer.next();
    }
    lexemAnalyzer.back();
    EXPECT_EQ(lexemAnalyzer.next(), MathParser::Lexem(MathParser::LexemType::PLUS, "+"));
    EXPECT_TRUE(true);
}

TEST(Parser, MulDiv) {
    MathParser::LexemAnalyzer lexemAnalyzer("3 * 4");
    MathParser::Parser parser;
    double res = parser.expression(lexemAnalyzer);
    EXPECT_EQ(res, 12);
    EXPECT_TRUE(true);
}

TEST(Parser, PlusMinus) {
    MathParser::LexemAnalyzer lexemAnalyzer("3 + 4");
    MathParser::Parser parser;
    double res = parser.expression(lexemAnalyzer);
    EXPECT_EQ(res, 7);
    EXPECT_TRUE(true);
}

TEST(Parser, Factor2) {
    MathParser::LexemAnalyzer lexemAnalyzer("(334)");
    MathParser::Parser parser;
    double res = parser.factor(lexemAnalyzer);
    EXPECT_EQ(res, 334);
    EXPECT_TRUE(true);
}

TEST(Parser, Text2) {
    MathParser::LexemAnalyzer lexemAnalyzer("3 + 4 * 4");
    MathParser::Parser parser;
    double res = parser.expression(lexemAnalyzer);
    EXPECT_EQ(res, 19);
    EXPECT_TRUE(true);
}
