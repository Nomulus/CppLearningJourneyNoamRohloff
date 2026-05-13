//g++ -o Helloworld.exe HelloWorld.cpp
#include <iostream>

int main(){
    int width {5};//direct-list-initialization (preferred)
    int height {};//value initialization because it will be replaced soon
    [[maybe_unused]] int i {4};

    std::cout << "Hello World!\n";
    std::cout << width << " cm wide, now gimme hight in cm: ";
    std::cin >> height;
    std::cout << "\n" << "You get a " << width * height << "cm cube." << std::endl;
    
    return 0;
}
