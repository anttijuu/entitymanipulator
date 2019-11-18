//
//  GraphVizMarshaller.cpp
//  EntityManipulatorExe
//
//  Created by Antti Juustila on 15.11.2019.
//

#include "GraphVizMarshaller.h"
#include "EntityComposite.h"
#include "EntityLeaf.h"

/**
 The constructor for the GraphVizMarshaller. It stores the reference to output stream
 to a member variable. It is done in the initialization list -- all reference member
 variables must be initialized in the constructor's initialization list. As well as const
 members.
 @param outputStream The output stream where to print stuff.
 */
GraphVizMarshaller::GraphVizMarshaller(std::ostream & outputStream)
: out(outputStream) {
   out << "digraph EntityGraph {" << std::endl;
   out << " node [color=antiquewhite2,style=filled];" << std::endl;
}

/**
 The manipulate method is inherited from EntityManipulator and since it is pure virtual
 (abstract) method there, it has to be overridden here. Otherwise, this class would also
 be abstract and  you couldn't instantiate it.<p>
 Here, the GraphVizMarshaller just writes the propertes of the Entity into the output stream
 in GraphViz DOT format. If the Entity has children, then all those are also visited by this marshaller.
 @param entity The entity to manipulate.
 @param level In which level of object hierarchy we are currently.
 */
void GraphVizMarshaller::manipulate(EntityComposite & entity, int level) {
   Entity * parent = entity.getParent();
   std::string shape;
   if (nullptr != parent) {
      out << " \"" << parent->getValue() << "\" -> \"" << entity.getValue() << "\";" << std::endl;
      shape = "box";
   } else {
      shape = "Mdiamond";
   }
   out << " \"" << entity.getValue() << "\" [shape=\"" << shape << "\"";
   out << ",label=\"" << entity.getName() << ":" << entity.getValue() << "\"];" << std::endl;
   entity.passToChildren(*this, level++);
   if (!parent) {
      out << "}" << std::endl;
   }
}

/**
 The manipulate method is inherited from EntityManipulator and since it is pure virtual
 (abstract) method there, it has to be overridden here. Otherwise, this class would also
 be abstract and  you couldn't instantiate it.<p>
 Here, the GraphVizMarshaller just writes the propertes of the Entity into the output stream
 in GraphViz DOT format.
 @param entity The entity to manipulate.
 @param level In which level of object hierarchy the marshaller is currently.
 */
void GraphVizMarshaller::manipulate(EntityLeaf & entity, int level) {
   Entity * parent = entity.getParent();
   if (nullptr != parent) {
      out << " \"" << parent->getValue() << "\" -> \"" << entity.getValue() << "\"" << std::endl;
   }
   out << " \"" << entity.getValue() << "\" [label=\"" << entity.getName() << ":" << entity.getValue() << "\"];" << std::endl;
}


