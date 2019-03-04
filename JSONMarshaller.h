//
//  JSONMarshaller.h
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 10.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __EntityManipulatorExample__JSONMarshaller__
#define __EntityManipulatorExample__JSONMarshaller__

#include <iostream>

#include "EntityManipulator.h"

/**
 The JSONMarshaller class implements the EntityManipulator interface. Thus
 it is-a-kind-of EntityManipulator. It overrides the manipulate method, a pure
 virtual in EntityManipulator.
 What is marshalling: https://en.wikipedia.org/wiki/Marshalling_(computer_science)
 */
class JSONMarshaller : public EntityManipulator {
public:
   JSONMarshaller(std::ostream & os);
   void manipulate(Entity & entity, int level) override;
   
private:
   /** The output stream where the marshaller writes the entity objects as JSON. */
   std::ostream & out;
};

#endif /* defined(__EntityManipulatorExample__JSONMarshaller__) */
