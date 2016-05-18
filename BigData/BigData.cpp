#include"BigData.h"
void Itoa(LONG data, string &str);
bool IsValid(string &str);
string _ADD(string s1, string s2);
string _SUB(string s1, string s2);
string _MUL(string s1, string s2);
string _DIV(string s1, string s2);
string DisSymbol(string s);
int WhoBigger(string s1, string s2);
//拷贝构造
BigData:: BigData(const BigData &b)
{
	//_str.resize(b._str.size());

	_str = b._str;
	_symbol = b._symbol;
	_data = b._data;
}
//赋值运算符
BigData BigData::operator=(BigData b)
{
	swap(_str, b._str);
	swap(_symbol, b._symbol);
	swap(_data, b._data);
	return *this;
}
//输出
ostream& operator<<(ostream &os, const BigData &b)
{
	int Len = (b._str).size();
	if (b._symbol == "-")
		os << '-';
	for (int i = 0; i < Len; i++)
	{
		os << b._str[i];
	}
	return os;
}

//构造   直接用字符串来模拟不用longlong类型的数据
BigData::BigData(string str) :_str(str),_symbol("+") ,_data(0)
{
	if (str[0] == '-')
	{
		_symbol = "-";
	}
	if (!IsValid(_str))
		_str = "0";
	else
		_str = DisSymbol(_str);
}
BigData::BigData(long long data) :_str(),_symbol("+"),_data(data)
{
	if (_data < 0)
	{
		_symbol = "-";
		_data *= (-1);
	}
	Itoa(_data, _str);
}
BigData::~BigData()
{
	_str.erase();
}
BigData BigData::operator+(const BigData &b)
{
	BigData result;
	if (_symbol == "-"&&b._symbol == "-")
	{
		result._symbol = "-";
		result._str = _ADD(_str, b._str);
	}
	if (_symbol == "-"&&b._symbol == "+")
		result._str = _SUB(b._str, _str);
	if (_symbol == "+"&&b._symbol == "-")
		result._str = _SUB(_str, b._str);
	else
		result._str = _ADD(_str, b._str);
	return result;
}
BigData BigData::operator-(const BigData &b)
{
	BigData result;
	//同号相减
	if (_symbol == "+"&&b._symbol == "+")
	{
		if (WhoBigger(_str, b._str) == 1 || WhoBigger(_str, b._str)==0)
		{
			result._str = _SUB(_str, b._str);
		}
		else
		{
			result._str = _SUB(b._str, _str);
			result._symbol = "-";
		}
	}
	if (_symbol == "-"&&b._symbol == "+")
	{
		result._str = _ADD(_str, b._str);
		result._symbol = "-";
	}
	if (_symbol == "+"&&b._symbol == "-")
	{
		result._str = _ADD(_str, b._str);
	}
	if (_symbol == "-"&&b._symbol == "-")
	{
		if (WhoBigger(_str, b._str)==1)
		{
			result._str = _SUB(_str, b._str);
			result._symbol = "-";
		}
		else
			result._str = _SUB(b._str, _str);
	}
	return result;
 }
BigData BigData:: operator*(const BigData &b)
{
	BigData result;
	if (_symbol != b._symbol)
		result._symbol = "-";
	result._str = _MUL(_str, b._str);
	return result;
}
BigData BigData::operator/(const BigData&b)
{
	assert(b._str != "0");
	BigData result;
	if (_symbol ==b._symbol)
	{
		if (WhoBigger(_str, b._str) == 1)
		{
			result._str = _DIV(_str, b._str);
		}
		else
			return "0";
	}
	if (_symbol != b._symbol)
	{
		if (WhoBigger(_str, b._str) == 1)
		{
			result._str = _DIV(_str, b._str);
			result._symbol = "-";
		}
		else
			return "0";
	}
	return result;
}
//只考虑没有带符号的数字(数字转换成字符串)
void Itoa(LONG data,string &str)
{
	stack<int> s;
	while (data > 0)
	{
		s.push(data % 10);
		data = data / 10;
	}
	str.resize(s.size());
	int i = 0;
	while (!s.empty())
	{
		str[i++] = s.top() + '0';
		s.pop();
	}
}
//字符串的有效性判断
bool IsValid(string &str)
{
	int Len = str.size();
	if (str[0] != '+' && str[0] != '-' && (str[0] > '9' || str[0] < '0'))
		return false;
	for (int i = 1; i < Len; i++)
	{
		if (str[i]<'0' || str[i]>'9')
			return false;
	}
	return true;
}
//模拟两个正数相加
string _ADD(string s1, string s2)
{
	string result = "0";
	if (s1.size() < s2.size())
		swap(s1, s2);
	int len1 = s1.size();
	int len2 = s2.size();
	int sum = 0;
	int	ntakeover = 0;
	result.resize(len1,'0');
	for (int i = len1 - 1, j = len2 - 1; i >= 0; j--,i--)
	{
		if (j>=0)
			sum = s1[i] - '0' + (s2[j] - '0') + ntakeover;
		else
			sum = s1[i] - '0' + ntakeover;
		if (sum >= 10)
		{
			sum -= 10;
			ntakeover = 1;
			result[i] = sum + '0';
		}
		else
		{
			result[i] = sum + '0';
			ntakeover = 0;
		}
	}
	//最高位有进位
	if (result < s1)
	{
		string tmp = "1";
		tmp.resize(result.size() + 1);
		for (int i = 0; i < result.size(); i++)
		{
			tmp[i + 1] = result[i];
		}
		result = tmp;
	}
	return result;
}
//模拟两个数相减只需要(s1>s2)的情况
string _SUB(string s1, string s2)
{
	string result;
	int Len1 = s1.size();
	int Len2 = s2.size();
	result.resize(Len1,'0');
	int sub = 0;
	int nflow = 0;
	for (int i = Len1 - 1, j = Len2 - 1; i >= 0; j--, i--)
	{
		if (j >= 0)
			sub = s1[i] - '0' - (s2[j] - '0') + nflow;
		else
			sub = s1[i] - '0' + nflow;
		if (sub >= 0)
		{
			result[i] = sub + '0';
			nflow = 0;
		}
		else
		{
			sub += 10;
			nflow = -1;
			result[i] = sub + '0';
		}
	}
	string NoZero;
	int m = 0;
	while (result[m] == '0'&&m < result.size())
		m++;
	NoZero.resize(result.size() - m);
	for (int k=0; m < result.size(); m++,k++)
	{
		NoZero[k] = result[m];
	}
	result = NoZero;
	return result;
}

string _MUL(string s1, string s2)
{
	//s1*s2   1234556*12321
	//取长度比较长的字符串
	if (s1.size() < s2.size())
		swap(s1, s2);
	int Len2 = s2.size();
	string result = "0";
	for (int i = 0; i < Len2; i++)
	{
		if (i>0)
			result.push_back('0');
		int j = s2[i] - '0';
		for (j; j>0; j--)
		{
			result = _ADD(result, s1);
		}
	}
	return result;
}


//s1,s2都是正数而且s1大于s2
//效率太低  采用下面高效的方法
string _myDIV(string s1, string s2)
{
	//用减法模拟
	string result = "0";
	if (s1.size() > s2.size())
	{
		while (s1.size() > s2.size())
		{
			s1 = _SUB(s1, s2);
			result = _ADD(result, "1");
		}
	}
	if (s1.size() == s2.size())
	{
		while (s1 >= s2&&s1.size() == s2.size())
		{
			s1 = _SUB(s1, s2);
			result = _ADD(result, "1");
		}
	}
	return result;
}
//去掉符号
string DisSymbol(string s)
{
	string result;
	int len = s.size();
	if (s[0] == '+' || s[0] == '-')
	{
		result.resize(len - 1);
		for (int i = 1; i < len; i++)
		{
			result[i - 1] = s[i];
		}
	}
	else
	{
		result = s;
	}
	return result;
}

int WhoBigger(string s1, string s2)
{
	int len1 = s1.size();
	int len2 = s2.size();
	if (len1 > len2)
		return 1;
	if (len1 == len2)
	{
		if (s1.compare(s2) > 0)
			return 1;
		else if (s1.compare(s2) == 0)
			return 0;
		else
			return -1;
	}
	else
		return -1;
}

string _DIV(string s1, string s2)
{
	string result = "0";
	int len1 = s1.size();
	int len2 = s2.size();
	int index = 0;
	string count = "1";
	string onenumber = "0";
	//减数
	string  subtrahend = "";
	for (int i = 0; i < len2; i++)
	{
		subtrahend.push_back(s1[i]);
	}
	index = len1 - len2;
	while (index>0)
	{
		count.push_back('0');
		index--;
	}
	for (int j = len2-1; j < len1; j++)
	{
		if (WhoBigger(subtrahend, s2) == -1)
		{
			string tmp = "0";
			tmp[0] = s1[j];
			subtrahend = _ADD(_MUL(subtrahend, "10"),tmp);
			tmp = "0";
			count.pop_back();
		}
		while (WhoBigger(subtrahend, s2) >= 0)
		{
			subtrahend = _SUB(subtrahend, s2);
			onenumber = _ADD(onenumber,"1");
		}
		result = _ADD(result, _MUL(onenumber, count));
		onenumber = "0";
	}
	return result;
}