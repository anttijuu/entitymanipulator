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
#include "GraphVizMarshaller.h"

// Forward declaration of a function.
std::unique_ptr<Entity> createEntities();

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
      std::cout << "Marshal objects to XML..." << "\n\n";
      // Create the marshaller..
      XMLMarshaller xmlMarshaller(std::cout);
      customers->accept(xmlMarshaller);
      
      std::cout << "\n" << "Marshal objects to JSON..." << "\n\n";
      JSONMarshaller jsonMarshaller(std::cout);
      customers->accept(jsonMarshaller);

		std::cout << "\n" << "Marshal objects to GraphViz file in graph.gv..." << "\n\n";
      std::ofstream file("graph.gv");
      GraphVizMarshaller graphviz(file);
      customers->accept(graphviz);
      file.flush();
      file.close();

      std::cout << "Cloning root entity and removing customer Antti Juustila from clone..." << "\n\n";
      std::unique_ptr<Entity> newComposite(customers->clone());
      newComposite->remove({"name", "Antti Juustila"}, true);
      std::cout << "Marshal objects to XML..." << "\n\n";
      newComposite->accept(xmlMarshaller);
      std::cout << "\n" << "Marshal objects to JSON..." << "\n\n";
      newComposite->accept(jsonMarshaller);
      
      
   } catch (std::exception & e) {
      std::cout << "ERROR: " << e.what() << "\n";
   }
   
   return 0;
}

std::unique_ptr<Entity> createEntities() {
   std::unique_ptr<EntityComposite> customers(new EntityComposite("customers"));
	customers->setEntitiesAreRepeating(true);
   // First customer.
   Entity * customer = new EntityComposite("customer", "Key customer");
   customers->add(customer);
	customer->add(new EntityLeaf("name", "FooBar Ltd"));
   customer->add(new EntityLeaf("id", "9897765"));
   customer->add(new EntityLeaf("type", "Company"));
	EntityComposite * addresses = new EntityComposite("addresses");
	addresses->setEntitiesAreRepeating(true);
   Entity * address = new EntityComposite("address", "Billing");
   addresses->add(address);
   address->add(new EntityLeaf("street", "Technovillage Post Office"));
   address->add(new EntityLeaf("postnumber", "FI-90570"));
   address->add(new EntityLeaf("city", "Oulu"));
   address = new EntityComposite("address", "Street");
   addresses->add(address);
   address->add(new EntityLeaf("street", "Technology Village Road 11"));
   address->add(new EntityLeaf("entrance", "B 21"));
   address->add(new EntityLeaf("postnumber", "FI-90570"));
   address->add(new EntityLeaf("city", "Oulu"));
	customer->add(addresses);
   // Second customer.
   customer = new EntityComposite("customer", "VIP");
	customers->add(customer);
	customer->add(new EntityLeaf("name", "Antti Juustila"));
   customer->add(new EntityLeaf("id", "123456"));
   customer->add(new EntityLeaf("type", "Person"));
	addresses = new EntityComposite("addresses");
	addresses->setEntitiesAreRepeating(true);
   address = new EntityComposite("address", "Home");
   addresses->add(address);
   address->add(new EntityLeaf("street", "Grand Vista Boulevard 125"));
   address->add(new EntityLeaf("entrance", "A1"));
   address->add(new EntityLeaf("postnumber", "JE3-10560"));
   address->add(new EntityLeaf("city", "St Brelades"));
   address = new EntityComposite("address", "Work");
   addresses->add(address);
   address->add(new EntityLeaf("street", "Linnanmaa"));
   address->add(new EntityLeaf("entrance", "R"));
   address->add(new EntityLeaf("postnumber", "FI-90014"));
   address->add(new EntityLeaf("city", "Oulun yliopisto"));
	customer->add(addresses);
   return customers;
}
