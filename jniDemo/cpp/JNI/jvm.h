#ifndef __SDP_JNI_JVM_H__
#define __SDP_JNI_JVM_H__

#include <jni.h>

jint InitGlobalJniVariables(JavaVM* jvm);

// Return a |JNIEnv*| usable on this thread or NULL if this thread is detached.
JNIEnv* GetEnv();

JavaVM* GetJVM();

// Return a |JNIEnv*| usable on this thread.  Attaches to |g_jvm| if necessary.
JNIEnv* AttachCurrentThreadIfNeeded();


#endif  // __SDP_JNI_JVM_H__
