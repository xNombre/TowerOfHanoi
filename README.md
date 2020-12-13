# Tower Of Hanoi

This is Tower Of Hanoi game implementation using dynamic arrays in pure C.
The number of pegs and disks can be dynamically set during runtime.

## Sample app
Library provides a sample app in which you can use manual or automatic mode.

#### Automatic mode
Automatic mode generates step-by-step solution for given parameters -
i.e. moves all disks from the 1st peg to the last.

It is an implementation of Frame-Steward algorithm which is said to
solve the game in the fewest moves.

#### Manual mode
Manual mode gives you an opportunity to move disks on your own and
print current progress out to the console.

#### Example usage
```
Element count: 3
Rods count: 3
Choose mode auto/manual: (a/m)
a
    ^      ^      ^   
   ===     |      |   
  =====    |      |   
 =======   |      |   
<=====================>

    ^      ^      ^   
    |      |      |   
  =====    |      |   
 =======   |     ===  
<=====================>

    ^      ^      ^   
    |      |      |   
    |      |      |   
 ======= =====   ===  
<=====================>

    ^      ^      ^   
    |      |      |   
    |     ===     |   
 ======= =====    |   
<=====================>

    ^      ^      ^   
    |      |      |   
    |     ===     |   
    |    ===== =======
<=====================>

    ^      ^      ^   
    |      |      |   
    |      |      |   
   ===   ===== =======
<=====================>

    ^      ^      ^   
    |      |      |   
    |      |    ===== 
   ===     |   =======
<=====================>

    ^      ^      ^   
    |      |     ===  
    |      |    ===== 
    |      |   =======
<=====================>

Completed with 7 moves!
```

## Features
You can't perform illegal moves - place larger disk on the smaller one.
All functions are coded with error-handling.

## Background
It was an exercise given to me by university teacher to show my
skills using advanced programming techniques (dynamic arrays)
but I decided to widen its features by implementing solving algorithm
and dynamically setting the number of elements and pegs. It came out to
be pretty complete project thus I decided to publish it.

## License

MIT

Copyright (c) 2020 Andrzej Perczak
