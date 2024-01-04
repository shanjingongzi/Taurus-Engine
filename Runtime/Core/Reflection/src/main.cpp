#include <iostream>
#include "TClass.h"
#include <math.h>
using namespace std;


class Vec
{
public:
    void* p;
    float x;
    float y;
    Vec(float inX,float inY):x(inX),y(inY){
    }
    Vec(){
        x=1;
        y=1;
    }
    float Norm()
    {
        return 1;
        return sqrt(x * x + y * y);
    }
};


struct A { int a = 1; virtual int add() { return 0; } };

struct B : virtual A {
    int b = 2; int add() { return 2; }
};



int main()
{
    A* a = new B();
    auto ret = dynamic_cast<B*>(a);
    auto ret1 = ret->a;
    auto ret2 = ret->b;
    auto ret3 = ret->add();

    TClass imp;
    imp.RegisterType<Vec>();
    imp.AddConstructor<Vec,float,float>();
    imp.AddMethod<&Vec::Norm>({"Norm"});
    auto obj = imp.MakeShared(type_of<Vec>, TempArgsView{ 1.0f,2.0f });
    float a1;
    imp.Invoke(obj, { "Norm" }, (void*)(&a1), TempArgsView{1.0f,2.0f}, MethodFlag::Variable);
    Vec vec=obj.As<Vec>();
    imp.AddField<&Vec::y>({"y"});

  //  auto y = imp.Var(obj,{ "y" },FieldFlag::Basic);
  //  float zY = y.As<float>();
}
