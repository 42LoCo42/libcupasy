#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include "Component.h"

class FileReader : public Component {
	std::string path;

	void updComp() override;

public:
	FileReader(std::string _path);
};

#endif // FILEREADER_H
