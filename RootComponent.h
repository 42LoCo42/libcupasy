#ifndef ROOTCOMPONENT_H
#define ROOTCOMPONENT_H

#include "Component.h"

/**
A component that automatically fills the screen and handles printing.
*/
class RootComponent : public Component {
public:
	RootComponent();
	//~RootComponent() override;

	bool draw(ulong minX, ulong minY, ulong maxX, ulong maxY, const Component* child) const;
	bool draw() const;
};

#endif // ROOTCOMPONENT_H
