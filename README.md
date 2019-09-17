# EntityManipulator demonstration project

This project is meant to demonstrate the relationships between UML class diagrams and C++ code.

See the included png file for the class diagram, and study the code to see how the class diagram and code relate to each other. Note that three design patterns have been implemented in the app -- [Composite](https://en.wikipedia.org/wiki/Composite_pattern), [Visitor](https://en.wikipedia.org/wiki/Visitor_pattern) and [Prototype](https://en.wikipedia.org/wiki/Prototype_pattern).

![UML class diagram](UML-class-diagram-of-EntityManipulator.png)

In the `main.cpp` an object structure is created. Then code demonstrates two ways (JSON & XML) to externalize the object structure into a stream using *marshallers*. The object structure looks like this:

```
             customers
          /              \
    customer             customer   ______
    FooBar Ltd__         Antti Juustila   \_
   /   |  \     \            /  |   \        \
id  type street billing    id   type  street  work
          addr   addr                  addr     addr
    
Where street, billing and work addresses have details (street name, post number etc).
```


## Building and running the app

If you wish, you can build the app and run it to see how it works.

What you need is a C++ compiler and [CMake](https://cmake.org) build system.

After installing the tools, do this in the project root directory:

1. mkdir build
2. cd build
3. cmake ..
4. make

After this, you should have a binary executable EntityManipulatorExe in the build directory.

You can then execute it and see the results:


```
OY1902105:build juustila$ ./EntityManipulatorExe 
Marshal objects to XML...

<?xml version="1.0" encoding="UTF-8"?>
<customers>
   <customer customer-identifier="FooBar Ltd">
      <id>9897765</id>
      <type>Company</type>
      <address address-identifier="Billing">
         <street>Technovillage Post Office</street>
         <postnumber>FI-90570</postnumber>
         <city>Oulu</city>
      </address>
      <address address-identifier="Street">
         <street>Technology Village Road 11</street>
         <entrance>B 21</entrance>
         <postnumber>FI-90570</postnumber>
         <city>Oulu</city>
      </address>
   </customer>
   <customer customer-identifier="Antti Juustila">
      <id>123456</id>
      <type>Person</type>
      <address address-identifier="Home">
         <street>Grand Vista Boulevard 125</street>
         <entrance>A1</entrance>
         <postnumber>JE3-10560</postnumber>
         <city>St Brelades</city>
      </address>
      <address address-identifier="Work">
         <street>Linnanmaa</street>
         <entrance>R</entrance>
         <postnumber>FI-90014</postnumber>
         <city>Oulun yliopisto</city>
      </address>
   </customer>
</customers>

Marshal objects to JSON...

{
"customers" : [
   {
   "customer" : [
      { "customer-name" : "FooBar Ltd"},
      { "id" : "9897765" },
      { "type" : "Company" },
      {
      "address" : [
         { "address-name" : "Billing"},
         { "street" : "Technovillage Post Office" },
         { "postnumber" : "FI-90570" },
         { "city" : "Oulu" }
      ]
      },
      {
      "address" : [
         { "address-name" : "Street"},
         { "street" : "Technology Village Road 11" },
         { "entrance" : "B 21" },
         { "postnumber" : "FI-90570" },
         { "city" : "Oulu" }
      ]
      }
   ]
   },
   {
   "customer" : [
      { "customer-name" : "Antti Juustila"},
      { "id" : "123456" },
      { "type" : "Person" },
      {
      "address" : [
         { "address-name" : "Home"},
         { "street" : "Grand Vista Boulevard 125" },
         { "entrance" : "A1" },
         { "postnumber" : "JE3-10560" },
         { "city" : "St Brelades" }
      ]
      },
      {
      "address" : [
         { "address-name" : "Work"},
         { "street" : "Linnanmaa" },
         { "entrance" : "R" },
         { "postnumber" : "FI-90014" },
         { "city" : "Oulun yliopisto" }
      ]
      }
   ]
   }
]
}
```

## Who made this

Original idea developed by Toni Raeisaenen (trai), redesigned and implemented by Antti Juustila

INTERACT Research Group, Study Program of Information Processing Science, University of Oulu, Finland
