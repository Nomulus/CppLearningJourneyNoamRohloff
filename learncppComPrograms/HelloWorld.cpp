#include <iostream>

int main(){
    int width {5};//direct-list-initialization (preferred)
    int height {};//value initialization because it will be replaced soon

    std::cout << "Hello World!\n";
    std::cout << width << " cm, now gimme hight in cm: ";
    std::cin >> height;
    std::cout << "\n" << "You get a " << width * height << "cm cube.";
    
    return 0;
}
