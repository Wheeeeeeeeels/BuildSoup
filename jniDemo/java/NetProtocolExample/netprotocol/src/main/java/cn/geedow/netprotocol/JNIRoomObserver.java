package cn.geedow.netprotocol;

import android.util.Log;

import java.util.ArrayList;

import cn.geedow.netprotocol.basicDataStructure.JNIBarrage;
import cn.geedow.netprotocol.basicDataStructure.JNIIMMessage;
import cn.geedow.netprotocol.basicDataStructure.JNIPresetPositionConfigInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIView;

public class JNIRoomObserver {
    private static final String TAG = "JNIRoomObserver";
    
    public void onMeetingCreated(String roomId) {
        Log.d(TAG, "JAVA onMeetingCreated");
    }

    public void onMeetingClosed(int reason){
        Log.d(TAG, "JAVA onMeetingClosed");
    }

    public void onMeetingInfoChanged(int option, JNIStMeeting meeting){
        Log.d(TAG, "JAVA onMeetingInfoChanged");
    }

    public void onJoined(String roomId, String account, JNIStParticipantInfo participant){
        Log.d(TAG, "JAVA onJoined");
    }

    public void onLeftNotify(String roomId, String account, int reason){
        Log.d(TAG, "JAVA onLeft reason");
    }

    public void onPublished(String roomId, String account, int streamType, boolean videoStatus, boolean audioStatus){
        Log.d(TAG, "JAVA onPublished");
    }

    public void onStopPublished(String roomId, String account, int streamType){
        Log.d(TAG, "JAVA onStopPublished");
    }

    public void onIceCandidate(String roomId, String account, int streamType, String sdpMid, String sdpMLineIndex, String candidate){
        Log.d(TAG, "JAVA onIceCandidate");
    }

    public void onSetShareState(String handleAccount, String shareAccount, boolean shareState) {
        Log.d(TAG, "JAVA onSetShareState");
    }

    public void onInvite(String roomId, String subject, String accountFrom, String usernameFrom,
                         long expireTime, String password, String userIcon, boolean audioInStatus, boolean videoStatus){
        Log.d(TAG, "JAVA onInvite");
    }

    public void onCancelInvite(String roomId, String accountFrom, String usernameFrom){
        Log.d(TAG, "JAVA onCancelInvite");
    }

    public void onRinging(String roomId, String accountFrom) {
        Log.d(TAG, "JAVA onRinging");
    }

    public void onRefuseInvite(String roomId, String accountFrom, String usernameFrom, int reason){
        Log.d(TAG, "JAVA onRefuseInvite");
    }

    public void onToggleCamera(){
        Log.d(TAG, "JAVA onToggleCamera");
    }

    public void onVideoStatus(String roomId, String accountFrom, String accountTo, boolean status){
        Log.d(TAG, "JAVA onVideoStatus");
    }

    public void onAudioInStatus(String roomId, String accountFrom, String accountTo, boolean status){
        Log.d(TAG, "JAVA onAudioInStatus");
    }

    public void onAudioOutStatus(String roomId, String accountFrom, String accountTo, boolean status){
        Log.d(TAG, "JAVA onAudioOutStatus");
    }

    public void onHandStatus(String roomId, String accountFrom, String accountTo, boolean status){
        Log.d(TAG, "JAVA onHandStatus");
    }

    public void onSetRollCallStatus(boolean lecturerStatus, String newLecturer, String oldLecturer) {
        Log.d(TAG, "JAVA onSetRollCallStatus");
    }

    public void onNotifyPartRoleChanged(String account, int presentRole){
        Log.d(TAG, "JAVA onNotifyPartRoleChanged 1.3.5");
    }

    public void onSwitchVoiceModeNotify(String account, int operation){
        Log.d(TAG, "JAVA onSwitchVoiceModeNotify");
    }

    public void onDisconnect(String account){
        Log.d(TAG, "JAVA onDisconnect");
    }

    public void onReconnect(String account){
        Log.d(TAG, "JAVA onReconnect");
    }

    public void onTempBroken(String account){
        Log.d(TAG, "JAVA onTempBroken");
    }

    public void onStartConferenceRecord(long startRecordingTime) {
        Log.d(TAG, "JAVA onStartConferenceRecord");
    }

    public void onStopConferenceRecord(boolean isStoped, int reason) {
        Log.d(TAG, "JAVA onStopConferenceRecord");
    }

    public void onStartLive() {
        Log.d(TAG, "JAVA onStartLive");
    }

    public void onStopLive() {
        Log.d(TAG, "JAVA onStopLive");
    }

    public void onUpdateParticipantsOrder(ArrayList<JNIStParticipantInfo> participantInfos) {
        Log.d(TAG, "JAVA onUpdateParticipantsOrder");
    }

    public void onUpdateParticipantsOrder(JNIStParticipantInfo[] participantInfos, int size) {
        Log.d(TAG, "JAVA onUpdateParticipantsOrder");
    }

	public void onSetSpeakerPermission(String account, boolean action){
        Log.d(TAG, "JAVA onSetSpeakerPermission");	
	}

	public void onMessage(String account, String nickName, int msgType){
		Log.d(TAG, "JAVA onMessage");
	}

    public void onSetPushStreamStatus(String roomId, String account, int streamType, int status){
        Log.d(TAG, "JAVA onSetPushStreamStatus");
    }

    public void onSetPtzControlStatus(boolean action, String serialNumber, int operationCode, int maxDuration){
        Log.d(TAG, "JAVA onSetPtzControlStatus");
    }

    public void onAdjustResolution(String serialNumber, int resolution){
        Log.d(TAG, "JAVA onAdjustResolution");
    }

    public void onAdjustToPresetPosition(String serialNumber, int index, JNIPresetPositionConfigInfo configInfo)
    {
        Log.d(TAG, "JAVA onAdjustToPresetPosition");
    }

    public void onSetPollingStatus(String roomId, boolean status, int timeInterval)
    {
        Log.d(TAG, "JAVA onSetPollingStatus");
    }

    public void onPollingNotify(int pollingNotify, String account) {
        Log.d(TAG, "JAVA onPollingNotify");
    }

    public void onRoomAutoProlong(String roomId, String ruid) {
        Log.d(TAG, "JAVA onRoomAutoProlong");
    }

    public void onUploadMeetingQuality(String roomId){
        Log.d(TAG, "JAVA onUploadMeetingQuality");
    }

    public void onScrollBarrage(String roomId, boolean status, JNIBarrage barrage){
        Log.d(TAG, "JAVA onScrollBarrage");
    }

    public void onIMMessage(String roomId, JNIIMMessage message) {
        Log.d(TAG, "JAVA onIMMessage");
    }

    public void onIMPermission(String roomId, int permission) {
        Log.d(TAG, "JAVA onIMPermission");
    }

    public void onCountDown(String roomId, String subject, String creator, long startTime, int minutesAheadOfSchedule) {
        Log.d(TAG, "JAVA onCountDown");
    }

    public void onMediaModeChanged(int mediaMode) {
        Log.d(TAG, "JAVA onMediaModeChanged");
    }

    public void onMeetingLayoutChanged(JNIView[] layouts, int size) {
        Log.d(TAG, "JAVA onMeetingLayoutChanged");
    }

    public void onNumberOfParticipantChanged(int numberOfParticipant) {
        Log.d(TAG, "JAVA onNumberOfParticipantChanged: " + numberOfParticipant);
    }
}
