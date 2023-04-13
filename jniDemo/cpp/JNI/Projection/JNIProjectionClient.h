#ifndef __SRC_JNI_PROJECTION_JNIPROJECTION_CLIENT_H__
#define __SRC_JNI_PROJECTION_JNIPROJECTION_CLIENT_H__

#include <jni.h>

#include "SDNPDefine.h"

extern "C" 
{
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_init(
		JNIEnv *env, jclass thisClass);
		
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_setIpv4Address(
		JNIEnv *env, jclass thisClass, jstring jstrIpv4Address);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_registerObserver(
		JNIEnv *env, jclass thisClass, jobject joObserver);
		
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_startProject(
		JNIEnv *env, jclass thisClass, jstring jstrProjectionCode, jstring jstrName);
		
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_finishProject(
		JNIEnv *env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_sendSdpOffer(
		JNIEnv *env, jclass thisClass, jstring jstrSdpOffer, OUT jobject joSdpAnswer);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_projection_JNIProjectionClient_sendIceCandidate(
		JNIEnv *env, jclass thisClass, jstring jstrSdpMid, jstring jstrSdpMLineIndex, jstring jstrCandidate);
}

#endif //! __SRC_JNI_PROJECTION_JNIPROJECTION_CLIENT_H__
