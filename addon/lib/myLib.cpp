#include <nan.h>
#include <string>
#include <iostream>

using namespace std;
using namespace v8;


// Basic no param method that prints
NAN_METHOD(MyPrint) {
    std::cout << "Hello there JavaScript" << std::endl;
}

// Receives a number adds 3 and returns
NAN_METHOD(AddThree) {
    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    Nan::Maybe<double> value = Nan::To<double>(info[0]);
    Local<Number> newValue = Nan::New(value.FromJust() + 3);
    info.GetReturnValue().Set(newValue);
}

NAN_MODULE_INIT(Init) {
    Nan::Set(target,
        Nan::New<String>("myPrint").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(MyPrint)).ToLocalChecked());

    Nan::Set(target,
        Nan::New<String>("addThree").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(AddThree)).ToLocalChecked());
}

NODE_MODULE(my_cpp_addon, Init)
