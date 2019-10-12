#ifndef ASCIIMOVIE_H
#define ASCIIMOVIE_H

#include <string>
#include "Component.h"

class ASCIIMovie : public Component {
	std::string movieDir;
public:
	ASCIIMovie(const char* _movieDir);
	[[nodiscard]] bool draw();
	bool fileExists(const std::string& name);
};

#endif // ASCIIMOVIE_H
