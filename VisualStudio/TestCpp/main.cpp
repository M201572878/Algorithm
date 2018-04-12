#include <iostream>
#include "diff_match_patch.h"
#include <locale> 

using namespace std;

//int main()
//{
//	diff_match_patch<string> dmp;
//
//	string commonStr = "I am jack";
//	string text1 = "I am  a coder";
//	diff_match_patch<string>::Diffs diffs = dmp.diff_main(commonStr, text1);
//	diff_match_patch<string>::Diffs::iterator itDiff = diffs.begin();
//	for (; itDiff != diffs.end(); ++itDiff)
//	{
//		cout << itDiff->toString() << " ";
//	}
//	cout << endl;
//	//Result: [(-1, 'Hell'), (1, 'G'), (0, 'o'), (1, 'odbye'), (0, ' World.')]
//	diff_match_patch<string>::Patches patches = dmp.patch_make(diffs);
//	string patchesStr = dmp.patch_toText(patches);
//	cout << patchesStr << endl;
//	patches = dmp.patch_fromText(patchesStr);
//	pair<string, vector<bool> > results = dmp.patch_apply(patches, commonStr);
//
//	cout << results.first << endl;
//	getchar();
//	return 0;
//}

int main()
{
	diff_match_patch<wstring> dmp;

	wstring commonStr = L"我是 jack";
	wstring text1 = L"这是测试比较";
	wcout.imbue(locale("chs"));
	wcout << commonStr << endl;
	diff_match_patch<wstring>::Diffs diffs = dmp.diff_main(commonStr, text1);
	diff_match_patch<wstring>::Diffs::iterator itDiff = diffs.begin();
	for (; itDiff != diffs.end(); ++itDiff)
	{
		wcout << itDiff->toString() << " ";
	}
	wcout << endl;
	//Result: [(-1, 'Hell'), (1, 'G'), (0, 'o'), (1, 'odbye'), (0, ' World.')]
	diff_match_patch<wstring>::Patches patches = dmp.patch_make(diffs);
	wstring patchesStr = dmp.patch_toText(patches);
	wcout << patchesStr << endl;
	patches = dmp.patch_fromText(patchesStr);
	pair<wstring, vector<bool> > results = dmp.patch_apply(patches, commonStr);

	wcout << results.first << endl;
	getchar();
	return 0;
}