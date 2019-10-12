#ifndef LABEL_H
#define LABEL_H


#include "Component.h"
#include <string>

class Label : public Component {
	void updComp() override;
	std::wstring text = L"";

public:
	Label();
	Label(const std::wstring& _text);
	Label(const std::string& _text);

	void setText(const std::wstring& _text);
	void setText(const std::string& _text);

	void getText(std::wstring& _text) const;
};

#endif // LABEL_H
