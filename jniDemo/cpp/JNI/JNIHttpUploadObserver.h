#ifndef __JNI_HTTP_UPLOAD_OBSERVER_H__
#define __JNI_HTTP_UPLOAD_OBSERVER_H__

#include <jni.h>
#include "INetProtocol.h"
#include "JNICustomGlobalRef.h"

#include <map>
#include <mutex>

namespace SDNP
{

class CJNIHttpUploadObserver : public IHttpUploadObserver
{
public:
    CJNIHttpUploadObserver();

    virtual ~CJNIHttpUploadObserver();

    void setJNIJavaObserver(jobject& observer);

public: // override parent class's methods
	virtual void onFailed(int requestCode, int errorCode, std::string extraInfo) override;

	virtual void onCompleted(int requestCode, std::string url) override;

public:
	void setGlobalRef(JNICustomGlobalRef* globalRef);

private:
	jobject m_jniJavaObserver;
	JNICustomGlobalRef* m_globalRef;
};

}   // end namespace SDP

#endif