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
   
   /** Accepts a visitor to visit the Entity.
    @param manipulator The visitor.
    @param level The level in object hierarchy where the visitor currently is. */
   virtual void accept(EntityManipulator & manipulator, int level = 0) = 0;
   /** Adds an entity as a child to this entity.
    @param child The child to add. */
   virtual void add(Entity * child) = 0;
   /** Removes and deletes a child object from this entity, if it can be found.
    @param child The child to remove and delete.
    @return Returns true if the child was found and removed. */
   virtual bool remove(Entity * child) = 0;
   /** Finds a child entity with name and value and removes and deletes it if found.
    @param nameValue Name and value pair to look for.
    @return Returns true if the child object was found, removed and deleted. */
   virtual bool remove(const std::pair<std::string,std::string> & nameValue) = 0;
   /** Use to check how many child entities this entity has.
    @return The count of child objects. */
   virtual int childCount() const = 0;
   /** Passes the visitor to children of this Entity.
    @param manipulator The visitor to pass
    @param level The level in object hierarchy visitor currently visits. */
   virtual void passToChildren(EntityManipulator & manipulator, int level) = 0;
   /** Check if this Entity has child entities after the specified child Entity.
    @param childEntity The Entity to check
    @return Returns true if this entity has additional children after childEntity. */
   virtual bool hasElementsAfter(const Entity * childEntity) const = 0;
   
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
