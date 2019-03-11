//
//  XMLMarshaller.h
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#pragma once

#include <ostream>

#include "EntityManipulator.h"

/**
 The XMLMarshaller class implements the EntityManipulator interface. Thus
 it is-a-kind-of EntityManipulator. It overrides the manipulate method, a pure
 virtual in EntityManipulator.
 What is marshalling: https://en.wikipedia.org/wiki/Marshalling_(computer_science)
 */
class XMLMarshaller : public EntityManipulator {
   
public:
   XMLMarshaller(std::ostream & outStream);
   virtual void manipulate(EntityComposite & entity, int level);
   virtual void manipulate(EntityLeaf & entity, int level);

private:
   /** The output stream where the marshaller writes the entity objects as xml. */
   std::ostream & out;
};

// EOF
