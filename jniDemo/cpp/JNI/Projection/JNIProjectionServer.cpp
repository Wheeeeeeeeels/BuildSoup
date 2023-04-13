#include "JNIProjectionServer.h"
#include "JNIProjectionServerObserver.h"

#include <memory>

#include "../JNICommon.h"
#include "../JNICustomGlobalRef.h"

#include "IProjection.h"
#include "SDNPLogger.h"

using namespace SDNP;

static std::unique_ptr<CJNINativeProjectionServerObserver> g_pProjectionServerObserverPtr = nullptr;
static jobject g_jniNativeProjectionServerObserver = nullptr;

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_init(
	JNIEnv *env, jclass thisClass)
{
	if (g_pProjectionServerObserverPtr.get() == nullptr)
	{
		g_pProjectionServerObserverPtr.reset(new CJNINativeProjectionServerObserver());
	}
	return 0;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_test(
	JNIEnv *env, jclass thisClass)
{
	IProjectionServer::instance()->test();
	return 0;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_registerObserver(
	JNIEnv *env, jclass thisClass, jobject joObserver)
{
	CHECK_NULL(g_pProjectionServerObserverPtr.get(), "", -1);

	// JNI的观察者注册到c++
	IProjectionServer::instance()->registerObserver(g_pProjectionServerObserverPtr.get());

	// Java的观察者注册到JNI
	g_jniNativeProjectionServerObserver = env->NewGlobalRef(joObserver);
	g_pProjectionServerObserverPtr->setJNINativeObserver(g_jniNativeProjectionServerObserver);

	return 0;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_setIpv4Address(
	JNIEnv *env, jclass thisClass, jstring jstrIpv4Address)
{
	return IProjectionServer::instance()->setIpv4Address(JNICommon::getJStringValue(env, jstrIpv4Address));
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_startProjectionService(
	JNIEnv *env, jclass thisClass)
{
	return IProjectionServer::instance()->startProjectionService();
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_stopProjectionService(
	JNIEnv *env, jclass thisClass)
{
	return IProjectionServer::instance()->stopProjectionService();
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_sendSdpAnswer(
	JNIEnv *env, jclass thisClass, jstring jstrUniqueIdentityCode, jint jintMsgId, jstring jstrSdpAnswer)
{
	std::string uniqueIdentityCode = JNICommon::getJStringValue(env, jstrUniqueIdentityCode);
	std::string sdpAnswer = JNICommon::getJStringValue(env, jstrSdpAnswer);

	return IProjectionServer::instance()->sendSdpAnswer(uniqueIdentityCode, jintMsgId, sdpAnswer);
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_sendIceCandidate(
	JNIEnv *env, jclass thisClass, jstring jstrUniqueIdentityCode, jstring jstrSdpMid, jint jintMsgId, jstring jstrSdpAnswer)
{
	std::string uniqueIdentityCode = JNICommon::getJStringValue(env, jstrUniqueIdentityCode);
	std::string sdpMid = JNICommon::getJStringValue(env, jstrSdpMid);
	std::string sdpAnswer = JNICommon::getJStringValue(env, jstrSdpAnswer);

	return IProjectionServer::instance()->sendIceCandidate(uniqueIdentityCode, sdpMid, jintMsgId, sdpAnswer);
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_replyProjectionRequest(
	JNIEnv *env, jclass thisClass, jstring jstrUniqueIdentityCode, jint jintResult)
{
	std::string uniqueIdentityCode = JNICommon::getJStringValue(env, jstrUniqueIdentityCode);

	return IProjectionServer::instance()->replyProjectionRequest(uniqueIdentityCode, static_cast<EnProjectionReply>(jintResult));
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_stopProjectingFromClient(
	JNIEnv *env, jclass thisClass, jstring jstrUniqueIdentityCode)
{
	std::string uniqueIdentityCode = JNICommon::getJStringValue(env, jstrUniqueIdentityCode);

	return IProjectionServer::instance()->stopProjectingFromClient(uniqueIdentityCode);
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_setProjectPropertiesByApp(
	JNIEnv *env, jclass thisClass,
	jstring jstrName,
	jstring jstrSerialNumber,
	jstring jstrProjectionCode,
	jstring jstrWsAddress)
{
	std::string name = JNICommon::getJStringValue(env, jstrName);
	std::string serialNumber = JNICommon::getJStringValue(env, jstrSerialNumber);
	std::string projectionCode = JNICommon::getJStringValue(env, jstrProjectionCode);
	std::string wsAddress = JNICommon::getJStringValue(env, jstrWsAddress);
	return IProjectionServer::instance()->setProjectPropertiesByApp(name, serialNumber, projectionCode, wsAddress);
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_applyForProjectionCode(
	JNIEnv *env, jclass thisClass, jstring jstrIpv4Address, jstring jstrName, jstring jstrSerialNumber, 
	OUT jobject joProjectionCode)
{
	std::string ipv4Address = JNICommon::getJStringValue(env, jstrIpv4Address);
	std::string name = JNICommon::getJStringValue(env, jstrName);
	std::string serialNumber = JNICommon::getJStringValue(env, jstrSerialNumber);
	std::string projectionCode;

	int ret = IProjectionServer::instance()->applyForProjectionCode(ipv4Address, name, serialNumber, projectionCode);
	if (ret != 0)
	{
		errorf("applyForProjectionCode failed.");
		return ret;
	}

	jclass jniCommonTypeClass = env->GetObjectClass(joProjectionCode);
	if (!jniCommonTypeClass) {
		errorf("GET OBJECT CLASS FAILED!!!");
		return -1;
	}
	jfieldID strID = env->GetFieldID(jniCommonTypeClass, "str", JNI_jstring_SIGN);
	if (!strID) {
		errorf("GetFieldID FAILED!!!");
		return -1;
	}
	env->DeleteLocalRef(jniCommonTypeClass);

	jstring jstrProjectionCode = env->NewStringUTF(projectionCode.c_str());
	env->SetObjectField(joProjectionCode, strID, jstrProjectionCode);
	env->DeleteLocalRef(jstrProjectionCode);

	return ret;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_applyForProjectionCodeDebug(
	JNIEnv *env, jclass thisClass, jstring jstrIpv4Address, jstring jstrName, jstring jstrSerialNumber)
{
	std::string ipv4Address = JNICommon::getJStringValue(env, jstrIpv4Address);
	std::string name = JNICommon::getJStringValue(env, jstrName);
	std::string serialNumber = JNICommon::getJStringValue(env, jstrSerialNumber);

	int ret = IProjectionServer::instance()->applyForProjectionCode(ipv4Address, name, serialNumber);
	if (ret != 0)
	{
		errorf("applyForProjectionCode failed.");
		return ret;
	}

	return ret;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_debugStartHttpServer(
	JNIEnv *env, jclass thisClass, jint jintPort)
{
	IProjectDebugHttpServer::start(true, nullptr, jintPort);
	return 0;
}

JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_debugStopHttpServer(
	JNIEnv *env, jclass thisClass)
{
	IProjectDebugHttpServer::stop();
	return 0;
}