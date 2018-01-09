#include <string>
#define MAX 10000 // for strings

using namespace std;
//-------------------------------------------------------------
class BigInteger
{
private:
	string number;
	bool sign;
public:
	BigInteger(); // empty constructor initializes zero
	BigInteger(string s); // "string" constructor
	BigInteger(string s, bool sin); // "string" constructor
	BigInteger(int n); // "int" constructor
	void setNumber(string s);
	const string& getNumber(); // retrieves the number
	void setSign(bool s);
	const bool& getSign();
	BigInteger absolute(); // returns the absolute value
	bool operator == (BigInteger b);
	bool operator > (BigInteger b);
	bool operator < (BigInteger b);
	BigInteger operator + (BigInteger b);
	BigInteger operator - (BigInteger b);
	BigInteger operator * (BigInteger b);
	operator string(); // for conversion from BigInteger to string
	static BigInteger MultiplyPowerOfTen(BigInteger baseBigInteger, int powerNumber);
	//将位数补位2的n次方
    void RegularBigInteger();
    //将位数短长度补位位数长的
    void RegularBigInteger(BigInteger& baseBigInteger);
private:
	bool equals(BigInteger n1, BigInteger n2);
	bool less(BigInteger n1, BigInteger n2);
	bool greater(BigInteger n1, BigInteger n2);
	string add(string number1, string number2);
	string subtract(string number1, string number2);
	string multiply(string n1, string n2);
	string toString(long long n);
	long long toInt(string s);
};

