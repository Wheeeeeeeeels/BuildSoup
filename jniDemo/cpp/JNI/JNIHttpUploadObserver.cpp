#include "JNIHttpUploadObserver.h"
#include "jvm.h"

#include "SDNPLogger.h"
#include "JNICommon.h"

#define HTTP_UPLOAD_OBSERVER_NAME "cn/geedow/netprotocol/JNIHttpUploadObserver"

namespace SDNP
{
	CJNIHttpUploadObserver::CJNIHttpUploadObserver()
	{
	}

	CJNIHttpUploadObserver::~CJNIHttpUploadObserver()
	{
		debugf("~CJNIHttpUploadObserver() ");
	}

	void CJNIHttpUploadObserver::setJNIJavaObserver(jobject& observer)
	{
		m_jniJavaObserver = observer;
	}

	void CJNIHttpUploadObserver::onFailed(int requestCode, int errorCode, std::string extraInfo)
	{
		infof("====== onFailed >>>");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		if (m_jniJavaObserver != NULL)
		{
			jclass jniUploadFileClass = jniEnv->GetObjectClass(m_jniJavaObserver);
			if (!jniUploadFileClass) {
				errorf("GET OBJECT CLASS FAILED!!!");
				return;
			}

			jmethodID onFailedMethodID = jniEnv->GetMethodID(jniUploadFileClass, "onFailed", "(IILjava/lang/String;)V");

			jstring jstrExtraInfo = jniEnv->NewStringUTF(extraInfo.c_str());
			jniEnv->CallVoidMethod(m_jniJavaObserver, onFailedMethodID, requestCode, errorCode, jstrExtraInfo);

			jniEnv->DeleteLocalRef(jstrExtraInfo);
			jniEnv->DeleteLocalRef(jniUploadFileClass);
		}

		infof("====== onFailed <<<");
	}

	void CJNIHttpUploadObserver::onCompleted(int requestCode, std::string url)
	{
		infof("====== onCompleted >>>");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		if (m_jniJavaObserver != NULL)
		{
			jclass jniUploadFileClass = jniEnv->GetObjectClass(m_jniJavaObserver);
			if (!jniUploadFileClass)
			{
				errorf("GET OBJECT CLASS FAILED!!!");
				return;
			}

			jmethodID onCompletedMethodID = jniEnv->GetMethodID(jniUploadFileClass, "onCompleted", "(ILjava/lang/String;)V");
			jstring jstrUrl = jniEnv->NewStringUTF(url.c_str());
			jniEnv->CallVoidMethod(m_jniJavaObserver, onCompletedMethodID, requestCode, jstrUrl);
			jniEnv->DeleteLocalRef(jstrUrl);
			jniEnv->DeleteLocalRef(jniUploadFileClass);
		}

		infof("====== onCompleted <<<");
	}

}   // end namespace SDP
