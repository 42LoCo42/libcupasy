#include "Component.h"
#include "RootComponent.h"
#include "utils.h"
using namespace std;
using namespace cupasy;

Component::Component(ulong width, ulong height) {
	if(!width) width = 1;
	if(!height) height = 1;
	resize(width, height);
}

void Component::resize(ulong width, ulong height) {
	if(width == 0 || height == 0) return;

	buffer = vector<column_t>(width);

	for(auto & x : buffer) {
		x = column_t(height);

		for(auto & y : x) {
			y = INVALID_CCHAR;
		}
	}
}

size_t Component::addChild(Component* child, ulong posX, ulong posY) {
	children.emplace_back(child_t(child, posX, posY));
	children[children.size()-1].comp->parent = this;
	return children.size()-1;
}

size_t Component::addChild(Component &child, ulong posX, ulong posY) {
	return addChild(&child, posX, posY);
}

void Component::removeChild(size_t index) {
	if(index < children.size()) {
		children[index].comp->parent = nullptr;
		children.erase(children.begin() + static_cast<long>(index));
	}
}

child_t* Component::getChild(size_t index) {
	return &children[index];
}

void Component::moveChild(size_t index, ulong x, ulong y) {
	if(index >= children.size()) return;
	if(x > getWidth()-1) return;
	if(y > getHeight()-1) return;

	children[index].posX = x;
	children[index].posY = y;
}

bool Component::findChild(const Component* child, size_t& index) const {
	for(index=0; index<children.size(); ++index) {
		if(children[index].comp == child) return true;
	}

	return false;
}

void Component::update() {
	// Update all children
	for(auto & i : children) {
		i.comp->update();
	}

	updComp();
}

bool Component::getCharAt(ulong x, ulong y, cchar_t& cc) const {
	if(x >= getWidth() || y >= getHeight()) return false; // position not part of component

	cchar_t cc_tmp = INVALID_CCHAR;

	if(isValid(buffer[x][y])) { // this component has a valid char at this location
		cc_tmp = buffer[x][y];
	}
	else { // get char from children; the last valid one will be used
		for(auto & i : children) {
			i.comp->getCharAt(x - i.posX, y - i.posY, cc_tmp);
		}
	}

	if(isValid(cc_tmp)) { // insert valid char into reference
		cc = cc_tmp;
		return true;
	}
	return false;
}

void Component::box(const char* hori, const char* vert, const char* lu, const char* ru, const char* ll, const char* rl) {
	cchar_t* tmp;
	ulong width = getWidth();
	ulong height = getHeight();

	// horizontal border
	ctocc(hori, tmp);
	for(size_t x=1; x<width-1; ++x) {
		buffer[x][0] = *tmp;
		buffer[x][height-1] = *tmp;
	}

	// vertical border
	ctocc(vert, tmp);
	for(size_t y=1; y<height-1; ++y) {
		buffer[0][y] = *tmp;
		buffer[width-1][y] = *tmp;
	}

	// corners
	ctocc(lu, tmp); buffer[0][0] = *tmp;
	ctocc(ru, tmp); buffer[width-1][0] = *tmp;
	ctocc(ll, tmp); buffer[0][height-1] = *tmp;
	ctocc(rl, tmp); buffer[width-1][height-1] = *tmp;
}

void Component::box() {
	box("─", "│", "┌", "┐", "└", "┘");
}

bool Component::draw() const {
	if(!parent) return false;

	return parent->draw(0, 0, getWidth()-1, getHeight()-1, this);
}

bool Component::draw(ulong minX, ulong minY, ulong maxX, ulong maxY, const Component* child) const {
	if(!parent) return false;

	resolveChildPosition(minX, minY, maxX, maxY, child);

	// check if our parent is a root component
	auto root = dynamic_cast<RootComponent*>(parent);
	if(root) {
		return root->draw(minX, minY, maxX, maxY, this);
	}
	return parent->draw(minX, minY, maxX, maxY, this);
}

void Component::resolveChildPosition(ulong& minX, ulong& minY, ulong& maxX, ulong& maxY, const Component* child) const {
	size_t index;
	if(findChild(child, index)) {
		ulong posX = children[index].posX;
		ulong posY = children[index].posY;

		// Resolve position
		minX += posX;
		minY += posY;
		maxX += posX;
		maxY += posY;
	}
}
