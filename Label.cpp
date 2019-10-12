#include "Label.h"
#include "utils.h"
using namespace std;
using namespace cupasy;

Label::Label() : Component(0, 0) {}

Label::Label(const wstring& _text) : Component(0, 0) {
	setText(_text);
}

Label::Label(const string& _text) : Component(0, 0) {
	setText(_text);
}

void Label::setText(const wstring& _text) {
	text = _text;
	setWidth(text.length());
}

void Label::setText(const string& _text) {
	wstring wtext;
	cstowcs(_text, wtext);
	setText(wtext);
}

void Label::getText(wstring& _text) const {
	_text = text;
}

void Label::updComp() {
	cchar_t* tmp;

	for(size_t i=0; i<text.length(); ++i) {
		wctocc(&text[i], tmp);
		buffer[i][0] = *tmp;
	}
}
