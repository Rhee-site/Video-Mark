#include "pch.h"
#include "Util.h"

int Util::CheckScope(const Point2i n2Center, const Point2i n2Start, const Point2i n2End)
{
	vector<Point2i> n2TempArea;
	n2TempArea.push_back(n2Start);
	n2TempArea.push_back(Point2i(n2End.x, n2Start.y));
	n2TempArea.push_back(n2End);
	n2TempArea.push_back(Point2i(n2Start.x, n2End.y));

	int nResult = 0;
	for (int j = 0; j < n2TempArea.size(); j++)
	{
		int k = (j + 1) % n2TempArea.size();
		if ((n2TempArea[j].y > n2Center.y) != (n2TempArea[k].y > n2Center.y))
		{
			double atX = (n2TempArea[k].x - n2TempArea[j].x) * (n2Center.y - n2TempArea[j].y) / (n2TempArea[k].y - n2TempArea[j].y) + n2TempArea[j].x;
			if (n2Center.x < atX)
				nResult++;
		}
	}

	return nResult;
}

int Util::ConvertRatioToPoint(const int nFrameLength, const float fRatio)
{
	return fRatio * nFrameLength;
}

float Util::ConvertPointToRatio(const int nFrameLength, const int nPoint)
{
	return (float)nPoint / (float)nFrameLength;
}

int Util::CheckSameNameIndex(const vector<string> VecstrSrc, const string strTarget)
{
	bool bCheck = false;
	int nResult = 0;
	for (int index = 0; index < VecstrSrc.size(); index++) {
		if (VecstrSrc[index] == strTarget) {
			bCheck = true;
			nResult = index;
			break;
		}
	}

	if (!bCheck)
		nResult = -1;
	
	return nResult;
}

vector<wstring> Util::GetFileListInFolder(wstring wstrFolderName, wstring wstrFileType)
{
	vector<wstring> names;
	wchar_t search_path[200];
	wsprintf(search_path, L"%s/%s", wstrFolderName.c_str(), wstrFileType.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	return names;
}

void Util::DrawObjectInImage(Mat& DrawFrame, ImageInfo ImageInformation)
{
	for (int index = 0; index < ImageInformation.Object.size(); index++) {
		rectangle(DrawFrame, ImageInformation.Object[index].n2Start, ImageInformation.Object[index].n2End, Scalar(255,255,255));
	}
}

TCHAR* Util::StringToTCHAR(string& s)
{
	std::basic_string<TCHAR> tstr;
	const char* all = s.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	mbstowcs(t, all, len);
	return (TCHAR*)t;
}

string Util::TCHARToString(TCHAR* ptsz)
{
	int len = wcslen((wchar_t*)ptsz);
	char* psz = new char[2 * len + 1];
	wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
	std::string s = psz;
	delete[] psz;
	return s;
}

wstring Util::StringToWString(string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
