//
//  functions.h
//  Cramer's Simulator (System of linear equations)
//
//  Created by Omar shaalan on 4/26/22.
//  Copyright © 2022 Omar shaalan. All rights reserved.
//

#ifndef functions_h
#define functions_h
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;


vector<string> UnKnowns;

class Terms // A term is definded using 3 things, the unkown variable, the coeff, and the sign
{
  public:
    string unknown;
    float coeff;
    string Sign;
    string Term; // Extra to store the whole term
    Terms(string Trm, string sign) ///constructor
    {
        Term = Trm;
        Sign = sign;
        int i;
        for (i = 0; i < Term.length(); i++)
        {
            if (isalpha(Term[i]))//we find the coffecient of the term
                break;
        }
        coeff = atoi(Term.substr(0, i).c_str()); //transfereing the number from string to int
        if (i == 0)
            coeff = 1; //e,g x+4
        unknown = Term.substr(i, 1); //the unkown
        int flag = 0;
        if (unknown != "") //If our term is not a constant
        {
            for (int i = 0; i < UnKnowns.size(); i++)
            {
                if (UnKnowns[i] == unknown)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                UnKnowns.push_back(unknown);
        }
    }
};
class Parsing_Equations_Side //Dividing each side into terms
{
  public:
    vector<Terms> TmpTerms; //A vector to store the terms so we can then use them when we want to chnage the sides of terms(from RHS -> LHS and vice versa)
    vector<Terms> CurTerms; 
    void SetSide(string side)
    {
        string CurTerm = ""; //We are going to add in it the term
        string TmpOper = "+"; //Added when no sign is written (6x - 10) the 6 has a +ve sign and it is NOT written
        int i;
        for (i = 0; i < side.length(); i++)
        {
            if (side.substr(i, 1) == "+" || side.substr(i, 1) == "-") //Finding the first sign either '+' or '-'
            {
                if (CurTerm != "") //A condition to check whther the CurTerm already has a stored value
                {
                    cout << TmpOper << CurTerm << endl; //The stored curren term is displayed to the user as an output
                    TmpTerms.push_back(Terms(CurTerm, TmpOper));//Then it is pushed back
                }
                TmpOper = side.substr(i, 1); //Adding the new operator of the next term
                CurTerm = ""; //Emptying the Current Term var so we can store the next term
            }
            else
                CurTerm = CurTerm + side.substr(i, 1); //in the case that the next character in the string is not an operator, we want to add the whole part as the curr term
        }
        if (i == side.length()) //When we get out of the loop by reaching the end of the string
        {
            if (CurTerm != "") //A condition in case the Current term is still filled with a value
            {
                cout << TmpOper << CurTerm << endl; //Display this value as an output
                TmpTerms.push_back(Terms(CurTerm, TmpOper));
            }
        }
    }
    void Adding_Same_Unknowns() 
    {
        int flag;
        for (int j = 0; j < TmpTerms.size(); j++)
        {
            flag = 0;
            for (int i = 0; i < CurTerms.size(); i++)
            {
                if (CurTerms[i].unknown == TmpTerms[j].unknown)
                {
                    float c = CurTerms[i].coeff;
                    float t = TmpTerms[j].coeff;
                    if (CurTerms[i].Sign == "-")
                        c = -1 * CurTerms[i].coeff;
                    if (TmpTerms[j].Sign == "-")
                        t = -1 * TmpTerms[j].coeff;
                    CurTerms[i].coeff = c + t;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                CurTerms.push_back(Terms(TmpTerms[j].Term, TmpTerms[j].Sign));
        }
    }
};
class Equation // A class designed for dividng the equations into a LHS and a RHS
{
  public:
    Parsing_Equations_Side TmpLHS, TmpRHS, LHS, RHS;
    Equation(string Eqn) //constructor
    {
        int EqualIndex = Eqn.find("="); //Finding the index of the '=' so we can divide it into LHS and RHS
        cout << "New Equation : " << endl;
        cout << "LHS : " << Eqn.substr(0, EqualIndex) << endl; //The LHS
        cout << "RHS : " << Eqn.substr(EqualIndex + 1) << endl; //The RHS
        //Finished dividing the equation, now we divide each side using the parsing equations side class
        
        //Calling the SetSide function in order to divide the LHS into terms
        cout << "LHS Terms : " << endl;
        TmpLHS.SetSide(Eqn.substr(0, EqualIndex)); //Having the LHS assigned to the LHS
        cout << "RHS Terms : " << endl;
       //Calling the SetSide function in order to divide the RHS into terms
        TmpRHS.SetSide(Eqn.substr(EqualIndex + 1)); //Having the LHS assigned to the RHS
        string Oper = "";
        for (int i = 0; i < TmpLHS.TmpTerms.size(); i++)
        {
            if (TmpLHS.TmpTerms[i].unknown == "")
            {
                if (TmpLHS.TmpTerms[i].Sign == "-")
                    Oper = "+";
                else if (TmpLHS.TmpTerms[i].Sign == "+")
                    Oper = "-";
                RHS.TmpTerms.push_back(Terms(TmpLHS.TmpTerms[i].Term, Oper));// After changing thesign we add to the RHS
            }
            else
                LHS.TmpTerms.push_back(Terms(TmpLHS.TmpTerms[i].Term, TmpLHS.TmpTerms[i].Sign));//If it has an unknown it will be assigned to the LHS
        }
        //Same loop for the RHS
        for (int k = 0; k < TmpRHS.TmpTerms.size(); k++)
        {
            if (TmpRHS.TmpTerms[k].unknown != "")
            {
                if (TmpRHS.TmpTerms[k].Sign == "-")
                    Oper = "+";
                else if (TmpRHS.TmpTerms[k].Sign == "+")
                    Oper = "-";
                LHS.TmpTerms.push_back(Terms(TmpRHS.TmpTerms[k].Term, Oper));
            }
            else
            {
                RHS.TmpTerms.push_back(Terms(TmpRHS.TmpTerms[k].Term, TmpRHS.TmpTerms[k].Sign));
            }
        }
        LHS.Adding_Same_Unknowns();
        RHS.Adding_Same_Unknowns();
    }
};
vector<Equation> Equations; //A vector that will have all the equations pushed back
vector<vector<float> > CoeffsMatrix;
vector<float> Constants_Matrix;

class Utility
{
  public:
    static void SetMatrix()
    {
        for (int i = 0; i < Equations.size(); i++)
        {
            vector<float> coef;
            float c = 0;
            for (int j = 0; j < UnKnowns.size(); j++)
            {
                int flag = 0;
                for (int k = 0; k < Equations[i].LHS.CurTerms.size(); k++)
                {
                    if (UnKnowns[j] == Equations[i].LHS.CurTerms[k].unknown)
                    {
                        c = Equations[i].LHS.CurTerms[k].coeff;
                        if (Equations[i].LHS.CurTerms[k].Sign == "-")
                            c = -1 * Equations[i].LHS.CurTerms[k].coeff;
                        coef.push_back(c);
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                    coef.push_back(0);
            }
            CoeffsMatrix.push_back(coef);
            c = Equations[i].RHS.CurTerms[0].coeff;
            if (Equations[i].RHS.CurTerms[0].Sign == "-")
                c = -1 * Equations[i].RHS.CurTerms[0].coeff;
            Constants_Matrix.push_back(c);
        }
    }
    static vector<vector<float> > GetVariableMatrix(int var, vector<vector<float> > CoeffMatrix, vector<float> RhsMatrix) //Creating the voofeicents matrix
    {
        for (int i = 0; i < CoeffMatrix.size(); i++)
        {
            CoeffMatrix[i][var] = RhsMatrix[i];
        }
        return CoeffMatrix;
    }
    static void DisplayEquation() //displaying the eqation after defining each side
    {
        for (int i = 0; i < Equations.size(); i++)
        {
            cout << endl;
            for (int j = 0; j < Equations[i].LHS.CurTerms.size(); j++)
            {
                if (j != 0 || Equations[i].LHS.CurTerms[j].Sign == "-")
                    cout << Equations[i].LHS.CurTerms[j].Sign;
                cout << Equations[i].LHS.CurTerms[j].coeff << Equations[i].LHS.CurTerms[j].unknown;
            }
            cout << "=";
            for (int k = 0; k < Equations[i].RHS.CurTerms.size(); k++)
            {
                if (k != 0 || Equations[i].RHS.CurTerms[k].Sign == "-")
                    cout << Equations[i].RHS.CurTerms[k].Sign;
                cout << Equations[i].RHS.CurTerms[k].coeff << Equations[i].RHS.CurTerms[k].unknown;
            }
            cout << endl;
        }
    }
    static void DisplayMatrix(vector<vector<float> > mat)
    {
        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[i].size(); j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    static int CalculateDeterminant(vector<vector<float> > Matrix) //Checking if the det(A) is = 0
    {
        float det = 0;
        if (Matrix.size() == 1)
        {
            return Matrix[0][0];
        }
        else if (Matrix.size() == 2)
        {
            det = (Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0]); //The first rule we have taken
            return det;
        }
        else
        {
            for (int p = 0; p < Matrix[0].size(); p++)
            {
                vector<vector<float> > TmpMatrix;
                for (int i = 1; i < Matrix.size(); i++)
                {
                    vector<float> TmpRow;
                    for (int j = 0; j < Matrix[i].size(); j++)
                    {
                        if (j != p)
                        {
                            TmpRow.push_back(Matrix[i][j]);
                        }
                    }
                    if (TmpRow.size() > 0)
                        TmpMatrix.push_back(TmpRow);
                }
                det = det + Matrix[0][p] * pow(-1, p) * CalculateDeterminant(TmpMatrix);
            }
            return det;
        }
    }
};
#endif /* functions_h */
