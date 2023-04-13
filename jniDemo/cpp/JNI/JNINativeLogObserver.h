#ifndef __JNI_NATIVE_LOG_OBSERVER_H__
#define __JNI_NATIVE_LOG_OBSERVER_H__

#include <jni.h>
#include "INetProtocol.h"

namespace SDNP
{

class CJNINativeLogObserver : public ILogObserver
{
public:
    CJNINativeLogObserver();

    virtual ~CJNINativeLogObserver();

    virtual void onPrintLog(int level, std::string logMessage) override;

    void setJNIJavaObserver(jobject& observer);

    virtual void setLogLevel(int logLevel) override;

private:
    jobject m_jniJavaObserver;
};

}   // end namespace SDP

#endif