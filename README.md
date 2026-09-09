# OBSIDIAN-VODKA

> A Zig-inspired memory allocator interface in C, exploring arena-based and other allocation strategies for safer and simpler memory management.

## Overview

**What is this project:** A personal project intended to implement  a safer zig-style library for safer memory management in C for my projects. Inspired by the NASA power 10 rules for critical systems. 

**Why it exists:** I used malloc once. I don't want to debug user-after-frees and keeping track of allocated pointers for the rest of my life.

**What problems it solves:** It aims to reduce the cognitive load required when manually handling memory, which in turn reduces the chances of writing memory leaks or commiting user-after-free's. 

It also incentivizes the avoidance of dynamic memory allocation after initialization and also makes the decisions behind lifetimes of each allocation, being explicit and deliberate based on the strategy chosen.

## Features

* Generic and dumb memory allocator
* Allocator strategies
* Data structures
* Error as value (yes it's verbose. And that is great)

## Usage
A quick example using the allocator + arena strategy
```c
Allocator allocator;
Error e = allocator_heap_init(4096, &allocator);
//Allocating exactly 4096 bytes
if(e != SUCCESS){/*explicitly handle the error*/}

Arena arena;
e = create_arena(&allocator, allocator.capacity, &arena);    
if(e != SUCCESS){/* explicity handle the error */}

uint8_t item[256]; //allocating a 256 bytes item to the arena 
void *item_ptr;
e = add_to_arena(&arena, sizeof(item), item, &item_ptr);
if(e != SUCCESS){/* explicity handle the error */}

//... 
//Suppose we dont need any of that anymore, then all we need to do is: 
e = allocator_heap_destroy(&allocator);
if(e != SUCCESS){/* explicity handle the error */}
//Kill the allocator and everything is gone
```

## Building

### Requirements

* C compiler
* Python 

### example Build

```text
python .\bin\test_arena_allocation.exe
```

## Project Structure

```text
project/
├── include/       # Public headers
├── src/           # Implementation
├── tests/         # Tests
├── examples/      # Examples
├── bin/           # Generated binaries
└── build/         # Build scripts in python
```

## Design

- The allocator is dumb. And that's a deliberate feature.
- The allocator is there just to provide a block of memory
- The allocator owns the memory and the allocator is the one
responsible for releasing the memory if necessary.

The ideia is that you would only ever call free(ptr) for allocators,
which reduces drastically the number of possible memory leaks by just as many allocators you have. 

It also means that you can reutilize the same allocator, just passing it to a different strategy and overwriting the memory there.

- The strategies decides how to subdivide the memory block provided by the allocator.

- The strategies also determine the type lifetime of the objects living in there will have. 

- Data Structures live in the regions provided by the strategy. 
- This forces a deliberate and explicit choice at initialization onto what sort of lifetime a datastructure is going to have, based on the strategy chosen for accomodating it.

- The datastructures are not dependant on this architecture. The structure shouldn't care where the memory it needs comes from. See the example for the stack data structure. 

It's pretty much a zero cost abstraction in terms of performance. Since it's dumb and simple. All it does is allocate a block of memory, subdivide a block of memory and provide it to whatever requires it. That is all it does and all it should do.

It could also potentially help with cache-locality since every allocator is a contiguous buffer.

## Status

>  In development

The allocator works. And the arena strategy is functional. Working on other strategies like memory pools, circular buffers, and etc. 

## License

This project is licensed under the MIT License.
