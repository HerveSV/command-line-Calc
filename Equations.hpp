//
//  Equations.hpp
//  BetterCalc
//
//  Created by Hervé Schmit-Veiler on 3/12/19.
//  Copyright © 2019 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef Equations_hpp
#define Equations_hpp

#include <stdio.h>
#include <vector>

class Equation;

enum Operand_type
{
    TYPE_NUMBER,
    TYPE_OPERATOR,
    TYPE_BRACKETED_EXPRESSION,
};

struct Operand
{
    Operand_type type;
    double num = 0;
    std::string numStr;
    char op;
    //int brackIndex = 0;
    //std::vector<Operand> brackExpr;
    //Equation bracketExpr();
};

struct Section
{
    std::vector<Operand> Expr;
    double answer = 0;
};

typedef std::vector<Section> Equat;
typedef std::vector<std::string> ParseString;

class Equation
{
private:
    //Expr m_expr{'q'};
    
    std::string m_exprStr;
    ParseString m_exprParsed;
    Equat m_equation;
    const int brackets_not_equal = 2;
    
    double applyOp(char op, double num1, double num2);
    void solveExpr(Equat &equat, int sectIndex, int &brackSubIndex);
    bool numCheck(char n);
    int numDigits(double n);
    //void parseNum(Expr &expr, int &exprIndex, ParseString &parser, int &i);
    //void parseChar(Expr &expr, int &exprIndex, ParseString &parser, int &i);
    //void parseBrack(Expr &expr, int &exprIndex, ParseString &parser, int &i, char brackID);
    
    
public:
    //Equation(void);
    
    void define();
    int inputEquation();
    double solve();
    void format();
    std::string retrieveStr();
    ParseString retrieveParsed();
    void debugShoweEquation();

};

class Bracketed_Expression : Equation
{
    
};

#endif /* Equations_hpp */
