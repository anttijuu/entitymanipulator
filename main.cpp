//
//  main.cpp
//  EntityManipulatorExample
//
//  Created by Antti Juustila on 30.5.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <iostream>

#include "EntityComposite.h"
#include "EntityLeaf.h"
#include "XMLMarshaller.h"
#include "JSONMarshaller.h"

Entity * createEntities();

int main(int argc, const char * argv[])
{
   // Create a following structure of objects...
   /*
             customers
          /              \
    customer             customer   ______
    FooBar Ltd__         Antti Juustila   \_
   /   |  \     \            /  |   \        \
id  type street billing    id   type  street  work
          addr   addr                  addr     addr
    
Where street, billing and work addresses have details (street name, post number etc).
    */
   try {
      
      std::unique_ptr<Entity> customers(createEntities());
      
      // ...and give the marshaller to the root entity.
      std::cout << "Marshal objects to XML..." << std::endl << std::endl;
      // Create the marshaller..
      XMLMarshaller xmlMarshaller(std::cout);
      customers->accept(xmlMarshaller);
      
      std::cout << std::endl << "Marshal objects to JSON..." << std::endl << std::endl;
      JSONMarshaller jsonMarshaller(std::cout);
      customers->accept(jsonMarshaller);
      
      std::cout << "Cloning root entity and removing customer Antti Juustila from clone..." << std::endl << std::endl;
      std::unique_ptr<Entity> newComposite(customers->clone());
      newComposite->remove({"customer", "Antti Juustila"});
      std::cout << "Marshal objects to XML..." << std::endl << std::endl;
      newComposite->accept(xmlMarshaller);
      std::cout << std::endl << "Marshal objects to JSON..." << std::endl << std::endl;
      newComposite->accept(jsonMarshaller);
      
   } catch (std::exception & e) {
      std::cout << "ERROR: " << e.what() << std::endl;
   }
   
   return 0;
}

Entity * createEntities() {
   std::unique_ptr<EntityComposite> customers(new EntityComposite("customers", ""));
   // First customer.
   EntityComposite * customer = new EntityComposite("customer", "FooBar Ltd");
   customers->add(customer);
   customer->add(new EntityLeaf("id", "9897765"));
   customer->add(new EntityLeaf("type", "Company"));
   EntityComposite * address = new EntityComposite("address", "Billing");
   customer->add(address);
   address->add(new EntityLeaf("street", "Technovillage Post Office"));
   address->add(new EntityLeaf("postnumber", "FI-90570"));
   address->add(new EntityLeaf("city", "Oulu"));
   address = new EntityComposite("address", "Street");
   customer->add(address);
   address->add(new EntityLeaf("street", "Technology Village Road 11"));
   address->add(new EntityLeaf("entrance", "B 21"));
   address->add(new EntityLeaf("postnumber", "FI-90570"));
   address->add(new EntityLeaf("city", "Oulu"));
   // Second customer.
   customer = new EntityComposite("customer", "Antti Juustila");
   customers->add(customer);
   customer->add(new EntityLeaf("id", "123456"));
   customer->add(new EntityLeaf("type", "Person"));
   address = new EntityComposite("address", "Home");
   customer->add(address);
   address->add(new EntityLeaf("street", "Grand Vista Boulevard 125"));
   address->add(new EntityLeaf("entrance", "A1"));
   address->add(new EntityLeaf("postnumber", "JE3-10560"));
   address->add(new EntityLeaf("city", "St Brelades"));
   address = new EntityComposite("address", "Work");
   customer->add(address);
   address->add(new EntityLeaf("street", "Linnanmaa"));
   address->add(new EntityLeaf("entrance", "R"));
   address->add(new EntityLeaf("postnumber", "FI-90014"));
   address->add(new EntityLeaf("city", "Oulun yliopisto"));
   return customers.release();
}
