# Set implementation in C++
## A. Intro
Welcome! This repository contains the implementation of an *integer* set data structure coded in C++.
## 1. Interactive Trial Program & Compilation
This project comes with an interactive text-based program, which lets the user try out the basic set operations.
**The executable works only on Windows**. To run this program, simply type `bin/set` into your shell
( make sure your working directory is the parent folder `set/` ). If any changes have been made in the source code
( or if you want to recompile the executable ), you can run `script/make`. The batch file can additionally take
the following arguments: `script/make [-r|-t] [-t]`, where -r automatically runs the executable after compilation
and -t takes in the testing file. Script `make` compiles `main.cpp` by default, `testing.cpp` when -t is used.
I additionally offer `script/cmake`, which compiles the C program `main.c`.
More on C in **4.3&nbsp;Library&nbsp;in&nbsp;C**.
## 2. Project Structure
- `./bin/`: executable files ( the only relevant program is mentioned in the previous chapter: `set.exe` )
- `./debug/`: nothing interesting, used for executables ready for debugging
- `./lib/`: header files ready for *in-code* use ( `set.h` for C++ programs, `cset.h` for C programs )
- `./script/`: batch scripts used for compilation ( `make.bat` & `cmake.bat`, both mentioned in the previous chapter )
- `./src/`: the actual codebase
## 3. Implementation
One of the basic structures used in a set are *Hash-Tables*. However, another structure ( a.k.a *backend structure* )
must be implemented, since there might be cases, when we try to insert a *key* into an already occupied *cell*.
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

For both *backend structures*, the average ( and expected ) time complexity is *O(1)*

### 3.2 Space Complexity
The disadvantage of using a *Red-Black Tree* is worse space complexity. Lets look at the current *node* structure I am using:
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
By *memory management* I mean how much of the allocated memory is used only for management ( e.g. *next pointer* ).
Let's make this more precise.
* **Red-Black Tree**:
  * first two attributes are *integer* values, the last three are *pointers*
  * since the size of *pointers* is 8 bytes, alignment may need padding
  * *integers* are 4 bytes each, so together they occupy 8 bytes, so there is no need for padding
  * the total size of a single *node* is 32 bytes
  * since only 4 bytes are relevant to data, only 12.5 % is used for data
  * that means we are using 8x more memory ( i.e., 800% of the raw data size )
  * 512 KiB of data would actually allocate 4 MiB
* **Linked-List**:
  * the first attribute is an *integer*, the second is a *pointer*
  * size of *pointers* is 8 bytes and the size of *integers* is 4 bytes
  * there is a need for padding, so we need to add 4 bytes after the first attribute
  * the total size of a single *node* is 16 bytes
  * since only 4 bytes are relevant to data, only 25 % is used for data
  * that means we are using 4x more memory ( i.e., 400% of the raw data size )
  * 512 KiB of data would actually allocate 2 MiB

We can see that *Linked-Lists* potentially use 2x less memory than *Red-Black Trees*.
For 5 GB of data, a *Linked-List* would ideally allocate ~20 GB and a *Red-Black Tree* would ideally allocate ~40 GB
( however, 5 GB is over a billion *integer* values&nbsp;-&nbsp;that is a very rare case ).
Due to this, I offer the option to choose the *backend structure*, either *Linked-List* or *Red-Black Tree*.
### 3.3 Source Code
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
### 3.4 Hash-Table
For the *Hash-Table*, I am using a simple *array* of a fixed size
( set in the *constant* BASE_SIZE&nbsp;-&nbsp;it is set to 256 *buckets* by default, but feel free to change it ).
For *indexing*, I am using a simple *bit-mixing routine*.
## 4. Library
The *header* files are available for free use. They are located in the `./lib/` folder.
I assume you know the basic concepts of coding ( especially C/C++ ).
### 4.1 Functionality
The following methods are available:
* **add** ( returns *true* if no duplicate was added, *false* otherwise )
* **contains** ( self-explanatory )
* **remove** ( returns *false* if the *key* is not present, *true* otherwise )
* **len** ( returns *set size* as an *unsigned* value )

The implementation also allows *iteration* ( in a specific way ).
It is **important** to note that the methods will not *iterate* in the order *keys* were added.
* **reset_iter** ( a void function that moves the *"pointer"* to the beginning of the *"sequence"* )
* **get_next** ( takes an *integer* output parameter and returns *false* if there is no next *key*, *true* otherwise )

In **get_next**, it is important to note that the output parameter is valid only if the method returned true
( if the method returned false, the output parameter will not change ). A simple iteration of a set could look like this:
```
int val;
while ( set.get_next( &val ) )
    ...
```
If a set is empty or the *"sequence pointer"* is at the end, **get_next** will return *false*.

The last function ( which is not a member of the Set Class ) is:
* **print** ( takes a *set*, and *iteratively* prints all *keys* )
### 4.2 Library in C++
This implementation was particularly coded for the C++ coding language. The relevant *header* file is `./lib/set.h`.
To use the *set*, simply use `#include "lib/set.h"` ( be aware of your working directory ).
The *object* you will be working with, is a *class Set*. A simple definition could be `Set *set = new Set()`.
Optionally, you can use *true* or *false* in the *constructor* to define whether you want to use the
*lite* version ( *lite* = *Linked-List buckets*, otherwise *Red-Black Tree buckets* ).
Make sure the `./src/` folder is included as well ( at least relevant files ).
### 4.3 Library in C
I also offer a C library, the relevant *header* file is `./lib/cset.h`. Again, simply use `#include "lib/cset.h"`.
The *object* you will be working with, is a *struct Set*. The constructor is `Set *set_init(bool lite)` and
the destructor is `void set_fini(Set *set)`. Instead of methods, you will be working with functions, in the following
form: `set_*`, e.g. `bool set_add(Set *set, int key)`. The functionality stays the same,
Make sure the `./src/` folder is included as well ( at least relevant files ).
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

PS: The codebase might have bugs, so don't rely on it (especially in critical situations).
