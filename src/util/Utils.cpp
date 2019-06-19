#include "../stdafx.h"
#include "Utils.h"

unsigned long Utils::id = 0;

int Utils::movingObject_id_count = 0;
int Utils::movingObject_id_total_numble = 5;

std::hash<string> Utils::hashFun;

long long Utils::getTime() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
}

//string Utils::getTimeStr() {
//    time_t timep;
//    time(&timep);
//    char tmp[64];
//    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
//    return tmp;
//}

double Utils::randomFloat(int min, int max) {
    double m1 = (double)(rand() % 101) / 101;// 计算 0，1之间的随机小数,得到的值域近似为(0,1)
    min++; //将 区间变为(min+1,max),
    //计算 min+1,max 之间的随机整数，得到的值域为[min+1,max]
    double m2 = (double)((rand() % (max - min + 1)) + min);
    m2 = m2 - 1; //令值域为[min,max-1]
    return m1 + m2; //返回值域为(min,max),为所求随机浮点数
}

double Utils::randMToN(double M, double N)
{
	return M + (rand() / (RAND_MAX / (N - M)));
}

int Utils::randOneOrNegativeOne() {
	if (rand() % 2 == 0) return 1;
	else return -1;
}

string Utils::getRandomGroupName(int startRange, int endRange) {
    int randomNumForGroup = randomInt(startRange, endRange);
    stringstream groupName;
    groupName << "battle" << randomNumForGroup;
    return groupName.str();
}

void Utils::lTrim(char * str) {
    int i, len;


    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] != ' ') break;
    }
    memmove(str, str + i, len - i + 1);
    return;
}

void Utils::rTrim(char * str) {
    int i, len;

    len = strlen(str);
    for (i = len - 1; i >= 0; i--) {
        if ((str[i] != ' ') && (str[i] != 0x0a) && (str[i] != 0x0d))  break;
    }
    str[i + 1] = 0;
    return;
}

void Utils::trim(char * str) {
    int i, len;

    //先去除左边的空格
    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] != ' ') break;
    }
    memmove(str, str + i, len - i + 1);

    //再去除右边的空格
    len = strlen(str);
    for (i = len - 1; i >= 0; i--) {
        if (str[i] != ' ') break;
    }
    str[i + 1] = 0;

    return;
}

string Utils::lTrim(const string& str) {
    if (str.length() < 1) return "";
    return str.substr(str.find_first_not_of(" \n\r\t"));
}

string Utils::rTrim(const string& str) {
    if (str.length() < 1) return "";
    return str.substr(0, str.find_last_not_of(" \n\r\t") + 1);
}

string Utils::trim(const string& str) {
    return lTrim(rTrim(str));
}

string Utils::toLower(const string& s) {
    string result = s;
    int len = s.size();
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'A'&&s[i] <= 'Z') {
            result[i] += 32;//+32转换为小写
            //s[i]=s[i]-'A'+'a';
        }
    }
    return result;
}

string Utils::toUpper(const string& s) {
    string result = s;
    int len = s.size();
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'a'&&s[i] <= 'z') {
            result[i] -= 32;//+32转换为小写
            //s[i]=s[i]-'a'+'A';
        }
    }
    return result;
}

std::vector<std::string> Utils::split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> spiltCollection;
    if (str.size() == 0)
        return spiltCollection;
    int start = 0;
    int idx = str.find(delim, start);
    while (idx != std::string::npos){
        spiltCollection.push_back(str.substr(start, idx - start));
        start = idx + delim.size();
        idx = str.find(delim, start);
    }
    spiltCollection.push_back(str.substr(start));
    return spiltCollection;
}

std::vector<std::string> Utils::split(const std::string& str, const std::string& delim, 
										const string skipStart, const string skipEnd) {
	vector<string> result;
	if (str.size() == 0) return result;
	int skipStartIndex = str.find(skipStart, 0);
	int skipEndIndex = str.find(skipEnd, 0);
	if (skipStartIndex < 0 || skipEndIndex < 0 || (skipStartIndex >= skipEndIndex)) {
		skipStartIndex = -1;
		skipEndIndex = -1;
	}
	if (skipEndIndex > 0) {
		skipEndIndex += skipEnd.length() - 1;
	}

	int start = 0;
	int idx = str.find(delim, start);
	while (idx != string::npos) {
		if (idx >= skipStartIndex && idx <= skipEndIndex) {
			idx = str.find(delim, skipEndIndex+1);

			skipStartIndex = str.find(skipStart, idx + 1);
			skipEndIndex = str.find(skipEnd, idx + 1);

			if (idx != string::npos) {
				result.push_back(str.substr(start, idx-start));
				start = idx + delim.size();
				if (start >= str.length())
					return result;
				else 
					idx = str.find(delim, start);
				continue;
			}
			else {
				result.push_back(str.substr(start));
				return result;
			}
		}
		result.push_back(str.substr(start, idx - start));
		start = idx + delim.size();
		idx = str.find(delim, start);
	}
	result.push_back(str.substr(start));
	return result;
}




void Utils::deleteAllMark(string &s, const string &mark) {
    size_t nSize = mark.size();
    while (1) {
        size_t pos = s.find(mark);
        if (pos == string::npos) {
            return;
        }
        s.erase(pos, nSize);
    }
}


