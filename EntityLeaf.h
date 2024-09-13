//
//  Entity.h
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#pragma once

#include <string>
#include <list>

#include "Entity.h"

// Forward declaration of a class that does not need to be
// #include'd here.
class EntityManipulator;

/**
 The Entity Leaf class describes a concrete entity with a name but without child Entities.
 If you try to use the child Entity access methods, an exception is thrown.
 */
class EntityLeaf : public Entity {
public:
   EntityLeaf(const std::string & n, const std::string & v);
   EntityLeaf(const EntityLeaf & another);
   virtual ~EntityLeaf();
   
   virtual Entity * clone() override;
   
   virtual void accept(EntityManipulator & manipulator, int level = 0) override;
   void add(Entity * child) override;
   bool remove(Entity * child) override;
   virtual bool remove(const std::pair<std::string,std::string> & nameValue, bool removeParent = false) override;
   
   int childCount() const override;
   void passToChildren(EntityManipulator & manipulator, int level) override;
   bool hasElementsAfter(const Entity * entity) const override;
   
private:
   EntityLeaf() = delete;
};

// EOF
