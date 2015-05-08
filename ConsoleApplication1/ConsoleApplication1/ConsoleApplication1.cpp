// ConsoleApplication1.cpp : Defines the entry point for the console application.
/*Each input file contains one test case, which gives in one line the two rational numbers in the format ""a1 / b1 a2 / b2"".
The numerators and the denominators are all in the range of long int.If there is a negative sign, it must appear only in front of 
the numerator.The denominators are guaranteed to be non - zero numbers.

Output Specification :
For each test case, print in 4 lines the sum, difference, product and quotient of the two rational numbers, respectively.
The format of each line is ""number1 operator number2 = result"".Notice that all the rational numbers must be in their 
simplest form ""k a / b"", where k is the integer part, and a / b is the simplest fraction part.If the number is negative, 
it must be included in a pair of parentheses.If the denominator in the division is zero, output ""Inf"" as the result.
It is guaranteed that all the output integers are in the range of long int.
*/
//

#include "stdafx.h"
#include "string.h"
#include "stdlib.h"

typedef struct
{
	long numerator;
	long denominator;
}RationalNumber;

//Function to parse the operands from the input file
void ParseExpr(const char *, RationalNumber &operand1, RationalNumber &operand2);
//Function to format the Operand to show in the output.
void FormatRationalNumString(RationalNumber operand, char *strOperand);
//Function to add the Rational Number Operands
void AdditionExpression(const RationalNumber &operand1, const RationalNumber &operand2, RationalNumber &result);
//Function to Substract the Rational Number Operands
void SubtractExpression(const RationalNumber &operand1, const RationalNumber &operand2, RationalNumber &result);
//Function to Multiply the Rational Number Operands
void MultiplyExpression(const RationalNumber &operand1, const RationalNumber &operand2, RationalNumber &result);
//Function to divide the Rational Number Operands
void QuotientExpression(const RationalNumber &operand1, const RationalNumber &operand2, RationalNumber &result);
//Function to reduce the Rational Number to its simplest form
void ReduceRationalNumber(RationalNumber &rNum);

int main(int argc, char* argv[])
{
	FILE * fp = NULL;
	char inputExpression[256];
	char strOperand1[128];
	char strOperand2[128];
	char strResult[128];

	if (argc < 2)
	{
		printf_s("File argument is not present\n");
		return -1;
	}

	fopen_s(&fp, argv[1], "r");
	if (fp == NULL)
	{
		printf_s("Error opening the file %s\n", argv[1]);
		return -1;
	}

	fgets(inputExpression, 256, fp);
	RationalNumber operand1, operand2, result;
	long resNumer = 0, resDenom = 0;

	ParseExpr(inputExpression, operand1, operand2);
	ReduceRationalNumber(operand1);
	ReduceRationalNumber(operand2);
	FormatRationalNumString(operand1, strOperand1);
	FormatRationalNumString(operand2, strOperand2);
	printf_s("Sample Input : \n%s", inputExpression);
	printf_s("\n\nSample Output : \n");

	AdditionExpression(operand1, operand2, result);
	ReduceRationalNumber(result);
	FormatRationalNumString(result, strResult);
	printf_s("%s + %s = %s\n", strOperand1, strOperand2, strResult);

	SubtractExpression(operand1, operand2, result);
	ReduceRationalNumber(result);
	FormatRationalNumString(result, strResult);
	printf_s("%s - %s = %s\n", strOperand1, strOperand2, strResult);

	MultiplyExpression(operand1, operand2, result);
	ReduceRationalNumber(result);
	FormatRationalNumString(result, strResult);
	printf_s("%s * %s = %s\n", strOperand1, strOperand2, strResult);

	QuotientExpression(operand1, operand2, result);
	ReduceRationalNumber(result);
	FormatRationalNumString(result, strResult);
	printf_s("%s / %s = %s\n", strOperand1, strOperand2, strResult);

	return 0;
}

void ParseExpr(const char *inExpr, RationalNumber &operand1, RationalNumber &operand2)
{
	char _numer1[64], _numer2[64], _denom1[64], _denom2[64];
	int len, index;
	bool validExpr = true;

	len = strlen(inExpr);
	index = 0;
	while (inExpr[len - 1] == ' ') len--; // remove the spaces from the end if any.
	while (inExpr[index] == ' ') index++; // remove the spaces from the front if any.
	int subIndex = 0, operand = 0;
	for (; index < len; index++)
	{
		switch (inExpr[index])
		{
		case '/':
		case ' ':
			if (operand == 0)
				_numer1[subIndex++] = '\0';
			else if (operand == 1)
				_denom1[subIndex++] = '\0';
			else if (operand == 2)
				_numer2[subIndex++] = '\0';
			else if (operand == 3)
				_denom2[subIndex++] = '\0';

			operand++;
			subIndex = 0;
			continue;
		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			break;
		default:
			/*Invalid input*/
			break;
		}
		if (operand == 0)
			_numer1[subIndex++] = inExpr[index];
		else if (operand == 1)
			_denom1[subIndex++] = inExpr[index];
		else if (operand == 2)
			_numer2[subIndex++] = inExpr[index];
		else if (operand == 3)
			_denom2[subIndex++] = inExpr[index];
	}
	if (operand == 3)
		_denom2[subIndex] = inExpr[index];

	operand1.numerator = atol(_numer1);
	operand1.denominator = atol(_denom1);
	operand2.numerator = atol(_numer2);
	operand2.denominator = atol(_denom2);
}

void AdditionExpression(const RationalNumber &operand1, const RationalNumber &operand2, RationalNumber &result)
{
	result.numerator = (operand1.numerator * operand2.denominator) + (operand2.numerator * operand1.denominator);
	result.denominator = operand1.denominator * operand2.denominator;
}

void SubtractExpression(const RationalNumber &operand1, const RationalNumber &operand2, RationalNumber &result)
{
	result.numerator = (operand1.numerator * operand2.denominator) - (operand2.numerator * operand1.denominator);
	result.denominator = operand1.denominator * operand2.denominator;
}

void MultiplyExpression(const RationalNumber &operand1, const RationalNumber &operand2, RationalNumber &result)
{
	result.numerator = (operand1.numerator * operand2.numerator);
	result.denominator = operand1.denominator * operand2.denominator;
}

void QuotientExpression(const RationalNumber &operand1, const RationalNumber &operand2, RationalNumber &result)
{
	result.numerator = (operand1.numerator * operand2.denominator);
	result.denominator = operand1.denominator * operand2.numerator;
	if (result.denominator < 0)
	{
		result.numerator *= -1;
		result.denominator *= -1;
	}
}

void ReduceRationalNumber(RationalNumber &rNum)
{
	long max = 0;
	bool isNegative = false;
	
	if (rNum.numerator == 0 || rNum.denominator == 0)
		return;

	if (rNum.numerator < 0)
	{
		isNegative = true;
		rNum.numerator *= -1;
	}
	if (rNum.numerator == rNum.denominator)
	{
		rNum.numerator = 1;
		rNum.denominator = 1;
	}
	else
	{
		if (rNum.numerator > rNum.denominator)
			max = rNum.numerator;
		else
			max = rNum.denominator;

		for (int i = 2; i <= max / 2;)
		{
			if (rNum.numerator % i == 0 && rNum.denominator % i == 0)
			{
				rNum.numerator /= i;
				rNum.denominator /= i;
				if (rNum.numerator > rNum.denominator)
					max = rNum.numerator;
				else
					max = rNum.denominator;
			}
			else
			{
				i++;
			}
		}
	}
	if (isNegative)
		rNum.numerator *= -1;

}

void FormatRationalNumString(RationalNumber operand, char *strOperand)
{
	bool isNegative = false;
	char strLocal[128];
	if (operand.numerator < 0)
	{
		operand.numerator *= -1;
		isNegative = true;
	}

	if (operand.denominator == 0)
	{
		sprintf_s(strOperand, 128, "inf");
	}
	else if (operand.denominator == 1)
	{
		sprintf_s(strOperand, 128, "%d", operand.numerator);
	}
	else if (operand.numerator > operand.denominator && operand.denominator != 1)
	{
		sprintf_s(strOperand, 128, "%d %d/%d", operand.numerator / operand.denominator,
												operand.numerator % operand.denominator,
												operand.denominator);
	}
	else if (operand.numerator < operand.denominator && operand.denominator != 1)
	{
		sprintf_s(strOperand, 128, "%d/%d", operand.numerator, operand.denominator);

	}

	if (isNegative && operand.denominator != 0)
	{
		operand.numerator *= -1;
		strcpy_s(strLocal, strOperand);
		sprintf_s(strOperand, 128, "(-%s)", strLocal);
	}
}
