#include <jni.h>
#include "jvm.h"

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved) {
  jint ret = InitGlobalJniVariables(jvm);
  if (ret < 0)
    return -1; 

  return ret;
}

extern "C" JNIEXPORT void JNICALL JNI_OnUnLoad(JavaVM* jvm, void* reserved) {
}

