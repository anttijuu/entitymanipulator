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
JSONMarshaller::JSONMarshaller(std::ostream & os) : out(os) {
}

/**
 The manipulate method is inherited from EntityManipulator and since it is pure virtual
 (abstract) method there, it has to be overridden here. Otherwise, this class would also
 be abstract and  you couldn't instantiate it.<p>
 Here, the JSONMarshaller just writes the propertes of the Entity into the output stream
 in JSON format. If the Entity has children, then all those are also visited by this marshaller.
 @param entity The entity to manipulate.
 @param level In which level of object hierarchy we are currently.
 */
void JSONMarshaller::manipulate(Entity & entity, int level) {
   std::string indentStr("  ");
   for (int indent=0; indent < level; indent++) {
      indentStr += "  ";
   }

   if (level == 0) {
      out << "{" << std::endl;
   } else {
      out << indentStr << "{" << std::endl;
   }
   out << indentStr << "\"name\" : \"" << entity.getName() << "\"";
   // out << indentStr << "}";
   if (entity.hasChildren()) {
      out << "," << std::endl;
      out << indentStr << "\"children\" : " << std::endl;
      out << indentStr << "[" << std::endl;
      level++;
      entity.passToChildren(*this, level);
      level--;
      out << indentStr << "]";
   }

   const Entity * parent = entity.getParent();
   out << std::endl;
   if (level == 0) {
      out << "}";
   } else {
      out << indentStr << "}";
   }
   if (parent != nullptr && parent->hasElementsAfter(&entity)) {
      out << "," << std::endl;
   } else {
      out << std::endl;
   }

}
