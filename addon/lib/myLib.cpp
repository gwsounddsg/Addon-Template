#include <nan.h>
#include <string>
#include <iostream>

using namespace std;
using namespace Nan;
using namespace v8;


NAN_METHOD(MyPrint) {
    std::cout << "Hello there JavaScript" << std::endl;
}

NAN_MODULE_INIT(Init) {
    Nan::Set(target,
        New<String>("myPrint").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(MyPrint)).ToLocalChecked());
}

NODE_MODULE(my_cpp_addon, Init)
