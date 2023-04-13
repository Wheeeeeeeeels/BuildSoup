#ifndef __JNI_NATIVE_ROOM_OBSERVER_H__
#define __JNI_NATIVE_ROOM_OBSERVER_H__

#include <jni.h>
#include "INetProtocol.h"
#include "JNICustomGlobalRef.h"

namespace SDNP
{

class CJNINativeRoomObserver : public IRoomObserver
{
public:
    CJNINativeRoomObserver();

    virtual ~CJNINativeRoomObserver();

	virtual void onMeetingCreated(std::string roomId) override;

	virtual void onMeetingClosed(EnMeetingClosedReason reason) override;

	virtual void onMeetingInfoChanged(EnMeetingInfoOption option, StMeeting meetingInfo) override;

	virtual void onJoined(std::string roomId, std::string account, StParticipantInfo participant) override;

	virtual void onLeftNotify(std::string roomId, std::string account, EnParticipantLeftReason reason) override;

    virtual void onPublished(std::string roomId, std::string account, EnStreamType streamType, bool videoStatus, bool audioStatus) override;

	virtual void onStopPublished(std::string roomId, std::string account, EnStreamType streamType) override;

    virtual void onIceCandidate(std::string roomId, std::string account, EnStreamType streamType, std::string sdpMid, std::string sdpMLineIndex, std::string candidate) override;

	virtual void onSetShareState(std::string handleAccount, std::string shareAccount, bool shareState) override;

	virtual void onInvite(std::string roomId, std::string subject, std::string accountFrom, std::string usernameFrom,
		long long expireTime, std::string password, std::string userIcon, bool audioInStatus, bool videoStatus) override;

    virtual void onCancelInvite(std::string roomId, std::string accountFrom, std::string usernameFrom) override;

	virtual void onRinging(std::string roomId, std::string accountFrom) override;

    virtual void onRefuseInvite(std::string roomId, std::string accountFrom, std::string usernameFrom, EnRefuseInviteReason reason) override;

    virtual void onToggleCamera() override;

    virtual void onVideoStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status) override;

    virtual void onAudioInStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status) override;

    virtual void onAudioOutStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status) override;

    virtual void onHandStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status) override;

    virtual void onNotifyPartRoleChanged(std::string account, EnRoomRole presentRole) override;

    virtual void onSwitchVoiceModeNotify(std::string account, EnSwitch operation) override;

    virtual void onDisconnect(std::string account) override;

    virtual void onReconnect(std::string account) override;

    virtual void onTempBroken(std::string account) override;

	virtual void onStartConferenceRecord(long long startRecordingTime) override;

	virtual void onStopConferenceRecord(bool isStoped, EnStopRecordReason reason) override; 

    virtual void onStartLive() override;

    virtual void onStopLive() override;

	virtual void onSetRollCallStatus(bool lectureStatus, std::string newLecturer, std::string oldLecturer) override;

	virtual void onUpdateParticipantsOrder(std::vector<StParticipantInfo> participantList) override;

	virtual void onSetSpeakerPermission(std::string account, bool action) override;

	virtual void onMessage(std::string account, std::string nickname, EnMessageType msgType) override;

	virtual void onSetPushStreamStatus(std::string roomId, std::string account, EnStreamType streamType, EnStreamStatus status) override;

	virtual void onSetPtzControlStatus(bool action, std::string serialNumber, StPtzControlParam param) override;

	virtual void onAdjustResolution(std::string serialNumber, int resolution) override;

	virtual void onAdjustToPresetPosition(std::string serialNumber, int index, StPresetPositionConfigInfo configInfo) override;

	virtual void onSetPollingStatus(std::string roomId, bool status, int timeInterval) override;

	virtual void onPollingNotify(EnPollingNotify pollingNotify, std::string account) override;

	virtual void onRoomAutoProlong(std::string roomId, std::string ruid) override;

	virtual void onUploadMeetingQuality(std::string roomId) override;

	virtual void onScrollBarrage(std::string roomId, bool status, StBarrage barrage) override;

	virtual void onIMMessage(std::string roomId, StIMMessage message) override;

	virtual void onIMPermission(std::string roomId, EnIMPermission permission) override;
     
	virtual void onCountDown(std::string roomId, std::string subject, std::string creator, long long startTime, int minutesAheadOfSchedule) override;

	virtual void onMediaModeChanged(EnMediaMode mediaMode) override;

	virtual void onMeetingLayoutChanged(std::vector<StView> streamLayoutList) override;

	virtual void onNumberOfParticipantChanged(int numberOfParticipant) override;

public:
    void setJNIJavaRoomObserver(jobject jniRoomObserver);

	void setGlobalRef(JNICustomGlobalRef* globalRef);

private: 
    jobject     m_jniStreamInfo;
    jobject     m_jniPartInfo;
    jobject     m_jniRoomObserver;
	JNICustomGlobalRef* m_globalRef;
};

}   // end namespace SDP

#endif
