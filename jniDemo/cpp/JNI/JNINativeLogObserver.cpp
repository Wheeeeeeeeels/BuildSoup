#include "JNINativeLogObserver.h"
#include "jvm.h"

#include "SDNPLogger.h"

#define LOG_OBSERVER_CLASS_NAME "cn/geedow/netprotocol/JNILogObserver"

namespace SDNP
{

CJNINativeLogObserver::CJNINativeLogObserver()
{

}

CJNINativeLogObserver::~CJNINativeLogObserver() 
{   
    m_jniJavaObserver = nullptr;
}

void CJNINativeLogObserver::onPrintLog(int level, std::string logMessage)
{
    // infof("====== onPrintLog >>>");
    JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

    jclass logObserverClass = jniEnv->GetObjectClass(m_jniJavaObserver);
    if (logObserverClass == nullptr)
    {
        return;
    }
    jmethodID onPrintLogID = jniEnv->GetMethodID(logObserverClass, "onPrintLog", "(ILjava/lang/String;)V");
    jmethodID onPrintBinaryLogID = jniEnv->GetMethodID(logObserverClass, "onPrintBinaryLog", "(I[B)V");
    jniEnv->DeleteLocalRef(logObserverClass);

	// check input if it's not valid modified utf-t charater
	if (!CUtil::CheckUtfString(logMessage))
	{
		errorf("Detected invalid Modified UTF-8!!! Log message size[%zu]", logMessage.size());

        // "sd": ascii码为：115 100
        logMessage = "sd" + logMessage;
        jbyteArray jBALogMessage = jniEnv->NewByteArray(logMessage.size());
        jniEnv->SetByteArrayRegion(jBALogMessage, 0, logMessage.size(), (jbyte*)logMessage.c_str());
        jniEnv->CallVoidMethod(m_jniJavaObserver, onPrintBinaryLogID, level, jBALogMessage);
        jniEnv->DeleteLocalRef(jBALogMessage);

		logMessage = CUtil::stringToHex(logMessage);
	}

    jstring jstrLogMessage = jniEnv->NewStringUTF(logMessage.c_str());
    jniEnv->CallVoidMethod(m_jniJavaObserver, onPrintLogID, level, jstrLogMessage);
    jniEnv->DeleteLocalRef(jstrLogMessage);
}

void CJNINativeLogObserver::setJNIJavaObserver(jobject& observer)
{
    m_jniJavaObserver = observer;
}

void CJNINativeLogObserver::setLogLevel(int logLevel)
{
    ILogObserver::setLogLevel(logLevel);
    SDNP::setLogLevel((EnLogLevel)logLevel);
}

}   // end namespace SDP
