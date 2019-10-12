#include <fstream>
#include <locale>
#include <codecvt>
#include <utility>
#include "FileReader.h"
#include "utils.h"
using namespace std;

FileReader::FileReader(string _path) : Component(1, 1), path(move(_path)) {}

void FileReader::updComp() {
	vector<wstring> lbuf;
	wifstream file(path, ios::binary);

	// read file
	if(file.is_open()) {
		// consume head to allow the insanity that is unicode. the hivemind approaches.
		file.imbue(locale(file.getloc(), new codecvt_utf8_utf16<wchar_t, 0x10ffff, consume_header>));

		wstring line;
		while(getline(file, line)) {
			lbuf.emplace_back(line);
		}
		file.close();
	}

	// resize text buffer
	ulong maxWidth = 0;
	for(auto & s : lbuf) {
		if(s.size() > maxWidth) {
			maxWidth = s.size();
		}
	}
	resize(maxWidth, lbuf.size());

	// convert line buffer to text buffer
	cchar_t* tmp;
	for(size_t y=0; y<lbuf.size(); ++y) {
		for(size_t x=0; x<lbuf[y].size(); ++x) {
			cupasy::wctocc(&lbuf[y][x], tmp);
			buffer[x][y] = *tmp;
		}
	}
}
