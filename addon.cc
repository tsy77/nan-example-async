#include <nan.h>
#include "async.h"

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("async").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Async)->GetFunction());
}

NODE_MODULE(addon, Init)