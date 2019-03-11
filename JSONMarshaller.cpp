//
//  JSONMarshaller.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 10.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <iostream>
#include <iomanip>

#include "JSONMarshaller.h"
#include "EntityComposite.h"
#include "EntityLeaf.h"

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
void JSONMarshaller::manipulate(EntityComposite & entity, int level) {
   int baseWidth = level * 3;
   out << std::setw(baseWidth+1) << "{" << std::endl;

   // To get prettier printout, increase level and calculate indent again after printing "{"
   baseWidth = ++level * 3;

   out << std::setw(baseWidth+10) << "\"name\" : \"" << entity.getName() << "\"";
   std::string value = entity.getValue();
   if (value.length() > 0) {
      out << "," << std::endl << std::setw(baseWidth+11) << "\"value\" : \"" << entity.getValue() << "\"";
   } else {
      out << std::endl;
   }
   if (entity.hasChildren()) {
      out << "," << std::endl;
      out << std::setw(baseWidth+14) << "\"children\" : [" << std::endl;
      level++;
      entity.passToChildren(*this, level);
      level--;
      out << std::setw(baseWidth+1) << "]" << std::endl;
   }
   // To get prettier printout, decrease level and calculate indent again before printing "}"
   baseWidth = --level * 3;
   const Entity * parent = entity.getParent();
   if (parent != nullptr) {
      if (parent->hasElementsAfter(&entity)) {
         out << std::setw(baseWidth+2) <<  "}," << std::endl;
      } else {
         out << std::setw(baseWidth+1) << "}" << std::endl;
      }
   } else {
      out << "}" << std::endl;
   }
   
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
void JSONMarshaller::manipulate(EntityLeaf & entity, int level) {
   int baseWidth = level * 3;
   out << std::setw(baseWidth+1) << "{" << std::endl;

   baseWidth = ++level * 3;
   out << std::setw(baseWidth+10) << "\"name\" : \"" << entity.getName() << "\"";
   std::string value = entity.getValue();
   if (value.length() > 0) {
      out << "," << std::endl << std::setw(baseWidth+11) << "\"value\" : \"" << entity.getValue() << "\"" << std::endl;
   }
   baseWidth = --level * 3;
   const Entity * parent = entity.getParent();
   if (parent != nullptr) {
      if (parent->hasElementsAfter(&entity)) {
         out << std::setw(baseWidth+2) <<  "}," << std::endl;
      } else {
         out << std::setw(baseWidth+1) <<  "}" << std::endl;
      }
   } else {
      out << "asdfasdfasf}" << std::endl;
   }
   
}
