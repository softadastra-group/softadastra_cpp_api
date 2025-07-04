#include <iostream>
#include <variant>
#include <string>

struct LoginEvent{
    std::string username;
};

struct LogoutEvent{
    std::string username;
};

struct ErrorEvent{
    int code;
    std::string message;
};

using Event = std::variant<LoginEvent, LogoutEvent, ErrorEvent>;

int main(){
    Event e1 = LoginEvent{"Gaspard"};
    Event e2 = ErrorEvent{404, "Not found"};

    auto handle_event = [](const auto& event){
        using T = std::decay_t<decltype(event)>;
        if constexpr (std::is_same_v<T, LoginEvent>){
            std::cout << "login: " << event.username << std::endl;
        }else if constexpr (std::is_same_v<T, LogoutEvent>){
            std::cout << "Logout: " << event.username << std::endl;
        }else if constexpr(std::is_same_v<T, ErrorEvent>){
            std::cout << "Error: " << event.code << ": " << event.message << std::endl;
        }
    };

    std::visit(handle_event, e1);
    std::visit(handle_event, e2);
    
    return 0;
}
