//
// Created by Eden_ on 2024/9/6.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>

class object {
public:
    virtual ~object() = default;

    /**
     * change the data to (Json style?) string of the data structure
     * @return (Json style?) string of the data structure
     */
    [[nodiscard]] virtual std::string to_string() const = 0;

    /**
     * print (Json style?) string of the data structure
     */
    void print() const {
        std::cout << to_string() << std::endl;
    }
};

#endif //OBJECT_H
