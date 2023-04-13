#include "JNIProjectionServerObserver.h"

#include "SDNPLogger.h"
#include "../jvm.h"
#include "JNI/JNICommon.h"

namespace SDNP
{
	CJNINativeProjectionServerObserver::CJNINativeProjectionServerObserver()
	{
		m_globalRef = nullptr;
		m_jniNativeObserver = nullptr;
	}

	CJNINativeProjectionServerObserver::~CJNINativeProjectionServerObserver()
	{
	}

	void CJNINativeProjectionServerObserver::setGlobalRef(JNICustomGlobalRef * globalRef)
	{
		m_globalRef = globalRef;
	}

	void CJNINativeProjectionServerObserver::setJNINativeObserver(jobject observer)
	{
		m_jniNativeObserver = observer;
	}

	void CJNINativeProjectionServerObserver::onClientStartProject(std::string uniqueIdentityCode, std::string name)
	{
		CHECK_NULL(m_jniNativeObserver, "Hasn't register the native observer.", );

		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniNativeObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		std::string paramsSign = fmtToStr("(%s%s)V", JNI_jstring_SIGN, JNI_jstring_SIGN);
		jmethodID methodID = jniEnv->GetMethodID(observerClass, "onClientStartProject", paramsSign.c_str());
		jniEnv->DeleteLocalRef(observerClass);


		jstring jstrUniqueIdentityCode = jniEnv->NewStringUTF(uniqueIdentityCode.c_str());
		jstring jstrName = jniEnv->NewStringUTF(name.c_str());

		jniEnv->CallVoidMethod(m_jniNativeObserver, methodID, jstrUniqueIdentityCode, jstrName);

		jniEnv->DeleteLocalRef(jstrUniqueIdentityCode);
		jniEnv->DeleteLocalRef(jstrName);
	}

	void CJNINativeProjectionServerObserver::onClientFinishProject(std::string uniqueIdentityCode, std::string name)
	{
		CHECK_NULL(m_jniNativeObserver, "Hasn't register the native observer.", );

		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniNativeObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		std::string paramsSign = fmtToStr("(%s%s)V", JNI_jstring_SIGN, JNI_jstring_SIGN);
		jmethodID methodID = jniEnv->GetMethodID(observerClass, "onClientFinishProject", paramsSign.c_str());
		jniEnv->DeleteLocalRef(observerClass);


		jstring jstrUniqueIdentityCode = jniEnv->NewStringUTF(uniqueIdentityCode.c_str());
		jstring jstrName = jniEnv->NewStringUTF(name.c_str());

		jniEnv->CallVoidMethod(m_jniNativeObserver, methodID, jstrUniqueIdentityCode, jstrName);

		jniEnv->DeleteLocalRef(jstrUniqueIdentityCode);
		jniEnv->DeleteLocalRef(jstrName);
	}

	void CJNINativeProjectionServerObserver::onSdpOffer(std::string uniqueIdentityCode, int msgId, std::string sdpOffer)
	{
		CHECK_NULL(m_jniNativeObserver, "Hasn't register the native observer.", );

		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniNativeObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		std::string paramsSign = fmtToStr("(%s%s%s)V", JNI_jstring_SIGN, JNI_jint_SIGN, JNI_jstring_SIGN);
		jmethodID methodID = jniEnv->GetMethodID(observerClass, "onSdpOffer", paramsSign.c_str());
		jniEnv->DeleteLocalRef(observerClass);

		jstring jstrUniqueIdentityCode = jniEnv->NewStringUTF(uniqueIdentityCode.c_str());
		jstring jstrSdpOffer = jniEnv->NewStringUTF(sdpOffer.c_str());

		jniEnv->CallVoidMethod(m_jniNativeObserver, methodID, jstrUniqueIdentityCode, msgId, jstrSdpOffer);

		jniEnv->DeleteLocalRef(jstrUniqueIdentityCode);
		jniEnv->DeleteLocalRef(jstrSdpOffer);
	}

	void CJNINativeProjectionServerObserver::onIceCandidate(std::string uniqueIdentityCode, std::string sdpMid, int sdpMLineIndex, std::string candidate)
	{
		CHECK_NULL(m_jniNativeObserver, "Hasn't register the native observer.", );

		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniNativeObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		std::string paramsSign = fmtToStr("(%s%s%s%s)V", JNI_jstring_SIGN, JNI_jstring_SIGN, JNI_jint_SIGN, JNI_jstring_SIGN);
		jmethodID methodID = jniEnv->GetMethodID(observerClass, "onIceCandidate", paramsSign.c_str());
		jniEnv->DeleteLocalRef(observerClass);

		jstring jstrUniqueIdentityCode = jniEnv->NewStringUTF(uniqueIdentityCode.c_str());
		jstring jstrSdpMid = jniEnv->NewStringUTF(sdpMid.c_str());
		jstring jstrCandidate = jniEnv->NewStringUTF(candidate.c_str());

		jniEnv->CallVoidMethod(m_jniNativeObserver, methodID, jstrUniqueIdentityCode, jstrSdpMid, sdpMLineIndex, jstrCandidate);

		jniEnv->DeleteLocalRef(jstrUniqueIdentityCode);
		jniEnv->DeleteLocalRef(jstrSdpMid);
		jniEnv->DeleteLocalRef(jstrCandidate);
	}
}