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
   doFirstPart(entity, level, baseWidth);

   if (entity.hasChildren()) {
      baseWidth = ++level * 3;
      out << std::setw(baseWidth+14) << "\"children\" : [" << std::endl;
      entity.passToChildren(*this, ++level);
      baseWidth = --level * 3;
      out << std::setw(baseWidth+1) << "]" << std::endl;
   }
   baseWidth = --level * 3;
   doLastPart(entity, level, baseWidth);
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
   doFirstPart(entity, level, baseWidth);
   doLastPart(entity, level, baseWidth);
}

/** A helper method to externalize the beginning part of the object as JSON.
 @param entity The entity to export/marshal.
 @param level Level in object hierarchy were the marshaller currently navigates.
 @param baseWidth The amount of indentation currently calculate for this level.
 */
void JSONMarshaller::doFirstPart(Entity & entity, int level, int baseWidth) {
   out << std::setw(baseWidth+1) << "{" << std::endl;
   
   baseWidth = ++level * 3;
   out << std::setw(baseWidth+10) << "\"name\" : \"" << entity.getName() << "\"";
   std::string value = entity.getValue();
   if (value.length() > 0) {
      out << "," << std::endl << std::setw(baseWidth+11) << "\"value\" : \"" << entity.getValue() << "\"" << std::endl;
   }
}

/** A helper method to externalize the end part of the object as JSON.
 @param entity The entity to export/marshal.
 @param level Level in object hierarchy were the marshaller currently navigates.
 @param baseWidth The amount of indentation currently calculate for this level.
 */
void JSONMarshaller::doLastPart(Entity & entity, int level, int baseWidth) {
   const Entity * parent = entity.getParent();
   if (parent != nullptr) {
      if (parent->hasElementsAfter(&entity)) {
         out << std::setw(baseWidth+2) <<  "}," << std::endl;
      } else {
         out << std::setw(baseWidth+1) <<  "}" << std::endl;
      }
   } else {
      out << "}" << std::endl;
   }
}
