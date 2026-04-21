# Set implementation in C++
## A. Intro
Welcome! This repository contains the implementation of an *integer* set data structure coded in C++.

**Chapters**:
* [1. Interactive Trial Program & Compilation](#1-interactive-trial-program--compilation)
* [2. Project Structure](#2-project-structure)
* [3. Implementation](#3-implementation)
  * [3.1 Time Complexity](#31-time-complexity)
  * [3.2 Space Complexity](#32-space-complexity)
  * [3.3 Hash-Table](#33-hash-table)
  * [3.4 Cache](#34-cache)
    * [3.4.S Sentinel Index](#34s-sentinel-index)
  * [3.5 Lazy Initialization](#35-lazy-initialization)
  * [3.6 Source Code](#36-source-code)
* [4. Library](#4-library)
  * [4.1 Functionality](#41-functionality)
  * [4.2 Library in C++](#42-library-in-c)
  * [4.3 Library in C](#43-library-in-c)
* [5. Testing](#5-testing)
* [6. Data Structures](#6-data-structures)
## 1. Interactive Trial Program & Compilation
This project comes with an interactive text-based program, which lets the user try out the basic set operations.
**The executable works only on Windows**. To run this program, simply type `bin/set` into your shell
(&nbsp;make sure your working directory is the parent folder `set/`&nbsp;). If any changes have been made in the source code
(&nbsp;or if you want to recompile the executable&nbsp;), you can run `script/make`. The batch file can additionally take
the following arguments: `script/make [-r|-t] [-t]`, where -r automatically runs the executable after compilation
and -t takes in the testing file. Script `make` compiles `main.cpp` by default, `testing.cpp` when -t is used.
I additionally offer `script/cmake`, which compiles the C program `main.c`.
More on C in **4.3&nbsp;Library&nbsp;in&nbsp;C**.
## 2. Project Structure
- `./bin/`: executable files (&nbsp;the only relevant program is mentioned in the previous chapter: `set.exe`&nbsp;)
- `./debug/`: nothing interesting, used for executables ready for debugging
- `./lib/`: header files ready for *in-code* use (&nbsp;`set.h` for C++ programs, `cset.h` for C programs&nbsp;)
- `./script/`: batch scripts used for compilation (&nbsp;`make.bat` & `cmake.bat`, both mentioned in the previous chapter&nbsp;)
- `./src/`: the actual codebase
## 3. Implementation
One of the basic structures used in a set are *Hash-Tables*. However, another structure (&nbsp;a.k.a *backend structure*&nbsp;)
must be implemented, since there might be cases where we try to insert a *key* into an already occupied *cell*.
The most simple structure that can be used in a *bucket*, is a *Linked-List*.
I wondered whether a *Binary-Search Tree* would have better results in performance.
### 3.1 Time Complexity
Via both the theoretical observation and testing, the *BST* implementation showed better results in time complexity.

To compare:
* **Hash-Table with Linked-List buckets**:
  * **Insertion**: Best case *O(1)*, Worst case *O(1)*
  * **Search & Deletion**: Best case *O(1)*, Worst case *O(n)*
* **Hash-Table with Self-Balancing Binary-Search Tree buckets**:
  * **Search & Insertion & Deletion**: Best case *O(1)*, Worst case *O(log n)*

For both *backend structures*, the average (&nbsp;and expected&nbsp;) time complexity is *O(1)*

### 3.2 Space Complexity
The disadvantage of using a *Red-Black Tree* is worse space complexity. Let's look at the current *node* structure I am using:
```
struct node  // Red-Black Tree
{
    int key;
    int color;
    node *left;
    node *right;
    node *parent;
};
```
To compare, this is the *node* structure used in a *Linked-List*:
```
struct lnode  // Linked-List
{
    int key;
    lnode* next;
};
```
It is obvious that *Linked-List* has better space complexity, due to having less *memory management*.
By *memory management* I mean how much of the allocated memory is used only for management (&nbsp;e.g. *next pointer*&nbsp;).
Let's make this more precise.
* **Red-Black Tree**:
  * first two attributes are *integer* values, the last three are *pointers*
  * since the size of *pointers* is 8 bytes, alignment may need padding
  * *integers* are 4 bytes each, so together they occupy 8 bytes, so there is no need for padding
  * the total size of a single *node* is 32 bytes
  * since only 4 bytes are relevant to data, only 12.5&nbsp;% is used for data
  * that means we are using 8x more memory (&nbsp;i.e., 800&nbsp;% of the raw data size&nbsp;)
  * 512 KiB of data would actually allocate 4 MiB
* **Linked-List**:
  * the first attribute is an *integer*, the second is a *pointer*
  * size of *pointers* is 8 bytes and the size of *integers* is 4 bytes
  * there is a need for padding, so we need to add 4 bytes after the first attribute
  * the total size of a single *node* is 16 bytes
  * since only 4 bytes are relevant to data, only 25&nbsp;% is used for data
  * that means we are using 4x more memory (&nbsp;i.e., 400&nbsp;% of the raw data size&nbsp;)
  * 512 KiB of data would actually allocate 2 MiB

We can see that *Linked-Lists* potentially use 2x less memory than *Red-Black Trees*.
For 5 GB of data, a *Linked-List* would ideally allocate ~20 GB and a *Red-Black Tree* would ideally allocate ~40 GB
(&nbsp;however, 5 GB is over a billion *integer* values&nbsp;-&nbsp;that is a very rare case&nbsp;).
Due to this, I offer the option to choose the *backend structure*, either *Linked-List* or *Red-Black Tree*.
### 3.3 Hash-Table
For the *Hash-Table*, I am using a simple *array* of a fixed size
(&nbsp;set in the *constant* BASE_SIZE&nbsp;-&nbsp;it is set to 256 *buckets* by default, but feel free to change it&nbsp;).
For *indexing*, I employ a simple *bit-mixing routine*.
### 3.4 Cache
In case a user frequently modifies the *set* (&nbsp;meaning they *insert* and *delete* a lot&nbsp;), it wouldn't make sense to work with
such a heavy backend. That is why I introduced a *cache*. It is analogous to a real *cache* in *processing units*.
It is implemented as a simple *Hash-Table*, with the same *hashing function* as the real *backend structure*.
The table size is of course smaller, it is by default set to one fourth of the *backend size*.
If you add a value into a *set*, the *parent class* will firstly check the *cache*.
If the cell is *occupied* and the *keys* are not identical, the original *key* will get replaced, and then *inserted* into the actual *backend structure*.
Because of safety, the *set* will also check whether the *key* is not already in the *backend structue*.
For *search* the *parent set* will do a lazy check firstly in *cache* and then in the *backend structure*. For *remove*, the *set* will need to go through
both structures (&nbsp;thus a *cache* will not improve *deletion*, for *insertion* it might skip insertion into the *backend structure*&nbsp;).
#### 3.4.S Sentinel Index
To validate whether a *cell* is occupied, I didn't want to use *heavy metadata*. I simply calculated the *index*, where the *key 0* would be located and set it as
the *sentinel index*. Now, for all other *cells* I can freely use *0* as the indicator for vacancy. Then a plain *bool* occupancy indicator is enough for the *sentinel index*.
### 3.5 Lazy Initialization
Instead of initializing all *buckets* at once at *set initialization*, I set them all to *null*. Only if the *parent node* tries to modify it
(&nbsp;in this case, only during insertion&nbsp;), the *buckets* will be initialized. Both *remove* & *contains* interpret a *null bucket* as empty.
### 3.6 Source Code
Each *data structure* is coded in individual files. File structure:
* **Set**:
  * `./lib/`: `set.h` for C++, `cset.h` for C
  * `./src/`: `set.cpp` for C++, `cset.cpp` for C
* **Hash-Table**:
  * `./src/`: `htable.cpp & htable.h`, `bucket.h` for the *bucket interface*
* **Linked-List**:
  * `./src/`: `llist.cpp & llist.h`
* **Red-Black Tree**:
  * `./src/`: `rbtree.cpp & rbtree.h`
* **Cache**:
  * `./src/`: `cache.cpp & cache.h`
## 4. Library
The *header* files are available for free use. They are located in the `./lib/` folder.
I assume you know the basic concepts of coding (&nbsp;especially C/C++&nbsp;).
### 4.1 Functionality
The following methods are available:
* **add** (&nbsp;returns *true* if no duplicate was added, *false* otherwise, but this is not reliable for *Linked-List*&nbsp;)
* **contains** (&nbsp;self-explanatory&nbsp;)
* **remove** (&nbsp;returns *false* if the *key* is not present, *true* otherwise&nbsp;)
* **len** (&nbsp;returns *set size* as an *unsigned* value&nbsp;)

The implementation also allows *iteration* (&nbsp;in a specific way&nbsp;).
It is **important** to note that the methods will not *iterate* in the order *keys* were added.
* **reset_iter** (&nbsp;a void function that moves the *"pointer"* to the beginning of the *"sequence"*&nbsp;)
* **get_next** (&nbsp;takes an *integer* output parameter and returns *false* if there is no next *key*, *true* otherwise&nbsp;)

In **get_next**, it is important to note that the output parameter is valid only if the method returned true
(&nbsp;if the method returned false, the output parameter will not change&nbsp;). A simple iteration of a set could look like this:
```
int val;
while ( set.get_next( &val ) )
    ...
```
If a set is empty or the *"sequence pointer"* is at the end, **get_next** will return *false*.

The last function (&nbsp;which is not a member of the Set Class&nbsp;) is:
* **print** (&nbsp;takes a *set*, and *iteratively* prints all *keys*&nbsp;)
### 4.2 Library in C++
This implementation was particularly coded for the C++ coding language. The relevant *header* file is `./lib/set.h`.
To use the *set*, simply use `#include "lib/set.h"` (&nbsp;be aware of your working directory&nbsp;).
The *object* you will be working with, is a *class Set*. A simple definition could be `Set *set = new Set()`.
Optionally, you can use *true* or *false* in the *constructor* to define whether you want to use the
*lite* version (&nbsp;*lite* = *Linked-List buckets*, otherwise *Red-Black Tree buckets*&nbsp;).
Make sure the `./src/` folder is included as well (&nbsp;at least relevant files&nbsp;).
### 4.3 Library in C
I also offer a C library, the relevant *header* file is `./lib/cset.h`. Again, simply use `#include "lib/cset.h"`.
The *object* you will be working with, is a *struct Set*. The constructor is `Set *set_init(bool lite)` and
the destructor is `void set_fini(Set *set)`. Instead of methods, you will be working with functions, in the following
form: `set_*`, e.g. `bool set_add(Set *set, int key)`. The functionality stays the same.
Make sure the `./src/` folder is included as well (&nbsp;at least relevant files&nbsp;).
## 5. Testing
For testing, I use the file `testing.cpp` in the folder `./src/`.
For compilation, see 1.&nbsp;Interactive&nbsp;Trial&nbsp;Program&nbsp;&&nbsp;Compilation.
Additionally, I use `main.c` for testing in the coding language C.
## 6. Data Structures
For additional information, see:
- Set: [Wikipedia](https://en.wikipedia.org/wiki/Set_(abstract_data_type))
- Hash-Table: [Wikipedia](https://en.wikipedia.org/wiki/Hash_table) | [GeeksForGeeks](https://www.geeksforgeeks.org/dsa/hash-table-data-structure/)
- Binary-Search Tree: [Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree) | [GeeksForGeeks](https://www.geeksforgeeks.org/dsa/binary-search-tree-data-structure/)
- Linked-List: [Wikipedia](https://en.wikipedia.org/wiki/Linked_list) | [GeeksForGeeks](https://www.geeksforgeeks.org/dsa/linked-list-data-structure/)
- Red-Black Tree: [Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) | [GeeksForGeeks](https://www.geeksforgeeks.org/dsa/introduction-to-red-black-tree/)
## C. Conclusion
To conclude I want to thank you for looking through this repository. Feel free to use my code.

PS: The codebase might have bugs, so don't rely on it (&nbsp;especially in critical situations&nbsp;).
