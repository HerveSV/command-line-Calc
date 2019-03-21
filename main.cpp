//
//  main.cpp
//  BetterCalc
//
//  Created by Hervé Schmit-Veiler on 3/12/19.
//  Copyright © 2019 Hervé Schmit-Veiler. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#include "Equations.hpp"

void pringq();

/* pringg()
{
    std::cout<<"g"<<std::endl;
    pringq();
}

void pringq()
{
    std::cout<<"q"<<std::endl;
    pringq();
    
}*/
/*Eq retrieveInp()
{
    std::cout<< "Hello" <<std::endl;
    Eq equation;
    char inpDigit;
    do {
        std::cout<< "1";
        inpDigit = 'x';
        std::cin>>inpDigit;
        equation.push_back(inpDigit);
    } while (inpDigit != 'x');
    std::cout<<"Stop"<<std::endl;
    return equation;
}*/



int main(int argc, const char * argv[])
{
    std::cout<<"Enter equation"<<std::endl;
    Equation e;
    e.inputEquation();
    
    e.debugShoweEquation();
    //e.define();
    /*std::cout<< e.retrieveStr() <<std::endl;
    std::vector<std::string> q = e.retrieveParsed();
    for(int i = 0; i<q.size(); ++i)
    {
        std::cout<<i<<". "<<q[i]<<std::endl;
    }
    
    std::stringstream ss;*/
    //ouble answer = e.solve();
    //std::cout<<"\nAnswer: "<<answer<<std::endl;
    
    
    //std::string y = "hey";
    //ss<<y;
    //std::cout<<y<<std::endl;
    //std::string g = "10101";
    //pringq();
    //std::string p = e.retrieveStr();
    
    
    //std::cout<<"p. "<<p[8]<<std::endl;*/
    /*std::cout<<"Enter equation"<<std::endl;
    char string[255];
    std::cin.getline(string, 255);
    
    std::cout<<string<<std::endl;
    */
    //char i;
    //std::cin>>i;
    //std::cout<<"\n"<<i<<std::endl;
    /*std::vector<int> yee = {1,2,3,4,5,6,7,8,9,10};
    for(auto &i:yee) {
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
    yee.erase(yee.begin()+1,yee.begin()+4);
    for(auto &i:yee) {
        std::cout<<i<<" ";
    }
    std::cout<<"\n";*/
    
    
    return 0;
        
}

