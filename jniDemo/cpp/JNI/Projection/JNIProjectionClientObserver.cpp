#include "JNIProjectionClientObserver.h"

#include "../jvm.h"

#include "JNI/JNICommon.h"

#include "SDNPLogger.h"

namespace SDNP
{
	CJNINativeProjectionClientObserver::CJNINativeProjectionClientObserver()
	{
		m_globalRef = nullptr;
		m_jniNativeObserver = nullptr;
	}

	CJNINativeProjectionClientObserver::~CJNINativeProjectionClientObserver()
	{
	}

	void CJNINativeProjectionClientObserver::setGlobalRef(JNICustomGlobalRef * globalRef)
	{
		m_globalRef = globalRef;
	}

	void CJNINativeProjectionClientObserver::setJNINativeObserver(jobject observer)
	{
		m_jniNativeObserver = observer;
	}

	void CJNINativeProjectionClientObserver::onConnectionStatusChanged(EnProjectionConnectionStatus status, int errCode)
	{
		CHECK_NULL(m_jniNativeObserver, "Hasn't register the native observer.", );

		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniNativeObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		std::string paramsSign = fmtToStr("(%s%s)V", JNI_jint_SIGN, JNI_jint_SIGN);
		jmethodID methodID = jniEnv->GetMethodID(observerClass, "onConnectionStatusChanged", paramsSign.c_str());
		jniEnv->DeleteLocalRef(observerClass);

		jniEnv->CallVoidMethod(m_jniNativeObserver, methodID, static_cast<int>(status), errCode);
	}

	void CJNINativeProjectionClientObserver::onProjectionReplied(EnProjectionReply result, StProjectionInfo projectInfo)
	{
		CHECK_NULL(m_jniNativeObserver, "Hasn't register the native observer.", );

		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniNativeObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		std::string paramsSign = fmtToStr("(%s%s)V", JNI_jint_SIGN, PROJECTION_INFO_SIGN);
		jmethodID methodID = jniEnv->GetMethodID(observerClass, "onProjectionReplied", paramsSign.c_str());
		jniEnv->DeleteLocalRef(observerClass);

		jclass jniProjectionInfoClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(PROJECTION_INFO_NAME));
		jmethodID constructorID = jniEnv->GetMethodID(jniProjectionInfoClass, "<init>", "()V");
		jobject joProjectionInfo = jniEnv->NewObject(jniProjectionInfoClass, constructorID);
		jniEnv->DeleteLocalRef(jniProjectionInfoClass);

		JNICommon::setFieldValue(jniEnv, projectInfo, joProjectionInfo);

		jniEnv->CallVoidMethod(m_jniNativeObserver, methodID, static_cast<int>(result), joProjectionInfo);

		jniEnv->DeleteLocalRef(joProjectionInfo);
	}

	void CJNINativeProjectionClientObserver::onIceCandidate(std::string sdpMid, std::string sdpMLineIndex, std::string candidate)
	{
		CHECK_NULL(m_jniNativeObserver, "Hasn't register the native observer.", );

		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniNativeObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		std::string paramsSign = fmtToStr("(%s%s%s)V", JNI_jstring_SIGN, JNI_jstring_SIGN, JNI_jstring_SIGN);
		jmethodID methodID = jniEnv->GetMethodID(observerClass, "onIceCandidate", paramsSign.c_str());
		jniEnv->DeleteLocalRef(observerClass);

		jstring jstrSdpMid = jniEnv->NewStringUTF(sdpMid.c_str());
		jstring jstrSdpMLineIndex = jniEnv->NewStringUTF(sdpMLineIndex.c_str());
		jstring jstrCandidate = jniEnv->NewStringUTF(candidate.c_str());

		jniEnv->CallVoidMethod(m_jniNativeObserver, methodID, jstrSdpMid, jstrSdpMLineIndex, jstrCandidate);

		jniEnv->DeleteLocalRef(jstrSdpMid);
		jniEnv->DeleteLocalRef(jstrSdpMLineIndex);
		jniEnv->DeleteLocalRef(jstrCandidate);
	}

}
