//
//  GraphVizMarshaller.cpp
//  EntityManipulatorExe
//
//  Created by Antti Juustila on 15.11.2019.
//

#include "GraphVizMarshaller.h"
#include "EntityComposite.h"
#include "EntityLeaf.h"

template<>
struct std::hash<Entity>
{
	std::size_t operator()(const Entity& entity) const noexcept
	{
		std::size_t h1 = std::hash<std::string>{}(entity.getName());
		std::size_t h2 = std::hash<std::string>{}(entity.getValue());
		std::size_t h3 = 0;
		const Entity * parent = entity.getParent();
		if (parent != nullptr) {
			h3 = std::hash<Entity>{}(*parent);
		}
		return h1 ^ (h2 << 1) ^ (h3 << 2);
	}
};

/**
 The constructor for the GraphVizMarshaller. It stores the reference to output stream
 to a member variable. It is done in the initialization list -- all reference member
 variables must be initialized in the constructor's initialization list. As well as const
 members.
 @param outputStream The output stream where to print stuff.
 */
GraphVizMarshaller::GraphVizMarshaller(std::ostream & outputStream)
: out(outputStream) {
   out << "digraph EntityGraph {" << "\n";
   out << " node [color=antiquewhite2,style=filled];" << "\n";
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
		out << "\"" << std::hash<Entity>{}(*parent) << "\" -> \"" << std::hash<Entity>{}(entity) << "\";\n";
      // out << " \"" << parent->getValue() << "\" -> \"" << entity.getValue() << "\";" << "\n";
      shape = "box";
   } else {
      shape = "Mdiamond";
   }
   out << " \"" << std::hash<Entity>{}(entity) << "\" [shape=\"" << shape << "\"";
   out << ",label=\"" << entity.getName() << ":" << entity.getValue() << "\"];" << "\n";
   entity.passToChildren(*this, level++);
   if (!parent) {
      out << "}" << "\n";
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
      out << " \"" << std::hash<Entity>{}(*parent) << "\" -> \"" << std::hash<Entity>{}(entity) << "\"" << "\n";
   }
	out << " \"" << std::hash<Entity>{}(entity) << "\" [label=\"" << entity.getName() << ":" << entity.getValue() << "\"];" << "\n";
}


