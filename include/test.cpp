#include <variant>
#include <string>
#include <iostream>

int main(){

    std::variant<int, float, std::string> data;

    data = 10;
    std::visit([](const auto& val){
        std::cout << "Int is : " << val << std::endl;
    }, data);

    data = 3.14f;
    std::visit([](const auto& val){
        std::cout << "float is : " << val << std::endl;
    }, data);

    data = "Hello world";
    std::visit([](const auto& val){
        std::cout << "std::string is : " << val << std::endl;
    }, data);

    
}
