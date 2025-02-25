# Andesite VM Opcodes
- [Andesite VM Opcodes](#andesite-vm-opcodes)
  - [General](#general)
  - [References](#references)
  - [Constant Pools](#constant-pools)
  - [Local Variables](#local-variables)
  - [Compare](#compare)
    - [Numbers](#numbers)
    - [Other](#other)
  - [Checking](#checking)
  - [Stack](#stack)
  - [String](#string)
  - [Array](#array)
  - [Control](#control)
  - [Arithmetic](#arithmetic)
  - [Conversion](#conversion)
  - [Conversion (Unsigned)](#conversion-unsigned)
  - [Negation](#negation)
  - [Bitwise](#bitwise)
  - [Object Creation](#object-creation)
  - [Exception Handling](#exception-handling)
  - [Function Definition](#function-definition)
  - [Synchronization](#synchronization)

## General
1. `skip` do nothing
2. `halt` stop execution 
3. `dump` dump memory and stack trace to stdout
4. `print` print stack top value to stdout
5. `exit` stop execution and exit
6. `args` get arguments with string[]
7. `newthread` (constant pool index: i16) create and start a new thread with the specified function
8. `rnewthread` create and start a new thread with the specified function from stack top
9. `gload` (index: i32) get value from global and push to stack
10. `gstore` (index: i32) set specified global to stack value

## References
1. `null` load null to stack
2. `getfield` (constant pool index: i16) get specified instance field and push to stack
3. `setfield` (constant pool index: i16) set specified instance field to stack value
4. `getstatic` (constant pool index: i16) get specified static class field and push to stack
5. `setstatic` (constant pool index: i16) set specified class static field to stack value
6. `invoke`  (constant pool index: i16) invoke function from constant pool
7. `invokevirtual` (constant pool index: i16) invoke classmethod from constant pool
8. `invokereference` (constant pool index: i16) invoke method/function reference from constant pool
9. `invokestatic` (constant pool index: i16) invoke a static method from constant pool
10. `invokeinterface` (constant pool index: i16) invoke an interface method from an object reference on stack
11.  `cast` (constant pool index: i16) check object and cast to specified object 
12.  `ret` return to caller and push returned value to stack 

## Constant Pools
1. `cload_0~3` load constant pool and push to stack
2. `cload` (index: i32) load constant pool and push to stack

## Local Variables
1. `rload_0~3` load reference from local variable (indices 0-3) to stack
2. `rload` (index: i32) load reference from local variable to stack
3. `rstore_0~3` store stack top reference to local variable (indices 0-3)
4. `rstore` (index: i32) store stack top reference to local variable
5. `i8load` (index: i32) load 8-bit integer from local variable to stack
6. `i8store` (index: i32) store stack top 8-bit integer to local variable
7. `i16load` (index: i32) load 16-bit integer from local variable to stack
8. `i16store` (index: i32) store stack top 16-bit integer to local variable
9. `i32load` (index: i32) load 32-bit integer from local variable to stack
10. `i32store` (index: i32) store stack top 32-bit integer to local variable
11. `i64load` (index: i32) load 64-bit integer from local variable to stack
12. `i64store` (index: i32) store stack top 64-bit integer to local variable
13. `u8load` (index: i32) load 8-bit unsigned integer from local variable to stack
14. `u8store` (index: i32) store stack top 8-bit unsigned integer to local variable
15. `u16load` (index: i32) load 16-bit unsigned integer from local variable to stack
16. `u16store` (index: i32) store stack top 16-bit unsigned integer to local variable
17. `u32load` (index: i32) load 32-bit unsigned integer from local variable to stack
18. `u32store` (index: i32) store stack top 32-bit unsigned integer to local variable
19. `u64load` (index: i32) load 64-bit unsigned integer from local variable to stack
20. `u64store` (index: i32) store stack top 64-bit unsigned integer to local variable
21. `f32load` (index: i32) load 32-bit float from local variable to stack
22. `f32store` (index: i32) store stack top 32-bit float to local variable
23. `f64load` (index: i32) load 64-bit double from local variable to stack
24. `f64store` (index: i32) store stack top 64-bit double to local variable
25. `bload` (index: i32) load boolean from local variable to stack
26. `bstore` (index: i32) store stack top boolean to local variable
27. `c16load` (index: i32) load 16-bit character from local variable to stack
28. `c16store` (index: i32) store stack top 16-bit character to local variable
29. `incl` (index: i32, value: i32) increment local variable by 32-bit value
30. `decr` (index: i32, value: i32) decrement local variable by 32-bit value

## Compare

a == b => 0
a < b => -1
a > b => 1

### Numbers 
1. `cmpi8` compare 8-bit integers
2. `cmpi16` compare 16-bit integers
3. `cmpi32` compare 32-bit integers
4. `cmpi64` compare 64-bit integers
5. `cmpu8` compare 8-bit unsigned integers
6. `cmpu16` compare 16-bit unsigned integers
7. `cmpu32` compare 32-bit unsigned integers
8. `cmpu64` compare 64-bit unsigned integers
9. `cmpf32` compare 32-bit floats
10. `cmpf64` compare 64-bit doubles

### Other
1. `cmpstr` compare string
    - a == b => 0
    - a != b => 1
2. `cmpstrd` compare string in dictionary
    - "a" == "a" => 0
    - "a" < "b" => -1
    - "b" > "a" => 1
3. `cmpstrl` compare string length
    - "abc" == "def" => 0
    - "ab" < "cdef" => -1
    - "abcd" > "ef" => 1
4. `cmpref` compare object reference
    - a(0x0001) == b(0x0001) => 0
    - a(0x0001) == b(0x0002) => 1
5. `cmparr` compare array
    - [1, 2, 3] == [1, 2, 3] => 0
    - [1, 2, 3] == [4, 5, 6] => 1
6. `cmparrl` compare array length
    - [1, 2, 3] == [4, 5, 6] => 0
    - [1, 2] < [3, 4, 5, 6] => -1
    - [1, 2, 3, 4] > [5, 6] => 1
7. `cmpbool` compare boolean
    - a == b => 0
    - a != b => 1

## Checking
1. `isnan` check is nan
    - a == NaN => 0
    - a != NaN => 1
2. `isobj` check is specified object instance
    - a(Integer) == Integer => 0
    - a(Integer) == String => 1
3. `isnull` check is null
    - a == null => 0
    - a != null => 1

## Stack
1. `dup` duplicate stack top
2. `swap` swap stack top
3. `pop` remove stack top

## String
1. `strlen` get string length
2. `strsub` (start: i32, length: i32)
3. `strconcat` concatenate string (a + b)

## Array
1. `arrnew` (size: i32) create new array and push to stack
2. `arrnewmulti` (dimensions: i32, size: i32) create new multidimensional array and push to stack
3. `arrnewa` (size: i32) create new reference array and push to stack
4. `arrnewamulti` (dimensions: i32, size: i32) create new multidimensional reference array and push to stack
5. `arrlen` get array length
6. `arrget` (index: array size(default: i32)) get array value from specified index
7. `arrset` (index: array size(default: i32)) set array value to specified index

## Control
1. `jmp` (address: i32) jump to specified address
2. `jmpeq` (address: i32) if stack top is 0, jump to specified address
3. `jmpneq` (address: i32) if stack top is not 0, jump to specified address
4. `jmplt` (address: i32) if stack top is -1, jump to specified address
5. `jmpgt` (address: i32) if stack top is 1, jump to specified address
6. `jmplte` (address: i32) if stack top is -1 or 0, jump to specified address
7. `jmpgte` (address: i32) if stack top is 1 or 0, jump to specified address
8. `jmpo` (offset: i32) jump to offset applied address
9. `jmpoeq` (address: i32) if stack top is 0, jump to offset applied address
10. `jmponeq` (address: i32) if stack top is not 0, jump to offset applied address
11. `jmpolt` (address: i32) if stack top is -1, jump to offset applied address
12. `jmpogt` (address: i32) if stack top is 1, jump to offset applied address
13. `jmpolte` (address: i32) if stack top is -1 or 0, jump to offset applied address
14. `jmpogte` (address: i32) if stack top is 1 or 0, jump to offset applied address
15. `ifnull` (address: i32) if stack top is null, jump to specified address
16. `ifnotnull` (address: i32) if stack top is not null, jump to specified address
17. `tswitch` (low: i32, high: i32, default: i32, addresses: i32[]) switch on continuous range
18. `lswitch` (default: i32, npairs: i32, pairs: [i32, i32][]) switch on sparse keys

## Arithmetic
1. `addi8` add two 8-bit integers from stack and push result
2. `subi8` subtract two 8-bit integers (second from top) and push result
3. `muli8` multiply two 8-bit integers from stack and push result
4. `divi8` divide two 8-bit integers (second by top) and push result
5. `modi8` modulo of two 8-bit integers (second by top) and push result
6. `addi16` add two 16-bit integers from stack and push result
7. `subi16` subtract two 16-bit integers (second from top) and push result
8. `muli16` multiply two 16-bit integers from stack and push result
9. `divi16` divide two 16-bit integers (second by top) and push result
10. `modi16` modulo of two 16-bit integers (second by top) and push result
11. `addi32` add two 32-bit integers from stack and push result
12. `subi32` subtract two 32-bit integers (second from top) and push result
13. `muli32` multiply two 32-bit integers from stack and push result
14. `divi32` divide two 32-bit integers (second by top) and push result
15. `modi32` modulo of two 32-bit integers (second by top) and push result
16. `addi64` add two 64-bit integers from stack and push result
17. `subi64` subtract two 64-bit integers (second from top) and push result
18. `muli64` multiply two 64-bit integers from stack and push result
19. `divi64` divide two 64-bit integers (second by top) and push result
20. `modi64` modulo of two 64-bit integers (second by top) and push result
21. `addu8` add two 8-bit unsigned integers from stack and push result
22. `subu8` subtract two 8-bit unsigned integers (second from top) and push result
23. `mulu8` multiply two 8-bit unsigned integers from stack and push result
24. `divu8` divide two 8-bit unsigned integers (second by top) and push result
25. `modu8` modulo of two 8-bit unsigned integers (second by top) and push result
26. `addu16` add two 16-bit unsigned integers from stack and push result
27. `subu16` subtract two 16-bit unsigned integers (second from top) and push result
28. `mulu16` multiply two 16-bit unsigned integers from stack and push result
29. `divu16` divide two 16-bit unsigned integers (second by top) and push result
30. `modu16` modulo of two 16-bit unsigned integers (second by top) and push result
31. `addu32` add two 32-bit unsigned integers from stack and push result
32. `subu32` subtract two 32-bit unsigned integers (second from top) and push result
33. `mulu32` multiply two 32-bit unsigned integers from stack and push result
34. `divu32` divide two 32-bit unsigned integers (second by top) and push result
35. `modu32` modulo of two 32-bit unsigned integers (second by top) and push result
36. `addu64` add two 64-bit unsigned integers from stack and push result
37. `subu64` subtract two 64-bit unsigned integers (second from top) and push result
38. `mulu64` multiply two 64-bit unsigned integers from stack and push result
39. `divu64` divide two 64-bit unsigned integers (second by top) and push result
40. `modu64` modulo of two 64-bit unsigned integers (second by top) and push result
41. `addf32` add two 32-bit floats from stack and push result
42. `subf32` subtract two 32-bit floats (second from top) and push result
43. `mulf32` multiply two 32-bit floats from stack and push result
44. `divf32` divide two 32-bit floats (second by top) and push result
45. `modf32` modulo of two 32-bit floats (second by top) and push result
46. `addf64` add two 64-bit doubles from stack and push result
47. `subf64` subtract two 64-bit doubles (second from top) and push result
48. `mulf64` multiply two 64-bit doubles from stack and push result
49. `divf64` divide two 64-bit doubles (second by top) and push result
50. `modf64` modulo of two 64-bit doubles (second by top) and push result

## Conversion
1. `i8toi16` 8-bit integer to 16-bit integer
2. `i8toi32` 8-bit integer to 32-bit integer
3. `i8toi64` 8-bit integer to 64-bit integer
4. `i8tof32` 8-bit integer to 32-bit float
5. `i8tof64` 8-bit integer to 64-bit double
6. `i16toi8` 16-bit integer to 8-bit integer
7. `i16toi32` 16-bit integer to 32-bit integer
8. `i16toi64` 16-bit integer to 64-bit integer
9. `i16tof32` 16-bit integer to 32-bit float
10. `i16tof64` 16-bit integer to 64-bit double
11. `i32toi8` 32-bit integer to 8-bit integer
12. `i32toi16` 32-bit integer to 16-bit integer
13. `i32toi64` 32-bit integer to 64-bit integer
14. `i32tof32` 32-bit integer to 32-bit float
15. `i32tof64` 32-bit integer to 64-bit double
16. `i64toi8` 64-bit integer to 8-bit integer
17. `i64toi16` 64-bit integer to 16-bit integer
18. `i64toi32` 64-bit integer to 32-bit integer
19. `i64tof32` 64-bit integer to 32-bit float
20. `i64tof64` 64-bit integer to 64-bit double
21. `f32toi8` 32-bit float to 8-bit integer
22. `f32toi16` 32-bit float to 16-bit integer
23. `f32toi32` 32-bit float to 32-bit integer
24. `f32toi64` 32-bit float to 64-bit integer
25. `f32tof64` 32-bit float to 64-bit double
26. `f64toi8` 64-bit double to 8-bit integer
27. `f64toi16` 64-bit double to 16-bit integer
28. `f64toi32` 64-bit double to 32-bit integer
29. `f64toi64` 64-bit double to 64-bit integer
30. `f64tof32` 64-bit double to 32-bit float
31. `i32toc16` 32-bit integer to 16-bit character
32. `c16toi32` 16-bit character to 32-bit integer

## Conversion (Unsigned)
1. `u8toi8` 8-bit unsigned integer to 8-bit integer
2. `u8toi16` 8-bit unsigned integer to 16-bit integer
3. `u8toi32` 8-bit unsigned integer to 32-bit integer
4. `u8toi64` 8-bit unsigned integer to 64-bit integer
5. `u8tof32` 8-bit unsigned integer to 32-bit float
6. `u8tof64` 8-bit unsigned integer to 64-bit double
7. `u16toi8` 16-bit unsigned integer to 8-bit integer
8. `u16toi16` 16-bit unsigned integer to 16-bit integer
9. `u16toi32` 16-bit unsigned integer to 32-bit integer
10. `u16toi64` 16-bit unsigned integer to 64-bit integer
11. `u16tof32` 16-bit unsigned integer to 32-bit float
12. `u16tof64` 16-bit unsigned integer to 64-bit double
13. `u32toi8` 32-bit unsigned integer to 8-bit integer
14. `u32toi16` 32-bit unsigned integer to 16-bit integer
15. `u32toi32` 32-bit unsigned integer to 32-bit integer
16. `u32toi64` 32-bit unsigned integer to 64-bit integer
17. `u32tof32` 32-bit unsigned integer to 32-bit float
18. `u32tof64` 32-bit unsigned integer to 64-bit double
19. `u64toi8` 64-bit unsigned integer to 8-bit integer
20. `u64toi16` 64-bit unsigned integer to 16-bit integer
21. `u64toi32` 64-bit unsigned integer to 32-bit integer
22. `u64toi64` 64-bit unsigned integer to 64-bit integer
23. `u64tof32` 64-bit unsigned integer to 32-bit float
24. `u64tof64` 64-bit unsigned integer to 64-bit double

## Negation
1. `negi8` negate 8-bit integer
2. `negi16` negate 16-bit integer
3. `negi32` negate 32-bit integer
4. `negi64` negate 64-bit integer
5. `negu8` negate 8-bit unsigned integer
6. `negu16` negate 16-bit unsigned integer
7. `negu32` negate 32-bit unsigned integer
8. `negu64` negate 64-bit unsigned integer
9. `negf32` negate 32-bit float
10. `negf64` negate 64-bit double

## Bitwise
1. `andi8` and two 8-bit integers from stack and push result
2. `andi16` and two 16-bit integers from stack and push result
3. `andi32` and two 32-bit integers from stack and push result
4. `andi64` and two 64-bit integers from stack and push result
5. `andu8` and two 8-bit unsigned integers from stack and push result
6. `andu16` and two 16-bit unsigned integers from stack and push result
7. `andu32` and two 32-bit unsigned integers from stack and push result
8. `andu64` and two 64-bit unsigned integers from stack and push result
9. `ori8` or two 8-bit integers from stack and push result
10. `ori16` or two 16-bit integers from stack and push result
11. `ori32` or two 32-bit integers from stack and push result
12. `ori64` or two 64-bit integers from stack and push result
13. `oru8` or two 8-bit unsigned integers from stack and push result
14. `oru16` or two 16-bit unsigned integers from stack and push result
15. `oru32` or two 32-bit unsigned integers from stack and push result
16. `oru64` or two 64-bit unsigned integers from stack and push result
17. `xori8` xor two 8-bit integers from stack and push result
18. `xori16` xor two 16-bit integers from stack and push result
19. `xori32` xor two 32-bit integers from stack and push result
20. `xori64` xor two 64-bit integers from stack and push result
21. `xoru8` xor two 8-bit unsigned integers from stack and push result
22. `xoru16` xor two 16-bit unsigned integers from stack and push result
23. `xoru32` xor two 32-bit unsigned integers from stack and push result
24. `xoru64` xor two 64-bit unsigned integers from stack and push result
25. `noti8` not 8-bit integer from stack top and push result
26. `noti16` not 16-bit integer from stack top and push result
27. `noti32` not 32-bit integer from stack top and push result
28. `noti64` not 64-bit integer from stack top and push result
29. `notu8` not 8-bit unsigned integer from stack top and push result
30. `notu16` not 16-bit unsigned integer from stack top and push result
31. `notu32` not 32-bit unsigned integer from stack top and push result
32. `notu64` not 64-bit unsigned integer from stack top and push result
33. `shli8` shift left 8-bit integer from stack and push result
34. `shli16` shift left 16-bit integer from stack and push result
35. `shli32` shift left 32-bit integer from stack and push result
36. `shli64` shift left 64-bit integer from stack and push result
37. `shri8` shift right 8-bit integer (signed) from stack and push result
38. `shri16` shift right 16-bit integer (signed) from stack and push result
39. `shri32` shift right 32-bit integer (signed) from stack and push result
40. `shri64` shift right 64-bit integer (signed) from stack and push result
41. `shru8` shift right 8-bit unsigned integer from stack and push result
42. `shru16` shift right 16-bit unsigned integer from stack and push result
43. `shru32` shift right 32-bit unsigned integer from stack and push result
44. `shru64` shift right 64-bit unsigned integer from stack and push result

## Object Creation
1. `new` (constant pool index: i16) create a new object instance of the specified class and push to stack

## Exception Handling
1. `throw` throw an exception from the stack top
2. `catch` (constant pool index: i16, address: i32) catch an exception of the specified type and jump to the specified address

## Function Definition
1. `defun` (address: i32, nargs: i32) define a new function starting at the specified address with the given number of arguments, push the function object to stack
2. `closure` (address: i32, nargs: i32) define a new function with captured local variables, push the closure object to stack

## Synchronization
1. `lock` lock the object on stack top
2. `unlock` unlock the object on stack top