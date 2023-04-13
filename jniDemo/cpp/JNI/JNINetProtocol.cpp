//// Include header file.
#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include "INetProtocol.h"
#include "JNINativeObserver.h"
#include "JNINativeRoomObserver.h"
#include "JNINativeLogObserver.h"
#include "JNIHttpUploadObserver.h"
#include "JNICommon.h"
#include "JNICustomGlobalRef.h"

#include "SDNPLogger.h"


//// JNI
// #ifdef __cplusplus
extern "C" {
// #endif
    using namespace SDNP;
    static bool gSdnpProtocolInited = false;
    static jobject gJNIObserver = NULL;
    static jobject gJNIRoomObserver = NULL;
    static jobject gJNILogObserver = NULL;
    static jobject gJNIHttpUploadObserver = NULL;

    static CJNINativeLogObserver *gNativeLogObserver = NULL;
    static CJNINativeObserver *gNativeObserver = NULL;
    static CJNINativeRoomObserver *gNativeRoomObserver = NULL;
    static CJNIHttpUploadObserver *gHttpUploadObserver = NULL;
	static JNICustomGlobalRef *g_customGlobalRef = JNICustomGlobalRef::instance();

    ////////////////////////////////
    //// JNI interface
	////////////////////////////////

	JNIEXPORT jlong JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_geti18n(
		JNIEnv *env, jclass thisClass, jint jniI18nVersion, OUT jobject jniResult);

	JNIEXPORT jlong JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllConfig(
		JNIEnv *env, jclass thisClass, OUT jobject jniResult);

	JNIEXPORT jlong JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getCurrentServerTime(
		JNIEnv *env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_debugConvertSFU2MCU(
		JNIEnv *env, jclass thisClass);
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_jniTest(
		JNIEnv * env, jclass thisClass, jobject joCalleeInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_arrayListTest(
		JNIEnv *env, jclass thisClass, OUT jobject arrayList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setCommonTypeTest(
		JNIEnv *env, jclass thisClass, OUT jobject joCommType);

    JNIEXPORT jstring JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_version(
        JNIEnv *env, jclass thisClass);

    JNIEXPORT jstring JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_codeToMsg(
        JNIEnv *env, jclass thisClass, jint jniCode);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setLogObserver (
        JNIEnv *env, jclass thisClass, jobject jniLogObserver);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setLogLevel (
        JNIEnv *env, jclass thisClass, jint jniLogLevel);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getNetworkConnectStatus (
		JNIEnv *env, jclass thisClass, jobject jniSDKNetStatus);


	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_notifyNetworkDeviceStatusChange (
		JNIEnv *env, jclass thisClass, jboolean jniStatus);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_init (
        JNIEnv *env, jclass thisClass, jobject jniObserver, jobject jniRoomObserver);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_uninit (
        JNIEnv *env, jclass thisClass);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setParams (
        JNIEnv *env, jclass thisClass, jobject jniParam);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getParams (
		JNIEnv *env, jclass thisClass, OUT jobject jniParams);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setProxyServer(
		JNIEnv *env, jclass thisClass, jboolean jzStatus, jobject joServerInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setHttpUploadObserver(
		JNIEnv *env, jclass thisClass, jobject jniHttpUploadObserver);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateUsername (
        JNIEnv *env, jclass thisClass, jstring jstrUsername);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateUserIcon (
        JNIEnv *env, jclass thisClass, jint requestCode, jstring jstrFilePath);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateToken (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniPassword,
        OUT jobject jniToken);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getValidateCode (
		JNIEnv *env, jclass thisClass, jstring jniPhoneOrEmail, jint jiUsage);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_checkValidateCode(
		JNIEnv *env, jclass thisClass, jstring jniPhoneOrEmail, jstring jniValidateCode, jint jiUsage, jstring jstrAccount);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_loginByCode (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniValidateCode,
        OUT jobject jniToken, OUT jobject jniServerTime);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_loginByPwd (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniPassword,
        OUT jobject jniLoginInfo);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_loginByToken (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniToken,
		OUT jobject jniServerTime, OUT jobject jniAccountUuid);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getLoginInfo(
		JNIEnv *env, jclass thisClass, OUT jobject joLoginInfo);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getCurrentServerInfo(
		JNIEnv *env, jclass thisClass, OUT jobject joServerInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_logout(
		JNIEnv *env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_uploadTerminalInfo(
		JNIEnv *env, jclass thisClass, jobject joInfo);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getOrgTree (
        JNIEnv *env, jclass thisClass, OUT jobject jniOrgInfoArrSize,
        OUT jobjectArray jniOrgInfoArray);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPagesOfOrgDepart(
		JNIEnv *env, jclass thisClass, jint jintOrgId, jobject joPageInfoIn,
		OUT jobject joOrgInfoArrayList, OUT jobject joPageInfoOut);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getOrgMembers (
        JNIEnv *env, jclass thisClass, jint jniOrgId, OUT jobject jniOrgMemArrSize,
		OUT jobjectArray jniOrgMemArray);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPagesOfOrgMember(
		JNIEnv *env, jclass thisClass, jint jintOrgId, jobject joPageInfoIn,
		OUT jobject joMemberInfoArrayList, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getOrgMemberRecursively(
		JNIEnv *env, jclass thisClass, jobject joDepartList, jobject joAccountList,
		OUT jobject joMemberInfoArrayList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getFrequentContacts(
		JNIEnv *env, jclass thisClass, jobject joPageInfoIn,
		OUT jobject joMemberInfoArrayList, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getMemberDetails(
		JNIEnv *env, jclass thisClass, jstring jstrAccount,
		OUT jobject joMemberInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateContact(
		JNIEnv *env, jclass thisClass, jobject joMemberInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_createGroup(
		JNIEnv *env, jclass thisClass, jstring jstrGroupName, jobjectArray jniContactList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_delGroup(
		JNIEnv *env, jclass thisClass, jint jintGroupId);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateGroup(
		JNIEnv *env, jclass thisClass, jint jintGroupId, jstring jstrGroupName, jobjectArray jniContactList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getGroupList(
		JNIEnv *env, jclass thisClass, jint jintType, jobject joPageInfoIn,
		OUT jobject joGroupInfoArrayList, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getGroupMember(
		JNIEnv *env, jclass thisClass, jint jintGroupId, jobject joPageInfoIn,
		OUT jobject joMemberInfoArrayList, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateParticipantsOrder(
		JNIEnv *env, jclass thisClass, jobject joParticipantInfos);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_sendMessage (
        JNIEnv *env, jclass thisClass, jstring jniAccountTo, jstring jniReq,
        OUT jobject jniRsp);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_createMeeting(
		JNIEnv *env, jclass thisClass, jobject joStMeeting);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_joinMeeting(
		JNIEnv *env, jclass thisClass, jobject joStMeeting, jobject joStMeetingAttribute);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_leaveMeeting(
		JNIEnv *env, jclass thisClass, jobject joStMeeting);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_closeMeeting(
		JNIEnv *env, jclass thisClass, jobject joStMeeting);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getMeetingInfo(
		JNIEnv *env, jclass thisClass, jobject joStMeeting);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllPublishers(
		JNIEnv *env, jclass thisClass, OUT jobject joPartInfoArrayList,OUT jobject joStParticipantInfo_lecturer,
		OUT jobject joStParticipantInfo_partShared);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPartOfParticpantWhoRaiseHand(
		JNIEnv *env, jclass thisClass, OUT jobject joStPartInfoArrayList);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_publishVideo (
        JNIEnv *env, jclass thisClass, jint jniStreamType, jstring jniSdpOffer,
        jboolean jniVideoStatus, jboolean jniAudioStatus,
        OUT jobject jniSdpAnswer);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_stopPublishVideo (
        JNIEnv *env, jclass thisClass, jint jniStreamType);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_stopReceiveVideo(
		JNIEnv *env, jclass thisClass, jstring jniAccount, jint jniStreamType);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_receiveVideo (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jint jniStreamType,
		jstring jniSdpOffer, OUT jobject jniSdpAnswer);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_createMediaChannel(
        JNIEnv *env, jclass thisClass, jstring jniSdpOffer, OUT jobject jniChannelId, OUT jobject jniChannelResponse);
	
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_destroyMediaChannel(
        JNIEnv *env, jclass thisClass, jstring jniChannelId);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_addMediaTrack(
		JNIEnv *env, jclass thisClass, jobject joParams, OUT jobject joSdpAnswer,
		OUT jobject joFailedRsp);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_removeMediaTrack(
		JNIEnv *env, jclass thisClass, jstring jniAccount, jint jniStreamType, jobject jomediaTypes);
		

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPushStreamStatus(
		JNIEnv *env, jclass thisClass, jstring jstrAccount, jint jintStreamType, jint jintStatus);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPullStreamStatus(
		JNIEnv *env, jclass thisClass, jobject joParams, jint jintStatus);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_sendIceCandidate (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jint jniStreamType,
        jstring jniSDNPMid, jstring jniSDNPMLineIndex, jstring jniCandidate);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setShareState(
		JNIEnv *env, jclass thisClass, jstring jniOperateAccount, jstring jniShareAccount, jboolean jniShareState);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setMeetingInfo(
		JNIEnv *env, jclass thisClass, jint jintOption, jobject joMeetingInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllParticipantsHaveNotJoined (
		JNIEnv *env, jclass thisClass, OUT jobject joStPartInfoArrayList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPagesOfParticipants(
		JNIEnv *env, jclass thisClass, jint jintOrder, jint jintCountOfParticipant,
		jboolean jniIsPositiveSequence, OUT jobject joStPartInfoArrayList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_delParticipantHaveNotJoined(
		JNIEnv *env, jclass thisClass, jobject joAccountList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getParticipant(
		JNIEnv *env, jclass thisClass, jstring jstrAccount, OUT jobject jniStPartInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getParticipantByName(
		JNIEnv *env, jclass thisClass, jstring jstrName, OUT jobject joPartInfoArrayList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_inviteParticipant(
		JNIEnv *env, jclass thisClass, jstring jniRoomId, jobjectArray jniAccountToList, jlong expireTime);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_cancelInvite (
        JNIEnv *env, jclass thisClass, jstring jniRoomId, jobjectArray jniAccountToList);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getCalleeList (
        JNIEnv *env, jclass thisClass, jobject joCalleeList);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_removeCallee (
        JNIEnv *env, jclass thisClass, jobject joCalleeList);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_ringing (
        JNIEnv *env, jclass thisClass, jstring jniRoomId, jstring jniAccountTo);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_refuseInvite (
        JNIEnv *env, jclass thisClass, jstring jniRoomId, jstring jniAccountTo, jint reason);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_switchVideo (
        JNIEnv *env, jclass thisClass, jobjectArray jniAccountToList, jboolean jniAction);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_switchAudioIn (
        JNIEnv *env, jclass thisClass, jobjectArray jniAccountToList, jboolean jniAction);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_switchAudioOut (
		JNIEnv *env, jclass thisClass, jobjectArray jniAccountToList, jboolean jniAction);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setSpeakerPermission(
		JNIEnv *env, jclass thisClass, jstring jniRoomId, jboolean jniPermitted);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_applyOpenSpeaker(
		JNIEnv *env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_applyOpenMic(
		JNIEnv *env, jclass thisClass);
	
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setHandStatus(
		JNIEnv *env, jclass thisClass, jobjectArray jniAccountToList, jboolean jbStatus);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getRoomSettings (
        JNIEnv *env, jclass thisClass, OUT jobject jniCapacity);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getH5Pages (
        JNIEnv *env, jclass thisClass, jint jniH5PageType,
		OUT jobject joH5PageInfoList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getH5PagesByHttp(
		JNIEnv *env, jclass thisClass, jint jniH5PageType,
		OUT jobject joH5PageInfoList);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_loginAsVisitor(
        JNIEnv *env, jclass thisClass, jstring jniUsername, jstring jniMac, OUT jobject jniAccount,  OUT jobject jniServerTime);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_resetPassword (
		JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniValidateCode, jstring jniNewPassword);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAppointedMeetingRoom(
		JNIEnv *env, jclass thisClass, jstring jstrRoomId, OUT jobject joMeetingRoom, OUT jobject joRuid);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getMeetSimplify(
		JNIEnv *env, jclass thisClass, jstring jstrRuid, OUT jobject joMeeting);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllMeetingRooms(
		JNIEnv *env, jclass thisClass, jobject joPageInfoIn, jboolean jbIfLimitedByPermission,
		OUT jobject joAllMeetingRooms, OUT jobject joPageInfoOut);

	 JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_createAppointConference(
		 JNIEnv *env, jclass thisClass, jobject jniParam);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateAppointConference(
		JNIEnv *env, jclass thisClass, jobject jniParam);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_cancelAppointConference(
		JNIEnv *env, jclass thisClass, jstring jniRuid);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_deleteAppointConference(
		JNIEnv *env, jclass thisClass, jstring jniRuid);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllConferenceSummary(
		JNIEnv *env, jclass thisClass, jint jniStatus, jstring jstrDate, jobject joPageInfoIn,
		OUT jobject joSummaries, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllConferenceSummaryOfPeriodOfTime(
		JNIEnv *env, jclass thisClass, jint jniStatus, jstring jstrStartDate, jstring jstrEndDate, jobject joPageInfoIn,
		OUT jobject joSummaries, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllConferenceSummaryOfSpecifiedRoom(
		JNIEnv *env, jclass thisClass, jstring jstrRoomId, jobject joPageInfoIn,
		OUT jobject joSummaries, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAppointConferenceDetails(
		JNIEnv *env, jclass thisClass, jstring jniRuid, OUT jobject joStAppointConferenceInfo, OUT jobject joIsStart);

     JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPersonalConfRoomInfo (
        JNIEnv *env, jclass thisClass, OUT jobject jniParams);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updatePersonalConfRoomInfo(
        JNIEnv *env, jclass thisClass, jobject jniParam);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_modifyPassword(
        JNIEnv *env, jclass thisClass, jstring jniOriginalPassword, jstring jniNewPassword);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_switchVoiceMode (
        JNIEnv *env, jclass thisClass, jint jniOperation);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_evictedParticipant (
		JNIEnv *env, jclass thisClass, jstring jstrAccount);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_needVersionUpgrade (
         JNIEnv *env, jclass thisClass, OUT jobject needUpgrade, OUT jobject forceStatus, OUT jobject downLoadUrl,
         OUT jobject jniVersion, OUT jobject jniApkSize, OUT jobject jniDetails);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_needVersionUpgradeV2 (
         JNIEnv *env, jclass thisClass, OUT jobject needUpgrade, OUT jobject forceStatus, OUT jobject downLoadUrl,
         OUT jobject jniVersion, OUT jobject jniApkSize, OUT jobject jniDetails);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_reconnect(
         JNIEnv *env, jclass thisClass);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_startConferenceRecord(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId, jboolean jzForce);


    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_stopConferenceRecord(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getConferenceRecordStatus(
		JNIEnv *env, jclass thisClass, jstring jstrRoomId, OUT jobject joCommonType);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getConferenceRecord(
        JNIEnv *env, jclass thisClass, jint size, jint pageNum, OUT jobject jniTotal, OUT jobject jniRecordListsLen, OUT jobjectArray jniRecordLists);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_playbackConferenceRecord(
        JNIEnv *env, jclass thisClass, jlong jstrId, OUT jobject recordUrl);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_downloadConferenceRecord(
        JNIEnv *env, jclass thisClass, jlong jstrId, OUT jobject downloadUrl);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_delConferenceRecord(
        JNIEnv *env, jclass thisClass, jlong jstrId);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_startLive(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId, OUT jobject jobLivingUrl);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_stopLive(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getLiveStatus(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId, OUT jobject jniLivingStatus);

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_httpGet(
		JNIEnv *env, jclass thisClass, jstring jstrUrl, OUT jobject jniRspBody);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_pushLog(
		JNIEnv *env, jclass thisClass, jobject jniPushLogParams);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getUnfinishedRoom(
		JNIEnv *env, jclass thisClass, OUT jobject jniRoomInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setRollCallStatus(
		JNIEnv *env, jclass thisClass, jstring jniOldAccount, jstring jniNewAccount, jboolean jniStatus, jint jniSource);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAccount(
		JNIEnv *env, jclass thisClass, jstring jniSerialNumber, OUT jobject jniAccount, OUT jobject jniPassword);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_changeMeetingLayout(
		JNIEnv *env, jclass thisClass, jint jintLayoutType, jint jintNumberOfSplitScreen, jobject joLayouts);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPtzControlStatus(
		JNIEnv *env, jclass thisClass, jboolean jzAction, jobject joParam);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_adjustResolution(
		JNIEnv * env, jclass thisClass, jint jiResolution);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPresetPosition(
		JNIEnv * env, jclass thisClass, jstring jstrSerialNumber, jint jintIndex, jstring jstrImage, jobject joConfigInfo);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPollingStatus(
		JNIEnv * env, jclass thisClass, jstring jstrRoomId, jboolean jzStatus, jint jintTimeInterval);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPollingStatus(
		JNIEnv * env, jclass thisClass, jstring jstrRoomId, OUT jobject joCommonType);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getIceServerList(
		JNIEnv * env, jclass thisClass, OUT jobject joIceServerInfos);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_countParticipatedDuration(
		JNIEnv * env, jclass thisClass, jobject joPageInfoIn,
		OUT jobject joMeetingInfos, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_uploadMeetingQuality(
		JNIEnv * env, jclass thisClass, jobject joNetworkQuality, jobject joStreamQualityList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getScrollBarrage(
		JNIEnv * env, jclass thisClass, OUT jobject joStatus, OUT jobject joNetworkQuality);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_sendIMMessage(
		JNIEnv * env, jclass thisClass, jobject joMessage, jstring jstrClientMsgId, 
		OUT jobject joFinalMsgId, OUT jobject joFinalTimestamp);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getIMMessageHistory(
		JNIEnv * env, jclass thisClass, jobject joLastIMMessage, jint jintCountOfMsg, jboolean jbIsPositiveSequence,
		OUT jobject joMessageArrayList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_checkIfExistUnreadPushedMsg(
		JNIEnv * env, jclass thisClass, OUT jobject joUnreadMsgParams);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPagesOfPushedMsg(
		JNIEnv *env, jclass thisClass, jobject joPageInfoIn,
		OUT jobject joPushedMsgArrayList, OUT jobject joPageInfoOut);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_readPushedMsg(
		JNIEnv * env, jclass thisClass, jobject joIdArrayList);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_cleanPushedMsg(
		JNIEnv * env, jclass thisClass);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getDeployEnv(
		JNIEnv * env, jclass thisClass, OUT jobject joIsPrivateDeploy);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_uploadRegistrationId(
		JNIEnv * env, jclass thisClass, jstring jstrRegistrationId);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_queryOperationPermission(
		JNIEnv * env, jclass thisClass, OUT jobject joPermissions, OUT jobject joAbilities);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_hurryUp(
		JNIEnv * env, jclass thisClass, jstring jstrRoomId, jstring jstrRuid);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_changeMeetingRoom(
		JNIEnv * env, jclass thisClass, jstring jstrRuid, jint jintRoomIdType, jstring jstrRoomId);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_prolongMeeting(
		JNIEnv * env, jclass thisClass, jint jintMinsNeedToProlong);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_changePhoneNumber(
		JNIEnv * env, jclass thisClass, jstring jstrNewPhoneNumber, jstring jstrValidateCode);

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_cancelAccount(
		JNIEnv * env, jclass thisClass, jstring jstrNewPhoneNumber, jstring jstrValidateCode);

	////////////////////////////////
    //// JNI impl
	////////////////////////////////

	JNIEXPORT jlong JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_geti18n(JNIEnv *env, jclass thisClass, 
			jint jniI18nVersion, OUT jobject jniResult)
	{
		tracef("%s in >>>", __FUNCTION__);
		std::string cpprsp;
		jint nRet = -1;
		nRet = INetProtocol::instance()->geti18n(jniI18nVersion, cpprsp);
		if (nRet != 0) {
			errorf("%s FAILED!!!", __FUNCTION__);
            return nRet;
        }
		JNICommon::setCommonTypeValue(env, cpprsp, jniResult);

		return nRet;
	}

	JNIEXPORT jlong JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllConfig(JNIEnv *env, jclass thisClass, 
			OUT jobject jniResult)
	{
		tracef("%s in >>>", __FUNCTION__);
		std::string cpprsp;
		jint nRet = -1;
		nRet = INetProtocol::instance()->getAllConfig(cpprsp);
		if (nRet != 0) {
			errorf("%s FAILED!!!", __FUNCTION__);
            return nRet;
        }
		JNICommon::setCommonTypeValue(env, cpprsp, jniResult);

		return nRet;
	}

	JNIEXPORT jlong JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getCurrentServerTime(
		JNIEnv *env, jclass thisClass)
	{
		tracef("%s in >>>", __FUNCTION__);

		long long serverTime = INetProtocol::instance()->getCurrentServerTime();

		return serverTime;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_arrayListTest(
		JNIEnv * env, jclass thisClass, OUT jobject joArrayList)
	{
		tracef("%s in >>>", __FUNCTION__);

		jclass jniOrgInfoClass = env->FindClass(ORG_INFO_CLASS_NAME);
		if (!jniOrgInfoClass) {
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}

		jfieldID orgIdID = env->GetFieldID(jniOrgInfoClass, "orgId", "I");
		jfieldID orgNameID = env->GetFieldID(jniOrgInfoClass, "orgName", "Ljava/lang/String;");
		jfieldID parentIdID = env->GetFieldID(jniOrgInfoClass, "parentId", "I");
		jfieldID hasChildID = env->GetFieldID(jniOrgInfoClass, "hasChild", "Z");
		jmethodID orgInfoConstructorID = env->GetMethodID(jniOrgInfoClass, "<init>", "()V");

		char orgNameOrder[5] = { 0 };
		for (int i = 0; i < 1000; ++i)
		{
			int orgId = i;
			memset(orgNameOrder, 0, 5);
			sprintf(orgNameOrder, "%d", i);
			std::string orgName = std::string("orgName_") + std::string(orgNameOrder);
			int parentId = -1;
			bool hasChild = false;

			jstring jstrOrgName = (jstring)env->NewStringUTF(orgName.c_str());

			jobject joOrgInfo = env->NewObject(jniOrgInfoClass, orgInfoConstructorID);
			env->SetIntField(joOrgInfo, orgIdID, orgId);
			env->SetObjectField(joOrgInfo, orgNameID, jstrOrgName);
			env->SetIntField(joOrgInfo, parentIdID, parentId);
			env->SetBooleanField(joOrgInfo, hasChildID, hasChild);

			JNICommon::addEleIntoArrayList(env, joArrayList, joOrgInfo);
			
			env->DeleteLocalRef(jstrOrgName);
			env->DeleteLocalRef(joOrgInfo);
		}

		env->DeleteLocalRef(jniOrgInfoClass);

		tracef("%s out <<<", __FUNCTION__);
		return 0;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setCommonTypeTest(
		JNIEnv * env, jclass thisClass, OUT jobject joCommType)
	{
		JNICommon::setCommonTypeValue<int>(env, 1, joCommType);
		JNICommon::setCommonTypeValue<std::string>(env, "Hello world", joCommType);
		JNICommon::setCommonTypeValue<long>(env, 1, joCommType);
		JNICommon::setCommonTypeValue<bool>(env, true, joCommType);
		JNICommon::setCommonTypeValue<double>(env, 1.0, joCommType);

		return 0;
	}

    JNIEXPORT jstring JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_version(
        JNIEnv *env, jclass thisClass) {
        tracef("%s in >>>", __FUNCTION__);

        std::string sdnpSdkVersion = INetProtocol::instance()->version();

        tracef("%s out <<<", __FUNCTION__);
        return env->NewStringUTF(sdnpSdkVersion.c_str());
    }

    JNIEXPORT jstring JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_codeToMsg(
        JNIEnv *env, jclass thisClass, jint jniCode) {
        tracef("%s in >>>", __FUNCTION__);

        std::string codeMsg = INetProtocol::instance()->codeToMsg(jniCode);

        tracef("%s out <<<", __FUNCTION__);
        return env->NewStringUTF(codeMsg.c_str());
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setLogObserver (
        JNIEnv *env, jclass thisClass, jobject jniLogObserver) {
        tracef("%s in >>>", __FUNCTION__);
        if (NULL == jniLogObserver || gJNILogObserver) {
            return -1;
        }

        jint nRet = -1;

        jclass jniLogObserverClass = env->GetObjectClass(jniLogObserver);
        if (!jniLogObserverClass) {
            errorf("GET OBJECT CLASS FAILED!!!");
            return -1;
        }

        jfieldID logLevelID = env->GetFieldID(jniLogObserverClass, "logLevel", "I");
        jint jiLogLevel = env->GetIntField(jniLogObserver, logLevelID);

        gJNILogObserver = env->NewGlobalRef(jniLogObserver);

        if (NULL == gNativeLogObserver) {
            gNativeLogObserver = new CJNINativeLogObserver();
        }
		gNativeLogObserver->setJNIJavaObserver(gJNILogObserver);
		nRet = INetProtocol::instance()->setLogObserver(gNativeLogObserver);
     
        gNativeLogObserver->setLogLevel((EnLogLevel)jiLogLevel);

		env->DeleteLocalRef(jniLogObserverClass);

        tracef("%s out <<<", __FUNCTION__);

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setLogLevel (
        JNIEnv *env, jclass thisClass, jint jniLogLevel) {
        tracef("%s in >>>", __FUNCTION__);
        if (NULL == gNativeLogObserver) {
            return -1;
        }

        jint nRet = -1;

        gNativeLogObserver->setLogLevel((EnLogLevel)jniLogLevel);
        tracef("%s out <<<", __FUNCTION__);

        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getNetworkConnectStatus (
		JNIEnv *env, jclass thisClass, jobject jniSDKNetStatus)
	{
		tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        EnNetState state;

        // JNI CommonType
        jclass jniSDKNetStatusClass = env->GetObjectClass(jniSDKNetStatus);
        if (!jniSDKNetStatusClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID sdkNetStateID = env->GetFieldID(jniSDKNetStatusClass, "number", "I");
        if (!sdkNetStateID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        nRet = INetProtocol::instance()->getNetworkConnectStatus(state);
		if (nRet != 0) {
			errorf("%s FAILED!!!", __FUNCTION__);
            return nRet;
        }

        infof("state:%d", state);
        env->SetIntField(jniSDKNetStatus, sdkNetStateID, (int)state);
        env->DeleteLocalRef(jniSDKNetStatusClass);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_notifyNetworkDeviceStatusChange(
		JNIEnv * env, jclass thisClass, jboolean jniStatus)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet =  INetProtocol::instance()->notifyNetworkDeviceStatusChange(jniStatus);
		if (nRet != 0) {
			errorf("%s FAILED!!!", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_init (
        JNIEnv *env, jclass thisClass, jobject jniObserver, jobject jniRoomObserver) {
        tracef("%s in >>>", __FUNCTION__);
        if (gSdnpProtocolInited) {
            warnf("already inited.");
            return -1;
		}

        jint nRet = -1;

        // initLogger("./configuration.xml");
        gJNIObserver = env->NewGlobalRef(jniObserver);
        gJNIRoomObserver = env->NewGlobalRef(jniRoomObserver);

        gNativeObserver = new CJNINativeObserver();
        gNativeObserver->setJNIJavaObserver(gJNIObserver);

        gNativeRoomObserver = new CJNINativeRoomObserver();
        gNativeRoomObserver->setJNIJavaRoomObserver(gJNIRoomObserver);

        nRet = INetProtocol::instance()->init(gNativeObserver, gNativeRoomObserver);
        gSdnpProtocolInited = true;

		// 设置全局引用
		g_customGlobalRef->setJNIEnv(env);
		g_customGlobalRef->setGlobalRef(STREAM_INFO_CLASS_NAME);
		g_customGlobalRef->setGlobalRef(STSTREAM_INFO_CLASS_NAME);
		g_customGlobalRef->setGlobalRef(STPARTICIPANTINFO_INFO_CLASS_NAME);
		g_customGlobalRef->setGlobalRef(PRESET_POSITION_CONFIG_INFO_CLASS_NAME);
		g_customGlobalRef->setGlobalRef(BARRAGE_CLASS_NAME);
		g_customGlobalRef->setGlobalRef(IM_MESSAGE_CLASS_NAME);
		g_customGlobalRef->setGlobalRef(HARD_TERMINAL_DEVICE_INFO_CLASS_NAME);
		g_customGlobalRef->setGlobalRef(VIEW_CLASS_NAME);
		g_customGlobalRef->setGlobalRef(STMEETING_INFO_CLASS_NAME);
		
		gNativeRoomObserver->setGlobalRef(g_customGlobalRef);
		gNativeObserver->setGlobalRef(g_customGlobalRef);

        tracef("%s out <<<", __FUNCTION__);

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_uninit (
        JNIEnv *env, jclass thisClass) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        nRet = INetProtocol::instance()->uninit();

        if (NULL != gHttpUploadObserver) {
            delete gHttpUploadObserver;
			gHttpUploadObserver = NULL;
		}

		if (NULL != gNativeObserver) {
			delete gNativeObserver;
			gNativeObserver = NULL;
		}

        if (NULL != gNativeRoomObserver) {
            delete gNativeRoomObserver;
            gNativeRoomObserver = NULL;
        }

        if (NULL != gNativeLogObserver) {
            delete gNativeLogObserver;
            gNativeLogObserver = NULL;
            env->DeleteGlobalRef(gJNILogObserver);
        }

        env->DeleteGlobalRef(gJNIObserver);
        env->DeleteGlobalRef(gJNIRoomObserver);
        gSdnpProtocolInited = false;

		// 清除所有全局引用
		g_customGlobalRef->clearAllGlobalRef();
		// g_customGlobalRef = NULL;

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setParams (
        JNIEnv *env, jclass thisClass, jobject jniParam) {
        tracef("%s in >>>", __FUNCTION__);

        jint nRet = -1;
        BasicInfo param;
		JNICommon::getFieldValue(env, jniParam, param);

        nRet = INetProtocol::instance()->setParams(param);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getParams (
        JNIEnv *env, jclass thisClass, OUT jobject jniParams) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        BasicInfo param;

        nRet = INetProtocol::instance()->getParams(param);
        if (nRet < 0) {
            errorf("GET PARAMS FAILED!!!");
            return nRet;
        }

		JNICommon::setFieldValue(env, param, jniParams);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setProxyServer(
		JNIEnv * env, jclass thisClass, jboolean jzStatus, jobject joServerInfo)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		ServerInfo cppServerInfo;
		JNICommon::getFieldValue(env, joServerInfo, cppServerInfo);

		nRet = INetProtocol::instance()->setProxyServer(jzStatus, cppServerInfo);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setHttpUploadObserver(
		JNIEnv *env, jclass thisClass, jobject jniHttpUploadObserver)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (gHttpUploadObserver != NULL)
		{
			warnf("%s maybe call repeated", __FUNCTION__);
			return nRet;
		}

		gJNIHttpUploadObserver = env->NewGlobalRef(jniHttpUploadObserver);
		gHttpUploadObserver = new CJNIHttpUploadObserver();
		gHttpUploadObserver->setJNIJavaObserver(gJNIHttpUploadObserver);

		tracef("%s out <<<", __FUNCTION__);

		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateUsername (
        JNIEnv *env, jclass thisClass, jstring jstrUsername) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jstrUsername == NULL)
        {
            return nRet;
        }

        const char *cppUsername = env->GetStringUTFChars(jstrUsername, NULL);
        nRet = INetProtocol::instance()->updateUsername(cppUsername);
        env->ReleaseStringUTFChars(jstrUsername, cppUsername);
        if (nRet < 0) {
            errorf("UPDATE USERNAME FAILED!!!");
        }

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateUserIcon (
        JNIEnv *env, jclass thisClass, jint requestCode, jstring jstrFilePath)
	{
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        nRet = INetProtocol::instance()->updateUserIcon(requestCode, 
			JNICommon::getJStringValue(env, jstrFilePath),
			gHttpUploadObserver);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateToken (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniPassword,
        OUT jobject jniToken) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        std::string token;
        if (jniAccount == NULL || jniPassword == NULL)
        {
            return nRet;
        }

        const char *cppAccount = env->GetStringUTFChars(jniAccount, NULL);
        const char *cppPassword = env->GetStringUTFChars(jniPassword, NULL);
        nRet = INetProtocol::instance()->updateToken(cppAccount, cppPassword, token);
        env->ReleaseStringUTFChars(jniAccount, cppAccount);
        env->ReleaseStringUTFChars(jniPassword, cppPassword);
        if (nRet < 0) {
            errorf("UPDATE TOKEN FAILED!!!");
        }

        // COMM_TYPE_CLASS_NAME
        jclass jniTokenClass = env->GetObjectClass(jniToken);
        if (!jniTokenClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID tokenStrID = env->GetFieldID(jniTokenClass, "str", "Ljava/lang/String;");
        if (!tokenStrID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        jstring jstrToken = env->NewStringUTF(token.c_str());
        env->SetObjectField(jniToken, tokenStrID, jstrToken);
        env->DeleteLocalRef(jstrToken);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getValidateCode (
        JNIEnv *env, jclass thisClass, jstring jniPhoneOrEmail, jint jiUsage) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniPhoneOrEmail == NULL)
        {
           return nRet;
        }

        nRet = INetProtocol::instance()->getValidateCode(
			JNICommon::getJStringValue(env, jniPhoneOrEmail),
			static_cast<EnValidateCodeUsage>(jiUsage));

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_checkValidateCode(
		JNIEnv *env, jclass thisClass, jstring jniPhoneOrEmail, jstring jniValidateCode, jint jiUsage, jstring jstrAccount) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		if (jniPhoneOrEmail == NULL || jniValidateCode == NULL)
		{
			return nRet;
		}

		nRet = INetProtocol::instance()->checkValidateCode(
			JNICommon::getJStringValue(env, jniPhoneOrEmail),
			JNICommon::getJStringValue(env, jniValidateCode),
			static_cast<EnValidateCodeUsage>(jiUsage),
			JNICommon::getJStringValue(env, jstrAccount));

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_loginByCode (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniValidateCode,
        OUT jobject jniToken, OUT jobject jniServerTime) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniAccount == NULL || jniValidateCode == NULL)
        {
           return nRet;
        }

        std::string token;
    	long long serverTime = 0;
        nRet = INetProtocol::instance()->loginByCode(
			JNICommon::getJStringValue(env, jniAccount), 
			JNICommon::getJStringValue(env, jniValidateCode), 
			token, serverTime);

		JNICommon::setCommonTypeValue(env, token, jniToken);
		JNICommon::setCommonTypeValue(env, serverTime, jniServerTime);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_loginByPwd (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniPassword,
        OUT jobject jniLoginInfo) {        
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		if (jniAccount == NULL || jniPassword == NULL)
		{
			return nRet;
		}

		LoginInfo loginInfo;
		nRet = INetProtocol::instance()->login(			
			JNICommon::getJStringValue(env, jniAccount), 
			JNICommon::getJStringValue(env, jniPassword), 
			loginInfo);
		if (nRet != 0) {
			errorf("%s FAILED!!! ret:%d", __FUNCTION__, nRet);
			return nRet;
		}

		JNICommon::setFieldValue(env, loginInfo, jniLoginInfo);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_loginByToken (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniToken,
        OUT jobject jniServerTime,  OUT jobject jniAccountUuid) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniAccount == NULL || jniToken == NULL)
        {
            return nRet;
        }

        long long serverTime = 0;
        std::string accountUuid;
        nRet = INetProtocol::instance()->login(
			JNICommon::getJStringValue(env, jniAccount), 
			JNICommon::getJStringValue(env, jniToken), 
			serverTime, accountUuid);

		JNICommon::setCommonTypeValue(env, accountUuid, jniAccountUuid);
		JNICommon::setCommonTypeValue(env, serverTime, jniServerTime);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}
    // 锚点
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getLoginInfo(
		JNIEnv *env, jclass thisClass, OUT jobject joLoginInfo) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		LoginInfo loginInfo;
		nRet = INetProtocol::instance()->getLoginInfo(loginInfo);
		if (nRet != 0) {
			errorf("%s FAILED!!! ret:%d", __FUNCTION__, nRet);
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, loginInfo, joLoginInfo);
		if (nRet != 0) {
			errorf("%s FAILED!!! ret:%d", __FUNCTION__, nRet);
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getCurrentServerInfo (
		JNIEnv *env, jclass thisClass, OUT jobject joServerInfo) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		ServerInfo serverInfo;
		nRet = INetProtocol::instance()->getCurrentServerInfo(serverInfo);
		if (nRet != 0) {
			errorf("%s FAILED!!! ret:%d", __FUNCTION__, nRet);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, serverInfo, joServerInfo);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_logout (
        JNIEnv *env, jclass thisClass) {
        tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

        nRet = INetProtocol::instance()->logout();

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_uploadTerminalInfo(
		JNIEnv * env, jclass thisClass, jobject joInfo)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		StTerminalLocalInfo cppInfo;
		nRet = JNICommon::getFieldValue(env, joInfo, cppInfo);

		nRet = INetProtocol::instance()->uploadTerminalInfo(cppInfo);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getOrgTree (
        JNIEnv *env, jclass thisClass, OUT jobject jniOrgInfoArrSize,
        OUT jobjectArray jniOrgInfoArray) {
        tracef("%s in >>>", __FUNCTION__);

        jint nRet = -1;
        std::vector<OrgInfo> orgList;
        nRet = INetProtocol::instance()->getOrgTree(orgList);

        if (orgList.empty()) {
            errorf("%s is empty", __FUNCTION__);
            return nRet;
        }

        jclass jniOrgInfoClass = env->FindClass(ORG_INFO_CLASS_NAME);
        if (!jniOrgInfoClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID orgIdID = env->GetFieldID(jniOrgInfoClass, "orgId", "I");
        jfieldID orgNameID = env->GetFieldID(jniOrgInfoClass, "orgName", "Ljava/lang/String;");
        jfieldID parentIdID = env->GetFieldID(jniOrgInfoClass, "parentId", "I");
        jfieldID hasChildID = env->GetFieldID(jniOrgInfoClass, "hasChild", "Z");
        jmethodID orgInfoConstructorID = env->GetMethodID(jniOrgInfoClass, "<init>", "()V");

        int nOrgListSize = orgList.size();
        int jniArrayLen = env->GetArrayLength(jniOrgInfoArray);
        if (nOrgListSize > jniArrayLen) {
            warnf("MAYBE ARRAY IS SUB!!!");
        }
        int minLen = std::min(nOrgListSize, jniArrayLen);
        // jobjectArray joaOrgList = env->NewObjectArray(nOrgListSize, jniOrgInfoClass, NULL);
        for (int i = 0; i < minLen; i++) {
            jobject joOrgInfo = env->NewObject(jniOrgInfoClass, orgInfoConstructorID);
            env->SetIntField(joOrgInfo, orgIdID, orgList.at(i).orgId);
            jstring jstrOrgName = env->NewStringUTF(orgList.at(i).orgName.c_str());
            env->SetObjectField(joOrgInfo, orgNameID, jstrOrgName);
            env->SetIntField(joOrgInfo, parentIdID, orgList.at(i).parentId);
            env->SetBooleanField(joOrgInfo, hasChildID, orgList.at(i).hasChild);
            env->SetObjectArrayElement(jniOrgInfoArray, i, joOrgInfo);

            env->DeleteLocalRef(jstrOrgName);
            env->DeleteLocalRef(joOrgInfo);
        }

        env->DeleteLocalRef(jniOrgInfoClass);

        // COMM_TYPE_CLASS_NAME
        jclass jniArrSizeClass = env->GetObjectClass(jniOrgInfoArrSize);
        if (!jniArrSizeClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID arrSizeNumberID = env->GetFieldID(jniArrSizeClass, "number", "I");
        if (!arrSizeNumberID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

		env->DeleteLocalRef(jniArrSizeClass);

        env->SetIntField(jniOrgInfoArrSize, arrSizeNumberID, minLen);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}


	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPagesOfOrgDepart(
		JNIEnv * env, jclass thisClass, jint jintOrgId, jobject joPageInfoIn,
		OUT jobject joOrgInfoArrayList, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		StDataPageInfo pageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, pageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<OrgInfo> departList;
		StDataPageInfo pageInfoOut;
		nRet = INetProtocol::instance()->getPagesOfOrgDepart(jintOrgId, pageInfoIn, departList, pageInfoOut);
		if (departList.empty()) {
			errorf("%s is empty", __FUNCTION__);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, departList, joOrgInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		nRet = JNICommon::setFieldValue(env, pageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getOrgMembers (
        JNIEnv *env, jclass thisClass, jint jniOrgId, OUT jobject jniOrgMemArrSize,
        OUT jobjectArray jniOrgMemArray) {
        tracef("%s in >>>", __FUNCTION__);

        jint nRet = -1;
        std::vector<OrgMemberInfo> orgMemberList;
        nRet = INetProtocol::instance()->getOrgMembers(jniOrgId, orgMemberList);

        if (orgMemberList.empty()) {
            errorf("%s is empty", __FUNCTION__);
            return nRet;
        }

        jclass jniOrgMemberInfoClass = env->FindClass(ORG_MEMBER_INFO_CLASS_NAME);
        if (!jniOrgMemberInfoClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID orgIdID = env->GetFieldID(jniOrgMemberInfoClass, "orgId", "I");
        jfieldID accountID = env->GetFieldID(jniOrgMemberInfoClass, "account", "Ljava/lang/String;");
        jfieldID nameID = env->GetFieldID(jniOrgMemberInfoClass, "name", "Ljava/lang/String;");
        jfieldID statusID = env->GetFieldID(jniOrgMemberInfoClass, "status", "I");
        jfieldID serialNumberID = env->GetFieldID(jniOrgMemberInfoClass, "serialNumber", "Ljava/lang/String;");
		jfieldID uuidID = env->GetFieldID(jniOrgMemberInfoClass, "uuid", "Ljava/lang/String;");
		jfieldID phoneID = env->GetFieldID(jniOrgMemberInfoClass, "phone", "Ljava/lang/String;");
        jmethodID orgMemberInfoConstructorID = env->GetMethodID(jniOrgMemberInfoClass, "<init>", "()V");

        int nOrgMemberInfoListSize = orgMemberList.size();
        int jniArrayLen = env->GetArrayLength(jniOrgMemArray);
        if (nOrgMemberInfoListSize > jniArrayLen) {
            warnf("MAYBE ARRAY IS SUB!!!");
        }
        int minLen = std::min(nOrgMemberInfoListSize, jniArrayLen);
        for (int i = 0; i < minLen; i++) {
            jobject joOrgMemberInfo = env->NewObject(jniOrgMemberInfoClass, orgMemberInfoConstructorID);
            env->SetIntField(joOrgMemberInfo, orgIdID, orgMemberList.at(i).orgId);

            jstring jstrAccount = env->NewStringUTF(orgMemberList.at(i).account.c_str());
            env->SetObjectField(joOrgMemberInfo, accountID, jstrAccount);
            jstring jstrName = env->NewStringUTF(orgMemberList.at(i).name.c_str());
            env->SetObjectField(joOrgMemberInfo, nameID, jstrName);
            env->SetIntField(joOrgMemberInfo, statusID, orgMemberList.at(i).status);
            jstring jstrSerialNumber = env->NewStringUTF(orgMemberList.at(i).serialNumber.c_str());
			env->SetObjectField(joOrgMemberInfo, serialNumberID, jstrSerialNumber);
			jstring jstrUuid = env->NewStringUTF(orgMemberList.at(i).uuid.c_str());
			env->SetObjectField(joOrgMemberInfo, uuidID, jstrUuid);
			jstring jstrPhone = env->NewStringUTF(orgMemberList.at(i).phone.c_str());
			env->SetObjectField(joOrgMemberInfo, phoneID, jstrPhone);

            env->SetObjectArrayElement(jniOrgMemArray, i, joOrgMemberInfo);
            env->DeleteLocalRef(jstrAccount);
            env->DeleteLocalRef(jstrUuid);
			env->DeleteLocalRef(jstrName);
			env->DeleteLocalRef(jstrPhone);
            env->DeleteLocalRef(jstrSerialNumber);
            env->DeleteLocalRef(joOrgMemberInfo);
        }

        env->DeleteLocalRef(jniOrgMemberInfoClass);

        // COMM_TYPE_CLASS_NAME
        jclass jniArrSizeClass = env->GetObjectClass(jniOrgMemArrSize);
        if (!jniArrSizeClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID arrSizeNumberID = env->GetFieldID(jniArrSizeClass, "number", "I");
        if (!arrSizeNumberID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

		env->DeleteLocalRef(jniArrSizeClass);

        env->SetIntField(jniOrgMemArrSize, arrSizeNumberID, minLen);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPagesOfOrgMember(
		JNIEnv * env, jclass thisClass, jint jintOrgId, jobject joPageInfoIn,
		OUT jobject joMemberInfoArrayList, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		StDataPageInfo pageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, pageInfoIn);

		std::vector<OrgMemberInfo> memberList;
		StDataPageInfo pageInfoOut;
		nRet = INetProtocol::instance()->getPagesOfOrgMember(jintOrgId, pageInfoIn, memberList, pageInfoOut);
		if (memberList.empty())
		{
			errorf("%s is empty", __FUNCTION__);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, memberList, joMemberInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		nRet = JNICommon::setFieldValue(env, pageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getOrgMemberRecursively(
		JNIEnv * env, jclass thisClass, jobject joDepartList, jobject joAccountList,
		OUT jobject joMemberInfoArrayList)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		std::vector<int> cppDepartList;
		std::vector<std::string> cppAccountList;

		nRet = JNICommon::getIntFieldValue<int>(env, joDepartList, cppDepartList);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}
		nRet = JNICommon::getFieldValue(env, joAccountList, cppAccountList);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<OrgMemberInfo> memberInfoList;
		nRet = INetProtocol::instance()->getOrgMemberRecursively(cppDepartList, cppAccountList, memberInfoList);
		if (nRet != 0)
		{
			errorf("%s failed", __FUNCTION__);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, memberInfoList, joMemberInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getFrequentContacts(
		JNIEnv * env, jclass thisClass, jobject joPageInfoIn,
		OUT jobject joMemberInfoArrayList, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		StDataPageInfo pageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, pageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<OrgMemberInfo> memberList;
		StDataPageInfo pageInfoOut;
		nRet = INetProtocol::instance()->getFrequentContacts(pageInfoIn, memberList, pageInfoOut);
		if (memberList.empty()) {
			errorf("%s is empty", __FUNCTION__);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, pageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, memberList, joMemberInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getMemberDetails(
		JNIEnv * env, jclass thisClass, jstring jstrAccount,
		OUT jobject joMemberInfo)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		const char* cppAccount = env->GetStringUTFChars(jstrAccount, NULL);
		OrgMemberInfo cppMemberInfo;
		nRet = INetProtocol::instance()->getMemberDetails(cppAccount, cppMemberInfo);
		env->ReleaseStringUTFChars(jstrAccount, cppAccount);
		if (nRet != 0) {
			errorf("%s failed", __FUNCTION__);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, cppMemberInfo, joMemberInfo);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateContact(
		JNIEnv * env, jclass thisClass, jobject joMemberInfo)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		OrgMemberInfo cppMemberInfo;
		nRet = JNICommon::getFieldValue(env, joMemberInfo, cppMemberInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		nRet = INetProtocol::instance()->updateContact(cppMemberInfo);
		if (nRet != 0) {
			errorf("%s failed", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_createGroup(
		JNIEnv * env, jclass thisClass, jstring jstrGroupName, jobjectArray jniContactList)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		const char* cppGroupName = env->GetStringUTFChars(jstrGroupName, NULL);

		std::vector<std::string> accountToList;
		int size = env->GetArrayLength(jniContactList);
		for (int i = 0; i < size; ++i)
		{
			jstring jstrAccountTo = (jstring)env->GetObjectArrayElement(jniContactList, i);
			const char *cppAccountTo = env->GetStringUTFChars(jstrAccountTo, NULL);

			accountToList.emplace_back(cppAccountTo);

			env->ReleaseStringUTFChars(jstrAccountTo, cppAccountTo);
			env->DeleteLocalRef(jstrAccountTo);
		}

		nRet = INetProtocol::instance()->createGroup(cppGroupName, accountToList);
		env->ReleaseStringUTFChars(jstrGroupName, cppGroupName);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_delGroup(
		JNIEnv * env, jclass thisClass, jint groupId)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		nRet = INetProtocol::instance()->delGroup(groupId);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateGroup(
		JNIEnv * env, jclass thisClass, jint jintGroupId, jstring jstrGroupName, jobjectArray jniContactList)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		const char* cppGroupName = env->GetStringUTFChars(jstrGroupName, NULL);

		std::vector<std::string> accountToList;
		int size = env->GetArrayLength(jniContactList);
		for (int i = 0; i < size; ++i)
		{
			jstring jstrAccountTo = (jstring)env->GetObjectArrayElement(jniContactList, i);
			const char *cppAccountTo = env->GetStringUTFChars(jstrAccountTo, NULL);

			accountToList.emplace_back(cppAccountTo);

			env->ReleaseStringUTFChars(jstrAccountTo, cppAccountTo);
			env->DeleteLocalRef(jstrAccountTo);
		}

		nRet = INetProtocol::instance()->updateGroup(jintGroupId, cppGroupName, accountToList);
		env->ReleaseStringUTFChars(jstrGroupName, cppGroupName);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getGroupList(
		JNIEnv * env, jclass thisClass, jint jintType, jobject joPageInfoIn,
		OUT jobject joGroupInfoArrayList, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		StDataPageInfo pageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, pageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<StChatGroup> cppGroupList;
		StDataPageInfo pageInfoOut;
		nRet = INetProtocol::instance()->getGroupList((EnGroupType)jintType, pageInfoIn, cppGroupList, pageInfoOut);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, cppGroupList, joGroupInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		nRet = JNICommon::setFieldValue(env, pageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getGroupMember(
		JNIEnv * env, jclass thisClass, jint jintGroupId, jobject joPageInfoIn,
		OUT jobject joMemberInfoArrayList, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		StDataPageInfo pageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, pageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<OrgMemberInfo> cppMemberList;
		StDataPageInfo pageInfoOut;
		nRet = INetProtocol::instance()->getGroupMember(jintGroupId, pageInfoIn, cppMemberList, pageInfoOut);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, cppMemberList, joMemberInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		nRet = JNICommon::setFieldValue(env, pageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateParticipantsOrder(
		JNIEnv *env, jclass thisClass, jobject joParticipantInfos) {
		tracef("%s in >>>", __FUNCTION__);

		std::vector<StParticipantInfo> cppParticipantInfos;
		JNICommon::getFieldArrayValue(env, joParticipantInfos, cppParticipantInfos);

		jint nRet = INetProtocol::instance()->updateParticipantsOrder(cppParticipantInfos);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_sendMessage (
        JNIEnv *env, jclass thisClass, jstring jniAccountTo, jstring jniReq,
        OUT jobject jniRsp) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniAccountTo == NULL || jniReq == NULL)
        {
          return nRet;
        }

        std::string rsp;

        const char *cppAccountTo = env->GetStringUTFChars(jniAccountTo, NULL);
        const char *cppReq = env->GetStringUTFChars(jniReq, NULL);
        nRet = INetProtocol::instance()->sendMessage(cppAccountTo, cppReq, rsp);
        env->ReleaseStringUTFChars(jniAccountTo, cppAccountTo);
        env->ReleaseStringUTFChars(jniReq, cppReq);
        if (nRet < 0) {
            errorf("SENDMESSAGE FAILED!!! ret:%d", nRet);
            return nRet;
        }

        // COMM_TYPE_CLASS_NAME
        jclass jniRspClass = env->GetObjectClass(jniRsp);
        if (!jniRspClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID rspStrID = env->GetFieldID(jniRspClass, "str", "Ljava/lang/String;");
        if (!rspStrID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        jstring jstrRsp = env->NewStringUTF(rsp.c_str());
        env->SetObjectField(jniRsp, rspStrID, jstrRsp);
        env->DeleteLocalRef(jniRspClass);
        env->DeleteLocalRef(jstrRsp);


        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_createMeeting(
		JNIEnv *env, jclass thisClass, jobject joStMeeting) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		StMeeting meetingInfo;

		nRet = JNICommon::getFieldValue(env, joStMeeting, meetingInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}

		nRet = INetProtocol::instance()->createMeeting(meetingInfo);
		if (nRet != 0)
		{
			errorf("CREATE MEETING FAILED!!!");
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, meetingInfo, joStMeeting);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;

	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_joinMeeting(
		JNIEnv *env, jclass thisClass, jobject joStMeeting, jobject joStMeetingAttribute) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		StMeeting meetingInfo;
		StMeetingAttribute attributeInfo;

		nRet = JNICommon::getFieldValue(env, joStMeeting, meetingInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}
		nRet = JNICommon::getFieldValue(env, joStMeetingAttribute, attributeInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}
		nRet = INetProtocol::instance()->joinMeeting(meetingInfo, attributeInfo);
		if (nRet != 0)
		{
			errorf("JOIN MEETING FAILED!!!");
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, meetingInfo, joStMeeting);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_leaveMeeting(
		JNIEnv *env, jclass thisClass, jobject joStMeeting) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		StMeeting meetingInfo;

		nRet = JNICommon::getFieldValue(env, joStMeeting, meetingInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}

		nRet = INetProtocol::instance()->leaveMeeting(meetingInfo);
		if (nRet != 0)
		{
			errorf("LEAVE MEETING FAILED!!!");
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, meetingInfo, joStMeeting);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_closeMeeting(
		JNIEnv *env, jclass thisClass, jobject joStMeeting) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		StMeeting meetingInfo;

		nRet = JNICommon::getFieldValue(env, joStMeeting, meetingInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}

		nRet = INetProtocol::instance()->closeMeeting(meetingInfo);
		if (nRet != 0)
		{
			errorf("CLOSE MEETING FAILED!!!");
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, meetingInfo, joStMeeting);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_publishVideo (
        JNIEnv *env, jclass thisClass, jint jniStreamType, jstring jniSdpOffer,
        jboolean jniVideoStatus, jboolean jniAudioStatus,
        OUT jobject jniSdpAnswer) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniSdpOffer == NULL)
        {
            return nRet;
        }

        //StStreamInfo streamInfo;
        std::string sdpAnswer;


        // JNI StreamInfo
  //      jclass jniParamClass = env->GetObjectClass(jniParam);
  //      if (!jniParamClass) {
  //          errorf("GET OBJECT CLASS FAILED!!!");
  //          return -1;
  //      }

  //      jfieldID idID = env->GetFieldID(jniParamClass, "id", "Ljava/lang/String;");
  //      jfieldID typeID = env->GetFieldID(jniParamClass, "type", "I");
  //      jfieldID hasVideoID = env->GetFieldID(jniParamClass, "hasVideo", "Z");
  //      jfieldID hasAudioID = env->GetFieldID(jniParamClass, "hasAudio", "Z");
		//jfieldID pushStreamStatusID = env->GetFieldID(jniParamClass, "pushStreamStatus", "I");
		//jfieldID pullStreamStatusID = env->GetFieldID(jniParamClass, "pullStreamStatus", "I");

  //      jstring jstrId = (jstring)env->GetObjectField(jniParam, idID);
  //      jint jiType = env->GetIntField(jniParam, typeID);
  //      jboolean jbHasVideo = env->GetBooleanField(jniParam, hasVideoID);
  //      jboolean jbHasAudio = env->GetBooleanField(jniParam, hasAudioID);
		//jint jiPushStreamStatus = env->GetIntField(jniParam, pushStreamStatusID);
		//jint jiPullStreamStatus = env->GetIntField(jniParam, pullStreamStatusID);

  //      const char *cppStrId = env->GetStringUTFChars(jstrId , NULL);
        const char *cppSdpOffer = env->GetStringUTFChars(jniSdpOffer , NULL);

  //      // CPP StreamInfo
  //      streamInfo.id = cppStrId;
  //      streamInfo.type = (EnStreamType)jiType;
  //      streamInfo.hasVideo = jbHasVideo;
  //      streamInfo.hasAudio = jbHasAudio;
		//streamInfo.pushStreamStatus = (EnStreamStatus)jiPushStreamStatus;
		//streamInfo.pullStreamStatus = (EnStreamStatus)jiPullStreamStatus;

        nRet = INetProtocol::instance()->publishVideo((EnStreamType)jniStreamType, cppSdpOffer, jniVideoStatus, jniAudioStatus, sdpAnswer);

        //env->ReleaseStringUTFChars(jstrId , cppStrId);
        env->ReleaseStringUTFChars(jniSdpOffer , cppSdpOffer);

        //env->DeleteLocalRef(jstrId);
       // env->DeleteLocalRef(jniParamClass);

        if (nRet != 0) {
            errorf("publishVideo FAILED!!!");
            return nRet;
        }

        // COMM_TYPE_CLASS_NAME
        jclass jniSdpAnswerClass = env->GetObjectClass(jniSdpAnswer);
        if (!jniSdpAnswerClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID sdpAnswerStrID = env->GetFieldID(jniSdpAnswerClass, "str", "Ljava/lang/String;");
        if (!sdpAnswerStrID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        jstring jstrSdpAnswer = env->NewStringUTF(sdpAnswer.c_str());
        env->SetObjectField(jniSdpAnswer, sdpAnswerStrID, jstrSdpAnswer);
        env->DeleteLocalRef(jstrSdpAnswer);
        env->DeleteLocalRef(jniSdpAnswerClass);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_stopPublishVideo (
        JNIEnv *env, jclass thisClass, jint jniStreamType) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        nRet = INetProtocol::instance()->stopPublishVideo((EnStreamType)jniStreamType);

        if (nRet != 0) {
            errorf("stopPublishVideo FAILED!!!");
            return nRet;
        }

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_stopReceiveVideo(
		JNIEnv *env, jclass thisClass, jstring jniAccount, jint jniStreamType) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		nRet = INetProtocol::instance()->stopReceiveVideo(
			JNICommon::getJStringValue(env, jniAccount),
			(EnStreamType)jniStreamType);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_receiveVideo (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jint jniStreamType,
        jstring jniSdpOffer, OUT jobject jniSdpAnswer) 
	{
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniAccount == NULL || jniSdpOffer == NULL)
        {
            return nRet;
        }

        std::string sdpAnswer;
        nRet = INetProtocol::instance()->receiveVideo(
			JNICommon::getJStringValue(env, jniAccount), 
			(EnStreamType)jniStreamType, 
			JNICommon::getJStringValue(env, jniSdpOffer), 
			sdpAnswer);

        if (nRet != 0) {
            errorf("receiveVideo FAILED!!!");
            return nRet;
        }

		JNICommon::setCommonTypeValue(env, sdpAnswer, jniSdpAnswer);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_createMediaChannel(
		JNIEnv *env, jclass thisClass, jstring jniSdpOffer, OUT jobject jniChannelId, OUT jobject jniChannelResponse)
	{
		tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniSdpOffer == NULL)
        {
            return nRet;
        }

        std::string channelId;
		std::string channelResponse;
        nRet = INetProtocol::instance()->createMediaChannel(JNICommon::getJStringValue(env, jniSdpOffer),channelId, channelResponse);
        if (nRet != 0) {
            errorf("createMediaChannel FAILED!!!");
            return nRet;
        }
		JNICommon::setCommonTypeValue(env, channelId, jniChannelId);
		JNICommon::setCommonTypeValue(env, channelResponse, jniChannelResponse);
        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_destroyMediaChannel(
        JNIEnv *env, jclass thisClass, jstring jniChannelId)
	{
		tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniChannelId == NULL)
        {
            return nRet;
        }
        nRet = INetProtocol::instance()->destroyMediaChannel(JNICommon::getJStringValue(env, jniChannelId));
        if (nRet != 0) {
            errorf("destroyMediaChannel FAILED!!!");
            return nRet;
        }
        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_addMediaTrack(
	JNIEnv *env, jclass thisClass, jobject joParams, OUT jobject joSdpAnswer,
	OUT jobject joFailedRsp)
	{

		tracef("%s in >>>", __FUNCTION__);

		jint nRet = -1;

		std::vector<StSubscribeStreamParam> cppParams;
		nRet = JNICommon::getFieldArrayValue(env, joParams, cppParams);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}
		std::vector<StSubscribeStreamResponse> cppSuccess;
		std::vector<StSubscribeStreamResponse> cppFailed;
		nRet = INetProtocol::instance()->addMediaTrack(cppParams, cppSuccess, cppFailed);
		if (nRet != 0)
		{
			errorf("%s failed", __FUNCTION__);
			return nRet;
		}
		
		nRet = JNICommon::setFieldArrayValue(env, cppSuccess, Subscribe_Stream_Response_CLASS_NAME, joSdpAnswer); //setFieldValue(env, cppSuccess, joSdpAnswer);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}
		nRet =  JNICommon::setFieldArrayValue(env, cppFailed, Subscribe_Stream_Response_CLASS_NAME, joFailedRsp);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_removeMediaTrack(
	JNIEnv *env, jclass thisClass, jstring jniAccount, jint jniStreamType, jobject jomediaTypes)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<EnMediaType> mediaTypeCpp;
		std::vector<int> mediaType;
		nRet = JNICommon::getIntFieldValue<int>(env, jomediaTypes, mediaType);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}
		for (int type: mediaType) {
			mediaTypeCpp.push_back((EnMediaType)type);
		}

		nRet = INetProtocol::instance()->removeMediaTrack(JNICommon::getJStringValue(env, jniAccount), (EnStreamType)jniStreamType, mediaTypeCpp); 
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}


	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPushStreamStatus(
		JNIEnv * env, jclass thisClass, jstring jstrAccount, jint jintStreamType, jint jintStatus)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		const char *cppAccount = env->GetStringUTFChars(jstrAccount, NULL);

		nRet = INetProtocol::instance()->setPushStreamStatus(cppAccount, (EnStreamType)jintStreamType, (EnStreamStatus)jintStatus);

		env->ReleaseStringUTFChars(jstrAccount, cppAccount);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPullStreamStatus(
		JNIEnv * env, jclass thisClass, jobject joParams, jint jintStatus)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<StMediaControlParam> cppParams;
		nRet = JNICommon::getFieldValue(env, joParams, cppParams);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}

		nRet = INetProtocol::instance()->setPullStreamStatus(cppParams, (EnStreamStatus)jintStatus);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_sendIceCandidate (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jint jniStreamType,
        jstring jniSdpMid, jstring jniSdpMLineIndex, jstring jniCandidate) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        const char *cppAccount = env->GetStringUTFChars(jniAccount, NULL);
        const char *cppSdpMid = env->GetStringUTFChars(jniSdpMid , NULL);
        const char *cppSdpMLineIndex = env->GetStringUTFChars(jniSdpMLineIndex, NULL);
        const char *cppCandidate = env->GetStringUTFChars(jniCandidate , NULL);
        nRet = INetProtocol::instance()->sendIceCandidate(cppAccount, (EnStreamType)jniStreamType, cppSdpMid,
                                                           cppSdpMLineIndex, cppCandidate);
        env->ReleaseStringUTFChars(jniAccount, cppAccount);
        env->ReleaseStringUTFChars(jniSdpMid, cppSdpMid);
        env->ReleaseStringUTFChars(jniSdpMLineIndex, cppSdpMLineIndex);
        env->ReleaseStringUTFChars(jniCandidate, cppCandidate);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setShareState(
		JNIEnv *env, jclass thisClass, jstring jniOperateAccount, jstring jniShareAccount, jboolean jniShareState) 
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		 
		nRet = INetProtocol::instance()->setShareState(
			JNICommon::getJStringValue(env, jniOperateAccount),
			JNICommon::getJStringValue(env, jniShareAccount),
			jniShareState);
		if (nRet != 0) {
			errorf("SET SHARE STATE FAILED!!! ret:%d", nRet);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getMeetingInfo(
		JNIEnv *env, jclass thisClass, jobject joStMeeting)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		StMeeting meetingInfo;

		nRet = INetProtocol::instance()->getMeetingInfo(meetingInfo);
		if (nRet != 0) {
			errorf("GET MEETINGINFO FAILED!!! ret:%d", nRet);
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, meetingInfo, joStMeeting);
		if (nRet != 0) {
			errorf("setFieldValue FAILED!!!");
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setMeetingInfo(
		JNIEnv *env, jclass thisClass, jint jintOption, jobject joMeetingInfo)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StMeeting cppMeetingInfo;
		nRet = JNICommon::getFieldValue(env, joMeetingInfo, cppMeetingInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}
		nRet = INetProtocol::instance()->setMeetingInfo((EnMeetingInfoOption)jintOption, cppMeetingInfo);
		if (nRet != 0) {
			errorf("%s FAILED!!!", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllPublishers(
		JNIEnv *env, jclass thisClass, OUT jobject joPartInfoArrayList, OUT jobject joStParticipantInfo_lecturer,
		OUT jobject joStParticipantInfo_partShared) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<StParticipantInfo> participantList;
		StParticipantInfo lecturer;
		StParticipantInfo partShared;
		nRet = INetProtocol::instance()->getAllPublishers(participantList, lecturer, partShared);
		if (nRet != 0)
		{
			errorf("GET ALL PUBLISHERS FAILED!!! ret:%d", nRet);
			return nRet;
		}

		nRet = JNICommon::setFieldArrayValue(env, participantList, STPARTICIPANTINFO_INFO_CLASS_NAME, joPartInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, lecturer, joStParticipantInfo_lecturer);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, partShared, joStParticipantInfo_partShared);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getParticipantByName(
		JNIEnv *env, jclass thisClass, jstring jstrName, OUT jobject joPartInfoArrayList) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<StParticipantInfo> participantList;
		nRet = INetProtocol::instance()->getParticipantByName(
			JNICommon::getJStringValue(env, jstrName),
			participantList);
		if (nRet != 0)
		{
			errorf("Get participants by name FAILED!!! ret:%d", nRet);
			return nRet;
		}

		nRet = JNICommon::setFieldArrayValue(env, participantList, STPARTICIPANTINFO_INFO_CLASS_NAME, joPartInfoArrayList);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPartOfParticpantWhoRaiseHand(
		JNIEnv *env, jclass thisClass, OUT jobject joStPartInfoArrayList)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<StParticipantInfo> participantList;
		nRet = INetProtocol::instance()->getPartOfParticpantWhoRaiseHand(participantList);
		if (nRet != 0)
		{
			errorf("GET ALL PUBLISHERS FAILED!!! ret:%d", nRet);
			return nRet;
		}
		nRet = JNICommon::setFieldArrayValue(env, participantList, STPARTICIPANTINFO_INFO_CLASS_NAME, joStPartInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllPollers(
        JNIEnv *env, jclass thisClass, OUT jobject joStringArrayList)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<std::string> pollerList;
		nRet = INetProtocol::instance()->getAllPollers(pollerList);
		if (nRet != 0)
		{
			errorf("GET ALL PUBLISHERS FAILED!!! ret:%d", nRet);
			return nRet;
		}

        jclass jniCommonTypeClass = env->FindClass(COMM_TYPE_CLASS_NAME);
        if (jniCommonTypeClass == NULL) {
            errorf("FIND CLASS FAILED!!!");
            return nRet;
		}
		jmethodID constructorID = env->GetMethodID(jniCommonTypeClass, "<init>", "()V");

		for (auto poller : pollerList)
		{
            jobject joPoller = env->NewObject(jniCommonTypeClass, constructorID);

			JNICommon::setCommonTypeValue(env, poller, joPoller);
			JNICommon::addEleIntoArrayList(env, joStringArrayList, joPoller);
			
            env->DeleteLocalRef(joPoller);
		}

		env->DeleteLocalRef(jniCommonTypeClass);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllParticipantsHaveNotJoined(
		JNIEnv * env, jclass thisClass, OUT jobject joStPartInfoArrayList)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<StParticipantInfo> participantList;
		nRet = INetProtocol::instance()->getAllParticipantsHaveNotJoined(participantList);
		if (nRet != 0)
		{
			errorf("GET ALL PARTICIPANTS HAVE NOT JOINED FAILED!!! ret:%d", nRet);
			return nRet;
		}

		nRet = JNICommon::setFieldArrayValue(env, participantList, STPARTICIPANTINFO_INFO_CLASS_NAME, joStPartInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPagesOfParticipants(
		JNIEnv *env, jclass thisClass, jint jintOrder, jint jintCountOfParticipant,
		jboolean jniIsPositiveSequence, OUT jobject joStPartInfoArrayList)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		std::vector<StParticipantInfo> participantList;
		nRet = INetProtocol::instance()->getPagesOfParticipants(jintOrder, jintCountOfParticipant, jniIsPositiveSequence, participantList);
		if (nRet != 0)
		{
			errorf("GET PAGES OF  PARTICIPANTS  FAILED!!! ret:%d", nRet);
			return nRet;
		}
		nRet = JNICommon::setFieldArrayValue(env, participantList, STPARTICIPANTINFO_INFO_CLASS_NAME, joStPartInfoArrayList);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_delParticipantHaveNotJoined(
		JNIEnv * env, jclass thisClass, jobject joAccountList)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<std::string> accounts;
		JNICommon::getFieldValue(env, joAccountList, accounts);
		nRet = INetProtocol::instance()->delParticipantHaveNotJoined(accounts);
		if (nRet != 0)
		{
			errorf("DEL PARTICIPANTS FAILED!!! ret:%d", nRet);
			return nRet;
		}

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getParticipant(
		JNIEnv *env, jclass thisClass, jstring jstrAccount, OUT jobject jniStPartInfo)
	{
		tracef("%s in >>>", __FUNCTION__);

		StParticipantInfo participantInfo;
		jint nRet = INetProtocol::instance()->getParticipant(
			JNICommon::getJStringValue(env, jstrAccount), 
			participantInfo);

		nRet = JNICommon::setFieldValue(env, participantInfo, jniStPartInfo);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getSubscriber(
		JNIEnv *env, jclass thisClass, jstring jstrAccount, OUT jobject jniStPartInfo)
	{
		tracef("%s in >>>", __FUNCTION__);

		StParticipantInfo participantInfo;
		jint nRet = INetProtocol::instance()->getSubscriber(
			JNICommon::getJStringValue(env, jstrAccount),
			participantInfo);

		nRet = JNICommon::setFieldValue(env, participantInfo, jniStPartInfo);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_debugTerminateNet(
		JNIEnv *env, jclass thisClass, jstring jniAccount) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		if (jniAccount == NULL)
		{
			return nRet;
		}
		nRet = INetProtocol::instance()->debugTerminateNet();

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_debugConvertSFU2MCU(
		JNIEnv *env, jclass thisClass) {
		tracef("%s in >>>", __FUNCTION__);

		jint nRet = INetProtocol::instance()->debugConvertSFU2MCU();

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_inviteParticipant(
		JNIEnv *env, jclass thisClass, jstring jniRoomId, jobjectArray jniAccountToList, jlong expireTime) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		if (jniRoomId == NULL)
		{
			errorf("%s jniRoomId is NULL >>>", __FUNCTION__);
			return nRet;
		}
		const char *cppRoomId = env->GetStringUTFChars(jniRoomId, NULL);

		std::vector<std::string> accountToList;
		int jniAccountToListSize = env->GetArrayLength(jniAccountToList);
		for (int i = 0; i < jniAccountToListSize; i++)
		{
			jstring jstrAccountTo = (jstring)env->GetObjectArrayElement(jniAccountToList, i);
			const char *cppAccountTo = env->GetStringUTFChars(jstrAccountTo, NULL);
			accountToList.emplace_back(cppAccountTo);
			env->ReleaseStringUTFChars(jstrAccountTo, cppAccountTo);
			env->DeleteLocalRef(jstrAccountTo);
		}

		nRet = INetProtocol::instance()->inviteParticipant(cppRoomId, accountToList, expireTime);
		if (nRet != 0) {
			errorf("inviteParticipant error");
			return nRet;
		}

		env->ReleaseStringUTFChars(jniRoomId, cppRoomId);
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_cancelInvite (
        JNIEnv *env, jclass thisClass, jstring jniRoomId, jobjectArray jniAccountToList) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
		if (jniRoomId == NULL)
		{
			errorf("%s jniRoomId is NULL >>>", __FUNCTION__);
			return nRet;
		}
		const char *cppRoomId = env->GetStringUTFChars(jniRoomId, NULL);

        std::vector<std::string> accountToList;
        int jniAccountToListSize = env->GetArrayLength(jniAccountToList);
        for (int i = 0; i < jniAccountToListSize; i++)
        {
            jstring jstrAccountTo = (jstring)env->GetObjectArrayElement(jniAccountToList, i);
            const char *cppAccountTo = env->GetStringUTFChars(jstrAccountTo, NULL);
            accountToList.emplace_back(cppAccountTo);
            env->ReleaseStringUTFChars(jstrAccountTo , cppAccountTo);
            env->DeleteLocalRef(jstrAccountTo);
        }

        nRet = INetProtocol::instance()->cancelInvite(cppRoomId, accountToList);
		
		env->ReleaseStringUTFChars(jniRoomId, cppRoomId);
        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_ringing (
        JNIEnv *env, jclass thisClass, jstring jniRoomId, jstring jniAccountTo) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniRoomId == NULL || jniAccountTo == NULL)
        {
			errorf("%s jniRoomId or jniAccountTo is NULL >>>", __FUNCTION__);
			return nRet;
        }

        const char *cppRoomId = env->GetStringUTFChars(jniRoomId , NULL);
        const char *cppAccountTo = env->GetStringUTFChars(jniAccountTo, NULL);
        nRet = INetProtocol::instance()->ringing(cppRoomId, cppAccountTo);
        env->ReleaseStringUTFChars(jniRoomId , cppRoomId);
        env->ReleaseStringUTFChars(jniAccountTo, cppAccountTo);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_refuseInvite (
        JNIEnv *env, jclass thisClass, jstring jniRoomId, jstring jniAccountTo, jint reason) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        if (jniRoomId == NULL || jniAccountTo == NULL)
        {
			errorf("%s jniRoomId or jniAccountTo is NULL >>>", __FUNCTION__);
			return nRet;
        }

        const char *cppRoomId = env->GetStringUTFChars(jniRoomId , NULL);
        const char *cppAccountTo = env->GetStringUTFChars(jniAccountTo, NULL);
        nRet = INetProtocol::instance()->refuseInvite(cppRoomId, cppAccountTo, (EnRefuseInviteReason)reason);
        env->ReleaseStringUTFChars(jniRoomId , cppRoomId);
        env->ReleaseStringUTFChars(jniAccountTo, cppAccountTo);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_switchVideo (
        JNIEnv *env, jclass thisClass, jobjectArray jniAccountToList, jboolean jniAction) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        std::vector<std::string> accountToList;

        int jniAccountToListSize = env->GetArrayLength(jniAccountToList);
        for (int i = 0; i < jniAccountToListSize; i++)
        {
            jstring jstrAccountTo = (jstring)env->GetObjectArrayElement(jniAccountToList, i);
            const char *cppAccountTo = env->GetStringUTFChars(jstrAccountTo, NULL);
            accountToList.emplace_back(cppAccountTo);
            infof("account:%s", cppAccountTo);
            env->ReleaseStringUTFChars(jstrAccountTo , cppAccountTo);
            env->DeleteLocalRef(jstrAccountTo);
        }

        nRet = INetProtocol::instance()->switchVideo(accountToList, jniAction);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_switchAudioIn (
        JNIEnv *env, jclass thisClass, jobjectArray jniAccountToList, jboolean jniAction) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        std::vector<std::string> accountToList;

        int jniAccountToListSize = env->GetArrayLength(jniAccountToList);
        for (int i = 0; i < jniAccountToListSize; i++)
        {
            jstring jstrAccountTo = (jstring)env->GetObjectArrayElement(jniAccountToList, i);
            const char *cppAccountTo = env->GetStringUTFChars(jstrAccountTo, NULL);
            accountToList.emplace_back(cppAccountTo);
            infof("account:%s", cppAccountTo);
            env->ReleaseStringUTFChars(jstrAccountTo , cppAccountTo);
            env->DeleteLocalRef(jstrAccountTo);
        }

        nRet = INetProtocol::instance()->switchAudioIn(accountToList, jniAction);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_switchAudioOut (
        JNIEnv *env, jclass thisClass, jobjectArray jniAccountToList, jboolean jniAction) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        std::vector<std::string> accountToList;

        int jniAccountToListSize = env->GetArrayLength(jniAccountToList);
        for (int i = 0; i < jniAccountToListSize; i++)
        {
            jstring jstrAccountTo = (jstring)env->GetObjectArrayElement(jniAccountToList, i);
            const char *cppAccountTo = env->GetStringUTFChars(jstrAccountTo, NULL);
            accountToList.emplace_back(cppAccountTo);
            env->ReleaseStringUTFChars(jstrAccountTo , cppAccountTo);
            env->DeleteLocalRef(jstrAccountTo);
        }

        nRet = INetProtocol::instance()->switchAudioOut(accountToList, jniAction);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setSpeakerPermission(
		JNIEnv * env, jclass thisClass, jstring jniRoomId, jboolean jniPermitted)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (jniRoomId == NULL)
		{
			errorf("roomId is NULL");
			return nRet;
		}

		const char* cppRoomId = env->GetStringUTFChars(jniRoomId, NULL);

		nRet = INetProtocol::instance()->setSpeakerPermission(cppRoomId, jniPermitted);

		env->ReleaseStringUTFChars(jniRoomId, cppRoomId);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_applyOpenSpeaker(
		JNIEnv * env, jclass thisClass)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		nRet = INetProtocol::instance()->applyOpenSpeaker();

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_applyOpenMic(
		JNIEnv * env, jclass thisClass)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		nRet = INetProtocol::instance()->applyOpenMic();

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setHandStatus(
		JNIEnv *env, jclass thisClass, jobjectArray jniAccountToList, jboolean jbStatus)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<std::string> accountToList;

		int jniAccountToListSize = env->GetArrayLength(jniAccountToList);
		for (int i = 0; i < jniAccountToListSize; i++)
		{
			jstring jstrAccountTo = (jstring)env->GetObjectArrayElement(jniAccountToList, i);
			accountToList.emplace_back(JNICommon::getJStringValue(env, jstrAccountTo));
			env->DeleteLocalRef(jstrAccountTo);
		}

		nRet = INetProtocol::instance()->setHandStatus(accountToList, jbStatus);
		if (nRet != 0)
		{
			errorf("SET HAND STATUS FAILED!!! ret:%d", nRet);
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getRoomSettings (
        JNIEnv *env, jclass thisClass, OUT jobject jniCapacity) 
	{
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        int nCapacity = 0;

        nRet = INetProtocol::instance()->getRoomSettings(nCapacity);
        if (nRet != 0) {
            warnf("getRoomSettings failed.");
        }

		JNICommon::setCommonTypeValue(env, nCapacity, jniCapacity);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getH5Pages (
        JNIEnv *env, jclass thisClass, jint jniH5PageType,
        OUT jobject joH5PageInfoList) 
	{
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        std::vector<H5PageInfo> h5pageInfoList;

        nRet = INetProtocol::instance()->getH5Pages((EnH5PageType)jniH5PageType, h5pageInfoList);
        if (nRet != 0) {
            warnf("getH5Pages failed.");
			return nRet;
		}

        jclass jniH5PageInfoClass = env->FindClass(H5_PAGE_INFO_CLASS_NAME);
        if (jniH5PageInfoClass == NULL) {
            errorf("FIND CLASS FAILED!!!");
            return nRet;
		}
		jfieldID typeID = env->GetFieldID(jniH5PageInfoClass, "type", "I");
		jfieldID urlID = env->GetFieldID(jniH5PageInfoClass, "url", "Ljava/lang/String;");
		jmethodID constructorID = env->GetMethodID(jniH5PageInfoClass, "<init>", "()V");

        for (auto cppH5pageInfo : h5pageInfoList)
        {
            jobject joH5PageInfo = env->NewObject(jniH5PageInfoClass, constructorID);

            jstring jstrUrl = env->NewStringUTF(cppH5pageInfo.url.c_str());

			env->SetObjectField(joH5PageInfo, urlID, jstrUrl);
			env->SetIntField(joH5PageInfo, typeID, cppH5pageInfo.type);

			JNICommon::addEleIntoArrayList(env, joH5PageInfoList, joH5PageInfo);

            env->DeleteLocalRef(jstrUrl);
            env->DeleteLocalRef(joH5PageInfo);
        }

        env->DeleteLocalRef(jniH5PageInfoClass);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getH5PagesByHttp(
		JNIEnv *env, jclass thisClass, jint jniH5PageType,
		OUT jobject joH5PageInfoList) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;
		std::vector<H5PageInfo> h5pageInfoList;

		nRet = INetProtocol::instance()->getH5PagesByHttp((EnH5PageType)jniH5PageType, h5pageInfoList);
		if (nRet != 0) {
			warnf("getH5Pages failed.");
		}

		jclass jniH5PageInfoClass = env->FindClass(H5_PAGE_INFO_CLASS_NAME);
		if (jniH5PageInfoClass == NULL) {
			errorf("FIND CLASS FAILED!!!");
			return nRet;
		}
		jfieldID typeID = env->GetFieldID(jniH5PageInfoClass, "type", "I");
		jfieldID urlID = env->GetFieldID(jniH5PageInfoClass, "url", "Ljava/lang/String;");
		jmethodID constructorID = env->GetMethodID(jniH5PageInfoClass, "<init>", "()V");

		for (auto cppH5pageInfo : h5pageInfoList)
		{
			jobject joH5PageInfo = env->NewObject(jniH5PageInfoClass, constructorID);

			jstring jstrUrl = env->NewStringUTF(cppH5pageInfo.url.c_str());

			env->SetObjectField(joH5PageInfo, urlID, jstrUrl);
			env->SetIntField(joH5PageInfo, typeID, cppH5pageInfo.type);

			JNICommon::addEleIntoArrayList(env, joH5PageInfoList, joH5PageInfo);

			env->DeleteLocalRef(jstrUrl);
			env->DeleteLocalRef(joH5PageInfo);
		}

		env->DeleteLocalRef(jniH5PageInfoClass);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_loginAsVisitor(
        JNIEnv *env, jclass thisClass, jstring jniUsername, jstring jniMac, 
		OUT jobject jniAccount,  OUT jobject jniServerTime) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (NULL == jniUsername) {
            errorf("input username is null");
            return nRet;
        }

        if (NULL == jniMac)
        {
            errorf("input mac is null");
            return nRet;
        }

        std::string account;
        long long serverTime = 0;
        nRet = INetProtocol::instance()->loginAsVisitor(
			JNICommon::getJStringValue(env, jniUsername), 
			JNICommon::getJStringValue(env, jniMac), 
			account, serverTime);
        if (nRet != 0) {
            warnf("loginAsVisitor failed.");
            return nRet;
        }
		
		JNICommon::setCommonTypeValue(env, account, jniAccount);
		JNICommon::setCommonTypeValue(env, serverTime, jniServerTime);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }


    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_resetPassword (
        JNIEnv *env, jclass thisClass, jstring jniAccount, jstring jniValidateCode, jstring jniNewPassword) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (NULL == jniAccount) {
            errorf("input account is null");
            return nRet;
        }

        if (NULL == jniValidateCode)
        {
            errorf("input validateCode is null");
            return nRet;
        }

        if (NULL == jniNewPassword)
        {
            errorf("input newPassWord is null");
            return nRet;
        }

        const char *cppAccount = env->GetStringUTFChars(jniAccount, NULL);
        const char *cppValidateCode = env->GetStringUTFChars(jniValidateCode, NULL);
        const char *cppNewPassword = env->GetStringUTFChars(jniNewPassword, NULL);
        nRet = INetProtocol::instance()->resetPassword(cppAccount, cppValidateCode, cppNewPassword);
        env->ReleaseStringUTFChars(jniAccount, cppAccount);
        env->ReleaseStringUTFChars(jniValidateCode, cppValidateCode);
        env->ReleaseStringUTFChars(jniNewPassword, cppNewPassword);
        if (nRet != 0) {
            warnf("resetPassword failed.");
            return nRet;
        }

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAppointedMeetingRoom(
		JNIEnv * env, jclass thisClass, jstring jstrRoomId, OUT jobject joMeetingRoom, OUT jobject joRuid)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::string cppRoomId = JNICommon::getJStringValue(env, jstrRoomId);
		StMeetingRoom cppMeetingRoom;
		std::string cppRuid;
		nRet = INetProtocol::instance()->getAppointedMeetingRoom(cppRoomId, cppMeetingRoom, cppRuid);
		if (nRet != 0) {
			errorf("GET APPOINTED MEETING ROOMS FAILED!!!");
			return nRet;
		}

		nRet &= JNICommon::setFieldValue(env, cppMeetingRoom, joMeetingRoom);
		nRet &= JNICommon::setCommonTypeValue(env, cppRuid, joRuid);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getMeetSimplify(
		JNIEnv *env, jclass thisClass, jstring jstrRuid, OUT jobject joMeeting)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::string cppRuid = JNICommon::getJStringValue(env, jstrRuid);
		StMeeting cppMeet;
		nRet = INetProtocol::instance()->getMeetSimplify(cppRuid, cppMeet);
		if (nRet != 0) {
			errorf("GET RoomInfoSimplify FAILED!!!");
			return nRet;
		}

		nRet &= JNICommon::setFieldValue(env, cppMeet, joMeeting);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllMeetingRooms(
		JNIEnv * env, jclass thisClass, jobject joPageInfoIn, jboolean jbIfLimitedByPermission,
		OUT jobject joAllMeetingRooms, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StDataPageInfo cppPageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, cppPageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}
		StAllMeetingRooms cppMeetingRooms;
		StDataPageInfo cppPageInfoOut;

		nRet = INetProtocol::instance()->getAllMeetingRooms(cppPageInfoIn, jbIfLimitedByPermission, cppMeetingRooms, cppPageInfoOut);
		if (nRet != 0) {
			errorf("GET ALL MEETING ROOMS FAILED!!!");
			return nRet;
		}

		nRet = JNICommon::setFieldValue(env, cppMeetingRooms, joAllMeetingRooms);

		nRet = JNICommon::setFieldValue(env, cppPageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_createAppointConference(
		JNIEnv *env, jclass thisClass, jobject jniParam)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (NULL == jniParam) {
			errorf("input conferenceInfo is null");
			return nRet;
		}
		StAppointConference conferenceInfo;
		nRet = JNICommon::getFieldValue(env, jniParam, conferenceInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}
		nRet = INetProtocol::instance()->createAppointConference(conferenceInfo);
		if (nRet != 0) {
			errorf("CREATE APPOINT CONFERENCE FAILED!!!");
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, conferenceInfo, jniParam);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updateAppointConference(
		JNIEnv *env, jclass thisClass, jobject jniParam)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (NULL == jniParam) {
			errorf("input conferenceInfo is null");
			return nRet;
		}
		StAppointConference conferenceInfo;
		nRet = JNICommon::getFieldValue(env, jniParam, conferenceInfo);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return nRet;
		}
		nRet = INetProtocol::instance()->updateAppointConference(conferenceInfo);
		if (nRet != 0) {
			errorf("UPDATE APPOINT CONFERENCE FAILED!!!");
			return nRet;
		}
		nRet = JNICommon::setFieldValue(env, conferenceInfo, jniParam);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_cancelAppointConference(
		JNIEnv *env, jclass thisClass, jstring jniRuid)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (jniRuid == NULL)
		{
			return nRet;
		}

		std::string cppRuid = JNICommon::getJStringValue(env, jniRuid);
		nRet = INetProtocol::instance()->cancelAppointConference(cppRuid);
		if (nRet != 0)
		{
			errorf("CANCEL APPOINT CONFERENCE FAIELD.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_deleteAppointConference(
		JNIEnv *env, jclass thisClass, jstring jniRuid)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (jniRuid == NULL)
		{
			return nRet;
		}

		std::string cppRuid = JNICommon::getJStringValue(env, jniRuid);
		nRet = INetProtocol::instance()->deleteAppointConference(cppRuid);
		if (nRet != 0)
		{
			errorf("DELETE APPOINT CONFERENCE FAIELD.");
			return nRet;
		}
		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllConferenceSummary(
		JNIEnv * env, jclass thisClass, jint jniStatus, jstring jstrDate, jobject joPageInfoIn,
		OUT jobject joSummaries, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StDataPageInfo cppPageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, cppPageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<StAppointConference> cppSummaries;
		StDataPageInfo cppPageInfoOut;
		std::string cppDate = JNICommon::getJStringValue(env, jstrDate);
		nRet = INetProtocol::instance()->getAllConferenceSummary((EnConferenceStatus)jniStatus, cppDate, cppPageInfoIn, cppSummaries, cppPageInfoOut);
		if (nRet != 0)
		{
			errorf("getAllConferenceSummary failed.");
			return nRet;
		}

		nRet = JNICommon::setFieldArrayValue<StAppointConference>(env, cppSummaries, STAPPOINT_CONFERENCE_CLASS_NAME, joSummaries);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		nRet = JNICommon::setFieldValue(env, cppPageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllConferenceSummaryOfPeriodOfTime(
		JNIEnv * env, jclass thisClass, jint jniStatus, jstring jstrStartDate, jstring jstrEndDate, jobject joPageInfoIn,
		OUT jobject joSummaries, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StDataPageInfo cppPageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, cppPageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<StAppointConference> cppSummaries;
		StDataPageInfo cppPageInfoOut;
		std::string cppStartDate = JNICommon::getJStringValue(env, jstrStartDate);
		std::string cppEndDate = JNICommon::getJStringValue(env, jstrEndDate);
		nRet = INetProtocol::instance()->getAllConferenceSummaryOfPeriodOfTime(
            (EnConferenceStatus)jniStatus, cppStartDate, cppEndDate, cppPageInfoIn, cppSummaries, cppPageInfoOut);
		if (nRet != 0)
		{
			errorf("getAllConferenceSummaryOfPeriodOfTime failed.");
			return nRet;
		}

		nRet = JNICommon::setFieldArrayValue<StAppointConference>(env, cppSummaries, STAPPOINT_CONFERENCE_CLASS_NAME, joSummaries);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		nRet = JNICommon::setFieldValue(env, cppPageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAllConferenceSummaryOfSpecifiedRoom(
		JNIEnv *env, jclass thisClass, jstring jstrRoomId, jobject joPageInfoIn,
		OUT jobject joSummaries, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StDataPageInfo cppPageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, cppPageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<StAppointConference> cppSummaries;
		StDataPageInfo cppPageInfoOut;
		std::string cppRoomId = JNICommon::getJStringValue(env, jstrRoomId);
		nRet = INetProtocol::instance()->getAllConferenceSummaryOfSpecifiedRoom(
            cppRoomId, cppPageInfoIn, cppSummaries, cppPageInfoOut);
		if (nRet != 0)
		{
			errorf("getAllConferenceSummaryOfSpecifiedRoom failed.");
			return nRet;
		}

		nRet = JNICommon::setFieldArrayValue<StAppointConference>(env, cppSummaries, STAPPOINT_CONFERENCE_CLASS_NAME, joSummaries);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		nRet = JNICommon::setFieldValue(env, cppPageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAppointConferenceDetails(
		JNIEnv *env, jclass thisClass, jstring jniRuid, OUT jobject joStAppointConferenceInfo, OUT jobject joIsStart)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (jniRuid == NULL || joStAppointConferenceInfo == NULL || joIsStart == NULL)
		{
			return nRet;
		}

		const char *cppRuid = env->GetStringUTFChars(jniRuid, NULL);
		StAppointConference cppStAppointConferenceInfo;
		bool isStart = false;
		nRet = INetProtocol::instance()->getAppointConferenceDetails(cppRuid, cppStAppointConferenceInfo, isStart);
		env->ReleaseStringUTFChars(jniRuid, cppRuid);
		if (nRet != 0)
		{
			errorf("GET APPOINT CONFERENCE DETAILS FAILED.");
			return nRet;
		}

		JNICommon::setFieldValue(env, cppStAppointConferenceInfo, joStAppointConferenceInfo);

		jclass commonTypeClass = env->GetObjectClass(joIsStart);
		if (commonTypeClass == NULL)
		{
			errorf("GET OBJECT CLASS FAILED.");
			return nRet;
		}
		jfieldID isStartId = env->GetFieldID(commonTypeClass, "boolVar", "Z");
		env->SetBooleanField(joIsStart, isStartId, isStart);
		env->DeleteLocalRef(commonTypeClass);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPersonalConfRoomInfo (
        JNIEnv *env, jclass thisClass, OUT jobject jniParams) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        ConfRoomInfo confRoomInfoList;
        nRet = INetProtocol::instance()->getPersonalConfRoomInfo(confRoomInfoList);
        if (nRet != 0)
        {
            return nRet;
        }

        jclass jniConfRoomInfoClass = env->GetObjectClass(jniParams);
        if (!jniConfRoomInfoClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return nRet;
        }

        jfieldID userID = env->GetFieldID(jniConfRoomInfoClass, "userId", "I");
        jfieldID idID = env->GetFieldID(jniConfRoomInfoClass, "id", "I");
        jfieldID roomSubjectID = env->GetFieldID(jniConfRoomInfoClass, "roomSubject", "Ljava/lang/String;");
        jfieldID roomIdID = env->GetFieldID(jniConfRoomInfoClass, "roomId", "Ljava/lang/String;");
        jfieldID roomCapacityID = env->GetFieldID(jniConfRoomInfoClass, "roomCapacity", "I");
        jfieldID passwordID = env->GetFieldID(jniConfRoomInfoClass, "password", "Ljava/lang/String;");
        jfieldID moderatorPasswordID = env->GetFieldID(jniConfRoomInfoClass, "moderatorPassword", "Ljava/lang/String;");
        jfieldID micStatusID = env->GetFieldID(jniConfRoomInfoClass, "micStatus", "Ljava/lang/String;");
        jfieldID videoStatusID = env->GetFieldID(jniConfRoomInfoClass, "videoStatus", "Ljava/lang/String;");
        jfieldID sharePowerID = env->GetFieldID(jniConfRoomInfoClass, "sharePower", "Ljava/lang/String;");
        jfieldID allowPartOperMicID = env->GetFieldID(jniConfRoomInfoClass, "allowPartOperMic", "Ljava/lang/String;");
        jfieldID allowPartOperShareID = env->GetFieldID(jniConfRoomInfoClass, "allowPartOperShare", "Ljava/lang/String;");

        env->SetIntField(jniParams, userID, confRoomInfoList.userId);
        env->SetIntField(jniParams, idID, confRoomInfoList.id);
        jstring jstrRoomSubject = env->NewStringUTF(confRoomInfoList.roomSubject.c_str());
        env->SetObjectField(jniParams, roomSubjectID, jstrRoomSubject);
        jstring jstrRoomId = env->NewStringUTF(confRoomInfoList.roomId.c_str());
        env->SetObjectField(jniParams, roomIdID, jstrRoomId);
        env->SetIntField(jniParams, roomCapacityID, confRoomInfoList.roomCapacity);
        jstring jstrPassword = env->NewStringUTF(confRoomInfoList.password.c_str());
        env->SetObjectField(jniParams, passwordID, jstrPassword);
        jstring jstrModeratorPassword = env->NewStringUTF(confRoomInfoList.moderatorPassword.c_str());
        env->SetObjectField(jniParams, moderatorPasswordID, jstrModeratorPassword);
        jstring jstrMicStatus = env->NewStringUTF(confRoomInfoList.micStatus.c_str());
        env->SetObjectField(jniParams, micStatusID, jstrMicStatus);
        jstring jstrVideoStatus = env->NewStringUTF(confRoomInfoList.videoStatus.c_str());
        env->SetObjectField(jniParams, videoStatusID, jstrVideoStatus);
        jstring jstrSharePower = env->NewStringUTF(confRoomInfoList.sharePower.c_str());
        env->SetObjectField(jniParams, sharePowerID, jstrSharePower);
        jstring jstrAllowPartOperMic = env->NewStringUTF(confRoomInfoList.allowPartOperMic.c_str());
        env->SetObjectField(jniParams, allowPartOperMicID, jstrAllowPartOperMic);
        jstring jstrAllowPartOperShare = env->NewStringUTF(confRoomInfoList.allowPartOperShare.c_str());
        env->SetObjectField(jniParams, allowPartOperShareID, jstrAllowPartOperShare);

        env->DeleteLocalRef(jstrRoomSubject);
        env->DeleteLocalRef(jstrRoomId);
        env->DeleteLocalRef(jstrPassword);
        env->DeleteLocalRef(jstrModeratorPassword);
        env->DeleteLocalRef(jstrMicStatus);
        env->DeleteLocalRef(jstrVideoStatus);
        env->DeleteLocalRef(jstrSharePower);
        env->DeleteLocalRef(jstrAllowPartOperMic);
        env->DeleteLocalRef(jstrAllowPartOperShare);

        env->DeleteLocalRef(jniConfRoomInfoClass);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_updatePersonalConfRoomInfo(
        JNIEnv *env, jclass thisClass, jobject jniParam)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        ConfRoomInfo roomInfo;
        if (!jniParam)
        {
            errorf("input param is null.");
            return -1;
        }

        // JNI BasicInfo
        jclass jniParamClass = env->GetObjectClass(jniParam);
        if (!jniParamClass)
        {
            errorf("GET OBJECT CLASS FAILED!!!");
            return -1;
        }

        jfieldID idID = env->GetFieldID(jniParamClass, "id", "I");
        jfieldID userIdID = env->GetFieldID(jniParamClass, "userId", "I");
        jfieldID roomSubjectID = env->GetFieldID(jniParamClass, "roomSubject", "Ljava/lang/String;");
        jfieldID roomIdID = env->GetFieldID(jniParamClass, "roomId", "Ljava/lang/String;");
        jfieldID roomCapacityID = env->GetFieldID(jniParamClass, "roomCapacity", "I");
        jfieldID passwordID = env->GetFieldID(jniParamClass, "password", "Ljava/lang/String;");
        jfieldID moderatorPasswordID = env->GetFieldID(jniParamClass, "moderatorPassword", "Ljava/lang/String;");
        jfieldID micStatusID = env->GetFieldID(jniParamClass, "micStatus", "Ljava/lang/String;");
        jfieldID videoStatusID = env->GetFieldID(jniParamClass, "videoStatus", "Ljava/lang/String;");
        jfieldID sharePowerID = env->GetFieldID(jniParamClass, "sharePower", "Ljava/lang/String;");
        jfieldID allowPartOperMicID = env->GetFieldID(jniParamClass, "allowPartOperMic", "Ljava/lang/String;");
        jfieldID allowPartOperShareID = env->GetFieldID(jniParamClass, "allowPartOperShare", "Ljava/lang/String;");

        jint jiId = env->GetIntField(jniParam, idID);
        jint jiUserId = env->GetIntField(jniParam, userIdID);
        jstring jstrRoomSubject = (jstring)env->GetObjectField(jniParam, roomSubjectID);
        jstring jstrRoomId = (jstring)env->GetObjectField(jniParam, roomIdID);
        jint jiRoomCapacity = env->GetIntField(jniParam, roomCapacityID);
        jstring jstrPassword = (jstring)env->GetObjectField(jniParam, passwordID);
        jstring jstrModeratorPassword = (jstring)env->GetObjectField(jniParam, moderatorPasswordID);
        jstring jstrMicStatus = (jstring)env->GetObjectField(jniParam, micStatusID);
        jstring jstrVideoStatus = (jstring)env->GetObjectField(jniParam, videoStatusID);
        jstring jsrtSharePower = (jstring)env->GetObjectField(jniParam, sharePowerID);
        jstring jstrAllowPartOperMic = (jstring)env->GetObjectField(jniParam, allowPartOperMicID);
        jstring jstrAllowPartOperShare = (jstring)env->GetObjectField(jniParam, allowPartOperShareID);

        const char *cppRooomSubject = env->GetStringUTFChars(jstrRoomSubject, NULL);
        const char *cppRooomId = env->GetStringUTFChars(jstrRoomId, NULL);
        const char *cppPassword = env->GetStringUTFChars(jstrPassword, NULL);
        const char *cppModeratorPassword = env->GetStringUTFChars(jstrModeratorPassword, NULL);
        const char *cppMicStatus = env->GetStringUTFChars(jstrMicStatus, NULL);
        const char *cppVideoStatus = env->GetStringUTFChars(jstrVideoStatus, NULL);
        const char *cppSharePower = env->GetStringUTFChars(jsrtSharePower, NULL);
        const char *cppAllowPartOperMic = env->GetStringUTFChars(jstrAllowPartOperMic, NULL);
        const char *cppAllowPartOperShare = env->GetStringUTFChars(jstrAllowPartOperShare, NULL);

        roomInfo.id = jiId;
        roomInfo.userId = jiUserId;
        roomInfo.roomCapacity = jiRoomCapacity;
        roomInfo.roomSubject = cppRooomSubject;
        roomInfo.roomId = cppRooomId;
        roomInfo.password = cppPassword;
        roomInfo.moderatorPassword = cppModeratorPassword;
        roomInfo.micStatus = cppMicStatus;
        roomInfo.videoStatus = cppVideoStatus;
        roomInfo.sharePower = cppSharePower;
        roomInfo.allowPartOperMic = cppAllowPartOperMic;
        roomInfo.allowPartOperShare = cppAllowPartOperShare;
        nRet = INetProtocol::instance()->updatePersonalConfRoomInfo(roomInfo);

        env->ReleaseStringUTFChars(jstrRoomSubject, cppRooomSubject);
        env->ReleaseStringUTFChars(jstrRoomId, cppRooomId);
        env->ReleaseStringUTFChars(jstrPassword, cppPassword);

        env->ReleaseStringUTFChars(jstrModeratorPassword, cppModeratorPassword);
        env->ReleaseStringUTFChars(jstrMicStatus, cppMicStatus);
        env->ReleaseStringUTFChars(jstrVideoStatus, cppVideoStatus);
        env->ReleaseStringUTFChars(jsrtSharePower, cppSharePower);
        env->ReleaseStringUTFChars(jstrAllowPartOperMic, cppAllowPartOperMic);
        env->ReleaseStringUTFChars(jstrAllowPartOperShare, cppAllowPartOperShare);

        env->DeleteLocalRef(jstrModeratorPassword);
        env->DeleteLocalRef(jstrMicStatus);
        env->DeleteLocalRef(jstrVideoStatus);
        env->DeleteLocalRef(jsrtSharePower);
        env->DeleteLocalRef(jstrAllowPartOperMic);
        env->DeleteLocalRef(jstrAllowPartOperShare);
        env->DeleteLocalRef(jstrRoomSubject);
        env->DeleteLocalRef(jstrRoomId);
        env->DeleteLocalRef(jstrPassword);
        env->DeleteLocalRef(jniParamClass);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;

    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_modifyPassword(
        JNIEnv *env, jclass thisClass, jstring jniOriginalPassword, jstring jniNewPassword) {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jniOriginalPassword == NULL)
        {
            return nRet;
        }

        if (jniNewPassword == NULL)
        {
            return nRet;
        }

        const char *cppOriginalPassword = env->GetStringUTFChars(jniOriginalPassword , NULL);
        const char *cppNewPassword = env->GetStringUTFChars(jniNewPassword , NULL);
        nRet = INetProtocol::instance()->modifyPassword(cppOriginalPassword, cppNewPassword);
        env->ReleaseStringUTFChars(jniOriginalPassword , cppOriginalPassword);
        env->ReleaseStringUTFChars(jniNewPassword , cppNewPassword);

        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_switchVoiceMode(
        JNIEnv *env, jclass thisClass, jint jniOperation)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        nRet = INetProtocol::instance()->switchVoiceMode((EnSwitch)jniOperation);
        tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_evictedParticipant(
        JNIEnv *env, jclass thisClass, jstring jniAccount)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jniAccount == NULL)
        {
            return nRet;
        }

		nRet = INetProtocol::instance()->evictedParticipant(JNICommon::getJStringValue(env, jniAccount));

		tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_needVersionUpgrade(
        JNIEnv *env, jclass thisClass, OUT jobject needUpgrade, OUT jobject forceStatus, OUT jobject downLoadUrl,
        OUT jobject jniVersion, OUT jobject jniApkSize, OUT jobject jniDetails)
    {
         tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;
        bool tempneedUpgrade, tmpforceStatus;
        std::string url, version, apkSize, details;
        nRet = INetProtocol::instance()->needVersionUpgrade(tempneedUpgrade, tmpforceStatus, url, version, apkSize, details);
		if (nRet != 0) {
			errorf("%s FAILED!!!", __FUNCTION__);
            return nRet;
		}

        JNICommon::setCommonTypeValue<int>(env, (int)tempneedUpgrade, needUpgrade);
		JNICommon::setCommonTypeValue<int>(env, (int)tmpforceStatus, forceStatus);
		JNICommon::setCommonTypeValue<std::string>(env, url, downLoadUrl);
		JNICommon::setCommonTypeValue<std::string>(env, version, jniVersion);
		JNICommon::setCommonTypeValue<std::string>(env, apkSize, jniApkSize);
		JNICommon::setCommonTypeValue<std::string>(env, details, jniDetails);

	tracef("%s out <<<", __FUNCTION__);
        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_needVersionUpgradeV2 (
         JNIEnv *env, jclass thisClass, OUT jobject needUpgrade, OUT jobject forceStatus, OUT jobject downLoadUrl,
         OUT jobject jniVersion, OUT jobject jniApkSize, OUT jobject jniDetails)
	{

		tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        bool tempneedUpgrade;
		EnForceUpgrade tmpforceStatus;
        std::string url, version, apkSize, details;
        nRet = INetProtocol::instance()->needVersionUpgradeV2(tempneedUpgrade, tmpforceStatus, url, version, apkSize, details);
		if (nRet != 0) {
			errorf("%s FAILED!!!", __FUNCTION__);
            return nRet;
		}
		JNICommon::setCommonTypeValue<int>(env, (int)tempneedUpgrade, needUpgrade);
		JNICommon::setCommonTypeValue<int>(env, (int)tmpforceStatus, forceStatus);
		JNICommon::setCommonTypeValue<std::string>(env, url, downLoadUrl);
		JNICommon::setCommonTypeValue<std::string>(env, version, jniVersion);
		JNICommon::setCommonTypeValue<std::string>(env, apkSize, jniApkSize);
		JNICommon::setCommonTypeValue<std::string>(env, details, jniDetails);
		tracef("%s out <<<", __FUNCTION__);
        return nRet;
	}

     JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_reconnect(
         JNIEnv *env, jclass thisClass)
    {
        tracef("%s in >>>", __FUNCTION__);

		INetProtocol::instance()->reconnect();

		return 0;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_startConferenceRecord(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId, jboolean jzForce)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jstrRoomId == NULL)
        {
            return nRet;
        }

        const char *cppRoomId = env->GetStringUTFChars(jstrRoomId, NULL);
        nRet = INetProtocol::instance()->startConferenceRecord(cppRoomId, jzForce);
        env->ReleaseStringUTFChars(jstrRoomId, cppRoomId);

        if (nRet != 0) {
            errorf("startConferenceRecord FAILED!!!");
            return nRet;
        }

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_stopConferenceRecord(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jstrRoomId == NULL)
        {
            return nRet;
        }

        const char *cppRoomId = env->GetStringUTFChars(jstrRoomId, NULL);
        nRet = INetProtocol::instance()->stopConferenceRecord(cppRoomId);
        env->ReleaseStringUTFChars(jstrRoomId, cppRoomId);
        if (nRet != 0)
        {
            errorf("stopConferenceRecord FAILED!!!");
            return nRet;
        }

        return nRet;
    }

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getConferenceRecordStatus(
		JNIEnv * env, jclass thisClass, jstring jstrRoomId, 
		OUT jobject joCommonType)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		bool conferenceRecordStatus = false;
		long long startRecordTimeMs = 0;
		nRet = INetProtocol::instance()->getConferenceRecordStatus(
			JNICommon::getJStringValue(env, jstrRoomId),
			conferenceRecordStatus,
			startRecordTimeMs);
		if (nRet != 0)
		{
			errorf("getConferenceRecordStatus FAILED!!!");
			return nRet;
		}

		JNICommon::setCommonTypeValue(env, conferenceRecordStatus, joCommonType);
		JNICommon::setCommonTypeValue(env, startRecordTimeMs, joCommonType);

		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getConferenceRecord(
        JNIEnv *env, jclass thisClass,  jint size, jint pageNum, OUT jobject jniTotal, OUT jobject jniRecordListsLen, OUT jobjectArray jniRecordLists)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jniRecordListsLen == NULL || jniRecordLists == NULL)
        {
           return nRet;
        }

        std::vector<ConferenceRecordInfo> conferenceRecordList;
        long total = 0;
        nRet = INetProtocol::instance()->getConferenceRecord(size, pageNum, total, conferenceRecordList);

        jclass jniConferenceRecordClass = env->FindClass(CONFERENCE_RECORD_CLASS_NAME);
        if (!jniConferenceRecordClass) {
            errorf("FIND CLASS FAILED!!!");
            return nRet;
        }

        jfieldID recordNameID = env->GetFieldID(jniConferenceRecordClass, "recordName", "Ljava/lang/String;");
        jfieldID recordSizeID = env->GetFieldID(jniConferenceRecordClass, "recordSize", "J");
        jfieldID thumbnailUrlID = env->GetFieldID(jniConferenceRecordClass, "thumbnailUrl", "Ljava/lang/String;");
        jfieldID idID = env->GetFieldID(jniConferenceRecordClass, "id", "J");
        jfieldID startTimeID = env->GetFieldID(jniConferenceRecordClass, "startTime", "J");
        jfieldID endTimeID = env->GetFieldID(jniConferenceRecordClass, "endTime", "J");
        jfieldID requestStartTimeID = env->GetFieldID(jniConferenceRecordClass, "requestStartTime", "J");

        int jniRecordListsSize = env->GetArrayLength(jniRecordLists);
        int localConferenceRecordListSize = conferenceRecordList.size();
        infof("jniRecordListsSize:%d localConferenceRecordListSize:%d", jniRecordListsSize, localConferenceRecordListSize);
        int minRecordListSize = std::min(jniRecordListsSize, localConferenceRecordListSize);

        for (int i = 0; i < minRecordListSize; i++)
        {
            jmethodID partInfoConstructorID = env->GetMethodID(jniConferenceRecordClass, "<init>", "()V");
            jobject joConferenceRecord = env->NewObject(jniConferenceRecordClass, partInfoConstructorID);

            jstring jstrRecordName = env->NewStringUTF(conferenceRecordList.at(i).recordName.c_str());
            env->SetObjectField(joConferenceRecord, recordNameID, jstrRecordName);
            env->SetLongField(joConferenceRecord, recordSizeID, conferenceRecordList.at(i).recordSize);
            jstring jstrThumbnailUrl = env->NewStringUTF(conferenceRecordList.at(i).thumbnailUrl.c_str());
            env->SetObjectField(joConferenceRecord, thumbnailUrlID, jstrThumbnailUrl);
            env->SetLongField(joConferenceRecord, idID, conferenceRecordList.at(i).id);
            env->SetLongField(joConferenceRecord, startTimeID, conferenceRecordList.at(i).startTime);
            env->SetLongField(joConferenceRecord, endTimeID, conferenceRecordList.at(i).endTime);
            env->SetLongField(joConferenceRecord, requestStartTimeID, conferenceRecordList.at(i).requestStartTime);

            env->SetObjectArrayElement(jniRecordLists, i, joConferenceRecord);

            env->DeleteLocalRef(jstrRecordName);
            env->DeleteLocalRef(jstrThumbnailUrl);
            env->DeleteLocalRef(joConferenceRecord);

        }

        env->DeleteLocalRef(jniConferenceRecordClass);


         // COMM_TYPE_CLASS_NAME
        jclass jniArrSizeClass = env->GetObjectClass(jniRecordListsLen);
        if (!jniArrSizeClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

		jfieldID arrSizeNumberID = env->GetFieldID(jniArrSizeClass, "longNumber", "J");
		env->DeleteLocalRef(jniArrSizeClass);
        if (!arrSizeNumberID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        env->SetLongField(jniRecordListsLen, arrSizeNumberID, (long)minRecordListSize);



          // COMM_TYPE_CLASS_NAME
        jclass jniTotalClass = env->GetObjectClass(jniTotal);
        if (!jniTotalClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

		jfieldID totalID = env->GetFieldID(jniTotalClass, "longNumber", "J");
		env->DeleteLocalRef(jniTotalClass);
        if (!totalID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        env->SetLongField(jniTotal, totalID, total);

        tracef("%s out <<<", __FUNCTION__);


        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_playbackConferenceRecord(
        JNIEnv *env, jclass thisClass, jlong jlId, OUT jobject jniRecordUrl)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jlId == 0 || jniRecordUrl == NULL)
        {
            return nRet;
        }

        std::string recordUrl;
        nRet = INetProtocol::instance()->playbackConferenceRecord(jlId, recordUrl);
        if (nRet != 0)
        {
            errorf("playbackConferenceRecord FAILED!!!");
            return nRet;
        }


         // COMM_TYPE_CLASS_NAME
        jclass jniRecordUrlClass = env->GetObjectClass(jniRecordUrl);
        if (!jniRecordUrlClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID recordUrlStrID = env->GetFieldID(jniRecordUrlClass, "str", "Ljava/lang/String;");
		env->DeleteLocalRef(jniRecordUrlClass);
        if (!recordUrlStrID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        jstring jstrRecordUrlOut = env->NewStringUTF(recordUrl.c_str());
        env->SetObjectField(jniRecordUrl, recordUrlStrID, jstrRecordUrlOut);
        env->DeleteLocalRef(jstrRecordUrlOut);

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_downloadConferenceRecord(
        JNIEnv *env, jclass thisClass, jlong jlId, OUT jobject jniDownloadUrl)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jlId == 0 || jniDownloadUrl == NULL)
        {
            return nRet;
        }

        std::string downLoadUrl;
        nRet = INetProtocol::instance()->downloadConferenceRecord(jlId, downLoadUrl);
        if (nRet != 0)
        {
            errorf("downloadConferenceRecord FAILED!!!");
            return nRet;
        }


         // COMM_TYPE_CLASS_NAME
        jclass jniDownloadUrlClass = env->GetObjectClass(jniDownloadUrl);
        if (!jniDownloadUrlClass) {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID downLoadUrlStrID = env->GetFieldID(jniDownloadUrlClass, "str", "Ljava/lang/String;");
		env->DeleteLocalRef(jniDownloadUrlClass);
        if (!downLoadUrlStrID) {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        jstring jstrDownLoadUrlOut = env->NewStringUTF(downLoadUrl.c_str());
        env->SetObjectField(jniDownloadUrl, downLoadUrlStrID, jstrDownLoadUrlOut);
        env->DeleteLocalRef(jstrDownLoadUrlOut);

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_delConferenceRecord(
        JNIEnv *env, jclass thisClass, jlong jlId)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jlId == 0)
        {
            return nRet;
        }

        nRet = INetProtocol::instance()->delConferenceRecord(jlId);
        if (nRet != 0)
        {
            errorf("delConferenceRecord FAILED!!!");
            return nRet;
        }

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_startLive(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId, OUT jobject jobLivingUrl)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jstrRoomId == NULL || jobLivingUrl == NULL)
        {
            return nRet;
        }

        const char *cppRoomId = env->GetStringUTFChars(jstrRoomId, NULL);
        std::string livingUrl;
        nRet = INetProtocol::instance()->startLive(cppRoomId, livingUrl);
        env->ReleaseStringUTFChars(jstrRoomId, cppRoomId);
        if (nRet != 0)
        {
            errorf("startLive FAILED!!!");
            return nRet;
        }

        // COMM_TYPE_CLASS_NAME
        jclass jniLivingUrlClass = env->GetObjectClass(jobLivingUrl);
        if (!jniLivingUrlClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID livingUrlStrID = env->GetFieldID(jniLivingUrlClass, "str", "Ljava/lang/String;");
		env->DeleteLocalRef(jniLivingUrlClass);
        if (!livingUrlStrID)
        {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        jstring jstrLivingUrlOut = env->NewStringUTF(livingUrl.c_str());
        env->SetObjectField(jobLivingUrl, livingUrlStrID, jstrLivingUrlOut);
        env->DeleteLocalRef(jstrLivingUrlOut);

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_stopLive(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId)
    {
         tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jstrRoomId == NULL)
        {
            return nRet;
        }

        const char *cppRoomId = env->GetStringUTFChars(jstrRoomId, NULL);
        nRet = INetProtocol::instance()->stopLive(cppRoomId);
        env->ReleaseStringUTFChars(jstrRoomId, cppRoomId);
        if (nRet != 0)
        {
            errorf("stopLive FAILED!!!");
            return nRet;
        }

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getLiveStatus(
        JNIEnv *env, jclass thisClass, jstring jstrRoomId, OUT jobject jniLivingStatus)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jstrRoomId == NULL || jniLivingStatus == NULL)
        {
            return nRet;
        }

        const char *cppRoomId = env->GetStringUTFChars(jstrRoomId, NULL);
        bool livingStatus;
		std::string strLiveUrl;
        nRet = INetProtocol::instance()->getLiveStatus(cppRoomId, livingStatus, strLiveUrl);
        env->ReleaseStringUTFChars(jstrRoomId, cppRoomId);
        if (nRet != 0)
        {
            errorf("getLiveStatus FAILED!!!");
            return nRet;
        }

        // COMM_TYPE_CLASS_NAME
        jclass jniLiveStatusClass = env->GetObjectClass(jniLivingStatus);
        if (!jniLiveStatusClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID liveStatusID = env->GetFieldID(jniLiveStatusClass, "number", "I");
		env->DeleteLocalRef(jniLiveStatusClass);
        if (!liveStatusID)
        {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        env->SetIntField(jniLivingStatus, liveStatusID, (int)livingStatus);

        return nRet;
    }

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_httpGet(
        JNIEnv *env, jclass thisClass, jstring jstrUrl, OUT jobject jniRspBody)
    {
        tracef("%s in >>>", __FUNCTION__);
        jint nRet = -1;

        if (jstrUrl == NULL || jniRspBody == NULL)
        {
            return nRet;
        }

        const char *cppUrl = env->GetStringUTFChars(jstrUrl, NULL);
        std::string rsp;
        nRet = INetProtocol::instance()->httpGet(cppUrl, rsp);
        env->ReleaseStringUTFChars(jstrUrl, cppUrl);
        if (nRet != 0)
        {
            errorf("httpGet FAILED!!!");
            return nRet;
        }

        // COMM_TYPE_CLASS_NAME
        jclass jniRspBodyClass = env->GetObjectClass(jniRspBody);
        if (!jniRspBodyClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return -1;
        }

        jfieldID rspBodyID = env->GetFieldID(jniRspBodyClass, "str", "Ljava/lang/String;");
		env->DeleteLocalRef(jniRspBodyClass);
        if (!rspBodyID)
        {
            errorf("GetFieldID FAILED!!!");
            return -1;
        }

        jstring jstrRspBodyOut = env->NewStringUTF(rsp.c_str());
        env->SetObjectField(jniRspBody, rspBodyID, jstrRspBodyOut);
        env->DeleteLocalRef(jstrRspBodyOut);
        return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_pushLog(
		JNIEnv *env, jclass thisClass, jobject jniPushLogParams)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (jniPushLogParams == NULL)
		{
			return nRet;
		}

		jclass jniPushLogParamsClass = env->GetObjectClass(jniPushLogParams);
		if (!jniPushLogParamsClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID accountID = env->GetFieldID(jniPushLogParamsClass, "account", "Ljava/lang/String;");
		jfieldID logNameID = env->GetFieldID(jniPushLogParamsClass, "logName", "Ljava/lang/String;");
		jfieldID versionID = env->GetFieldID(jniPushLogParamsClass, "version", "Ljava/lang/String;");
		jfieldID terminalTypeID = env->GetFieldID(jniPushLogParamsClass, "terminalType", "I");
		jfieldID deviceModelID = env->GetFieldID(jniPushLogParamsClass, "deviceModel", "Ljava/lang/String;");
		env->DeleteLocalRef(jniPushLogParamsClass);

		jstring  jstrAccount = (jstring)env->GetObjectField(jniPushLogParams, accountID);
		jstring  jstrLogName = (jstring)env->GetObjectField(jniPushLogParams, logNameID);
		jstring  jstrVersion = (jstring)env->GetObjectField(jniPushLogParams, versionID);
		jint  jintTerminalType = env->GetIntField(jniPushLogParams, terminalTypeID);
		jstring  jstrDeviceModel = (jstring)env->GetObjectField(jniPushLogParams, deviceModelID);

		PushLogParams pushLogParams;
		pushLogParams.account = JNICommon::getJStringValue(env, jstrAccount);
		pushLogParams.logName = JNICommon::getJStringValue(env, jstrLogName);
		pushLogParams.version = JNICommon::getJStringValue(env, jstrVersion);
		pushLogParams.terminalType = static_cast<EnTerminalType>(jintTerminalType);
		pushLogParams.deviceModel = JNICommon::getJStringValue(env, jstrDeviceModel);

		nRet = INetProtocol::instance()->pushLog(pushLogParams);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrLogName);
		env->DeleteLocalRef(jstrVersion);
		env->DeleteLocalRef(jstrDeviceModel);

		if (nRet != 0)
		{
			errorf("%s FAILED!!!", __FUNCTION__);
			return nRet;
		}

		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getUnfinishedRoom(
		JNIEnv * env, jclass thisClass, OUT jobject jniRoomInfo)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (jniRoomInfo == NULL)
		{
			return nRet;
		}

		StUnfinishedRoomInfo cppRoomInfo;
		nRet = INetProtocol::instance()->getUnfinishedRoom(cppRoomInfo);
		if (nRet != 0)
		{
			errorf("%s FAILED!!!", __FUNCTION__);
			return nRet;
		}

		JNICommon::setFieldValue(env, cppRoomInfo, jniRoomInfo);

		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getAccount(
		JNIEnv *env, jclass thisClass, jstring jniSerialNumber, OUT jobject jniAccount, OUT jobject jniPassword) {
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		if (NULL == jniSerialNumber) {
			errorf("input serialNumber is null");
			return nRet;
		}

		const char *cppSerialNumber = env->GetStringUTFChars(jniSerialNumber, NULL);
		std::string account;
		std::string password;
		nRet = INetProtocol::instance()->getAccount(cppSerialNumber, account, password);
		env->ReleaseStringUTFChars(jniSerialNumber, cppSerialNumber);
		if (nRet != 0) {
			warnf("getAccount failed.");
			return nRet;
		}

		// COMM_TYPE_CLASS_NAME
		jclass jniAccountIdClass = env->GetObjectClass(jniAccount);
		if (!jniAccountIdClass) {
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}

		jfieldID accountStrID = env->GetFieldID(jniAccountIdClass, "str", "Ljava/lang/String;");
		env->DeleteLocalRef(jniAccountIdClass);
		if (!accountStrID) {
			errorf("GetFieldID FAILED!!!");
			return -1;
		}

		jstring jstrAccountOut = env->NewStringUTF(account.c_str());
		env->SetObjectField(jniAccount, accountStrID, jstrAccountOut);
		env->DeleteLocalRef(jstrAccountOut);

		// COMM_TYPE_CLASS_NAME
		jclass jniPasswordIdClass = env->GetObjectClass(jniPassword);
		if (!jniPasswordIdClass) {
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}

		jfieldID passwordStrID = env->GetFieldID(jniPasswordIdClass, "str", "Ljava/lang/String;");
		env->DeleteLocalRef(jniPasswordIdClass);
		if (!passwordStrID) {
			errorf("GetFieldID FAILED!!!");
			return -1;
		}

		jstring jstrPasswordOut = env->NewStringUTF(password.c_str());
		env->SetObjectField(jniPassword, passwordStrID, jstrPasswordOut);
		env->DeleteLocalRef(jstrPasswordOut);


		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}
	
	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setRollCallStatus(
		JNIEnv * env, jclass thisClass, jstring jniOldAccount, jstring jniNewAccount, jboolean jniStatus, jint jniSource)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		if (jniOldAccount == NULL)
		{
			errorf("account is NULL.");
			return nRet;
		}

		const char* cppAccount = env->GetStringUTFChars(jniOldAccount, NULL);

		if (jniNewAccount != NULL)
		{
			const char* cppNewAccount = env->GetStringUTFChars(jniNewAccount, NULL);
			nRet = INetProtocol::instance()->setRollCallStatus(cppAccount, cppNewAccount, jniStatus, (EnRollCallSource)jniSource);
			env->ReleaseStringUTFChars(jniNewAccount, cppNewAccount);
		}
		else
		{
			nRet = INetProtocol::instance()->setRollCallStatus(cppAccount, "", jniStatus, (EnRollCallSource)jniSource);
		}

		env->ReleaseStringUTFChars(jniOldAccount, cppAccount);
		
		if (nRet != 0)
		{
			errorf("%s FAILED!!!", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_changeMeetingLayout(
		JNIEnv *env, jclass thisClass, jint jintLayoutType, jint jintNumberOfSplitScreen, jobject joLayouts)
	{
		tracef("%s in >>>", __FUNCTION__);

		std::vector<StView> layouts;
		JNICommon::getFieldArrayValue(env, joLayouts, layouts);

		int nRet = INetProtocol::instance()->changeMeetingLayout(
			static_cast<EnMeetingLayoutType>(jintLayoutType),
			jintNumberOfSplitScreen, 
			layouts);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPtzControlStatus(
		JNIEnv * env, jclass thisClass, jboolean jzAction, jobject joParam)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		StPtzControlParam cppParam;
		nRet = JNICommon::getFieldValue(env, joParam, cppParam);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		nRet = INetProtocol::instance()->setPtzControlStatus(jzAction, cppParam);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_adjustResolution(
		JNIEnv * env, jclass thisClass, jint jiResolution)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		nRet = INetProtocol::instance()->adjustResolution(jiResolution);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPresetPosition(
		JNIEnv * env, jclass thisClass, jstring jstrSerialNumber, jint jintIndex, jstring jstrImage, jobject joConfigInfo)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		std::string serialNumber = JNICommon::getJStringValue(env, jstrSerialNumber);
		std::string image = JNICommon::getJStringValue(env, jstrImage);
		StPresetPositionConfigInfo configInfo;
		JNICommon::getFieldValue(env, joConfigInfo, configInfo);

		nRet = INetProtocol::instance()->setPresetPosition(serialNumber, jintIndex, image, configInfo);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_setPollingStatus(
		JNIEnv * env, jclass thisClass, jstring jstrRoomId, jboolean jzStatus, jint jintTimeInterval)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		std::string roomId = JNICommon::getJStringValue(env, jstrRoomId);

		nRet = INetProtocol::instance()->setPollingStatus(roomId, jzStatus, jintTimeInterval);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPollingStatus(
		JNIEnv * env, jclass thisClass, jstring jstrRoomId, 
		OUT jobject joCommonType)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		std::string roomId = JNICommon::getJStringValue(env, jstrRoomId);
		bool status = false;

		nRet = INetProtocol::instance()->getPollingStatus(roomId, status);
		if (nRet != 0)
		{
			errorf("getPollingStatus failed.");
			return nRet;
		}

		jclass commonTypeClass = env->GetObjectClass(joCommonType);
		if (commonTypeClass == NULL)
		{
			errorf("GET OBJECT CLASS FAILED.");
			return nRet;
		}
		jfieldID statusId = env->GetFieldID(commonTypeClass, "boolVar", "Z");
		env->SetBooleanField(joCommonType, statusId, status);
		env->DeleteLocalRef(commonTypeClass);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getIceServerList(
		JNIEnv * env, jclass thisClass, 
		OUT jobject joIceServerInfos)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		std::vector<StIceServerInfo> iceServerInfos;

		nRet = INetProtocol::instance()->getIceServerList(iceServerInfos);
		if (nRet != 0)
		{
			errorf("getIceServerList failed.");
			return nRet;
		}

		nRet = JNICommon::setFieldArrayValue(env, iceServerInfos, ICE_SERVER_INFO_CLASS_NAME, joIceServerInfos);
		if (nRet != 0)
		{
			errorf("setFieldArrayValue failed.");
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_countParticipatedDuration(
		JNIEnv * env, jclass thisClass, jobject joPageInfoIn, 
		OUT jobject joMeetingInfos, OUT jobject joPageInfoOut)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StDataPageInfo cppPageInfoIn;
		nRet = JNICommon::getFieldValue(env, joPageInfoIn, cppPageInfoIn);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<StMeeting> cppMeetingInfos;
		StDataPageInfo cppPageInfoOut;
		nRet = INetProtocol::instance()->countParticipatedDuration(cppPageInfoIn, cppMeetingInfos, cppPageInfoOut);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		nRet = JNICommon::setFieldArrayValue(env, cppMeetingInfos, STMEETING_INFO_CLASS_NAME, joMeetingInfos);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		nRet = JNICommon::setFieldValue(env, cppPageInfoOut, joPageInfoOut);
		if (nRet != 0)
		{
			errorf("setFieldValue failed.");
			return -1;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_uploadMeetingQuality(
		JNIEnv * env, jclass thisClass, jobject joNetworkQuality, jobject joStreamQualityList)
	{
		tracef("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StNetworkQuality cppNetQuality;
		nRet = JNICommon::getFieldValue(env, joNetworkQuality, cppNetQuality);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		std::vector<StStreamQuality> cppStreamQualities;
		nRet = JNICommon::getFieldArrayValue<StStreamQuality>(env, joStreamQualityList, cppStreamQualities);
		if (nRet != 0)
		{
			errorf("getFieldValue failed.");
			return -1;
		}

		nRet = INetProtocol::instance()->uploadMeetingQuality(cppNetQuality, cppStreamQualities);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getScrollBarrage(
		JNIEnv * env, jclass thisClass, OUT jobject joStatus, OUT jobject joBarrage)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		bool cppStatus = false;
		StBarrage cppBarrage;
		nRet = INetProtocol::instance()->getScrollBarrage(cppStatus, cppBarrage);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		JNICommon::setCommonTypeValue<bool>(env, cppStatus, joStatus);
		JNICommon::setFieldValue(env, cppBarrage, joBarrage);

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_sendIMMessage(
		JNIEnv * env, jclass thisClass, jobject joMessage, jstring jstrClientMsgId,
		OUT jobject joFinalMsgId, OUT jobject joFinalTimestamp)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StIMMessage cppMessage;
		JNICommon::getFieldValue(env, joMessage, cppMessage);
		std::string cppClientMsgId = JNICommon::getJStringValue(env, jstrClientMsgId);
		long long finalMsgId = 0;
		long long finalTimestamp = 0;

		nRet = INetProtocol::instance()->sendIMMessage(cppMessage, cppClientMsgId, finalMsgId, finalTimestamp);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		JNICommon::setCommonTypeValue<long long>(env, finalMsgId, joFinalMsgId);
		JNICommon::setCommonTypeValue<long long>(env, finalTimestamp, joFinalTimestamp);

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getIMMessageHistory(
		JNIEnv * env, jclass thisClass, jobject joLastIMMessage, jint jintCountOfMsg, jboolean jbIsPositiveSequence, 
		OUT jobject joMessageArrayList)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StIMMessage lsatIMMessage;
		JNICommon::getFieldValue(env, joLastIMMessage, lsatIMMessage);

		std::vector<StIMMessage> cppMessageList;
		nRet = INetProtocol::instance()->getIMMessageHistory(lsatIMMessage, jintCountOfMsg, jbIsPositiveSequence, cppMessageList);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		JNICommon::setFieldArrayValue(env, cppMessageList, IM_MESSAGE_CLASS_NAME, joMessageArrayList);

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_checkIfExistUnreadPushedMsg(
		JNIEnv * env, jclass thisClass, OUT jobject joUnreadMsgParams)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		bool existUnreadMsg = false;
		int countOfMsg = 0;
		nRet = INetProtocol::instance()->checkIfExistUnreadPushedMsg(existUnreadMsg, countOfMsg);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		JNICommon::setCommonTypeValue<bool>(env, existUnreadMsg, joUnreadMsgParams);
		JNICommon::setCommonTypeValue<int>(env, countOfMsg, joUnreadMsgParams);

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getPagesOfPushedMsg(
		JNIEnv * env, jclass thisClass, jobject joPageInfoIn, 
		OUT jobject joPushedMsgArrayList, OUT jobject joPageInfoOut)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		StDataPageInfo cppPageInfoIn, cppPageInfoOut;
		std::vector<StPushedMsg> cppPushedMsgs;
		JNICommon::getFieldValue(env, joPageInfoIn, cppPageInfoIn);

		nRet = INetProtocol::instance()->getPagesOfPushedMsg(cppPageInfoIn, cppPushedMsgs, cppPageInfoOut);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		JNICommon::setFieldArrayValue(env, cppPushedMsgs, PUSHED_MSG_CLASS_NAME, joPushedMsgArrayList);
		JNICommon::setFieldValue(env, cppPageInfoOut, joPageInfoOut);

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_readPushedMsg(
		JNIEnv * env, jclass thisClass, jobject joIdArrayList)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		std::vector<long long> cppIdList;
		JNICommon::getFieldArrayValue(env, joIdArrayList, cppIdList);

		nRet = INetProtocol::instance()->readPushedMsg(cppIdList);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_cleanPushedMsg(
		JNIEnv * env, jclass thisClass)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		nRet = INetProtocol::instance()->cleanPushedMsg();
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getDeployEnv(
		JNIEnv * env, jclass thisClass, OUT jobject joIsPrivateDeploy)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		bool isPrivateDeploy = false;
		nRet = INetProtocol::instance()->getDeployEnv(isPrivateDeploy);
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		JNICommon::setCommonTypeValue<bool>(env, isPrivateDeploy, joIsPrivateDeploy);

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_uploadRegistrationId(
		JNIEnv * env, jclass thisClass, jstring jstrRegistrationId)
	{
		infof("%s in >>>", __FUNCTION__);
		jint nRet = -1;

		nRet = INetProtocol::instance()->uploadRegistrationId(
			JNICommon::getJStringValue(env, jstrRegistrationId));
		if (nRet != 0)
		{
			errorf("%s failed.", __FUNCTION__);
			return nRet;
		}

		infof("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_queryOperationPermission(
		JNIEnv * env, jclass thisClass, OUT jobject joPermissions, OUT jobject joAbilities)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		std::vector<EnOperationPermission> cppPermissions;
		std::vector<EnAccountAbility> cppAlibities;
		nRet = INetProtocol::instance()->queryOperationPermission(cppPermissions, cppAlibities);
		if (nRet != 0)
		{
			errorf("Querying permissions failed.");
			return nRet;
		}

		JNICommon::setIntFieldValue(env, cppPermissions, joPermissions);
		JNICommon::setIntFieldValue(env, cppAlibities, joAbilities);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_hurryUp(
		JNIEnv * env, jclass thisClass, jstring jstrRoomId, jstring jstrRuid)
	{
		tracef("%s in >>>", __FUNCTION__);

		int nRet = INetProtocol::instance()->hurryUp(
			JNICommon::getJStringValue(env, jstrRoomId),
			JNICommon::getJStringValue(env, jstrRuid)
		);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_changeMeetingRoom(
		JNIEnv * env, jclass thisClass, jstring jstrRuid, jint jintRoomIdType, jstring jstrRoomId)
	{
		tracef("%s in >>>", __FUNCTION__);

		int nRet = INetProtocol::instance()->changeMeetingRoom(
			JNICommon::getJStringValue(env, jstrRuid), 
			static_cast<EnRoomIdType>(jintRoomIdType),
			JNICommon::getJStringValue(env, jstrRoomId));

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_prolongMeeting(
		JNIEnv * env, jclass thisClass, jint jintMinsNeedToProlong)
	{
		tracef("%s in >>>", __FUNCTION__);

		int nRet = INetProtocol::instance()->prolongMeeting(jintMinsNeedToProlong);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getCompanyResourceInfo(
		JNIEnv * env, jclass thisClass, OUT jobject joCompanyInfo)
	{
		tracef("%s in >>>", __FUNCTION__);
		int nRet = -1;

		StCompanyInfo companyInfo;
		nRet = INetProtocol::instance()->getCompanyResourceInfo(companyInfo);

		JNICommon::setFieldValue(env, companyInfo, joCompanyInfo);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_changePhoneNumber(
		JNIEnv * env, jclass thisClass, jstring jstrNewPhoneNumber, jstring jstrValidateCode)
	{
		tracef("%s in >>>", __FUNCTION__);

		int nRet = INetProtocol::instance()->changePhoneNumber(
			JNICommon::getJStringValue(env, jstrNewPhoneNumber),
			JNICommon::getJStringValue(env, jstrValidateCode)
		);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_cancelAccount(
		JNIEnv * env, jclass thisClass, jstring jstrNewPhoneNumber, jstring jstrValidateCode)
	{
		tracef("%s in >>>", __FUNCTION__);

		int nRet = INetProtocol::instance()->cancelAccount(
			JNICommon::getJStringValue(env, jstrNewPhoneNumber),
			JNICommon::getJStringValue(env, jstrValidateCode)
		);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

	JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_jniTest(
		JNIEnv * env, jclass thisClass, jobject joCalleeInfo)
	{
		tracef("%s in >>>", __FUNCTION__);

		StCalleeInfo calleeInfo;
		int nRet = INetProtocol::instance()->jniTest(calleeInfo);

		JNICommon::setFieldValue(env, calleeInfo, joCalleeInfo);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}	

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_getCalleeList(
        JNIEnv *env, jclass thisClass, jobject joCalleeList)
	{
		tracef("%s in >>>", __FUNCTION__);

		std::vector<StCalleeInfo> calleeList;
		int nRet = INetProtocol::instance()->getCalleeList(calleeList);
		if (nRet != 0)
		{
			errorf("%s FAILED!!!", __FUNCTION__);
			return nRet;
		}

		JNICommon::setFieldArrayValue(env, calleeList, CALLEE_INFO_NAME, joCalleeList);

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    JNIEXPORT jint JNICALL Java_cn_geedow_netprotocol_JNINetProtocol_removeCallee(
        JNIEnv *env, jclass thisClass, jobject joCalleeList)
	{
		tracef("%s in >>>", __FUNCTION__);

		std::vector<StCalleeInfo> calleeList;
		JNICommon::getFieldArrayValue(env, joCalleeList, calleeList);
		int nRet = INetProtocol::instance()->removeCallee(calleeList);
		if (nRet != 0)
		{
			errorf("%s FAILED!!!", __FUNCTION__);
			return nRet;
		}

		tracef("%s out <<<", __FUNCTION__);
		return nRet;
	}

    // #ifdef __cplusplus
}
// #endif
