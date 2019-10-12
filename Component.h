#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <ncurses.h>
#include <sys/types.h>

class Component;

struct child_t {
public:
	Component* comp;
	ulong posX, posY;

	child_t(Component* _comp, ulong _posX, ulong _posY): comp(_comp), posX(_posX), posY(_posY) {}
};
using column_t = std::vector<cchar_t>;
using scrbuf_t = std::vector<column_t>;


/**
	A Component is a container for formatted text and other components.
	Redefine updComp() to your needs, then call update() externally to (re-)generate the text buffer(s).
	After that, call getCharAt() to get a character at a specific location.
	The character is retrieved from the this component if valid and all children otherwise.
	Or call draw() to request drawing from the root component.
*/
class Component {
protected:
	Component* parent = nullptr;
	scrbuf_t buffer; // the character buffer for this component
	std::vector<child_t> children;

	/** Override this method to add text to the component. */
	virtual void updComp() {}

	/** This method is called from a child to adjust the drawn area. */
	bool draw(ulong minX, ulong minY, ulong maxX, ulong maxY, const Component* child) const;
	/** Used in draw() to get the requested position relative to us. */
	void resolveChildPosition(ulong& minX, ulong& minY, ulong& maxX, ulong& maxY, const Component* child) const;

public:
	/** Constructor. Takes the size of the component */
	Component(ulong width, ulong height);
	virtual ~Component() = default;

	[[nodiscard]] inline size_t getWidth() const {return buffer.size();}
	[[nodiscard]] inline size_t getHeight() const {return buffer[0].size();}

	/** Resets the buffer to the specified size. */
	void resize(ulong width, ulong height);
	void setWidth(ulong width) {resize(width, getHeight());}
	void setHeight(ulong height) {resize(getWidth(), height);}

	/** Adds a component to this one. Returns the index of the new child. */
	size_t addChild(Component* child, ulong posX, ulong posY);
	size_t addChild(Component& child, ulong posX, ulong posY);
	/** Removes the child with that index. */
	void removeChild(size_t index);
	/** Return the child with that index. */
	child_t* getChild(size_t index);
	/** Changes the position of the child with that index relative to its parent component. */
	void moveChild(size_t index, ulong x, ulong y);
	/** Sets the index of the child, returns if found. */
	bool findChild(const Component* child, size_t& index) const;

	/** Update all buffers */
	void update();
	/** If this component has specified a valid character for this location, return it. Otherwise, return the last valid one from the children. */
	bool getCharAt(ulong x, ulong y, cchar_t& cc) const;
	/** Request drawing from root component. Therefore a root component is REQUIRED! */
	[[nodiscard]] bool draw() const;

	/** Draws a box around this component. */
	void box(const char* hori, const char* vert, const char* lu, const char* ru, const char* ll, const char* rl);
	void box();

};

#endif // COMPONENT_H
