#include <nan.h>
#include <string>
#include <iostream>

#include "stdLib.h"

using namespace std;
using namespace v8;

enum Colors { Red, Green, Blue };

v8::Local<v8::Context> getContext(Nan::NAN_METHOD_ARGS_TYPE info) {
    return info.GetIsolate()->GetCurrentContext();
}


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

// Take a bool, flip it, and return
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

// accepts an int for an enum, returns its int value
NAN_METHOD(EnumValue) {
    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        Nan::ThrowTypeError("Argument is not a bool");
        return;
    }

    auto context = info.GetIsolate()->GetCurrentContext();
    int value = info[0]->IntegerValue(context).FromJust();

    info.GetReturnValue().Set(value);
}

// returns a color from an enum as an int
NAN_METHOD(CurrentColor) {
    auto currentColor = Colors::Blue;
    info.GetReturnValue().Set(currentColor);
}

NAN_METHOD(PrintMessage) {
    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsString()) {
        Nan::ThrowTypeError("Argument is not a string");
        return;
    }

    // auto context = getContext(info);
    // auto localStr(info[0]->ToString(context));

    // std::cout << localStr << std::endl;

    v8::String::Utf8Value val(info[0]->ToString());

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

    Nan::Set(target,
        Nan::New<String>("flipBool").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(FlipBool)).ToLocalChecked());

    Nan::Set(target,
        Nan::New<String>("enumValue").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(EnumValue)).ToLocalChecked());

    Nan::Set(target,
        Nan::New<String>("currentColor").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(CurrentColor)).ToLocalChecked());
}

NODE_MODULE(my_cpp_addon, Init)
