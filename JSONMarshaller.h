//
//  JSONMarshaller.h
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 10.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#pragma once

#include <iostream>

#include "EntityManipulator.h"

class Entity;

/**
 The JSONMarshaller class implements the EntityManipulator interface. Thus
 it is-a-kind-of EntityManipulator. It overrides the manipulate method, a pure
 virtual in EntityManipulator.
 What is marshalling: https://en.wikipedia.org/wiki/Marshalling_(computer_science)
 */
class JSONMarshaller : public EntityManipulator {
public:
   JSONMarshaller(std::ostream & os);
   virtual void manipulate(EntityComposite & entity, int level);
   virtual void manipulate(EntityLeaf & entity, int level);

private:
   // Helper functions to avoid duplicate code.
   void doFirstPart(Entity & entity, int level, int baseWidth);
   void doLastPart(Entity & entity, int level, int baseWidth);
   
private:
   /** The output stream where the marshaller writes the entity objects as JSON. */
   std::ostream & out;
};

