//
//  XMLMarshaller.h
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __EntityManipulatorExample__XMLMarshaller__
#define __EntityManipulatorExample__XMLMarshaller__

#include <ostream>

#include "EntityManipulator.h"

// Forward declaration of a class that does not need to be
// #include'd here.
class Entity;

/**
 The XMLMarshaller class implements the EntityManipulator interface. Thus
 it is-a-kind-of EntityManipulator. It overrides the manipulate method, a pure
 virtual in EntityManipulator. 
 */
class XMLMarshaller : public EntityManipulator {
	
public:
	XMLMarshaller(std::ostream & outStream);
	void manipulate(Entity & entity, int level) override;
	
private:
	/** The output stream where the marshaller writes the entity objects as xml. */
	std::ostream & out;
};

#endif /* defined(__EntityManipulatorExample__XMLMarshaller__) */
