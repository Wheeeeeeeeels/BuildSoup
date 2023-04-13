package cn.geedow.netprotocol;

import java.util.ArrayList;
import cn.geedow.netprotocol.basicDataStructure.*;

public class JNINetProtocol {
    static {
        String strLoadCheck = System.getProperty("TestDllLoaded", "false");
        if (strLoadCheck.equals("false"))
        {
            strLoadCheck = System.setProperty("TestDllLoaded", "true");
            System.loadLibrary("NetProtocol");
        }
    }

    /// 获取国际化code
    public native static int geti18n(int i18nVersion, JNICommType result);
    public native static int getAllConfig(JNICommType result);


    /// 获取当前服务器时间，登陆后有效
    public native static long getCurrentServerTime();

    public native static int arrayListTest(ArrayList<JNIOrgInfo> arrayList);

    public native static int setCommonTypeTest(JNICommType commType);

    public native static int debugTerminateNet();

    public native static int debugConvertSFU2MCU();
    public native static int jniTest(JNICalleeInfo calleeInfo);

    public native static String version();

    public native static String codeToMsg(int code);

    public native static int setLogObserver(JNILogObserver logObserver);

    public native static int setLogLevel(int logLevel);

    public native static int getNetworkConnectStatus(JNICommType status);

    /// Media Channel
    public native static int createMediaChannel(String sdpOffer, JNICommType channelId, JNICommType channelResponse);

    public native static int destroyMediaChannel(String channelId);

    public native static int addMediaTrack(ArrayList<JNISubscribeStreamParam> params,
                              ArrayList<JNISubscribeStreamResponse> sdpAnswer,
                              ArrayList<JNISubscribeStreamResponse> failedRsp);

    public native static int removeMediaTrack(String account, int streamType, ArrayList<Integer> mediaType);



    public native static int notifyNetworkDeviceStatusChange(boolean status);

    public native static int init(JNIObserver observer, JNIRoomObserver roomObserver);

    public native static int uninit();

    public native static int setParams(JNIBasicInfo param);

    public native static int getParams(JNIBasicInfo param);

    public native static int setProxyServer(boolean status, JNIServerInfo serverInfo);

    public native static int setHttpUploadObserver(JNIHttpUploadObserver httpUploadObserver);

    public native static int updateUsername(String username);

    public native static int updateUserIcon(int requestCode, String filePath);

    public native static int updateToken(String account, String password, JNICommType token);

    public native static int getValidateCode(String phoneOrEmail, int usage);

    public native static int checkValidateCode(String phoneOrEmail, String validateCode, int usage, String account);

    public native static int loginByCode(String account, String validateCode, JNICommType token, JNICommType serverTime);

    public native static int loginByPwd(String account, String password, JNILoginInfo loginInfo);

    public native static int loginByToken(String account, String token, JNICommType serverTime, JNICommType accountUuid);

    public native static int logout();

    public native static int getLoginInfo(JNILoginInfo loginInfo);

    public native static int getCurrentServerInfo(JNIServerInfo serverInfo);

    public native static int uploadTerminalInfo(JNITerminalLocalInfo info);

    public native static int getOrgTree(JNICommType orgInfoLen, JNIOrgInfo[] orgInfoArray);

    public native static int getOrgMembers(int orgId, JNICommType orgMemLen, JNIOrgMemberInfo[] orgMemArray);

    /**
     * @brief 分片获取指定组织下部门信息
     * @param[in] orgId 组织ID，根节点ID=0
     * @param[in] pageInfoIn 传入的分页信息
     * @param[out] orgInfoArrayList 返回的部门信息列表
     * @param[out] pageInfoOut 平台返回的分页信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    public native static int getPagesOfOrgDepart(int orgId, JNIDataPageInfo pageInfoIn, ArrayList<JNIOrgInfo> orgInfoArrayList, JNIDataPageInfo pageInfoOut);

    /**
     * @brief 获取指定组织节点下的成员信息
     * @param[in] orgId 组织ID
     * @param[in] pageInfoIn 传入的分页信息
     * @param[out] memberInfoArrayList 返回的成员信息列表
     * @param[out] pageInfoOut 平台返回的分页信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    public native static int getPagesOfOrgMember(int orgId, JNIDataPageInfo pageInfoIn, ArrayList<JNIOrgMemberInfo> memberInfoArrayList, JNIDataPageInfo pageInfoOut);

    public native static int getOrgMemberRecursively(ArrayList<Integer> departList, ArrayList<String> accountList, ArrayList<JNIOrgMemberInfo> memberInfoArrayList);

    /**
     * @brief 获取常用联系人列表信息
     * @param[in] pageInfoIn 传入的分页信息
     * @param[out] memberInfoArrayList 常用联系人列表信息
     * @param[out] pageInfoOut 平台返回的分页信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    public native static int getFrequentContacts(JNIDataPageInfo pageInfoIn, ArrayList<JNIOrgMemberInfo> memberInfoArrayList, JNIDataPageInfo pageInfoOut);

    public native static int getMemberDetails(String account, JNIOrgMemberInfo memberInfo);

    public native static int updateContact(JNIOrgMemberInfo memberInfo);

    /* 群组相关 */
    public native static int createGroup(String groupName, String[] contactList);
    public native static int delGroup(int groupId);
    public native static int updateGroup(int groupId, String groupName, String[] contactList);
    public native static int getGroupList(int type, JNIDataPageInfo pageInfoIn, ArrayList<JNIGroupInfo> groupInfoArrayList, JNIDataPageInfo pageInfoOut);
    public native static int getGroupMember(int groupId, JNIDataPageInfo pageInfoIn, ArrayList<JNIOrgMemberInfo> memberInfoArrayList, JNIDataPageInfo pageInfoOut);

    public native static int updateParticipantsOrder(ArrayList<JNIStParticipantInfo> participantInfos);

    public native static int sendMessage(String accountTo, String req, JNICommType rsp);

	public native static int createMeeting(JNIStMeeting meetingInfo);

    public native static int closeMeeting(JNIStMeeting meetingInfo);
    
	public native static int joinMeeting(JNIStMeeting meetingInfo, JNIStMeetingAttribute attributeInfo);

	public native static int leaveMeeting(JNIStMeeting meetingInfo);

    public native static int publishVideo (int streamType, String sdpOffer, boolean videoStatus, boolean audioStatus, JNICommType sdpAnswer);

    public native static int stopPublishVideo (int streamType);

    public native static int stopReceiveVideo(String account, int streamType);

    public native static int receiveVideo (String account, int streamType, String sdpOffer, JNICommType sdpAnswer);

    public native static int setPushStreamStatus(String account, int streamType, int status);

    public native static int setPullStreamStatus(ArrayList<JNIMediaControlParam> params, int status);

    public native static int sendIceCandidate(String account, int streamType, String sdpMid, String sdpMLineIndex, String Candidate);

    public native static int setShareState(String operateAccount, String shareAccount, boolean shareState);

	public native static int getMeetingInfo(JNIStMeeting meetingInfo);

    public native static int setMeetingInfo(int option, JNIStMeeting meetingInfo);

    public native static int getAllParticipantsHaveNotJoined (ArrayList<JNIStParticipantInfo> participantInfos);
    public native static int delParticipantHaveNotJoined(ArrayList<String> account);

    public native static int getPagesOfParticipants(int order, int countOfParticipant, boolean isPositiveSequence, ArrayList<JNIStParticipantInfo> participantInfos);
    public native static int getAllPublishers(ArrayList<JNIStParticipantInfo> participantInfos, JNIStParticipantInfo participantInfo_lecturer, JNIStParticipantInfo participantInfo_partShared);
    public native static int getPartOfParticpantWhoRaiseHand(ArrayList<JNIStParticipantInfo> participantList);
    public native static int getAllPollers(ArrayList<JNICommType> pollerList);
    public native static int getParticipant(String account, JNIStParticipantInfo participant);
    public native static int getParticipantByName(String name, ArrayList<JNIStParticipantInfo> participantInfos);
    public native static int getSubscriber(String account, JNIStParticipantInfo participant);

    public native static int inviteParticipant(String roomId, String[] accountToList, long expireTime);
    public native static int cancelInvite(String roomId, String[] accountToList);
    public native static int getCalleeList(ArrayList<JNICalleeInfo> calleeList);
    public native static int removeCallee(ArrayList<JNICalleeInfo> calleeList);

    public native static int ringing(String roomId, String accountTo);

    public native static int refuseInvite(String roomId, String accountTo, int reason);

    public native static int switchVideo(String[] accountToList, boolean action);

    public native static int switchAudioIn(String[] accountToList, boolean action);

    public native static int switchAudioOut(String[] accountToList, boolean action);

    public native static int setHandStatus(String[] accountToList, boolean status);

    public native static int getRoomSettings(JNICommType roomCapacity);

    public native static int getH5Pages(int h5PageType, ArrayList<JNIH5PageInfo> jnih5PageInfos);

    public native static int getH5PagesByHttp(int h5PageType, ArrayList<JNIH5PageInfo> jnih5PageInfos);

    public native static int loginAsVisitor(String username, String mac, JNICommType account, JNICommType serverTime);

    public native static int resetPassword(String account, String validateCode, String newPassword);

    public native static int getAppointedMeetingRoom(String roomId, JNIMeetingRoom meetingRoom, JNICommType ruid);

    public native static int getMeetSimplify(String ruid, JNIStMeeting meeting);

    public native static int getAllMeetingRooms(JNIDataPageInfo pageInfoIn, boolean ifLimitedByPermission, JNIAllMeetingRooms meetingRooms, JNIDataPageInfo pageInfoOut);

    public native static int createAppointConference(JNIStAppointConference conferenceInfo);

    public native static int updateAppointConference(JNIStAppointConference conferenceInfo);

    public native static int cancelAppointConference(String ruid);

    public native static int deleteAppointConference(String ruid);

    public native static int getAllConferenceSummary(int status, String date, JNIDataPageInfo pageInfoIn, ArrayList<JNIStAppointConference> summaries, JNIDataPageInfo pageInfoOut);

    public native static int getAllConferenceSummaryOfPeriodOfTime(
        int status, String startDate, String endDate, JNIDataPageInfo pageInfoIn, ArrayList<JNIStAppointConference> summaries, JNIDataPageInfo pageInfoOut);

    public native static int getAllConferenceSummaryOfSpecifiedRoom(
        String roomId, JNIDataPageInfo pageInfoIn, ArrayList<JNIStAppointConference> summaries, JNIDataPageInfo pageInfoOut);

    public native static int getAppointConferenceDetails(String ruid, JNIStAppointConference conferenceInfo, JNICommType isStart);

    public native static int getPersonalConfRoomInfo(JNIConfRoomInfo roomInfo);

    public native static int updatePersonalConfRoomInfo(JNIConfRoomInfo roomInfo);

    public native static int modifyPassword(String originalPassword, String newPassword);

    public native static int switchVoiceMode(int operation);

    public native static int evictedParticipant(String account);

    public native static int needVersionUpgrade(JNICommType needUpgrade, JNICommType forceStatus, JNICommType downLoadUrl, JNICommType version, JNICommType apkSize, JNICommType details);

    public native static int needVersionUpgradeV2(JNICommType needUpgrade, JNICommType forceStatus, JNICommType downLoadUrl, JNICommType version, JNICommType apkSize, JNICommType details);

    public native static int reconnect();

    public native static int startConferenceRecord(String roomId, boolean force);

    public native static int stopConferenceRecord(String roomId);

    /**
     * 获取当前录制状态
     * @param roomId 会议ID
     * @param commType commonType.boolVar表示是否正在录制，commonType.doubleNumber表示开始录制时间
     * @return
     */
    public native static int getConferenceRecordStatus(String roomId, JNICommType commType);

    public native static int getConferenceRecord(int size, int pageNum, JNICommType total, JNICommType recordListsLen, JNIConferenceRecordInfo[] recordLists);

    public native static int playbackConferenceRecord(long id, JNICommType recordUrl);

    public native static int downloadConferenceRecord(long id, JNICommType downloadUrl);

    public native static int delConferenceRecord(long id);

    public native static int startLive(String roomId, JNICommType livingUrl);

    public native static int stopLive(String roomId);

    public native static int getLiveStatus(String roomId, JNICommType livingStatus);

    public native static int httpGet(String url, JNICommType rspBody);

    public native static int pushLog(JNIPushLogParams pushLogParams);

    public native static int getUnfinishedRoom(JNIUnfinishedRoomInfo roomInfo);

    public native static int setSpeakerPermission(String roomId, boolean permitted);

    public native static int applyOpenSpeaker();

    public native static int applyOpenMic();

    public native static int getAccount(String serialNumber, JNICommType account, JNICommType password);

    public native static int setRollCallStatus(String account, String NewAccount, boolean status, int source);

    public native static int replaceLectrer(String account);

    public native static int changeMeetingLayout(int layoutType, int numberOfSplitScreen, ArrayList<JNIView> layouts);

    public native static int setPtzControlStatus(boolean action, JNIPtzControlParam param);

    public native static int adjustResolution(int resolution);

    public native static int setPresetPosition(String serialNumber, int index, String image, JNIPresetPositionConfigInfo configInfo);

    public native static int getCompanyResourceInfo(JNICompanyInfo companyInfo);

    public native static int setPollingStatus(String roomId, boolean status, int timeInterval);

    public native static int getPollingStatus(String roomId, JNICommType status);

    public native static int getIceServerList(ArrayList<JNIIceServerInfo> iceServerInfos);

    public native static int countParticipatedDuration(JNIDataPageInfo pageInfoIn, ArrayList<JNIStMeeting> meetingInfos, JNIDataPageInfo pageInfoOut);

    public native static int uploadMeetingQuality(JNINetworkQuality networkQuality, ArrayList<JNIStreamQuality> streamQualities);

    public native static int getScrollBarrage(JNICommType status, JNIBarrage barrage);

    public native static int sendIMMessage(JNIIMMessage message, String clientMsgId, JNICommType finalMsgId, JNICommType finalTimestamp);

    public native static int getIMMessageHistory(JNIIMMessage lastIMMessage, int countOfMsg, boolean isPositiveSequence, ArrayList<JNIIMMessage> messageArrayList);

    public native static int checkIfExistUnreadPushedMsg(JNICommType unreadMsgParams);

    public native static int getPagesOfPushedMsg(JNIDataPageInfo pageInfoIn, ArrayList<JNIPushedMsg> pushedMsgs, JNIDataPageInfo pageInfoOut);

    public native static int readPushedMsg(ArrayList<Long> idList);

    public native static int cleanPushedMsg();

    public native static int getDeployEnv(JNICommType isPrivateDeploy);

    public native static int uploadRegistrationId(String registrationId);

    public native static int queryOperationPermission(ArrayList<Integer> permissions, ArrayList<Integer> alilities);

    public native static int hurryUp(String roomId, String ruid);

    public native static int changeMeetingRoom(String ruid, int roomIdType, String roomId);

    public native static int prolongMeeting(int minsNeedToProlong);

    /**
     * 更换手机号
     * @param newPhoneNumber 新手机号
     * @param validateCode 验证码
     * @return
     */
    public native static int changePhoneNumber(String newPhoneNumber, String validateCode);

    /**
     * 注销账户
     * @param newPhoneNumber 新手机号
     * @param validateCode 验证码
     * @return
     */
    public native static int cancelAccount(String newPhoneNumber, String validateCode);
}
