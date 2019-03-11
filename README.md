# EntityManipulator demonstration project

This project is meant to demonstrate the relationships between UML class diagrams and C++ code.

See the included png file for the class diagram, and study the code to see how the class diagram and code relate to each other. Note that two design patterns have been implemented in the app -- [Composite](https://en.wikipedia.org/wiki/Composite_pattern) and [Visitor](https://en.wikipedia.org/wiki/Visitor_pattern).

![UML class diagram](UML-class-diagram-of-EntityManipulator.png)

In the `main.cpp` an object structure is created. Then code demonstrates two ways (JSON & XML) to externalize the object structure into a stream using *marshallers*. The object structure looks like this:

```
            root
         /       \
      numbers   letters
     /     \    /      \
    1      2   A        B
         /    / \
       21   A.p  A.q
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
Antti-iMac:build anttijuustila$ ./EntityManipulatorExe 
Marshal objects to XML...
<?xml version="1.0" encoding="UTF-8"?>
<entity name="root">The root object
   <entity name="numbers">All the numbers...
      <entity name="1">The only one</entity>
      <entity name="2">Second after one
         <entity name="21">Ventti</entity>
      </entity>
   </entity>
   <entity name="letters">a-b-c
      <entity name="B">beta</entity>
      <entity name="A">alpha
         <entity name="A.p">alpha pi</entity>
         <entity name="A.q">alpha queue</entity>
      </entity>
   </entity>
</entity>

Marshal objects to JSON...
{
  "name" : "root",
  "value" : "The root object",
  "children" : [
    {
    "name" : "numbers",
    "value" : "All the numbers...",
    "children" : [
      {
      "name" : "1",
      "value" : "The only one"
      },
      {
      "name" : "2",
      "value" : "Second after one",
      "children" : [
        {
        "name" : "21",
        "value" : "Ventti"
        }
      ]
      }
    ]
    },
    {
    "name" : "letters",
    "value" : "a-b-c",
    "children" : [
      {
      "name" : "B",
      "value" : "beta"
      },
      {
      "name" : "A",
      "value" : "alpha",
      "children" : [
        {
        "name" : "A.p",
        "value" : "alpha pi"
        },
        {
        "name" : "A.q",
        "value" : "alpha queue"
        }
      ]
      }
    ]
    }
  ]
}
```

## Who made this

Originally developed by Toni Raeisaenen (trai), modified by Antti Juustila (INTERACT Research Group)
Study Program of Information Processing Science, University of Oulu, Finland
