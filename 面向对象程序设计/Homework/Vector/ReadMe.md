## ReadMe

> Author: Ziteng Wang
>
> Date: 2020-05-26

**SourceCode**

- Main.cpp
- Vector.cpp
- Vector.h

**Vector.exe**



##### Test Cases:

1. > Purpose: Beyond boundary (Invalid)
   >
   > Input: 10 10

   ```
   Test0: Vector of type test
   vt.push_back(): t0
   Size: 1
   class type
   
   Test1: v1.push_back(): 1~10
   Size: 10
   0 1 2 3 4 5 6 7 8 9
   
   Test2: copy ctor
   v2 <- v1
   Size: 10
   0 1 2 3 4 5 6 7 8 9
   
   Test3: operate[]
   Please Input an Integer:
   10
   -842150451
   
   Test4: v1.at()
   Please Input an Integer:
   10
   std::out_of_range
   ```

2. > Purpose: Negative index (Invalid)
   >
   > Input: -1 -1

   ```
   Test0: Vector of type test
   vt.push_back(): t0
   Size: 1
   class type
   
   Test1: v1.push_back(): 1~10
   Size: 10
   0 1 2 3 4 5 6 7 8 9
   
   Test2: copy ctor
   v2 <- v1
   Size: 10
   0 1 2 3 4 5 6 7 8 9
   
   Test3: operate[]
   Please Input an Integer:
   -1
   -33686019
   
   Test4: v1.at()
   Please Input an Integer:
   -1
   std::out_of_range
   ```

3. > Purpose: Within boundary (Valid)
   >
   > Input: 3 4

   ```
   Test0: Vector of type test
   vt.push_back(): t0
   Size: 1
   class type
   
   Test1: v1.push_back(): 1~10
   Size: 10
   0 1 2 3 4 5 6 7 8 9
   
   Test2: copy ctor
   v2 <- v1
   Size: 10
   0 1 2 3 4 5 6 7 8 9
   
   Test3: operate[]
   Please Input an Integer:
   3
   3
   
   Test4: v1.at()
   Please Input an Integer:
   4
   4
   
   Test5: v1.empty()
   False
   
   Test6: v1.clear()
   Size: 0
   
   Test7: v1.empty()
   True
   ```

   