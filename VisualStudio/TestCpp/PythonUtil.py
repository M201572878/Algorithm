import zlib
import sys
sys.path.append('C://Users//hyhyx//Desktop//Code//CppPractise//VisualStudio//runtime//TestCpp//Win32')

def TestList():
	print("TestList")
	s = b"hello word, 00000000000000000000000000000000"
	print(len(s),s)
	c = zlib.compress(s)
	print(len(c), c)
	d =  zlib.decompress(c)
	print(d)

def compress(str):
	try:
		data = str
		print(data)
		c=b"----------------"
		c = zlib.compress(data)
	except Exception as e:
		print(e)
	finally:
		print(len(c),c)
		return c
	
#compress11("sssssss09765653453457679885674中文s")
# TestList()
