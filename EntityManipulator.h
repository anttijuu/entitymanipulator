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
class EntityComposite;
class EntityLeaf;

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
   /** The pure virtual method for visiting Composite Entities defined in this interface class. Must be overridden by implementors.
        @param entity Entity to visit and manipulate.
        @param level The level of object hierarchy the manipulator is currently traversing.
    */
   virtual void manipulate(EntityComposite & entity, int level) = 0;

   /** The pure virtual method for visiting Leaf Entities (with no child objects) defined in this interface class. Must be overridden by implementors.
    @param entity Entity to visit and manipulate.
    @param level The level of object hierarchy the manipulator is currently traversing.
    */
   virtual void manipulate(EntityLeaf & entity, int level) = 0;
	
   /** Destructor for the manipulator. It is always a good habit of defining
    destructor as virtual for base and interface classes in C++. */
   virtual ~EntityManipulator() { /* empty */ }
};

// EOF
