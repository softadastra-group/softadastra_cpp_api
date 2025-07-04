#include <iostream>
#include <vector>
#include <any>

int main(){
    std::any a = 5;
    int x = std::any_cast<int>(a);
    std::cout << x << std::endl;

    std::any b = std::string("C++");
    std::string s = std::any_cast<std::string>(b);
    std::cout << s << std::endl;


    try{
        std::any a2 = 42;
        std::cout << a2.type().name() << std::endl;
        std::string s2 = std::any_cast<std::string>(a2);
    }catch(const std::bad_any_cast& e){
        std::cout << "Pas de converion de int(42) a string(42) avec std::any" << std::endl;
    }

    std::any a3;
    if(!a3.has_value()){
        std::cout << "No value stored" << std::endl;
    }
    return 0;
}
