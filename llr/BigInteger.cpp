#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "BigInteger.h"
#define MAX 10000 // for strings

void int2str(const int &int_temp, string &string_temp)
{
	stringstream stream;
	stream << int_temp;
	string_temp = stream.str();   //此处也可以用 stream>>string_temp
}


BigInteger::BigInteger() // empty constructor initializes zero
{
	number = "0";
	sign = false;
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s) // "string" constructor
{
	if( isdigit(s[0]) ) // if not signed
	{
		setNumber(s);
		sign = false; // +ve
	}
	else
	{
		setNumber( s.substr(1) );
		sign = (s[0] == '-');
	}
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s, bool sin) // "string" constructor
{
	setNumber( s );
	setSign( sin );
}
//-------------------------------------------------------------
BigInteger::BigInteger(int n) // "int" constructor
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;


	if( isdigit(s[0]) ) // if not signed
	{
		setNumber( s );
		setSign( false ); // +ve
	}
	else
	{
		setNumber( s.substr(1) );
		setSign( s[0] == '-' );
	}
}
//-------------------------------------------------------------
void BigInteger::setNumber(string s)
{
	number = s;
}
//-------------------------------------------------------------
const string& BigInteger::getNumber() // retrieves the number
{
	return number;
}
//-------------------------------------------------------------
void BigInteger::setSign(bool s)
{
	sign = s;
}
//-------------------------------------------------------------
const bool& BigInteger::getSign()
{
	return sign;
}
//-------------------------------------------------------------
// returns the absolute value
BigInteger BigInteger::absolute()
{
	return BigInteger( getNumber() ); // +ve by default
}
//-------------------------------------------------------------

bool BigInteger::operator == (BigInteger b)
{
	return equals((*this) , b);
}
////-------------------------------------------------------------
bool BigInteger::operator > (BigInteger b)
{
	return greater((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator < (BigInteger b)
{
	return less((*this) , b);
}
//-------------------------------------------------------------
BigInteger BigInteger::operator + (BigInteger b)
{
	BigInteger addition;
	if( getSign() == b.getSign() ) // both +ve or -ve
	{
		addition.setNumber( add(getNumber(), b.getNumber() ) );
		addition.setSign( getSign() );
	}
	else // sign different
	{
		if( absolute() > b.absolute() )
		{
			addition.setNumber( subtract(getNumber(), b.getNumber() ) );
			addition.setSign( getSign() );
		}
		else
		{
			addition.setNumber( subtract(b.getNumber(), getNumber() ) );
			addition.setSign( b.getSign() );
		}
	}
	if(addition.getNumber() == "0") // avoid (-0) problem
		addition.setSign(false);

	return addition;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator - (BigInteger b)
{
	b.setSign( ! b.getSign() ); // x - y = x + (-y)
	return (*this) + b;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator * (BigInteger b)
{
	BigInteger mul;
	if (this == 0 || b == 0)
	{
		mul.setNumber("0");
		mul.setSign(false);
		return mul;
	}
	if (this->getNumber().length() == 1 || b.getNumber().length() == 1)
	{
	    //cout<<this->getNumber()<<"   "<<b.getNumber()<<endl;
	    //getchar();
			mul.setNumber(multiply(getNumber(), b.getNumber()));
		//mul.setSign(getSign() != b.getSign());
		//if (mul.getNumber() == "0") // avoid (-0) problem
		mul.setSign(false);
		return mul;
	}
	else
	{
		size_t lengthA = this->getNumber().length();
		size_t lengthB = b.getNumber().length();
		string tempA(this->getNumber());
		string tempb(b.getNumber());
		BigInteger a1(tempA.substr(0 , lengthA / 2 ), false);
		cout << "a1:" << a1.getNumber() << endl ;
		BigInteger a0(tempA.substr(lengthA / 2 , lengthA) , false);
		cout << "a0:" << a0.getNumber() << endl;
		BigInteger b1(b.getNumber().substr(0, lengthB / 2) , false);
		cout << "b1:" << b1.getNumber() << endl;
		BigInteger b0(b.getNumber().substr(lengthB / 2 , lengthB ) , false);
		cout << "b0:" << b0.getNumber() << endl;
		int x = (lengthA + 1) / 2 + (lengthB + 1) / 2;
		//BigInteger temp(x);
		int y = (lengthA + 1) / 2;
		//BigInteger temp1(y);
		int z = (lengthB + 1) / 2;
		//BigInteger temp2(z);

		return BigInteger::MultiplyPowerOfTen(a1 * b1, x) + BigInteger::MultiplyPowerOfTen(a1 * b0, y) +
                BigInteger::MultiplyPowerOfTen(a0 * b1, z) + a0 * b0;
	}
}

void BigInteger::RegularBigInteger()
{
    int length = number.length();
    if(length & (length - 1) == 0)
    {
        return;
    }

    int newLength = length;
    while(newLength & (newLength - 1) != 0)
    {
        number = '0' + number;
        newLength++;
    }
}

void BigInteger::RegularBigInteger(BigInteger& baseBigInteger)
{
    int selfLength = number.length();
    int otherLength = baseBigInteger.getNumber().length();
    if(selfLength == otherLength)
    {
        return;
    }

    int maxLength = max(selfLength, otherLength);
    BigInteger *changeInteger = selfLength < otherLength ? this : &baseBigInteger;

    ostringstream oss;
    oss<<setw(maxLength)<<setfill('0')<<changeInteger->getNumber();
    changeInteger->setNumber(oss.str());
}

BigInteger BigInteger::MultiplyPowerOfTen(BigInteger baseBigInteger, int powerNumber)
{
    string newNumberStr = baseBigInteger.getNumber();
    for(int i = 0; i < powerNumber; ++i)
    {
        newNumberStr += '0';
    }
    return BigInteger(newNumberStr);
}

//-------------------------------------------------------------
BigInteger::operator string() // for conversion from BigInteger to string
{
	string signedString = ( getSign() ) ? "-" : ""; // if +ve, don't print + sign
	signedString += number;
	return signedString;
}
//-------------------------------------------------------------

bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
	return n1.getNumber() == n2.getNumber()
		&& n1.getSign() == n2.getSign();
}

//-------------------------------------------------------------
bool BigInteger::less(BigInteger n1, BigInteger n2)
{
	bool sign1 = n1.getSign();
	bool sign2 = n2.getSign();

	if(sign1 && ! sign2) // if n1 is -ve and n2 is +ve
		return true;

	else if(! sign1 && sign2)
		return false;

	else if(! sign1) // both +ve
	{
		if(n1.getNumber().length() < n2.getNumber().length() )
			return true;
		if(n1.getNumber().length() > n2.getNumber().length() )
			return false;
		return n1.getNumber() < n2.getNumber();
	}
	else // both -ve
	{
		if(n1.getNumber().length() > n2.getNumber().length())
			return true;
		if(n1.getNumber().length() < n2.getNumber().length())
			return false;
		return n1.getNumber().compare( n2.getNumber() ) > 0; // greater with -ve sign is LESS
	}
}
//-------------------------------------------------------------
bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
	return ! equals(n1, n2) && ! less(n1, n2);
}

//-------------------------------------------------------------
// adds two strings and returns their sum in as a string
string BigInteger::add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ?  number1 : number2;
	char carry = '0';
	int differenceInLength = abs( (int) (number1.size() - number2.size()) );

	if(number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0'); // put zeros from left

	else// if(number1.size() < number2.size())
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.size()-1; i>=0; --i)
	{
		add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

		if(i != 0)
		{
			if(add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if(add[0] > '9')
	{
		add[0]-= 10;
		add.insert(0,1,'1');
	}
	return add;
}

//-------------------------------------------------------------
// subtracts two strings and returns their sum in as a string
string BigInteger::subtract(string number1, string number2)
{
	string sub = (number1.length()>number2.length())? number1 : number2;
	int differenceInLength = abs( (int)(number1.size() - number2.size()) );

	if(number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0');

	else
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.length()-1; i>=0; --i)
	{
		if(number1[i] < number2[i])
		{
			number1[i] += 10;
			number1[i-1]--;
		}
		sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
	}

	while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
		sub.erase(0,1);

	return sub;
}

//-------------------------------------------------------------
// multiplies two strings and returns their sum in as a string
string BigInteger::multiply(string n1, string n2)
{
	if(n1.length() > n2.length())
		n1.swap(n2);

	string res = "0";
	for(int i=n1.length()-1; i>=0; --i)
	{
		string temp = n2;
		int currentDigit = n1[i]-'0';
		int carry = 0;

		for(int j=temp.length()-1; j>=0; --j)
		{
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;

			if(temp[j] > 9)
			{
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			}
			else
				carry = 0;

			temp[j] += '0'; // back to string mood
		}

		if(carry > 0)
			temp.insert(0, 1, (carry+'0'));

		temp.append((n1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

		res = add(res, temp); // O(n)
	}

	while(res[0] == '0' && res.length()!=1) // erase leading zeros
		res.erase(0,1);

	return res;
}

// converts long long to string
string BigInteger::toString(long long n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}


//-------------------------------------------------------------
// converts string to long long
long long BigInteger::toInt(string s)
{
	long long sum = 0;

	for(int i=0; i<s.length(); i++)
		sum = (sum*10) + (s[i] - '0');

	return sum;
}

#endif

int main()
{
	string X;
	string Y;
	cout << "请分别输入乘数与被乘数（输入绝对值）：" << ends;
	cin >> X >> Y;
	BigInteger integerX(X);
	BigInteger integerY(Y);
	integerX.RegularBigInteger();
	integerY.RegularBigInteger();
	integerX.RegularBigInteger(integerY);
	BigInteger product(integerX * integerY);
	string sign(product.getSign() ? "-" : "+");
	string calResult = product.getNumber();
	calResult.erase(0, calResult.find_first_not_of('0'));
	if(calResult.length() == 0)
    {
        calResult = "0";
    }
	cout << sign << calResult << endl;
	//system("pause");
	return 0;
}
