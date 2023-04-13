#include "JNIProjectionClient.h"
#include "JNIProjectionClientObserver.h"

#include <memory>

#include "../JNICommon.h"
#include "../JNICustomGlobalRef.h"

#include "IProjection.h"
#include "SDNPLogger.h"

using namespace SDNP;

static std::unique_ptr<CJNINativeProjectionClientObserver> g_pProjectionClientObserverPtr = nullptr;
static jobject g_jniNativeProjectionClientObserver = nullptr;

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_init(
	JNIEnv *env, jclass thisClass)
{
	if (g_pProjectionClientObserverPtr.get() == nullptr)
	{
		g_pProjectionClientObserverPtr.reset(new CJNINativeProjectionClientObserver());
	}

	// 在全局引用管理类中注册JNIProjectionInfo
	JNICustomGlobalRef::instance()->setGlobalRef(PROJECTION_INFO_NAME);

	// 注册全局引用管理类指针到CJNINativeProjectionClientObserver
	g_pProjectionClientObserverPtr->setGlobalRef(JNICustomGlobalRef::instance());

	return 0;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_setIpv4Address(
	JNIEnv *env, jclass thisClass, jstring jstrIpv4Address)
{
	IProjectionClient::instance()->setIpv4Address(
		JNICommon::getJStringValue(env, jstrIpv4Address));

	return 0;
}	

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_registerObserver(
	JNIEnv *env, jclass thisClass, jobject joObserver)
{
	CHECK_NULL(g_pProjectionClientObserverPtr.get(), "", -1);

	// JNI的观察者注册到c++
	IProjectionClient::instance()->registerObserver(g_pProjectionClientObserverPtr.get());

	// Java的观察者注册到JNI
	g_jniNativeProjectionClientObserver = env->NewGlobalRef(joObserver);
	g_pProjectionClientObserverPtr->setJNINativeObserver(g_jniNativeProjectionClientObserver);

	return 0;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_startProject(
	JNIEnv *env, jclass thisClass, jstring jstrProjectionCode, jstring jstrName)
{
	return IProjectionClient::instance()->startProject(
		JNICommon::getJStringValue(env, jstrProjectionCode),
		JNICommon::getJStringValue(env, jstrName));
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_finishProject(
	JNIEnv *env, jclass thisClass)
{
	return IProjectionClient::instance()->finishProject();
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_sendSdpOffer(
	JNIEnv *env, jclass thisClass, jstring jstrSdpOffer, jobject joSdpAnswer)
{
	std::string cppSdpAnswer;
	int code = IProjectionClient::instance()->sendSdpOffer(
		JNICommon::getJStringValue(env, jstrSdpOffer),
		cppSdpAnswer);
	if (code != CODE_SUCCESS)
	{
		errorf("Negotiate failed.");
		return code;
	}

	JNICommon::setCommonTypeValue(env, cppSdpAnswer, joSdpAnswer);

	return code;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_sendIceCandidate(
	JNIEnv *env, jclass thisClass, jstring jstrSdpMid, jstring jstrSdpMLineIndex, jstring jstrCandidate)
{
	return IProjectionClient::instance()->sendIceCandidate(
		JNICommon::getJStringValue(env, jstrSdpMid),
		JNICommon::getJStringValue(env, jstrSdpMLineIndex),
		JNICommon::getJStringValue(env, jstrCandidate));
}
