#include "Framework.h"
#include "String.h"

#include <iomanip>
#include <sstream>

void String::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();
	int cutAt = 0;
	while ((cutAt)=(int)origin.find_first_of(tok)!=origin.npos)
	{
		if (cutAt > 0) // 자르는 위치가 0보다 클때
			result->push_back(origin.substr(0, cutAt));
		origin = origin.substr(cutAt+1);
	}

	if (origin.length() > 0) // 자르고 남을때
		result->push_back(origin.substr(0, cutAt));

	

}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();
	int cutAt = 0;
	while ((cutAt) = (int)origin.find_first_of(tok) != origin.npos)
	{
		if (cutAt > 0) // 자르는 위치가 0보다 클때
			result->push_back(origin.substr(0, cutAt));
		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) // 자르고 남을때
		result->push_back(origin.substr(0, cutAt));


}

bool String::StartWith(string str, string comp)
{	
	wstring::size_type index = str.find(comp);
	// 시작 값이 comp가 맞는지 확인
	if (index != wstring::npos && (int)index == 0)
	{
		return true;
	}

	return false;
}

bool String::StartWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);

	if (index != wstring::npos && (int)index == 0)
	{
		return true;
	}

	return false;
}

bool String::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

bool String::Replace(string* str, string comp, string rep)
{
	
	// ABCDE
	// CDE = AAAAAA
	// ABCAAAAAA

	string temp = *str;
	size_t startPos = 0;
	while ((startPos)==temp.find(comp) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}

bool String::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;
	size_t startPos = 0;
	while ((startPos) == temp.find(comp) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}

string String::ToString(D3DXVECTOR3 vec3, int precision)
{
	string temp;
	stringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	
	temp = "X : " + stream1.str() + " Y : " + stream2.str() + " Z : " + stream3.str();
	return temp;
}

wstring String::ToWstring(D3DXVECTOR3 vec3, int precision)
{
	wstring temp;
	wstringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;

	temp = L"X : " + stream1.str() + L" Y : " + stream2.str() + L" Z : " + stream3.str();

	return temp;
}

wstring String::ToWstring(string str)
{
	wstring temp = L"";
	temp.assign(str.begin(), str.end());
	return temp;
}

string String::ToString(wstring str)
{
	string temp = "";
	temp.assign(str.begin(), str.end());
	return temp;
}
