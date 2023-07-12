#include <stdio.h>
#include <math.h>

int main()
{
    // Number of program 1
    double squareRoot2 = sqrt(2);
    printf("%f\n", squareRoot2);

    // Number of program 2
    double half = 1.0 / 2;
    double third = 1.0 / 3;
    double sumResult = half + third;
    printf("%f\n", sumResult);

    // Number of program 3
    double varX, varY;
    double binomialExpr = pow(varX + varY, 6);
    printf("%f\n", binomialExpr);

    // Number of program 4
    double trigExpr = sin(varX) / cos(varX);
    printf("%f\n", trigExpr);

    // Number of program 5
    double equation = (sin(varX) - varX) / pow(varX, 3);
    printf("%f\n", equation);

    // Number of program 6
    double logExpr = log(varX);
    double logDerivative = 1 / varX;
    double inverseDerivative = 1 / pow(varX, 2);
    double sinDerivative = cos(varX);
    double cosDerivative = -sin(varX);
    printf("Derivative of log(x) with respect to x: %f\n", logDerivative);
    printf("Derivative of 1/x with respect to x: %f\n", inverseDerivative);
    printf("Derivative of sin(x) with respect to x: %f\n", sinDerivative);
    printf("Derivative of cos(x) with respect to x: %f\n", cosDerivative);

    // Number of program 7
    double equation1 = varX + varY - 2;
    double equation2 = 2 * varX + varY;
    printf("x = %f\n", equation1);
    printf("y = %f\n", equation2);

    // Number of program 8
    double integratedExpr1 = (pow(varX, 3)) / 3;
    printf("Integration of x^2: %f\n", integratedExpr1);

    double integratedExpr2 = -cos(varX);
    printf("Integration of sin(x): %f\n", integratedExpr2);

    double integratedExpr3 = sin(varX);
    printf("Integration of cos(x): %f\n", integratedExpr3);

    // Number of program 9
    double functionF = exp(varX);
    double differentialEquation = pow(functionF, 2) + 9 * functionF;
    printf("%f\n", differentialEquation);

    // Number of program 10
    double varX, varY, varZ;
    double coefficientMatrix[2][3] = {{3, 7, -12}, {4, -2, -5}};
    double constants[2] = {0, 0};

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%f ", coefficientMatrix[i][j]);
        }
        printf("\n");
    }

    printf("x = %f\n", constants[0]);
    printf("y = %f\n", constants[1]);

    return 0;
}
