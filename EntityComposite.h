//
//  EntityComposite.h
//  EntityCompositeManipulatorExample
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
 The EntityComposite class just describes some EntityComposite with a name. The EntityComposite can
 also have a parent EntityComposite. It may be null (0; there's no parent for the EntityComposite).
 EntityComposite can also have children.
 */
class EntityComposite : public Entity {
public:
   EntityComposite(const std::string & n, const std::string & v);
   EntityComposite(const EntityComposite & another);
   virtual ~EntityComposite();
   
   virtual void accept(EntityManipulator & manipulator, int level = 0) override;
   virtual void add(Entity * child) override;
   virtual bool remove(Entity * child) override;
   virtual bool remove(const std::string & withName) override;
   
   virtual bool hasChildren() const override;
   virtual void passToChildren(EntityManipulator & manipulator, int level) override;
   virtual bool hasElementsAfter(const Entity * entity) const override;
   
private:
   EntityComposite() = delete;
   
   typedef std::list<Entity*> EntityCollection;
   
   EntityCollection children;
   
};

// EOF
