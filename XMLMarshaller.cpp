//
//  XMLMarshaller.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include "XMLMarshaller.h"
#include "Entity.h"

/**
 The constructor for the XMLMarshaller. It stores the reference to output stream
 to a member variable. It is done in the initialization list -- all reference member
 variables must be initialized in the constructor's initialization list. As well as const
 members.
 @param outStream The output stream where to print stuff.
 */
XMLMarshaller::XMLMarshaller(std::ostream & outStream) : out(outStream), levels(0) {
}

/**
 The manipulate method is inherited from EntityManipulator and since it is pure virtual
 (abstract) method there, it has to be overridden here. Otherwise, this class would also
 be abstract and  you couldn't instantiate it.<p>
 Here, the XMLMarshaller just writes the propertes of the Entity into the output stream
 in XML format. It goes up the parent path of the Element to the topmost parent, and then
 starts printing out the objects hierarchy down the path to this element.
 @param entity The entity to manipulate.
 */
void XMLMarshaller::manipulate(Entity & entity) {
	static int topLevel = 0;
   // First find the topmost parent (entity who's parent is null).
	Entity * parent = entity.getParent();
	if (nullptr != parent) {
		topLevel = ++levels;
		parent->accept(*this);
		levels--;
	} else {
		out << "<?xml version=\"1.0\"?>\n";
	}
   // Then start printing, coming "down" from the call stack from the topmost to most
   // bottom Entity in the hierarchy.
	for (int indent=0; indent<topLevel-levels; indent++) {
		out << " ";
	}
	out << "<entity name=\"" << entity.getName() << "\">\n";
	if (levels == 0) {
		for (int i=topLevel; i>=0; i--) {
			for (int indent=i-1; indent>=0; indent--) {
				out << " ";
			}
			out << "</entity>\n";
		}
	}
}
