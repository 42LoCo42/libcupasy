#include "utils.h"
#include <locale>
#include <codecvt>
using namespace std;

namespace cupasy {
	// character converters
	void ctocc(const char* c, cchar_t*& cc, const attr_t attrs, const short color_pair) {
		std::wstring wcs;
		cupasy::cstowcs(std::string(c), wcs);
		cupasy::wctocc(&wcs[0], cc, attrs, color_pair);
	}

	void ctocc(const char c, cchar_t*& cc, const attr_t attrs, const short color_pair) {
		string s(1, c);
		ctocc(s.c_str(), cc, attrs, color_pair);
	}

	void wctocc(const wchar_t* wc, cchar_t*& cc, const attr_t attrs, const short color_pair) {
		cc = WACS_HLINE; // make cc valid
		setcchar(cc, wc, attrs, color_pair, nullptr); // nullptr is for opts (not in use)
	}

	// string converters
	void cstoccs(const char* cs, ccstring& ccs, const attr_t attrs, const short color_pair) {
		std::wstring wcs;
		cstowcs(cs, wcs);

		cchar_t* tmp;
		for(auto & i : wcs) {
			wctocc(&i, tmp, attrs, color_pair);
			ccs.push_back(*tmp);
		}
	}

	void cstowcs(const std::string& from, std::wstring& to) {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		to = converter.from_bytes(from);
	}

	// cchar_t validity
	bool isValid(const cchar_t& cc) {
		bool res = false;

		for(auto & i : cc.chars) {
			int val = static_cast<int>(i);
			res = res | val; // test if any character is nonzero
		}
		return res;
	}
}
