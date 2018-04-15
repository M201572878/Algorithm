#include <iostream>
#include "TestPython.hpp"
#include "TestDiffPatch.hpp"
#include "PythonUtil.hpp"

using namespace std;

static string pythonStr = "\
import zlib\n\
\n\
def TestList():\n\
	print(\"TestList\")\n\
	s = b\"hello word, 00000000000000000000000000000000\"\n\
	print(len(s),s)\n\
	c = zlib.compress(s)\n\
	print(len(c), c)\n\
	d =  zlib.decompress(c)\n\
	print(d)\n\
\n\
def compress(str):\n\
	try:\n\
		data = str\n\
		print(data)\n\
		c=b\"----------------\"\n\
		c = zlib.compress(data)\n\
	except Exception as e:\n\
		print(e)\n\
	finally:\n\
		print(len(c),c)\n\
		return c\n\
";

int main()
{
	cout << pythonStr << endl;
	//TestPython::run();

	//TestDiffPatch::RunWstring();
	string str = "1";
	cout << str.length() << " " << str.size() << endl;

	string inStr("sssssss09765653453457679885674ÖÐÎÄs"),outStr;
	PythonUtil::Instance().Compress(inStr, outStr);
	cout << outStr.length()<<" "<<outStr << endl;
	
	getchar();
	return 0;
}