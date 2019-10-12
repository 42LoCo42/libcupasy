#include "ASCIIMovie.h"
#include "FileReader.h"
#include "utils.h"

#include <sys/stat.h>
#include <chrono>
#include <thread>
#include <ncurses.h>
using namespace std;

ASCIIMovie::ASCIIMovie(const char* _movieDir) : Component(1, 1), movieDir(_movieDir) {}

bool ASCIIMovie::draw() {
	bool res = false;
	uint frameID = 0;

	while(true) {
		string frameName = movieDir + "/" + to_string(frameID) + ".asciimov";

		if(fileExists(frameName)) {
			FileReader frameText(frameName);
			frameText.update();

			resize(frameText.getWidth()+2, frameText.getHeight()+2);
			size_t myIndex;
			parent->findChild(this, myIndex);
			parent->moveChild(myIndex, (parent->getWidth() - getWidth())/2, (parent->getHeight() - getHeight())/2);

			size_t childID = addChild(&frameText, 0, 0);
			res |= frameText.draw();
			refresh();

			removeChild(childID);
			this_thread::sleep_for(chrono::milliseconds(300));
			++frameID;
		}
		else break;
	}

	return res;
}

bool ASCIIMovie::fileExists(const std::string& name) {
	struct stat buffer {};
	return(stat(name.c_str(), &buffer) == 0);
}
