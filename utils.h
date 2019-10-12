#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include <string>

using ccstring = std::basic_string<cchar_t>;

namespace cupasy {

	// character converters
	void ctocc(const char* c, cchar_t*&, attr_t attrs = 0, short color_pair = 0); /** char* (single) to cchar_t* */
	void ctocc(char c, cchar_t*&, attr_t attrs = 0, short color_pair = 0); /** char to cchar_t* */
	void wctocc(const wchar_t* wc, cchar_t*& cc, attr_t attrs = 0, short color_pair = 0); /** wchar_t to cchar_t */

	// string converters
	void cstoccs(const char* cs, ccstring& ccs, attr_t attrs = 0, short color_pair = 0); /** char* to ccstring */
	void cstowcs(const std::string& from, std::wstring& to); /** string to wstring */

	// cchar_t validity
	static const cchar_t INVALID_CCHAR {0, L"\000\000\000\000", 0};
	bool isValid(const cchar_t& cc);
}

#endif // UTILS_H
