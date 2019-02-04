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
XMLMarshaller::XMLMarshaller(std::ostream & outStream) : out(outStream) {
}

/**
 The manipulate method is inherited from EntityManipulator and since it is pure virtual
 (abstract) method there, it has to be overridden here. Otherwise, this class would also
 be abstract and  you couldn't instantiate it.<p>
 Here, the XMLMarshaller just writes the propertes of the Entity into the output stream
 in XML format. Then the marshaller is sent to visit the children of this Entity.
 @param entity The entity to manipulate.
 */
void XMLMarshaller::manipulate(Entity & entity, int level) {
   if (level == 0) {
      out << "<?xml version=\"1.0\"?>\n";
   }
   std::string indentStr("");
   for (int indent=0; indent < level; indent++) {
      indentStr += "  ";
   }
   out << indentStr << "<entity name=\"" << entity.getName()  << "\">" << std::endl;
   if (entity.hasChildren()) {
      level++;
      entity.passToChildren(*this, level);
      level--;
   }
   out << indentStr << "</entity>" << std::endl;
}
