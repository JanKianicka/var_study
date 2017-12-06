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
    std::shared_ptr<MyStruct> s1{new MyStruct(1)};
    std::weak_ptr<MyStruct> w1(s1);
    std::cout << "Weak ptr w1 has use count "<<w1.use_count() << std::endl;
    std::cout << "Shared ptr s1 has use count "<<s1.use_count() << std::endl;

    std::weak_ptr<MyStruct> w2 = get_my_struct(2); // No good.
    std::cout << "Weak ptr 2 has use count "<<w2.use_count() << std::endl;
    // The above does not work because the weak pointer does not own the
    // resource. So, it is deleted along with the temporary shared ptr
    // which owned the resource.

    // Indirect access to data from weak ptr
    std::shared_ptr<MyStruct> u3 = w1.lock();
    std::cout << "Data cooresponding to weak ptr-1 is "<<u3->vl<<std::endl;
    std::shared_ptr<MyStruct> s3(s1);
    std::cout << "Shared ptr s1 has use count "<<s1.use_count() << std::endl;
}

