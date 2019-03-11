//
//  EntityManipulator.h
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#pragma once

// Forward declaration of a class that does not need to be
// #include'd here.
class Entity;

/**
 The interface class EntityManipulator defines what EntityManipulators do.
 They manipulate entities. There's no cpp file for this class, since the
 manipulate method is pure virtual and does not need an implementation.
 Interface classes usually just contain public pure virtual methods, no data.
 This class and the subclasses of it implement the Visitor design pattern together
 with the Entity class. Manipulators visits Entity object structures.
 @see https://en.wikipedia.org/wiki/Visitor_pattern
 */
class EntityManipulator {
public:
   /** The pure virtual method defined in this interface class. Must be overridden by implementors. */
   virtual void manipulate(Entity & entity, int level) = 0;
   // virtual void manipulate(EntityComposite & entity, int level) = 0;

   /** Destructor for the manipulator. It is always a good habit of defining a virtual
    destructor for base and interface classes in C++. */
   virtual ~EntityManipulator() { /* empty */ }
};

// EOF
