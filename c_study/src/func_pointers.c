#include <stdio.h>

void call_func_pointer(int (*v_funct)(int, int), int x, int y){
	v_funct(x,y);
}


int func (int a, int b)
{
    printf("\n a = %d\n",a);
    printf("\n b = %d\n",b);

    return 0;
}

int main(void)
{
    int(*fptr)(int,int); // Function pointer

    fptr = func; // Assign address to function pointer
    call_func_pointer(fptr, 2,3);

    //func(2,3);
    //fptr(2,3);

    return 0;
}
