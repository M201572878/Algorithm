#include "Python\Python.h"
#include<string>
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
			int len = 0;
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

private:
	PyObject* m_pModule;

	PythonUtil()
	{
		Py_Initialize();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("print(sys.path)");
		PyRun_SimpleString("sys.path.append('C://Users//hyhyx//Desktop//Code//CppPractise//VisualStudio//runtime//TestCpp//Win32')");
		PyRun_SimpleString("print(sys.path)");
		m_pModule = PyImport_ImportModule("PythonUtil");

	}

	~PythonUtil()
	{
		Py_Finalize();
	}
	
};