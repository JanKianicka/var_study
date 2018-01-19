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

std::shared_ptr<MyStruct> get_my_struct(int p)
{
    return std::shared_ptr<MyStruct> {new MyStruct(p)};
}

int main()
{
    std::shared_ptr<MyStruct> u1{new MyStruct(1)};
    std::shared_ptr<MyStruct> u4;
    std::unique_ptr<MyStruct> u5{new MyStruct(3)};
    //    std::shared_ptr<MyStruct> u5{new MyStruct(3)};

    u4 = get_my_struct(2);
    std::shared_ptr<MyStruct> u2 = u1; //ok
    std::shared_ptr<MyStruct> u3 = std::move(u1);
    
    std::unique_ptr<MyStruct> u6{std::move(u5)};
    //    std::unique_ptr<MyStruct> u7 = u6; -- this is not allowed
    
    std::cout << "Data value for u3 is u3->vl = " << u3->vl <<std::endl;
    std::cout << "Reference count of u1 is "<< u1.use_count() << std::endl;
    std::cout << "Reference count of u2 is "<< u2.use_count() << std::endl;
    std::cout << "Reference count of u3 is "<< u3.use_count() << std::endl;
    std::cout << "Reference count of u4 is "<< u4.use_count() << std::endl;
    std::cout << "Data value for u4 is u4->vl = " << u4->vl <<std::endl;
    
    MyStruct *obj_u5 = nullptr;
    // obj_u5 = u5; -- this does not work
    //    u5 = new MyStruct(3);
    // It is possible to create smart pointer 
    // from normal pointer
    std::shared_ptr<MyStruct> u8{obj_u5};
}

