#include <iostream>
#include <memory>

struct MyStruct
{
    MyStruct(int i) : vl{i}
    {
        std::cout << "Creating MyStruct at memory address "<<(void *)this<<" with data "<<vl<<std::endl;
    }
    ~MyStruct()
    {
        std::cout << "Destroying MyStruct at memory address "<<(void *)this<<" with data "<<vl<<std::endl;
    }
    int vl=0;
    MyStruct() = delete;
};

std::unique_ptr<MyStruct> get_my_struct(int p)
{
    return std::unique_ptr<MyStruct> {new MyStruct(p)};
}

int main()
{
    std::unique_ptr<MyStruct> u1{new MyStruct(1)};
    std::unique_ptr<MyStruct> u4,u5;

    u4 = get_my_struct(2);
    
//    std::unique_ptr<MyStruct> u2 = u1; //won't compile
    std::unique_ptr<MyStruct> u3 = std::move(u1);
    std::cout << "Data value for u3 is u3->vl = " << u3->vl <<std::endl;
    u5 = std::move(u4);
    std::cout << "Data value for u5 is u5->vl = " << u5->vl <<std::endl;
}

