#ifndef BIGDATA_H
#define BIGDATA_H
#define LONG long long
#include<stack>
#include<assert.h>
#include<iostream>
using namespace std;
#include<string>
#define VALIDNUMBER_MAX  9223372036854775807
#define VALIDNUMBER_MIN (-9223372036854775808)
//#define INVALID_NUMBER 
#define MaxStr "9223372036854775807"
#define MinStr "-9223372036854775808"
class BigData
{
public:
	friend ostream& operator<<(ostream &os,const BigData &b);
	BigData(string str="0");
	BigData(long long data);
	BigData(const BigData &b);
	~BigData();
	BigData operator+(const BigData &b);
	BigData operator-(const BigData &b);
	BigData operator=(BigData b);
	BigData operator*(const BigData &b);
	BigData operator/(const BigData&b);
private:
	std::string _str; //私有成员用一个string对象
    std::string _symbol;//保存符号
	long long _data;

};
#endif //BIGDATA_H  