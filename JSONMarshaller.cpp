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
 @param os The output stream where to print stuff.
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

	const Entity * parent = entity.getParent();
	bool isArray = entity.entitiesAreRepeating();

	std::string opener = "{";
	if (parent == nullptr) {
		if (isArray) {
			opener = "[";
		}
		out << std::setw(baseWidth) << opener << "\n";
	} else {
		if (isArray) {
			opener = "[";
			std::string name = "\"" + entity.getName() + "\" : " + opener;
			int entityNameLength = (int)name.length();
			out << std::setw(baseWidth+entityNameLength) << name << "\n";
		} else {
			out << std::setw(baseWidth+1) << opener << "\n";
			std::string value = entity.getValue();
			if (value.length() > 0) {
				baseWidth = ++level * 3;
				std::string output = "\"" + entity.getName() + "-description\" : \"" + value + "\",";
				out << std::setw(baseWidth+(int)output.length()) << output<< "\n";
				baseWidth = --level * 3;
			}
		}
	}
   if (entity.childCount() > 0) {
      entity.passToChildren(*this, ++level);
   }
	std::string terminator = "}";
	if (isArray) {
		terminator = "]";
	}
	if (parent == nullptr) {
		baseWidth = --level * 3;
		out << std::setw(baseWidth+1) << terminator << "\n";
	} else {
		baseWidth = --level * 3;
		if (parent->hasElementsAfter(&entity)) {
			out << std::setw(baseWidth+1) << terminator << "," << "\n";
		} else {
			if (isArray) {
				out << std::setw(baseWidth+1) << "]" << "\n";
			} else {
				out << std::setw(baseWidth+1) << "}" << "\n";
			}
		}
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
   std::string name = "\"" + entity.getName() + "\" : ";
   int entityNameLength = (int)name.length();
   out << std::setw(baseWidth+entityNameLength) << name;
   std::string value = entity.getValue();
   if (value.length() > 0) {
      out << "\"" << entity.getValue() << "\"";
   }
   const Entity * parent = entity.getParent();
   if (parent != nullptr) {
      if (parent->hasElementsAfter(&entity)) {
         out <<  "," << "\n";
      } else {
         out << "\n";
      }
   }
}
