//
//  GraphVizMarshaller.hpp
//  EntityManipulatorExe
//
//  Created by Antti Juustila on 15.11.2019.
//

#pragma once

#include <string_view>
#include <fstream>
#include <unordered_map>

#include "Entity.h"
#include "EntityManipulator.h"

/**
 This visitor exports the Entity object structure into a GraphViz input file.
 A graphic representation of the object structure can then be created using the visitor.
 @see https://www.graphviz.org for DOT file notation and tools to generate graphics.
 */
class GraphVizMarshaller : public EntityManipulator {
public:
   
   GraphVizMarshaller(std::ostream & outputStream);
   
   virtual void manipulate(EntityComposite & entity, int level) override;
   virtual void manipulate(EntityLeaf & entity, int level) override;
   
private:
   
   /** The output stream where to this object is streamed. */
   std::ostream & out;

	std::unordered_map<std::size_t, std::shared_ptr<Entity>> entityIDs;
};
