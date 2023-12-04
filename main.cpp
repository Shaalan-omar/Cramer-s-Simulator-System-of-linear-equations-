//
//  main.cpp
//  Cramer's Simulator (System of linear equations)
//
//  Created by Omar shaalan & Abdelwahab Ganna on 4/22/22.
//  Copyright © 2022 Omar shaalan. All rights reserved.
//
#include "functions.h"

int main()
{
    int Number_Of_equations = 0; //Insitializing the system of linear equations to null
         cout<<"How many equations in your system of linear equations ?"<<endl;
         cin>> Number_Of_equations;
    if (Number_Of_equations < 2) //No system of linear equations
        return 0;
    for (int i = 0; i < Number_Of_equations; i++) //A loop that loops on each equation
    {
        string Eqn = ""; //A string to carry the equation
        cout << "Enter Equation No : " << (i + 1) << " ";
        cin >> Eqn;
        Equations.push_back(Equation(Eqn)); //storing the equations after getting them from the user in the vector of equations
    }
    Utility::DisplayEquation();
    Utility::SetMatrix();
    float CoefMatrixDet = Utility::CalculateDeterminant(CoeffsMatrix);
    vector<float> VariableDeterminant;
    for (int i = 0; i < UnKnowns.size(); i++)
    {
        VariableDeterminant.push_back(Utility::CalculateDeterminant(Utility::GetVariableMatrix(i, CoeffsMatrix, Constants_Matrix)));
    }
    cout << CoefMatrixDet;
    for (int j = 0; j < VariableDeterminant.size(); j++)
    {
        cout << endl
             << endl;
        cout << UnKnowns[j] << " = " << VariableDeterminant[j] / CoefMatrixDet;
        cout << endl
             << endl;
    }
}
