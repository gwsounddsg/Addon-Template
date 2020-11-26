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

// Add two values as integers. Can accept float/double but converted to int
NAN_METHOD(AddInts) {
    if (info.Length() != 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
        Nan::ThrowTypeError("Arguments are not Int32");
        return;
    }

    auto context = info.GetIsolate()->GetCurrentContext();

    int a = info[0]->IntegerValue(context).FromJust();
    int b = info[1]->IntegerValue(context).FromJust();

    auto result = Nan::New(a + b);
    info.GetReturnValue().Set(result);
}

NAN_METHOD(FlipBool) {
    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsBoolean()) {
        Nan::ThrowTypeError("Argument is not a bool");
        return;
    }

    auto isolate = info.GetIsolate();
    auto arg = info[0]->BooleanValue(isolate);

    auto result = Nan::New(!arg);
    info.GetReturnValue().Set(result);
}

NAN_MODULE_INIT(Init) {
    Nan::Set(target,
        Nan::New<String>("myPrint").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(MyPrint)).ToLocalChecked());

    Nan::Set(target,
        Nan::New<String>("addThree").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(AddThree)).ToLocalChecked());

    Nan::Set(target,
        Nan::New<String>("addInts").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(AddInts)).ToLocalChecked());
}

NODE_MODULE(my_cpp_addon, Init)
