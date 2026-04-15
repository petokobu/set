# Set implementation in C++
## A. Intro
Welcome! I will briefly talk about my implementation of an **integer** set coded in C++.

## 1. Running set operations
This implementation of a set comes with an interactive user-friendly text-based program, which let's the user try out the basic set operations.
To run this program, simply type `bin/set` (make sure your working directory is the parent folder). The program then prints a message, from which it should be straightforward.
If any changes were made in the source code (or if you want to recompile the executable), you can run `script/make`.
The batch script can additionally run the program by including argument **-r** (thus `script/make -r`).

## 2. Source code
In the codebase, there are 2 (theoretically 4) important files, which realize the set ( *rbtree.[ cpp|h ]*, *set.[ cpp|h ]* ). See in **3.&nbsp;Implementation** why *rbrtree* is used.
All files have less than 400 lines of code. The *main.cpp* file is used only for the interactive program, thus it is not interesting. The main part of both files are definitions of *classes* (essentially *data structures*).
For the *rbtree* it is an implementation of a *Red-Black Tree* and for the *set* it is simply a *Set*. None of these files use a library other than *standard* (*std*&nbsp;&&nbsp;*iostream*).

## 3. Implementation
This set instance is realized using a simple *Hash-Table*, where each bucket is essentially a *Red-Black Tree*. Even though basic concepts of a *Hash-Table* use *Linked Lists* as their buckets,
I wondered, whether a *Binary-Search Tree* would have better results in performance.
- To compare:
    * **Hash-Table with Linked List buckets**:
        * **Insertion**: Always *O(1)*
        * **Search & Deletion**: Worst case scenario *O(n)*, Best case scenario *O(1)*
    * **Hash-Table with Self-Balancing Binary-Search Tree buckets**:
        * **Search & Insertion & Deletion**: Worst case scenario *O(log n)*, Best case scenario *O(1)*
- Average time complexity depends on the size of the *Hash-Table* (but for both cases it is usually *O(1)*)

However, one could argue that a tree implementation would have a worse space complexity, but the difference would be within 2 class members (the *color* and *parent* value).
For the *hash function*, I use a simple *bit mixing routine*.

## 4. Use
If you want to use my implementation of a set, I assume you know the basic concepts of coding (especially in C/C++). All you need is the header file, so `#include "set.h"` (again, be aware of your working directory).
The following default methods are available:
- **add** (returns *true* if it is not a duplicate, *false* otherwise)
- **contains** (self-explanotary)
- **remove** (returns *false* if the *key* is not present in the set, *true* otherwise)
- **len** (returns size in an *unsigned* value)

The implementation also allows iteration (in a specific way). It is **important** to note that the function will not iterate in the order keys were added.
- **reset_iter** (a void function that moves the *"pointer"* to the beginning of the *"sequence"*)
- **get_next** (takes an *integer output parameter* and returns *false* if there is no next *key*, *true* otherwise)

In **get_next**, it is important to note that the *output parameter* is valid only if the method returned *true* (if the method returned *false*, the *output parameter* will not change).
A simple iteration of a set could look like this:

```
int val;
while ( set.get_next( &val ) )
    ...
```

If a set is empty or the *sequence pointer* is at the end, **get_next** will return *false*.

The last function (which is not a member of the *Set Class*) is:
- **print** (takes a set, and iteratively prints all *keys*)

There is a constant in *set*, which defines the size of the *Hash-Table*. It is set to 256 *keys* by default, but if you want to change it, look for **BASE_SIZE** in *set.h*.

The *Red-Black Tree* is implemented in the file *rbtree*. Feel free to use it as well. All basic functions run worst case in *O(log n)*, some in *O(1)*.

They are:
- **add** (functionally analogical to *set*)
- **contains** (functionally analogical to *set*)
- **remove** (functionally analogical to *set*)
- **is_empty** (self-explanatory)
- **reset_iter & get_next** (functionally analogical to *set*)

## 5. Data Structures
For additional information, see:
- Set: [Wikipedia](https://en.wikipedia.org/wiki/Set_(abstract_data_type))
- Hash-Table: [Wikipedia](https://en.wikipedia.org/wiki/Hash_table) | [GeeksForGeeks](https://www.geeksforgeeks.org/dsa/hash-table-data-structure/)
- Binary-Search Tree: [Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree) | [GeeksForGeeks](https://www.geeksforgeeks.org/dsa/binary-search-tree-data-structure/)
- Red-Black Tree: [Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) | [GeeksForGeeks](https://www.geeksforgeeks.org/dsa/introduction-to-red-black-tree/)

## 6. Project Structure
- **bin**: folder containing exetucable file/s `set`
- **script**: folder containing batch script/s `make`
- **src**: codebase `main.cpp, set.[ cpp|h ], rbtree.[ cpp|h ]`

## C. Conclusion
To conclude I want to thank you for looking through this repository. Feel free to use my code.

PS: The codebase might have bugs, so don't rely on it (especially in critical situations).
