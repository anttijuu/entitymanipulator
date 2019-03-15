//
//  Entity.h
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 11.3.2019.
//  Copyright (c) 2019 Antti Juustila. All rights reserved.
//

#pragma once

#include <string>
#include <list>

// Forward declaration of a class that does not need to be
// #include'd here.
class EntityManipulator;

/**
 The Entity class just describes some entity with a name. The entity can
 also have a parent entity. It may be null (0; there's no parent for the entity).
 Entity can also have children, but since this implements the Composite design pattern,
 Entity being the base class, Entity does not hold the children. The EntityComposite does.
 Entities can also be cloned using the clone() method, which is an implementation of the
 Prototype design pattern. Finally, Entities accept Visitors (@see EntityManipulator), fulfilling
 the Visitor design pattern.
 @see https://en.wikipedia.org/wiki/Composite_pattern
 */
class Entity {
public:
   Entity(const std::string & n, const std::string & v);
   Entity(const Entity & another);
   virtual ~Entity();

   virtual Entity * clone() = 0;
   
   void attach(Entity * parent);
   void detach();
   Entity * getParent();
   const std::string & getName() const;
   const std::string & getValue() const;
   
   virtual void accept(EntityManipulator & manipulator, int level = 0) = 0;
   
   virtual void add(Entity * child) = 0;
   virtual bool remove(Entity * child) = 0;
   virtual bool remove(const std::pair<std::string,std::string> & nameValue) = 0;
   
   virtual int childCount() const = 0;
   virtual void passToChildren(EntityManipulator & manipulator, int level) = 0;
   virtual bool hasElementsAfter(const Entity * entity) const = 0;
   
private:
   Entity() = delete;
   /** The entity's name. */
   std::string name;
   /** Entity's value. */
   std::string value;
   /** The parent entity of this entity. May be null when there's no parent. */
   Entity * parent;
   
};

// EOF
