#include "Python\Python.h"
#include<string>
#include<fstream>

static std::string g_pythonUtilStr = "\
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

class PythonUtil {
public:
	static PythonUtil& Instance()
	{
		static PythonUtil instance;
		return instance;
	}

	bool Compress(std::string& inDat, std::string& outDat)
	{
		try
		{
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, PyBytes_FromStringAndSize(inDat.data(), inDat.length()));//0—序号 i表示创建int型变量 
			PyObject * pFunc = PyObject_GetAttrString(m_pModule, "compress");
			PyObject *pResult = PyEval_CallObject(pFunc, pArgs);
			char *str = NULL;
			Py_ssize_t len = 0;
			PyBytes_AsStringAndSize(pResult, &str, &len);
			outDat.resize(len);
			strcpy_s(&outDat[0], len, str);

			Py_XDECREF(pResult);
			Py_XDECREF(pArgs);
			Py_XDECREF(pFunc);
		}
		catch (...)
		{
			printf("error\n");
			return false;
		}
		return true;
	}

	void Decompress()
	{}

	std::string GetCurrUserHomePath()
	{
		PyObject* pModule = PyImport_ImportModule("ntpath");
		PyObject * pFunc = PyObject_GetAttrString(pModule, "expanduser");
		PyObject *pArgs = PyTuple_New(1);
		PyTuple_SetItem(pArgs, 0, PyUnicode_FromString("~"));//0—序号 i表示创建int型变量 
		PyObject *pResult = PyEval_CallObject(pFunc, pArgs);
		std::string homePath = PyUnicode_AsUTF8(pResult);
		Py_XDECREF(pResult);
		Py_XDECREF(pArgs);
		Py_XDECREF(pFunc);
		Py_XDECREF(pModule);
		return homePath;
	}

private:
	PyObject* m_pModule;

	PythonUtil()
	{
		Py_Initialize();
		std::string homePath = GetCurrUserHomePath();
		std::string pythonUtilPath = homePath + "/PythonUtil.py";
		std::string appendPathStr = "sys.path.append('" + homePath + "')";
		while (true) {
			string::size_type   pos(0);
			if ((pos = appendPathStr.find('\\')) != string::npos)
				appendPathStr.replace(pos, 1, "/");
			else   break;
		}

		ofstream file(pythonUtilPath, ios::trunc | ios::out);
		file.write(g_pythonUtilStr.c_str(), g_pythonUtilStr.length());
		file.close();

		PyRun_SimpleString("import sys");
		PyRun_SimpleString(appendPathStr.c_str());
		m_pModule = PyImport_ImportModule("PythonUtil");
	}

	~PythonUtil()
	{
		Py_XDECREF(m_pModule);
		Py_Finalize();
	}
	
};