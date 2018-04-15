#include "diff_match_patch.h"
#include <locale> 
#include <iostream>

class TestDiffPatch {
public:
	static void RunWstring()
	{
		diff_match_patch<std::wstring> dmp;

		std::wstring commonStr = L"�հ�Ǩ������ͬʱ,���WORDPRESS����һЩ�Ż�,�ٶ����Ըо��ǿ��˺ܶࡣ ���...��ѽ,Ӱ����վ�����ٶȿ�����Ӧ�����������,ԭ����Ȼ������";
		std::wstring text1 = L"2017��3��6�� - �հ�Ǩ������ͬʱ,���WORDPRESS����һЩ�Ż�,�ٶ����Ըо��ǿ��˺ܶࡣ ���...��ѽ,Ӱ����վ�����ٶȿ�����Ӧ�����������,ԭ����Ȼ������ ��վ�ᵽ...";
		std::wcout.imbue(std::locale("chs"));
		std::wcout << commonStr << std::endl;
		diff_match_patch<std::wstring>::Diffs diffs = dmp.diff_main(commonStr, text1);
		diff_match_patch<std::wstring>::Diffs::iterator itDiff = diffs.begin();
		for (; itDiff != diffs.end(); ++itDiff)
		{
			std::wcout << itDiff->toString() << " ";
		}
		std::wcout << std::endl;
		//Result: [(-1, 'Hell'), (1, 'G'), (0, 'o'), (1, 'odbye'), (0, ' World.')]
		diff_match_patch<std::wstring>::Patches patches = dmp.patch_make(diffs);
		std::wstring patchesStr = dmp.patch_toText(patches);
		std::wcout << patchesStr << std::endl;
		patches = dmp.patch_fromText(patchesStr);
		std::pair<std::wstring, std::vector<bool> > results = dmp.patch_apply(patches, commonStr);

		std::wcout << results.first << std::endl;

		std::wcout << patchesStr.size() << " " << text1.size() << std::endl;
	}
};