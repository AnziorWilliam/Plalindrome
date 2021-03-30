#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//会超时，待优化
#pragma region brute解法
bool IsPlalindrome(string Detectstr);
void LongestPlalindrome(string Inputstr, string& LST_PLD, int& lens);
#pragma endregion
//25ms 534kb
#pragma region 中心点扩散解法
int SpreadCenter(int startPos, int endPos, string iptStr);
int LST_plalindrome(string iptstr);
#pragma endregion
//260ms 504kb
#pragma region 最长公共子串解法
void lstpld(string rawipt);
void LstSubstr(string& rawipt);
#pragma endregion
//755ms 24068kb ？？？？
#pragma region 动态规划解法
void TranStatus(string &Raput);
#pragma endregion
//
#pragma region Manacher解法
void AppendStr(string& InputStr);

int  Manacher_plalindrome(string InputStr);
#pragma endregion

int main()
{
	//string RetPlalindrome = "";//返回回文
	int PLD_maxlen = 0;//最长回文长度
	string inst;

	while (getline(cin, inst))
	{
		//***brute 解法***
		//LongestPlalindrome(inst, RetPlalindrome,PLD_maxlen);
		//cout << RetPlalindrome << endl;

		//中心扩散法
		//PLD_maxlen = LST_plalindrome(inst);

		//最长公共子串
		//LstSubstr(inst);
		//PLD_maxlen = inst.length();

		//动态规划
		//TranStatus(inst);
		//PLD_maxlen = inst.length();

		//Manacher
		if (inst == "")
		{
			cout << endl;
			continue;
		}
		string Manacher = inst;
		AppendStr(Manacher);
		PLD_maxlen = Manacher_plalindrome(Manacher);
		cout << PLD_maxlen << endl;
		PLD_maxlen = 0;
		//RetPlalindrome = "";
	}
	return 0;
}

#pragma region brute 解法
bool IsPlalindrome(string Detectstr)
{
	string RDt_str = Detectstr;
	reverse(RDt_str.begin(), RDt_str.end());

	return RDt_str != Detectstr ? false : true;
}

void LongestPlalindrome(string Inputstr, string& LST_PLD, int& lens)
{
	string RetPlalindrome = "";//返回回文
	int PLD_maxlen = 0;//最长回文长度

	int len = Inputstr.length();

	string temp = "";

	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j <= len; j++)
		{
			temp = Inputstr.substr(i, j);
			if (IsPlalindrome(temp) && temp.length() > PLD_maxlen)//是回文且回文长度大于已知最长的回文长
			{
				PLD_maxlen = temp.length() > PLD_maxlen ? temp.length() : PLD_maxlen;
				RetPlalindrome = temp;
			}
			temp = "";
		}
	}
	LST_PLD = RetPlalindrome;
	lens = PLD_maxlen;
}
#pragma endregion

#pragma region 中心点扩散解法
int SpreadCenter(int startPos, int endPos, string iptStr)
{
	int plalindrom_len = 0;
	int len = iptStr.length();
	int Lchild = startPos;
	int Rchild = endPos;
	if (iptStr[startPos] != iptStr[endPos])
	{
		return plalindrom_len;
	}
	if (startPos == endPos)
	{
		plalindrom_len = 1;
	}
	else
	{
		plalindrom_len = 2;
	}
	while (Lchild >= 0 && Rchild < len && iptStr[Lchild] == iptStr[Rchild])//回文中心
	{
		plalindrom_len += 2;
		Lchild--;
		Rchild++;
	}
	plalindrom_len -= 2;
	return plalindrom_len;
}
int LST_plalindrome(string iptstr)
{
	int plalindrome_mx = 0;
	if (iptstr == "")
	{
		return plalindrome_mx;
	}
	int lens = iptstr.length();

	for (int i = 0; i < lens; i++)
	{
		int SigLen = SpreadCenter(i, i, iptstr);
		int DooLen = SpreadCenter(i, i + 1, iptstr);
		int temps = SigLen > DooLen ? SigLen : DooLen;
		plalindrome_mx = plalindrome_mx > temps ? plalindrome_mx : temps;
	}
	return plalindrome_mx;
}
#pragma endregion

#pragma region 最长公共子串解法
void LstSubstr(string& rawipt)
{
	string RVTstr = rawipt;
	string MirIpt = rawipt;
	string retTp;

	int mxlen = 0;

	if (rawipt.length() == 1)
	{
		return;
	}
	reverse(RVTstr.begin(), RVTstr.end());
	if (RVTstr == MirIpt)
	{
		return;
	}

	int len = MirIpt.length();
	for (int i = 0; i < len; i++)
	{
		string temp;
		for (int j = i; j < len; j++)
		{
			temp += MirIpt[j];
			if (mxlen > temp.length())
			{
				continue;
			}

			else if (RVTstr.find(temp) != RVTstr.npos)//存在该子串
			{
				retTp = temp;
				reverse(retTp.begin(), retTp.end());

				if (retTp == temp)
				{
					mxlen = temp.length();
					rawipt = temp;
				}
			}
			else
				break;
		}
		temp = "";
	}
}
#pragma endregion

#pragma region 动态规划解法
void TranStatus(string &Raput)
{
	string tpRa = Raput;
	int Ralen = Raput.length();
	if (Raput.empty() || Ralen < 2)//空串或者单个字符
	{
		return;
	}

	int Lst = 0;
	//int Rst = 0;
	int mxLen = 1;

	/*bool **dp= new bool *[Ralen];
	for (int i = 0; i < Ralen; i++)
	{
		dp[i] = new bool[Ralen];
	}*/

	vector<vector<int>>dp(Ralen, vector<int>(Ralen));

	for (int i = 0; i < Ralen; i++)
	{
		dp[i][i] = 1;
		if (i < Ralen - 1 && tpRa[i] == tpRa[i + 1])
		{
			dp[i][i+1] = 1;
			mxLen = 2;
			Lst = i;
		}
	}


	for (auto Right = 3; Right <= Ralen ; Right++) //右边边界
	{
		for (auto Left = 0; Left + Right < Ralen + 1; Left++)//左边边界
		{
			int j = Left + Right - 1;
			if (tpRa[Left] == tpRa[j]&&dp[Left+1][j-1] == 1)
			{
				dp[Left][j] = 1;
				Lst = Left;
				mxLen = Right;
			}
		}
	}
	Raput = tpRa.substr(Lst, mxLen);
}
#pragma endregion

#pragma region Manacher解法
void AppendStr(string& InputStr)
{
	int len = InputStr.length();
	string ManacherStr ="";
	for (auto i : InputStr)
	{
		ManacherStr.append("*");
		ManacherStr.append(string(1,i));
	}
	ManacherStr.append("*");
	InputStr = ManacherStr;
}
int  Manacher_plalindrome(string InputStr)
{
	//字符串起始点
	int R = 0;
	int C = 0;

	int mx_Manacher = 0;
	int* p = new int[InputStr.length()];
	//memset(p, 1, InputStr.length());
	if (InputStr == "" || InputStr.length() < 2)
	{
		return 1;
	}

	string s = InputStr;
	int go;
	for (int i = 0; i < InputStr.length(); i++)
	{
		p[i] = R > i ? min(R - i, p[2 * C - i]) : 1;
		//当前位置在已知回文最右边界的左边还是右边；

		//在右边则暴力匹配，第一个点半径先设置为1

		//如果在左边则继续判断i点关于c的对称点的回文半径与r-i的关系;

		//如果该回文半径小于r-i说明i点的回文半径也必定小于r-i，基于回文对称特性p[i] = p[2c-i]

		/*如果该回文半径大于等于r-i，基于回文对称性规则：大于r-i的情况下，必定有p[i]=r-i
		这是因为如果p[i]>r-i的话那么i点的回文半径边界y必定大于r，y关于i的对称点为y'，y'关于c的对称点为x，x关于j的对称点为x'
		可以推导出x'必定也在r关于c的对称点l之外，同理基于回文内部的对称性可以知道这几个点字符必定都相等，那么原有的r为最右边界假设便不成立,
		此时p[i]=r-i 只能取等于*/

		/*如果取的是等于情况，那么j点的左边界+1不等于j的右边界+1，但i点的右边边界在已知的最右边界r之外，所以对于在边界之外的点仍需暴力匹配判断
		以i为对称中心的回文能否继续向外面扩张，这种情况下i的回文半径也应当以r-i为起点尝试往外扩张  ---》p[i]>=r-i*/

		while (i+p[i]< InputStr.length()&&i-p[i]>=0)//左右边界
		{
			if (s[i + p[i]] == s[i - p[i]])//向外扩张
			{
				p[i]++;
			}
			else//任意一次不匹配则退出
			{
				break;
			}
		}

		//更新 R,C的值 ，如有必要
		if (i + p[i] > R)
		{
			R = i + p[i];
			C = i;
		}
		mx_Manacher = max(mx_Manacher, p[i]);
	}
	delete[]p;
	return mx_Manacher - 1;
}
#pragma endregion