//
//  Equations.cpp
//  BetterCalc
//
//  Created by Hervé Schmit-Veiler on 3/12/19.
//  Copyright © 2019 Hervé Schmit-Veiler. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <list>
#include <sstream>
#include <string>
#include "Equations.hpp"


int Equation::numDigits(double n)
{
    std::cout<<"Hey "<<n<<std::endl;
    int digits = 0;
    std::string nStr;
    std::stringstream ss(n);
    ss>>nStr;
    std::cout<<nStr;
    digits = nStr.size();
    return digits;
}



bool Equation::numCheck(char n)
{
    if(n=='0'||n=='1'||n=='2'||n=='3'||n=='4'||n=='5'||n=='6'||n=='7'||n=='8'||n=='9'||n=='.')
        return true;
    return false;
}
/*void Equation::parseNum(Expr &expr, int &exprIndex, ParseString &parser, int &i)
{
    std::stringstream si;
    si<<parser[i];
    expr[exprIndex].type = TYPE_NUMBER;
    si>>expr[exprIndex].num;
    ++exprIndex;
    if(parser[i+1]=="(" && i+1<parser.size())
    {
        expr[exprIndex].type = TYPE_OPERATOR;
        expr[exprIndex].op = '*';
        ++exprIndex;
    }
}*?

/*void Equation::parseChar(Expr &expr, int &exprIndex, ParseString &parser, int &i)
{
    std::stringstream si;
    si<<parser[i];
    expr[exprIndex].type = TYPE_OPERATOR;
    si>>expr[exprIndex].op;
    ++exprIndex;
}

void Equation::parseBrack(Expr &expr, int &exprIndex, ParseString &parser, int &i, char brackID)
{
    expr[exprIndex].type = TYPE_BRACKETED_EXPRESSION;
    ++i;
    //int q = 0;
    std::string closeBrack = ")";
    closeBrack.push_back(brackID);
    std::cout<<brackID<<std::endl;
    for(int q = 0; parser[i]!= closeBrack && i < parser.size()-1; ++i, ++q)
    {
        if(numCheck(parser[i][0]))
        {
            expr[exprIndex].brackExpr.resize(expr[exprIndex].brackExpr.size()+1);
            parseNum(expr[exprIndex].brackExpr, q, parser, i);
            /*std::stringstream si;
             si<<parser[i];
             expr[exprIndex].brackExpr[q].type = TYPE_NUMBER;
             si>>expr[exprIndex].brackExpr[q].num;
             ++exprIndex;
             if(parser[i+1]=="(")
             {
             expr[exprIndex].type = TYPE_OPERATOR;
             expr[exprIndex].op = '*';
             ++exprIndex;
             }
        }
        else if(parser[i] == "(")
        {
            expr[exprIndex].brackExpr.resize(expr[exprIndex].brackExpr.size()+1);
            parseBrack(expr[exprIndex].brackExpr, q, parser, i, ++brackID);
            //expr[exprIndex];
        }
        else
        {
            expr[exprIndex].brackExpr.resize(expr[exprIndex].brackExpr.size()+1);
            parseChar(expr[exprIndex].brackExpr, q, parser, i);
        }
        //expression[exprIndex].bracketExpr().m_expression[q].num = 4;
    }
    ++i;
    
}*/
double Equation::applyOp(char op, double num1, double num2)
{
    switch(op)
    {
        case '*':
            return (num1*num2);
            break;
        case '/':
            return (num1/num2);
            break;
        case '+':
            return (num1+num2);
            break;
        case '-':
            return (num1-num2);
            break;
        default:
            return 0;
            break;
        
    }
}

void Equation::solveExpr(Equat &equat, int sectIndex, int &brackSubIndex)
{
    std::vector<Operand> &expr = equat[sectIndex].Expr;
    
    for(int i=0; i<expr.size(); ++i) {
        if(expr[i].type == TYPE_OPERATOR && expr[i].op == '#') {
            expr[i].num = equat[brackSubIndex].answer;
            --brackSubIndex;
            expr[i].type = TYPE_NUMBER;
        }
        if(expr.size() == 1) {
            equat[sectIndex].answer = expr[0].num;
        }
    }
    for(int i=0; i<expr.size(); ++i) {
        if(expr[i].type == TYPE_OPERATOR && (expr[i].op == '*' || expr[i].op == '/'))
        {
            expr[i-1].num = applyOp(expr[i].op, expr[i-1].num, expr[i+1].num);
            expr.erase(expr.begin()+i, expr.begin()+i+2);
        }
        if(expr.size() == 1) {
            equat[sectIndex].answer = expr[0].num;
        }
    }
    for(int i=0; i<expr.size(); ++i) {
        if(expr[i].type == TYPE_OPERATOR && (expr[i].op == '+' || expr[i].op == '+'))
        {
            expr[i-1].num = applyOp(expr[i].op, expr[i-1].num, expr[i+1].num);
            expr.erase(expr.begin()+i, expr.begin()+i+2);
        }
        if(expr.size() == 1) {
            equat[sectIndex].answer = expr[0].num;
        }
    }
    std::cout<<sectIndex<<" "<<equat[sectIndex].answer<<std::endl;
    
}

double Equation::solve()
{
    int answer;
    int brackIndex = m_equation.size()-1;
    for(int i = m_equation.size()-1; i>=0; --i)
    {
        solveExpr(m_equation, i, brackIndex);
    }
    answer = m_equation[0].answer;
    
    return answer;
}


/*void Equation::define()
{
    std::string string;
    //char string[255]
    std::cin>>string;
    std::cout<<string<<std::endl;
    m_exprStr = string;
    std::cout<<string<<std::endl;
    ParseString parser(string.size());
    
    bool startNew = true;
    bool digNum = numCheck(string[0]);
    bool lastDigNum = true;
    int strIndex = 0;
    char openBrackID = 'a';
    char closeBrackID = 'a';
    for(int i=0; i<string.size();++i)
    {
        digNum = numCheck(string[i]);
        //if(i==0)
        //    digNum = true;
        if(digNum && lastDigNum)
        {
            startNew = false;
            //++strIndex;
        }
        else if((digNum && !lastDigNum)||(!digNum && lastDigNum)||(!digNum && !lastDigNum))
        {
            startNew = true;
            if(i!=0)
                ++strIndex;
        }
        if(i == 0)
        {
            startNew = true;
        }
        
        if(!lastDigNum || !digNum)
        {
            //    startNew = true;
        }
        
        
        if(!startNew)
        {
            parser[strIndex] += string[i];
            //std::cout<<i<<".  "<<parser[strIndex]<<std::endl;
        }
        else if(startNew)
        {
            //parser.push_back(" ");
            //parser[parser.size()]
            //parser.resize(parser.size()+1);
            //parser.back().push_back(string[i]);
            //startNew = true;
            if(string[i] == '(')
            {
                
                parser[strIndex] = string[i];
                parser[strIndex] += openBrackID;
                closeBrackID = openBrackID;
                ++openBrackID;
                
            }
            else if(string[i] == ')')
            {
                parser[strIndex] = string[i];
                parser[strIndex] += closeBrackID;
                --closeBrackID;
            }
            else
                parser[strIndex] = string[i];
            //std::cout<<i<<". "<<parser[strIndex]<<std::endl;
        }
        
        lastDigNum = digNum;
    }
    
    parser.resize(strIndex+1);
    
    m_exprParsed = parser;
    
    ParseString x = parser;
    
    Expr expression(string.size());
    expression.resize(string.size());
    int exprIndex = 0;
    for(int i = 0; i<parser.size(); ++i)
    {
        if(numCheck(parser[i][0]))
        {
            parseNum(expression, exprIndex, parser, i);
            std::stringstream si;
             si<<parser[i];
             expression[exprIndex].type = TYPE_NUMBER;
             si>>expression[exprIndex].num;
             ++exprIndex;
             if(parser[i+1]=="(")
             {
             expression[exprIndex].type = TYPE_OPERATOR;
             expression[exprIndex].op = '*';
             ++exprIndex;
             }
        }
        else if(parser[i][0] == '(')
        {
            parseBrack(expression, exprIndex, parser, i, parser[i][1]);
            
            //do {
            
            //} while (parser[i-1]!=")"|| i > parser.size()-1);
        }
        else
        {
            parseChar(expression, exprIndex, parser, i);
        }
    }
    
    
    
}*/

int Equation::inputEquation()
{
    std::string string;
    //char string[255]
    std::cin>>string;
    string.push_back(')');
    string.resize(string.size()+1);
    for(int i = string.size()-1; i>0; --i)
    {
        string[i] = string[i-1];
    }
    string[0] = '(';
    std::cout<<string<<std::endl;
    
    for(int i = 0; i<string.size(); ++i) {
        if(numCheck(string[i]) && string[i+1] == '(') {
            string.insert(i+1, "*");
        }
        else if(string[i]=='-' && numCheck(string[i-1]) && numCheck(string.at(i+1)))
        {
            string.insert(i, "+");
        }
    }
    
    m_exprStr = string;
    
    int openBrack = 0;
    int closeBrack = 0;
    for(int i = 0; i<string.size(); ++i)
    {
        if(string[i] == '(')
        {
            ++openBrack;
        }
        else if(string[i] == ')')
        {
            ++closeBrack;
        }
    }
    std::cout<<closeBrack<<std::endl;
    if(openBrack != closeBrack)
    {
        return brackets_not_equal;
    }
    
    std::vector<std::array<int, 2>> iterateBrackets(openBrack);
    int temp2 = closeBrack;
    int temp1 = 1;
    for(int i = 0; temp2 > 0 && temp1 <= openBrack; ++i, --temp2, ++temp1)
    {
        iterateBrackets[i][0] = temp1;
        iterateBrackets[i][1] = temp2;
        
        std::cout<<i<<" "<<temp1<<", "<<temp2<<std::endl;
        
        
    }
    //for(int i = 0; i<openBrack; ++i)
    //{
        
    //}
    
    
    //int brackIndex = closeBrack-1;
    ParseString parser(closeBrack);
    
    for(int i = 0; i < closeBrack; ++i)
    {
        int numOpen = 0;
        int numClose = 0;
        int openEncount = 0;
        //int closeEncount = 0;
        //bool ref = false;
        bool inBrackOpen = false;
        for(int j = 0; j < string.size(); ++j){
            if(numClose == iterateBrackets[i][1]){
                break;
            }
            
            if(numOpen == iterateBrackets[i][0]) {
                
                if(string[j] == '(') {
                    ++openEncount;
                    if(!inBrackOpen)
                    {
                        parser[i] += '#';
                        inBrackOpen = true;
                    }
                }
                else if(string[j] == ')') {
                    ++numClose;
                    //inBrackOpen = false;
                }
                else if(!inBrackOpen){
                    parser[i] += string[j];
                }

            
            }
            else if(string[j] == '(') {
                ++numOpen;
            }
            else if(string[j] == ')') {
                ++numClose;
            }
            
            
            if(openEncount > numClose) {
                inBrackOpen = true;
            }
            else if(openEncount == numClose) {
                inBrackOpen = false;
            }
                
        }
        
    }
    m_exprParsed = parser;
    
    std::vector<ParseString> extraParse(parser.size());
    
    //use old technique
    
    Equat equation(parser.size());
    
    for(int i = 0; i < parser.size(); ++i)
    {
        int strIndex = 0;
        //equation[i].Expr.resize(parser[i].size());
        bool newNum = true;
        //equation[i].Expr.resize(parser[i].size());
        for(int j = 0; j < parser[i].size(); ++j)
        {
            
            if(numCheck(parser[i][j]) || parser[i][j] == '-') {
                //Operand temp;
                //temp.type = TYPE_NUMBER;
                if(parser[i][j] == '-') {
                    equation[i].Expr.resize(j+1);
                    if(j!= 0)
                        ++strIndex;
                    equation[i].Expr[strIndex].numStr += parser[i][j];
                    equation[i].Expr[strIndex].type = TYPE_NUMBER;
                    //std::cout<<"\n num "<<equation[i].Expr[strIndex].numStr;
                    newNum = false;
                }
                else if(newNum) {
                    //equation[i].Expr.resize(j+1);
                    equation[i].Expr.resize(j+1);
                    if(j!=0)
                        ++strIndex;
                    equation[i].Expr[strIndex].numStr += parser[i][j];
                    equation[i].Expr[strIndex].type = TYPE_NUMBER;
                    //std::cout<<"\n num "<<equation[i].Expr[strIndex].numStr;
                    newNum = false;
                    
                }
                else {
                    //equation[i].Expr[strIndex].type = TYPE_OPERATOR;
                    equation[i].Expr[strIndex].numStr += parser[i][j];
                    std::cout<<equation[i].Expr[strIndex].numStr;
                    //newNum = false;
                }
                
    
                
                //parser[i];
            }
            else
            {
                //equation[i].Expr.resize(j+1);
                ++strIndex;
                equation[i].Expr[strIndex].type = TYPE_OPERATOR;
                equation[i].Expr[strIndex].op = parser[i][j];
                //std::cout<<"\n op "<<equation[i].Expr[strIndex].op;
                ++strIndex;
                newNum = true;
            }
        }
        //std::cout<<"\n\n";
    }
    
    for(int i = 0; i<equation.size(); ++i) {
        for(int j = 0; j<equation[i].Expr.size(); ++j) {
            if(equation[i].Expr[j].type == TYPE_NUMBER) {
                std::stringstream st;
                st<<equation[i].Expr[j].numStr;
                double b;
                st>>b;
                equation[i].Expr[j].num = b;
            }
            else if(equation[i].Expr[j].type == TYPE_OPERATOR && equation[i].Expr[j].op == '#') {
                equation[i].Expr[j].type = TYPE_BRACKETED_EXPRESSION;
            }
        }
    }
    
    m_equation = equation;
    
    //std::cout<<"Hea: "<<equation[1].Expr[7].num<<std::endl;
    
//    for(int i = 0; i<equation.size(); ++i) {
//        std::cout<<i<<":: "<<std::endl;
//        for (int j = 0; j < equation[i].Expr.size(); ++j) {
//            equation[i].Expr.shrink_to_fit();
//            if(equation[i].Expr[j].type == TYPE_NUMBER) {
//                std::cout<<"num("<<equation[i].Expr[j].numStr<<")"<<std::endl;
//            }
//            else if(equation[i].Expr[j].type == TYPE_OPERATOR) {
//                std::cout<<"op("<<equation[i].Expr[j].op<<")"<<std::endl;
//            }
//        }
//        std::cout<<"\n\n";
//    }
    
    return 0;
}


std::string Equation::retrieveStr()
{
    return m_exprStr;
}

ParseString Equation::retrieveParsed()
{
    return m_exprParsed;
}

void Equation::debugShoweEquation() {
    Equat equa = m_equation;
    
    for(int i = 0; i<equa.size();++i) {
        std::cout<<"\n"<<i<<":"<<std::endl;
        for(int j = 0; j<equa[i].Expr.size(); ++j) {
            if(equa[i].Expr[j].type ==TYPE_NUMBER)
            {
                std::cout<<"num("<<equa[i].Expr[j].num<<"), ";
            }
            else if(equa[i].Expr[j].type ==TYPE_OPERATOR)
            {
                std::cout<<"op("<<equa[i].Expr[j].op<<"), ";
            }
            else if(equa[i].Expr[j].type ==TYPE_BRACKETED_EXPRESSION)
            {
                std::cout<<"brack("<<equa[i].Expr[j].op<<"), ";
            }

        }
    }
}
