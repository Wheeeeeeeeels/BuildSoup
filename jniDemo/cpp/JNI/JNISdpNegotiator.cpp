
#include <memory>

#include "ISdpNegotiator.h"
#include "JNICommon.h"
#include "JNICustomGlobalRef.h"

using namespace SDNP;

extern "C" {

/**
 * Function declaration.
 */
JNIEXPORT jlong JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeCreate(JNIEnv *env,
                                                          jclass thisClass);

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeDestroy(JNIEnv *env,
                                                           jclass thisClass,
                                                           jlong jNegotiator);

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeSetLocalSdpOffer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jstring jSdpOffer);

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeGetLocalSdpOffer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jstring vcodecSelected,
    jstring acodecSelected, OUT jobject joSdpOffer);

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeGetLocalJsonOffer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jboolean jTransportNeed,
    jobject jMidList, OUT jobject joJsonOffer);

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeAddRemoteJsonAnswer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jstring jSdpAnswer);

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeRemoveRemoteJsonAnswer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jobject jMidList);

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeCreateRemoteSdpAnswer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, OUT jobject joSdpAnswer);

/**
 * Function implementation.
 */
JNIEXPORT jlong JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeCreate(JNIEnv *env,
                                                          jclass thisClass) {
    return reinterpret_cast<jlong>(alpha::ISdpNegotiator::Create());
}

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeDestroy(JNIEnv *env,
                                                           jclass thisClass,
                                                           jlong jNegotiator) {
    if (jNegotiator == 0L) {
        errorf("jNegotiator is null");
        return -1;
    }
    alpha::ISdpNegotiator *negotiator =
        reinterpret_cast<alpha::ISdpNegotiator *>(jNegotiator);
    alpha::ISdpNegotiator::Destroy(negotiator);
    return 0;
}

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeSetLocalSdpOffer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jstring jSdpOffer) {
    if (jNegotiator == 0L) {
        errorf("jNegotiator is null");
        return -1;
    }
    return reinterpret_cast<alpha::ISdpNegotiator *>(jNegotiator)
        ->SetLocalSdpOffer(JNICommon::getJStringValue(env, jSdpOffer));
}

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeGetLocalSdpOffer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jstring vcodecSelected,
    jstring acodecSelected, OUT jobject joSdpOffer) {
    if (jNegotiator == 0L) {
        errorf("jNegotiator is null");
        return -1;
    }
    std::string sdpOffer =
        reinterpret_cast<alpha::ISdpNegotiator *>(jNegotiator)
            ->GetLocalSdpOffer(JNICommon::getJStringValue(env, vcodecSelected),
                               JNICommon::getJStringValue(env, acodecSelected));
    JNICommon::setCommonTypeValue(env, sdpOffer, joSdpOffer);
    return 0;
}

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeGetLocalJsonOffer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jboolean jTransportNeed,
    jobject jMidList, OUT jobject joJsonOffer) {
    if (jNegotiator == 0L) {
        errorf("jNegotiator is null");
        return -1;
    }
    std::vector<std::string> mids;
    JNICommon::getFieldValue(env, jMidList, mids);
    std::string jsonOffer =
        reinterpret_cast<alpha::ISdpNegotiator *>(jNegotiator)
            ->GetLocalJsonOffer(jTransportNeed, mids);
    JNICommon::setCommonTypeValue(env, jsonOffer, joJsonOffer);
    return 0;
}

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeAddRemoteJsonAnswer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jstring jSdpAnswer) {
    if (jNegotiator == 0L) {
        errorf("jNegotiator is null");
        return -1;
    }
    return reinterpret_cast<alpha::ISdpNegotiator *>(jNegotiator)
        ->AddRemoteJsonAnswer(JNICommon::getJStringValue(env, jSdpAnswer));
}

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeRemoveRemoteJsonAnswer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, jobject jMidList) {
    if (jNegotiator == 0L) {
        errorf("jNegotiator is null");
        return -1;
    }
    std::vector<std::string> mids;
    JNICommon::getFieldValue(env, jMidList, mids);
    return reinterpret_cast<alpha::ISdpNegotiator *>(jNegotiator)
        ->RemoveRemoteJsonAnswer(mids);
}

JNIEXPORT jint JNICALL
Java_cn_geedow_netprotocol_sdp_SdpNegotiator_nativeCreateRemoteSdpAnswer(
    JNIEnv *env, jclass thisClass, jlong jNegotiator, OUT jobject joSdpAnswer) {
    if (jNegotiator == 0L) {
        errorf("jNegotiator is null");
        return -1;
    }
    std::string sdpAnswer =
        reinterpret_cast<alpha::ISdpNegotiator *>(jNegotiator)
            ->CreateRemoteSdpAnswer();
    JNICommon::setCommonTypeValue(env, sdpAnswer, joSdpAnswer);
    return 0;
}

}  // extern "C"
