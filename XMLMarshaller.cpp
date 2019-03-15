//
//  XMLMarshaller.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//
#include <iomanip>

#include "XMLMarshaller.h"
#include "EntityComposite.h"
#include "EntityLeaf.h"

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
 Here, the XMLMarshaller just writes the propertes of the EntityComposite into the output stream
 in XML format. Then the marshaller is sent to visit the children of this Entity.
 @param entity The entity to manipulate.
 @param level In which level of object hierarchy we are.
 */
void XMLMarshaller::manipulate(EntityComposite & entity, int level) {
   if (level == 0) {
      out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
   }
   
   std::string name = "<" + entity.getName();
   if (entity.getValue().length()> 0) {
      name += " " + entity.getName() + "-identifier=\"" + entity.getValue() + "\">";
   } else {
      name += ">";
   }
   int entityNameLength = name.length();
   out << std::setw((level*3)+entityNameLength) << name;
   if (entity.childCount() > 0) {
      out << std::endl;
      level++;
      entity.passToChildren(*this, level);
      level--;
   }
   name = "</" + entity.getName() + ">";
   entityNameLength = name.length();
   out << (entity.childCount() > 0 ? std::setw((level*3)+entityNameLength) : std::setw(0)) << name << std::endl;
}

/**
 The manipulate method is inherited from EntityManipulator and since it is pure virtual
 (abstract) method there, it has to be overridden here. Otherwise, this class would also
 be abstract and  you couldn't instantiate it.<p>
 Here, the XMLMarshaller just writes the propertes of the EntityLeaf into the output stream
 in XML format.
 @param entity The entity to manipulate.
 @param level In which level of object hierarchy we are.
 */
void XMLMarshaller::manipulate(EntityLeaf & entity, int level) {
   if (level == 0) {
      out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
   }
   const std::string name = "<" + entity.getName() + ">";
   out << std::setw((level*3)+name.length()) << name
      << entity.getValue()
      << "</" << entity.getName() << ">" << std::endl;
}
