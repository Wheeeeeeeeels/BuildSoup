#ifndef __SRC_JNI_PROJECTION_JNIPROJECTION_SERVER_H__
#define __SRC_JNI_PROJECTION_JNIPROJECTION_SERVER_H__

#include <jni.h>

#include "SDNPDefine.h"

extern "C" 
{
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_init(
		JNIEnv *env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_test(
		JNIEnv *env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_registerObserver(
		JNIEnv *env, jclass thisClass, jobject joObserver);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_setIpv4Address(
		JNIEnv *env, jclass thisClass, jstring jstrIpv4Address);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_startProjectionService(
		JNIEnv *env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_stopProjectionService(
		JNIEnv *env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_sendSdpAnswer(
		JNIEnv *env, jclass thisClass, jstring jstrUniqueIdentityCode, jint jintMsgId, jstring jstrSdpAnswer);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_sendIceCandidate(
		JNIEnv *env, jclass thisClass, jstring jstrUniqueIdentityCode, jstring jstrSdpMid, jint jintMsgId, jstring jstrSdpAnswer);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_replyProjectionRequest(
		JNIEnv *env, jclass thisClass, jstring jstrUniqueIdentityCode, jint jintResult);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_stopProjectingFromClient(
		JNIEnv *env, jclass thisClass, jstring jstrUniqueIdentityCode);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_setProjectPropertiesByApp(
		JNIEnv *env, jclass thisClass,
		jstring jstrName,
		jstring jstrSerialNumber,
		jstring jstrProjectionCode,
		jstring jstrWsAddress);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_applyForProjectionCode(
		JNIEnv *env, jclass thisClass, jstring jstrIpv4Address, jstring jstrName, jstring jstrSerialNumber, OUT jobject jstrProjectionCode);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_applyForProjectionCodeDebug(
		JNIEnv *env, jclass thisClass, jstring jstrIpv4Address, jstring jstrName, jstring jstrSerialNumber);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_debugStartHttpServer(
		JNIEnv *env, jclass thisClass, jint jintPort);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionServer_debugStopHttpServer(
		JNIEnv *env, jclass thisClass);
}

#endif //! __SRC_JNI_PROJECTION_JNIPROJECTION_SERVER_H__