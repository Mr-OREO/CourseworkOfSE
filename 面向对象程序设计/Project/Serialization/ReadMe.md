## ReadMe

> Team Member: 王子腾，许可越
>
> Date: 2020/07/05

#### Current Function

1. Implement a module to support **binary** serialization/deserialization
2. Implement a wrapper module of [tinyxml2](https://github.com/leethomason/tinyxml2) to support **XML** serialization
3. Every module has its namespace
4. Both modules should at least support the serialization of arithmetic types (see [std::is_arithmetic](https://en.cppreference.com/w/cpp/types/is_arithmetic)), C++ string type (`std::string`), and STL containers (`std::pair`, `std::vector`, `std::list`, `std::set`, and `std::map`)
5. Both modules should provide a convenient mechanism to support the serialization of user-defined types
6. During testing, you should cover all the required types and options
7. **[Bonus]** Use binary-to-text encoding/decoding ([base64](https://en.wikipedia.org/wiki/Base64)) to implement a binary mode of XML serialization
8. **[Bonus]** Support the serialization of smart pointers, e.g., `std::unique_ptr`

#### Distribution

王子腾：`Binary` serialization/deserialization

许可越：`XML` serialization/deserialization