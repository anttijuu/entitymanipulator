//
//  JSONMarshaller.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 10.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <iostream>

#include "JSONMarshaller.h"
#include "Entity.h"

/**
 The constructor for the JSONMarshaller. It stores the reference to output stream
 to a member variable. It is done in the initialization list -- all reference member
 variables must be initialized in the constructor's initialization list. As well as const
 members.
 @param outStream The output stream where to print stuff.
 */
JSONMarshaller::JSONMarshaller(std::ostream & os) : out(os), levels(0) {
   
}

/**
 The manipulate method is inherited from EntityManipulator and since it is pure virtual
 (abstract) method there, it has to be overridden here. Otherwise, this class would also
 be abstract and  you couldn't instantiate it.<p>
 Here, the JSONMarshaller just writes the propertes of the Entity into the output stream
 in JSON format. It goes up the parent path of the Element to the topmost parent, and then
 starts printing out the objects hierarchy down the path to this element.
 @param entity The entity to manipulate.
 */
void JSONMarshaller::manipulate(Entity & entity) {
	static int topLevel = 0;
   // First find the topmost parent (entity who's parent is null).
	Entity * parent = entity.getParent();
	if (nullptr != parent) {
		topLevel = ++levels;
		parent->accept(*this);
		levels--;
	} else {
		out << "{" << std::endl;
	}
   // Then start printing, coming "down" from the call stack from the topmost to most
   // bottom Entity in the hierarchy.
   std::string indentStr("  ");
	for (int indent=0; indent<topLevel-levels; indent++) {
		indentStr += "  ";
	}
   out << indentStr << "\"entity\" : {" << std::endl;
   out << indentStr << "  \"name : \"" << entity.getName() << "\"" << std::endl;
   if (levels == 0) {
      for (int counter = topLevel; counter >= 0; --counter) {
         indentStr = "";
         for (int indent=counter; indent>=0; --indent) {
            indentStr += "  ";
         }
         out << indentStr << "}" << std::endl;
      }
		out << "}" << std::endl;
   }
}
