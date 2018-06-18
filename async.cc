#include <nan.h>
#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "async.h"

using namespace v8;

uv_loop_t* loop;

const char* ToCString(const String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

void Work(uv_work_t *req) {
  fprintf(stderr, "Work: %s\n", req->data);
}

void WorkComplete(uv_work_t *req, int status) {
  fprintf(stderr, "WorkComplete: %s\n", req->data);
}

void Async(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  loop = uv_default_loop();

  uv_work_t req;

  String::Utf8Value str(info[0]);
  const char* data = ToCString(str);

  req.data = (void*) data;

  uv_queue_work(loop, &req, Work, WorkComplete);
  uv_run(loop, UV_RUN_DEFAULT);
}