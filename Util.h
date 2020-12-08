#pragma once

#include <iostream>
#include <fstream>
#include <io.h> 
#include <direct.h> 

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#define BUFSIZE 256

typedef struct {
	int nClassNumber;
	Point2i n2Start;
	Point2i n2End;
}ObjectInfo;

typedef struct {
	int nFrameIndex;
	string strImageName;
	int nFrameWidth;
	int nFrameHeight;
	vector<ObjectInfo> Object;
}ImageInfo;

class Util
{
public:
	int CheckScope(const Point2i n2Center, const Point2i n2Start, const Point2i n2End);
	int ConvertRatioToPoint(const int nFrameLength, const float fRatio);
	float ConvertPointToRatio(const int nFrameLength, const int nPoint);
	int CheckSameNameIndex(const vector<string> VecstrSrc, const string strTarget);
	vector<wstring> GetFileListInFolder(wstring wstrFolderName, wstring wstrFileType);
	void DrawObjectInImage(Mat& DrawFrame, ImageInfo ImageInformation);
	TCHAR* StringToTCHAR(string& s);
	string TCHARToString(TCHAR * ptsz);
	wstring StringToWString(string & s);
};

