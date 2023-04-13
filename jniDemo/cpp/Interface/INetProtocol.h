
#ifndef __SRC_INTERFACE_INETPROTOCOL_H__
#define __SRC_INTERFACE_INETPROTOCOL_H__

#ifdef __cplusplus

#include <list>
#include <vector>
#include <string>
#include <map>
#include <functional>

#include "SDNPDefine.h"



namespace SDNP
{

/**
 * @brief 日志回调函数定义
 * @param[in] level 当前日志信息级别
 * @param[in] data 当前日志信息指针
 * @param[in] len 当前日志信息长度
 * @return 无
 */
typedef void (*FuncOnLog)(EnLogLevel level, const char *data, int len);

/// MARK: - ILogObserver
class SD_INTERFACE_EXPORT ILogObserver
{
public:
    virtual void onPrintLog(int level, std::string logMessage) = 0;

    virtual void setLogLevel(int logLevel) {
        m_logLevel = logLevel;
    }

    int getLogLevel() {
        return m_logLevel;
    }

private:
    int  m_logLevel;
};

/// MARK: - IObserver
class SD_INTERFACE_EXPORT IObserver
{
public:
    
    /// sdk 状态变化通知
    /// NetSDK告诉外面内部连接状态；
    virtual void onNetworkConnectStatusChange(EnNetState state, int code, std::string message) = 0;
    
    /// sdk 通知 客户端，Server Service 是否可用
    virtual void onServiceAvailableChange(bool available, int code, std::string message) = 0;
    
	/**
     * @brief sdk请求native当前网络环境
     * @return EnDeviceNetState
     */
    virtual EnDeviceNetState onFetchDeviceNetState() = 0;


    /**
     * @brief token失效通知，调用者应使用密码重新登录
     * @return 无
     */
    virtual void onTokenBecameInvalid() = 0;

    /**
     * @brief 当前账号已被其他人登录通知，调用者应使用密码重新登录
     * @return 无
     */
    virtual void onOthersLogin() = 0;

    /**
     * @brief 在线状态变化通知
     * @param[in] online 在线状态，true表示在线，false表示离线
     * @return 无
     */
    virtual void onOnlineStateChange(bool online) = 0;

    /**
    * @brief 版本升级通知
    * @param[in] foreStatus true表示强制版本升级，false表示非强制版本升级
    * @param[in] downLoadUrl 版本升级地址
    * @param[in] version 版本号
    * @param[in] details 升级详情描述
    * @return 无
    */  
	virtual void onVersionUpgrade(bool foreStatus, std::string downLoadUrl, std::string version, std::string details) {}

	/**
	* @brief 版本升级通知
	* @param[in] serialNumber 硬终端序列号
	* @param[in] foreStatus true表示强制版本升级，false表示非强制版本升级
	* @param[in] downLoadUrl 版本升级地址
	* @param[in] version 版本号
	* @param[in] details 升级详情描述
	* @return 无
	*/
	virtual void onVersionUpgrade(std::string serialNumber, bool foreStatus, std::string downLoadUrl, std::string version, std::string details) {}

	/**
	 * @brief 平台拉取终端日志通知
	 * @param[in] params 拉取参数
	 */
	virtual void onPushLog(PushLogStrategy strategy) {}

	/**
	 * @brief 平台拉取终端日志完成通知
	 * @param[in] result true表示成功，false表示失败
	 */
	virtual void onPushLogResult(bool result) {}

	/**
	 * @brief 服务到期通知
	 * @param[in] isExpired true表示到期，false表示未到期
	 * @param[in] expiredDate 企业服务到期时间
	 * @param[in] daysToExpiredDate 距到期时间天数
	 */
	virtual void onServiceExpired(bool isExpired, std::string expiredDate, int daysToExpiredDate) = 0;

	/**
	 * @brief 通话时长情况通知
	 * @param[in] duration 剩余通话时长枚举
	 * @param[in] hours 剩余通话时长小时数
	 * @param[in] minutes 剩余通话时长分钟数
	 */
	virtual void onConversationDurationStatus(EnConversationDuration duration, int hours, int minutes) = 0;

	/**
	 * @brief 时间校准通知
	 * @param[in] serverTimestamp 服务器时间戳
	 */
	virtual void onTimeSynchronization(long long serverTimestamp) = 0;

	/**
	 * @brief 设备被企业删除通知，仅硬终端有效
	 */
	virtual void onEvictedByCorp() {}

	/**
	 * @brief 硬终端设备信息变更通知
	 * @param[in] deviceInfo 硬终端设备信息
	 */
	virtual void onHardTerminalDeviceInfoChanged(StHardTerminalDeviceInfo deviceInfo) {}

	/**
	* @brief 预约会议即将开始通知
	* @param[in] username 会议发起人昵称
	* @param[in] subject 会议主题
	* @param[in] startTime 开始时间
	* @param[in] endTime 结束时间
	* @return 无
	*/
	virtual void onConferenceToBegin(std::string username, std::string subject, long long startTime, long long endTime) = 0;

	/**
	* @brief 预约会议创建通知
	* @param[in] username 会议发起人昵称
	* @param[in] subject 会议主题
	* @param[in] startTime 开始时间
	* @param[in] endTime 结束时间
	* @return 无
	*/
	virtual void onConferenceCreated(std::string username, std::string subject, long long startTime, long long endTime) = 0;

	/**
	* @brief 预约会议取消通知
	* @param[in] roomId 会议室ID
	* @param[in] ruid 会议ID
	* @param[in] subject 会议主题
	* @param[in] reason 取消原因
	* @return 无
	*/
	virtual void onConferenceCanceled(std::string roomId, std::string ruid, std::string subject, EnConferenceCanceledReason reason) = 0;

protected:
    /**
     * @brief 析构函数
     * @return 无
     */
    virtual ~IObserver() {}
};

/// MARK: - IRoomObserver
class SD_INTERFACE_EXPORT IRoomObserver
{
public:
    /**
     * @brief 会议创建完成通知
     * @param[in] roomId 会议室ID
     * @return 无
     */
	virtual void onMeetingCreated(std::string roomId) = 0;

    /**
	 * @brief 会议结束通知
	 * @param[in] reason 房间关闭原因
     * @return 无
     */
	virtual void onMeetingClosed(EnMeetingClosedReason reason) = 0;

	/**
	 * @brief 会议信息变更通知
	 * @param[in] option: 变更的会议属性
	 * @param[in] meetingInfo: 最新的会议信息
	 * @return 无
	 */
	virtual void onMeetingInfoChanged(EnMeetingInfoOption option, StMeeting meetingInfo) = 0;

    /**
     * @brief 与会者加入通知
     * @param[in] roomId 会议室ID
     * @param[in] account 与会者账号
     * @param[in] participant 与会者详细信息
     * @return 无
     */
    virtual void onJoined(std::string roomId, std::string account, StParticipantInfo participant) = 0;

  
	/**
	 * @brief 与会者离开通知，合并onLeft、onEvicted、onBreakLine
	 * @param[in] roomId 会议室ID
	 * @param[in] account 与会者账号
	 * @param[in] streamType 媒体流类型
	 * @param[in] reason 离开原因
	 * @return 无
	 */
	virtual void onLeftNotify(std::string roomId, std::string account, EnParticipantLeftReason reason) = 0;

    /**
     * @brief 与会者发布媒体流通知
     * @param[in] roomId 会议室ID
     * @param[in] account 与会者账号
     * @param[in] streamType 媒体流类型
     * @param[in] hasVideo 是否有视频
     * @param[in] hasAudio 是否有音频
     * @return 无
     */
    virtual void onPublished(std::string roomId, std::string account, EnStreamType streamType, bool videoStatus, bool audioStatus) = 0;

    /**
     * @brief 与会者停止发布媒体流通知
     * @param[in] roomId 会议室ID
     * @param[in] account 与会者账号
     * @param[in] streamType 媒体流类型
     * @return 无
     */
    virtual void onStopPublished(std::string roomId, std::string account, EnStreamType streamType) = 0;

    /**
     * @brief 收到ICE Candidate信息通知
     * @param[in] roomId 会议室ID
     * @param[in] account 目标用户账号P
     * @param[in] streamType 码流类型
     * @param[in] sdpMid 媒体ID
     * @param[in] sdpMLineIndex 媒体描述行索引
     * @param[in] candidate Candidate信息
     * @return 无
     */
    virtual void onIceCandidate(std::string roomId, std::string account, EnStreamType streamType, std::string sdpMid, std::string sdpMLineIndex, std::string candidate) = 0;

	/**
	 * @brief 设置共享状态通知
	 * @param[in] handleAccount: 操作者账号
	 * @param[in] shareAccount: 共享者账号
	 * @param[in] shareState: true表示开启共享，false表示结束共享
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual void onSetShareState(std::string handleAccount, std::string shareAccount, bool shareState) = 0;

	/**
	 * @brief 收到会议邀请通知（受邀者收到回调）
	 * @param[in] roomId 会议室ID
	 * @param[in] subject 会议主题
	 * @param[in] accountFrom 邀请人账号
	 * @param[in] usernameFrom 邀请人名称
	 * @param[in] expireTime 有效时长
	 * @param[in] password 会议设置密码时携带
	 * @param[in] userIcon 邀请人头像
	 * @param[in] micStatus 入会时麦克风状态
	 * @param[in] cameraStatus 入会时摄像头状态
	 * @return 无
	 */
	virtual void onInvite(std::string roomId, std::string subject, std::string accountFrom, std::string usernameFrom, 
		long long expireTime, std::string password, std::string userIcon, bool micStatus, bool cameraStatus) = 0;

    /**
     * @brief 收到取消会议邀请通知（受邀者收到回调）
     * @param[in] roomId 会议室ID
     * @param[in] accountFrom 取消邀请人账号
     * @param[in] usernameFrom 取消邀请人名称
     * @return 无
     */
    virtual void onCancelInvite(std::string roomId, std::string accountFrom, std::string usernameFrom) = 0;

    /**
     * @brief 收到响铃通知（邀请者收到回调）
     * @param[in] roomId 会议室ID
     * @param[in] accountFrom 响铃通知发起人账号
     * @return 无
     */
    virtual void onRinging(std::string roomId, std::string accountFrom) = 0;

    /**
     * @brief 收到拒绝会议邀请通知（邀请者收到回调）
     * @param[in] roomId 会议室ID
     * @param[in] accountFrom 拒绝邀请人账号
     * @param[in] usernameFrom 拒绝邀请人名称
     * @param[in] reason 拒绝邀请原因
     * @return 无
     */
    virtual void onRefuseInvite(std::string roomId, std::string accountFrom, std::string usernameFrom, EnRefuseInviteReason reason) = 0;

    /**
     * @brief 【硬终端】与会者摄像头切换通知
     * @return 无
     */
    virtual void onToggleCamera() {};

    /**
     * @brief 与会者视频（摄像机）状态变化通知
     * @param[in] roomId 会议室ID
     * @param[in] accountFrom 控制发起人账号
     * @param[in] accountTo 控制目标人账号
     * @param[in] status 与会者视频状态，true表示打开，false表示关闭
     * @return 无
     */
    virtual void onVideoStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status) = 0;

    /**
     * @brief 与会者声音输入（麦克风）状态变化通知
     * @param[in] roomId 会议室ID
	 * @param[in] accountFrom 控制发起人账号
	 * @param[in] accountTo 控制目标人账号，值为空表示控制全体与会者
	 * @param[in] status 与会者声音输入状态，true表示打开，false表示关闭
     * @return 无
     */
    virtual void onAudioInStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status) = 0;

    /**
     * @brief 与会者声音输出（扬声器）状态变化通知
     * @param[in] roomId 会议室ID
	 * @param[in] accountFrom 控制发起人账号
	 * @param[in] accountTo 控制目标人账号，值为空表示控制全体与会者
	 * @param[in] status 与会者声音输出状态，true表示打开，false表示关闭
     * @return 无
     */
    virtual void onAudioOutStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status) = 0;

    /**
     * @brief 与会者举手状态变化通知
     * @param[in] roomId 会议室ID
	 * @param[in] accountFrom 控制发起人账号
	 * @param[in] accountTo 控制目标人账号
	 * @param[in] status 与会者举手状态，true表示举手，false表示放下手
     * @return 无
     */
    virtual void onHandStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status) = 0;

	/**
	 * @brief 点名发言状态变更通知
	 * @param[in] lectureStatus: 发言状态，true表示发言，false表示结束发言
	 * @param[in] newLecturer: 新的发言者
	 * @param[in] oldLecturer: 旧的发言者，空字符串表示当前会议没有发言者
	 * @return 无
	 */
	virtual void onSetRollCallStatus(bool lectureStatus, std::string newLecturer, std::string oldLecturer) = 0;

	/**
	 * @brief 云平台通知参会者角色变更
	 * @param[in] account 与会者账号
	 * @param[in] presentRole 与会者当前角色
	 * @return 无
	 */
	virtual void onNotifyPartRoleChanged(std::string account, EnRoomRole presentRole) = 0;

    /**
     * @brief 云平台通知其他参与方，与会者切换语音模式
     * @param[in] account 与会者账号
     * @param[in] operation SWITCH_ON：会议中切换语音模式，SWITCH_OFF：会议中关闭语音模式
     * @return 无
     */
    virtual void onSwitchVoiceModeNotify(std::string account, EnSwitch operation) = 0;

	/**
	 * @brief 云平台通知其他参与方，与服务器断开连接
	 * @param[in] account 与会者账号
	 * @return 无
	 */
    virtual void onDisconnect(std::string account){};

	/**
	 * @brief 云平台通知其他参与方，与服务器重新连接
	 * @param[in] account 与会者账号
	 * @return 无
	 */
    virtual void onReconnect(std::string account){};

	/**
	 * @brief 云平台通知其他参与方，网络断开
	 * @param[in] account 与会者账号
	 * @return 无
	 */
    virtual void onTempBroken(std::string account){};

	/**
	 * @brief 云平台通知其他参与方，开始录制
	 * @param[in] startRecordingTime 开始录制时间戳
	 * @return 无
	 */
    virtual void onStartConferenceRecord(long long startRecordingTime) = 0;

	/**
	 * @brief 云平台通知其他参与方，停止录制
	 * @param[in] isStoped: 是否停止，true表示停止，false表示未停止
	 * @param[in] reason: 停止录制原因
	 * @return 无
	 */
    virtual void onStopConferenceRecord(bool isStoped, EnStopRecordReason reason) = 0;

    /**
     * @brief 直播开始通知
     * @return 无
     */
    virtual void onStartLive() = 0;

	/**
	 * @brief 直播停止通知
	 * @return 无
	 */
	virtual void onStopLive() = 0;

	/**
	 * @brief 与会者顺序变动通知
	 * @param[in] participantList 与会者列表
	 * @return 无
	 */
	virtual void onUpdateParticipantsOrder(std::vector<StParticipantInfo> participantList) = 0;

	/**
	 * @brief 实时转写/翻译结果回调
	 * @param[in]
	 * @return 无
	 */
	virtual void onNLPResults(StSubtitle subtitle) {};

	/**
	 * @brief 设置是否允许参会者自主开启扬声器通知
	 * @param[in] account 主持人账号
	 * @param[in] action 是否允许参会者自主开启扬声器，true表示允许，false表示不允许
	 * @return 无
	 */
	virtual void onSetSpeakerPermission(std::string account, bool action) = 0;

	/**
	 * @brief 消息通知
	 * @param[in] account 发消息与会者的账号
	 * @param[in] nickname 发消息与会者的昵称
	 * @param[in] msgType 消息类型
	 * @return 无
	 */
	virtual void onMessage(std::string account, std::string nickname, EnMessageType msgType) = 0;

	/**
	 * @brief 设置推流状态通知
	 * @param[in] roomId 会议室ID
	 * @param[in] account 设置推流状态的用户账号
	 * @param[in] streamType 流类型
	 * @param[in] status 流状态
	 * @return 无
	 */
	virtual void onSetPushStreamStatus(std::string roomId, std::string account, EnStreamType streamType, EnStreamStatus status) = 0;

	/**
	 * @brief 硬终端云台控制通知
	 * @param[in] action: true表示开始控制云台，false表示结束控制云台
	 * @param[in] serialNumber: 硬终端序列号
	 * @param[in] param: 云台控制参数
	 * @return 无
	 */
	virtual void onSetPtzControlStatus(bool action, std::string serialNumber, StPtzControlParam param) {}

	/**
	 * @brief 硬终端调整分辨率通知
	 * @param[in] serialNumber: 硬终端序列号
	 * @param[in] resolution: 分辨率，枚举值为：360,720,1080
	 * @return 无
	 */
	virtual void onAdjustResolution(std::string serialNumber, int resolution) {}

	/**
	 * @brief 硬终端调整至预置点通知
	 * @param[in] serialNumber: 硬终端序列号
	 * @param[in] index: 硬终端预置点索引
	 * @param[in] configInfo: 硬终端预置点配置信息
	 * @return 无
	 */
	virtual void onAdjustToPresetPosition(std::string serialNumber, int index, StPresetPositionConfigInfo configInfo) {}

	/**
	 * @brief 设置轮巡状态通知
	 * @param[in] roomId: 会议ID
	 * @param[in] status: 轮巡状态，true表示开始轮巡，false表示停止轮巡
	 * @param[in] timeInterval: 轮巡间隔时间，单位为秒/s
	 * @return 无
	 */
	virtual void onSetPollingStatus(std::string roomId, bool status, int timeInterval) = 0;

	/**
	 * @brief 轮巡状态通知
	 * @param[in] pollingNotify: 通知类别
	 * @param[in] account: 轮巡目标用户
	 * @return 无
	 */
	virtual void onPollingNotify(EnPollingNotify pollingNotify, std::string account) = 0;

	/**
	 * @brief 房间延时通知
	 * @param[in] roomId: 房间ID
	 * @param[in] ruid: 会议ID
	 * @return 无
	 */
	virtual void onRoomAutoProlong(std::string roomId, std::string ruid) = 0;

	/**
	 * @brief 会议质量上报通知
	 * @param[in] roomId: 房间ID
	 * @return 无
	 */
	virtual void onUploadMeetingQuality(std::string roomId) = 0;

	/**
	 * @brief 弹幕分发通知
	 * @param[in] roomId: 房间ID
	 * @param[in] status: 弹幕状态，true表示打开，false表示关闭
	 * @param[in] barrage: 弹幕信息
	 * @return 无
	 */
	virtual void onScrollBarrage(std::string roomId, bool status, StBarrage barrage) = 0;

	/**
	 * @brief IM信息推送通知
	 * @param[in] roomId: 房间ID
	 * @param[in] message: IM信息
	 * @return 无
	 */
	virtual void onIMMessage(std::string roomId, StIMMessage message) = 0;

	/**
	 * @brief IM权限设置通知
	 * @param[in] roomId: 房间ID
	 * @param[in] permission: IM权限
	 * @return 无
	 */
	virtual void onIMPermission(std::string roomId, EnIMPermission permission) = 0;

	/**
	 * @brief 倒计时通知
	 * @param[in] roomId: 会议ID
	 * @param[in] subject: 会议主题
	 * @param[in] creator: 发起人
	 * @param[in] startTime: 会议开始时间
	 * @param[in] minutesAheadOfSchedule: 提前通知分钟数，以min为单位
	 * @return 无
	 */
	virtual void onCountDown(std::string roomId, std::string subject, std::string creator, long long startTime, int minutesAheadOfSchedule) = 0;

	/**
	 * @brief 会议媒体模式变更通知
	 * @param[in] mediaMode: 媒体模式
	 * @return 无
	 */
	virtual void onMediaModeChanged(EnMediaMode mediaMode) = 0;

	/**
	 * @brief 会议布局变更通知
	 * @param[in] streamLayoutList: 流布局列表
	 * @return 无
	 */
	virtual void onMeetingLayoutChanged(std::vector<StView> streamLayoutList) = 0;

	/**
	 * @brief 人数变更变更通知
	 * @param[in] numberOfParticipant: 与会者数量
	 * @return 无
	 */
	virtual void onNumberOfParticipantChanged(int numberOfParticipant) = 0;

protected:
    /**
     * @brief 析构函数
     * @return 无
     */
    virtual ~IRoomObserver() {}
};

class SD_INTERFACE_EXPORT IHttpDownloadObserver
{
public:
    /**
     * @brief 下载数据回调
     * @param[in] requestCode 请求码，用于匹配对应下载请求
     * @param[in] buf 本次回调数据指针
     * @param[in] len 本次回调数据长度
     * @param[in] rangeBegin 本次回调数据在完整数据中的起始位置
     * @param[in] rangeEnd 本次回调数据在完整数据中的结束位置
     * @param[in] totalSize 完整数据长度
     * @return 无
     */
    virtual void onData(int requestCode, const char* buf, int len, int rangeBegin, int rangeEnd, int totalSize) = 0;

    /**
     * @brief 下载进度通知
     * @param[in] requestCode 请求码，用于匹配对应下载请求
     * @param[in] progress 进度，取值范围[0, 100]
     * @return 无
     */
    virtual void onProgress(int requestCode, int progress) = 0;

    /**
     * @brief 下载失败
     * @param[in] requestCode 请求码，用于匹配对应下载请求
     * @param[in] errorCode 错误码(CODE_DOWNLOAD_FAILED; CODE_FILE_EXIST; CODE_FILE_OPEN_ERROR)
     * @param[in] extraInfo 补充错误描述信息
     * @return 无
     */
    virtual void onFailed(int requestCode, int errorCode, std::string extraInfo) = 0;

    /**
     * @brief 下载已完成
     * @param[in] requestCode 请求码，用于匹配对应下载请求
     * @return 无
     */
    virtual void onCompleted(int requestCode) = 0;

protected:
    /**
     * @brief 析构函数
     * @return 无
     */
    virtual ~IHttpDownloadObserver() {}
};

class SD_INTERFACE_EXPORT IHttpUploadObserver
{
public:
    /**
     * @brief 上传失败
     * @param[in] requestCode 请求码，用于匹配对应上传请求
     * @param[in] errorCode 错误码(CODE_UPLOAD_FAILED; CODE_FILE_NOT_FOUND)
     * @param[in] extraInfo 补充错误描述信息
     * @return 无
     */
    virtual void onFailed(int requestCode, int errorCode, std::string extraInfo) = 0;

    /**
     * @brief 上传已完成
     * @param[in] requestCode 请求码，用于匹配对应上传请求
     * @param[in] url 文件url
     * @return 无
     */
    virtual void onCompleted(int requestCode, std::string url) = 0;

protected:
    /**
     * @brief 析构函数
     * @return 无
     */
    virtual ~IHttpUploadObserver() {}
};

/// MARK: - Http Wrap
class SD_INTERFACE_EXPORT IHttpWrapInterface {

public:

    /**
     * @brief post data.  contentType: "application/json"
     * @param[in] url: 请求地址
     * @param[in] headers: 请求header
     * @param[in] body: 请求body
     * @param[in] timeoutMs: 请求超时时间 毫秒
     * @param[in] callback: 请求结束 回调
     * @return 无
     */
    virtual void post(const std::string& url,
                      const std::map<std::string, std::string>& headers,
                      const std::string& body,
                      int timeoutMs,
                      const std::function<void(int code, std::string msg, std::string rspBody, std::map<std::string, std::string> rspHeaders)> callback) = 0;
    
    /**
     * @brief upload file,
     * @param[in] url: 请求地址
     * @param[in] headers: 请求header
     * @param[in] localFilePath: 本地file地址
     * @param[in] form: 其他form表单数据
     * @param[in] callback: 上传结束 回调
     * @return 无
     */
    virtual void postFormData(const std::string& url,
                        const std::map<std::string, std::string>& headers,
                        const std::string& localFilePath,
                        const std::map<std::string, std::string>& form,
                        int timeoutMs,
                        const std::function<void( int progress)> onProgress,
                        const std::function<void(int code, std::string msg, std::string rspBody)> callback) = 0;

    

    /**
     * @brief download file。 分片下载
     * @param[in] url: 请求地址
     * @param[in] headers: 请求header
     * @param[in] onDadaCallback: 下载数据回调 （data 二进制数据、length  二进制数据长度、totalSize 数据总长度）
     * @param[in] callback:  下载结束 回调
     * @return 无
     */
    virtual void get(const std::string& url,
                     const std::map<std::string, std::string>& headers,
                     const std::function<void(unsigned char *data,  int length, int totalSize)> onDadaCallback,
                     const std::function<void(int code, std::string msg)> callback) = 0;

};


/// MARK: - API
class SD_INTERFACE_EXPORT INetProtocol
{
public:
    /**
     * @brief 获取INetProtocol实例
     * @return INetProtocol实例
     */
    static INetProtocol* instance();

    /**
     * @brief 获取SDK版本信息
     * @return SDK版本信息
     */
    static std::string version();

    /**
     * @brief 根据错误码获取对应的描述信息
     * @param[in] code 错误码
     * @return 错误码描述信息
     */
    static std::string codeToMsg(int code);

public:
    virtual int testJson(std::string ss) = 0;
	virtual void printOrgTree(OrgInfoNode & orgTree, std::string placeholders) = 0;
	virtual int debugTerminateNet() = 0;
	virtual int debugConvertSFU2MCU() = 0;
	virtual int jniTest(StCalleeInfo& calleeInfo) = 0;
    virtual int debugPressApi() = 0;  /// 压测接口
    
    /*
     * @brief 设置Http impl参数。 在接口 setParams 之前调用
     * @param[in] httpHandler:  http 实现类
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int setHttpImplHandler(IHttpWrapInterface *httpHandler) = 0;
    
        
    /**
     * @brief 获取国际化code配置
     * @param[in] i18nVersion: 客户端本地国际化版本，默认0
     * @param[out] result: 平台返回结果，result 字段透传
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int geti18n(int i18nVersion, OUT std::string& result) = 0;
    
    
    /**
     * @brief 获取统一配置接口
     * @param[out] result: 平台返回结果，result 字段透传
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getAllConfig(OUT std::string& result) = 0;
    
    
    /**
     * @brief 获取当前服务器时间. 登陆之后有效
     * @return ms
     */
    virtual long long getCurrentServerTime() = 0;

    /**
     * @brief 设置日志参数
     * @param[in] logObserver 日志观察者对象
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int setLogObserver(ILogObserver* logObserver) = 0;

    /**
     * @brief 获取SDK网络状态， 内部不ping
     * @param[out]
     * @return
     */
    virtual int getNetworkConnectStatus(EnNetState& status) = 0;

    
	/**
	 * @brief 设置终端网络状态，内部会自动重连
	 * @param[in] status 当前网络状态，true表示外部网络连接正常，false表示外部网络连接异常
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int notifyNetworkDeviceStatusChange(bool status) = 0;

	/**
	 * @brief 重新连接，仅在websocket断开连接之后有效
	 * @return 无
	 */
	virtual void reconnect() = 0;

	/**
	 * @brief 上传终端日志
	 * @param[in] param 上传日志参数
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int pushLog(PushLogParams param) = 0;

    /**
     * @brief 初始化
     * @param[in] observer 事件观察者
     * @param[in] roomObserver 会议相关事件观察者
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int init(IObserver* observer, IRoomObserver* roomObserver) = 0;
    

    /**
     * @brief 反初始化
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int uninit() = 0;

    /**
     * @brief 设置参数
     * @param[in] param 输入参数
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int setParams(BasicInfo param) = 0;

    /**
     * @brief 获取参数
     * @param[out] param 输出参数
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getParams(OUT BasicInfo& param) = 0;

	/**
	 * @brief 设置代理服务器配置
	 * @param[in] status 是否开启代理服务器，true表示开启，false表示关闭
	 * @param[in] info 服务器信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setProxyServer(bool status, ServerInfo info) = 0;

    /**
     * @brief 更新用户名
     * @param[in] username 用户名
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int updateUsername(std::string username) = 0;

	/**
	 * @brief 更新头像
	 * @param[in] requestCode: 请求码，由上层指定
	 * @param[in] filePath: 待上传文件路径
	 * @param[in] observer: 上传事件观察者实例
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int updateUserIcon(int requestCode, std::string filePath, IHttpUploadObserver* observer) = 0;

    /**
     * @brief 更新token，只获取新token，不会登录
     * @param[in] account 用户账号
     * @param[in] password 用户密码
     * @param[out] token 临时登录令牌
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int updateToken(std::string account, std::string password, OUT std::string& token) = 0;

    /**
     * @brief 获取短信验证码
     * @param[in] phoneOrEmail 手机号或邮箱号
     * @param[in] usage 获取验证码的用途
     * @return CODE_SUCCESS表示成功，否则失败
	 */
    virtual int getValidateCode(std::string phoneOrEmail, EnValidateCodeUsage usage) = 0;

	/**
	 * @brief 检查短信验证码合法性
	 * @param[in] phoneOrEmail 手机号或邮箱号
	 * @param[in] validateCode 验证码
	 * @param[in] usage 获取验证码的用途
	 * @param[in] account 用户账号，在验证手机时必须输入
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int checkValidateCode(std::string phoneOrEmail, std::string validateCode, EnValidateCodeUsage usage, std::string account = "") = 0;

    /**
     * @brief 使用短息验证码快捷登录
     * @param[in] account 用户账号
     * @param[in] validateCode 短信验证码
     * @param[out] token 临时登录令牌
     * @param[out] serverTimestamp 服务器时间戳
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int loginByCode(std::string account, std::string validateCode, OUT std::string& token, OUT long long& serverTimestamp) = 0;

    /**
     * @brief 使用密码登录
     * @param[in] account 用户账号
     * @param[in] password 用户密码
     * @param[out] token 临时登录令牌
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int login(std::string account, std::string password, OUT std::string& token) = 0;

    /**
     * @brief 使用token登录，若返回token无效CODE_TOKEN_INVALID，需要重新使用密码登录，并更新token
     * @param[in] account 用户账号
	 * @param[in] token 终端保存的临时登录令牌
	 * @param[out] serverTimestamp 服务器时间戳
	 * @param[out] accountUuid 登录用户uuid
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int login(std::string account, std::string token, OUT long long& serverTimestamp, OUT std::string& accountUuid) = 0;

    /**
     * @brief 使用密码登录
     * @param[in] account 用户账号
     * @param[in] password 用户密码
     * @param[out] loginInfo 登录信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int login(std::string account, std::string password, OUT LoginInfo& loginInfo) = 0;

    /**
	 * @brief 登出
	 * @param[in] logoutFromPlatform: true表示从平台注销，false表示仅本地释放资源
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int logout(bool logoutFromPlatform = true) = 0;

	/**
	 * @brief 获取自己的登录信息
	 * @param[in] loginInfo: 登录信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getLoginInfo(OUT LoginInfo& loginInfo) = 0;

	/**
	 * @brief 获取当前正在连接的服务器信息
	 * @param[in] serverInfo: 服务器信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getCurrentServerInfo(OUT ServerInfo& serverInfo) = 0;

	/**
	 * @brief 设备本地信息上传
	 * @param[in] info 设备本地信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int uploadTerminalInfo(StTerminalLocalInfo info) = 0;

    /**
     * @brief 获取通讯录组织树
     * @param[out] orgList 返回的组织树节点信息列表
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getOrgTree(OUT std::vector<OrgInfo>& orgList) = 0;

	/**
	 * @brief 分片获取指定组织下部门信息
	 * @param[in] orgId 组织ID，根节点ID=0
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] departList 返回的部门信息列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getPagesOfOrgDepart(
		int orgId,
		StDataPageInfo pageInfoIn,
		OUT std::vector<OrgInfo>& departList,
		OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 获取通讯录组织树
	 * @param[out] orgTree 返回的组织树节点信息树
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getOrgTree(OUT OrgInfoNode& orgTree) = 0;

    /**
     * @brief 获取指定组织节点下的所有成员
     * @param[in] orgId 组织树节点ID
     * @param[out] memberList 成员信息列表
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getOrgMembers(int orgId, OUT std::vector<OrgMemberInfo>& memberList) = 0;

	/**
	 * @brief 获取指定组织节点下的成员信息，仅获取当前深度下的成员
	 * @param[in] orgId 组织ID
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] memberList 返回的成员信息列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getPagesOfOrgMember(
		int orgId,
		StDataPageInfo pageInfoIn,
		OUT std::vector<OrgMemberInfo>& memberList,
		OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 获取指定组织节点下的所有成员信息，包括子节点下的成员
	 * @param[in] departIdList 需要查询的部门ID数组
	 * @param[in] accountList 需要去重的成员账号数组
	 * @param[out] memberInfoList 去重后的所有成员信息数组
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getOrgMemberRecursively(std::vector<int> departIdList, std::vector<std::string> accountList, OUT std::vector<OrgMemberInfo>& memberInfoList) = 0;

	/**
	 * @brief 获取常用联系人列表信息
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] contactList 常用联系人列表信息
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getFrequentContacts(StDataPageInfo pageInfoIn, OUT std::vector<OrgMemberInfo>& contactList, OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 获取指定联系人详细信息
	 * @param[in] account 联系人账号
	 * @param[out] memberInfo 联系人详细信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getMemberDetails(std::string account, OUT OrgMemberInfo& memberInfo) = 0;

	/**
	 * @brief 更新指定联系人信息
	 * @param[in] memberInfo 联系人详细信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int updateContact(OrgMemberInfo memberInfo) = 0;

	/**
	 * @brief 创建群组
	 * @param[in] contactList 联系人列表
	 * @param[in] groupName 群组名称
	 * @return CODE_SUCCESS表示请求发送成功，否则失败
	 */
	virtual int createGroup(std::string groupName, std::vector<std::string> contactList) = 0;

	/**
	 * @brief 删除群组
	 * @param[in] groupId 群组ID
	 * @return CODE_SUCCESS表示请求发送成功，否则失败
	 */
	virtual int delGroup(int groupId) = 0;

	/**
	 * @brief 修改群组
	 * @param[in] groupId 群组ID
	 * @param[in] groupName 群组名称
	 * @param[in] contactList 联系人列表
	 * @return CODE_SUCCESS表示请求发送成功，否则失败
	 */
	virtual int updateGroup(int groupId, std::string groupName, std::vector<std::string> contactList) = 0;

	/**
	 * @brief 查询群组列表
	 * @param[in] type 群组类型
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] groupList 群组列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示请求发送成功，否则失败
	 */
	virtual int getGroupList(EnGroupType type, StDataPageInfo pageInfoIn, OUT std::vector<StChatGroup>& groupList, OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 查询群组成员信息
	 * @param[in] groupId 群组ID
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] memberList 群组成员列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示请求发送成功，否则失败
	 */
	virtual int getGroupMember(int groupId, StDataPageInfo pageInfoIn, OUT std::vector<OrgMemberInfo>& memberList, OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 调整与会人员顺序
	 * @param[in] partList: 修改过顺序的与会者列表，仅需传入account、新的order
	 * @return CODE_SUCCESS表示请求发送成功，否则失败
	 */
	virtual int updateParticipantsOrder(std::vector<StParticipantInfo> partList) = 0;

    /**
     * @brief 发送自定义消息
     * @param[in] accountTo 消息发送对象的账号
     * @param[in] req 发送的请求消息
     * @param[out] rsp 收到的回复消息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int sendMessage(std::string accountTo, std::string req, OUT std::string& rsp) = 0;

	/**
	 * @brief 创建会议
	 * @param[in/out] meetingInfo: 传入期望创建的会议信息，传出经平台校验补充后的会议信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int createMeeting(StMeeting& meetingInfo) = 0;

	/**
	 * @brief 关闭会议
	 * @param[in] meetingInfo: 会议信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int closeMeeting(StMeeting meetingInfo) = 0;

	/**
	 * @brief 加入会议
	 * @param[in] meetingInfo: 会议信息
	 * @param[in] attributeInfo: 加入会议相关属性信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int joinMeeting(StMeeting meetingInfo, StMeetingAttribute attributeInfo) = 0;

	/**
	 * @brief 离开会议
	 * @param[in] meetingInfo: 会议信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int leaveMeeting(StMeeting meetingInfo) = 0;

    /**
     * @brief 请求发布媒体流
     * @param[in] streamType 流类型
     *          : id 媒体流ID, 不用填
     *          ：type 码流类型
     *          ：hasVideo 是否有视频
     *          ：hasAudio 是否有音频
     * @param[in] sdpOffer 媒体描述信息
     * @param[in] videoStatus 视频状态
     * @param[in] audioStatus 音频状态
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int publishVideo(EnStreamType streamType, std::string sdpOffer, bool videoStatus, bool audioStatus, OUT std::string& sdpAnswer) = 0;

    /**
     * @brief 停止发布媒体流
     * @param[in] streamType 媒体流类型
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int stopPublishVideo(EnStreamType streamType) = 0;

	/**
	 * @brief 请求接收媒体流
	 * @param[in] account: 目标用户账号
	 * @param[in] streamType: 码流类型
	 * @param[in] sdpOffer: 媒体描述请求信息
	 * @param[out] sdpAnswer: 媒体协商应答信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int receiveVideo(std::string account, EnStreamType streamType, std::string sdpOffer, OUT std::string& sdpAnswer) = 0;
    
    /// MARK: - Alpha
    /**
     * @brief 创建推拉流通道。所有的后续推拉流都基于流通道, 在推拉流时由SDK指定通道，此通道在会议中的时候由SDK和MGC来管理销毁，不区分上下行，平台仅在该成员离会或关闭会议时候注销通道
     * @param[in] sdpOffer: 媒体描述请求信息
     * @param[out] channelId: 通道ID
     * @param[out] channelResponse:  answer
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int createMediaChannel(std::string sdpOffer, OUT std::string& channelId, OUT std::string& channelResponse) = 0;
    
    /**
     * @brief 销毁推拉流通道。
     * @param[in] channelId: 通道ID
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int destroyMediaChannel(std::string channelId) = 0;
    
    
    /**
     * @brief 添加拉流。 只支持SFU
     * @param[in] params: 参数
     * @param[out] sdpAnswer: 成功的拉流响应
     * @param[out] failedIdentifier: 失败的列表
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int addMediaTrack(std::vector<StSubscribeStreamParam> params,
                              OUT std::vector<StSubscribeStreamResponse>& sdpAnswer,
                              OUT std::vector<StSubscribeStreamResponse>& failedRsp) = 0;
    
    /**
     * @brief 移除拉流
     * @param[in] account:  账号
     * @param[in] streamType: 流类型
     * @param[in] mediaType:  媒体类型
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int removeMediaTrack(std::string account, EnStreamType streamType, std::vector<EnMediaType> mediaType) = 0;
    
    

	/**
	* @brief 与会人请求停止接收指定与会者的码流
	* @param[in] account: 与会者账号
	* @param[in] streamType: 媒体流类型
	* @return CODE_SUCCESS表示成功，否则失败
	*/
	virtual int stopReceiveVideo(std::string account, EnStreamType streamType) = 0;

	/**
	 * @brief 设置推流状态
	 * @param[in] account 用户账号
	 * @param[in] streamType 流类型
	 * @param[in] status 媒体流状态
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setPushStreamStatus(std::string account, EnStreamType streamType, EnStreamStatus status) = 0;

	/**
	 * @brief 批量设置拉流状态
	 * @param[in] param 媒体流信息列表
	 * @param[in] status 媒体流状态
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setPullStreamStatus(std::vector<StMediaControlParam> param, EnStreamStatus status) = 0;

    /**
     * @brief 发送ICE Candidate信息
     * @param[in] account 目标用户账号
     * @param[in] streamType 码流类型
     * @param[in] sdpMid 媒体ID
     * @param[in] sdpMLineIndex 媒体描述行索引
     * @param[in] candidate Candidate信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int sendIceCandidate(std::string account, EnStreamType streamType, std::string sdpMid, std::string sdpMLineIndex, std::string candidate) = 0;

	/**
	 * @brief 设置共享状态
	 * @param[in] operateAccount: 操作者账号
	 * @param[in] shareAccount: 共享者账号
	 * @param[in] shareState: true表示开启共享，false表示结束共享
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setShareState(std::string operateAccount, std::string shareAccount, bool shareState) = 0;

    /**
     * @brief 获取会议信息
	 * @param[in] meetingInfo: 会议信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getMeetingInfo(OUT StMeeting& meetingInfo) = 0;

	/**
	 * @brief 会议属性设置
	 * @param[in] option: 操作的会议属性
	 * @param[in] meetingInfo: 会议信息，仅需对option关联的会议属性赋值即可
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setMeetingInfo(EnMeetingInfoOption option, StMeeting meetingInfo) = 0;

	/**
	 * @brief 获取当前会议的所有与会者信息有序列表
	 * @param[in] order: 游标位于该位置
	 * @param[in] countOfParticipant: 游标前后<countOfParticipant>个与会者信息
	 * @param[in] isPositiveSequence: true表示查询<order>之后的消息，false表示查询<order>之前的消息
	 * @param[out] participantList: 与会者信息列表
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getPagesOfParticipants(int order, int countOfParticipant, bool isPositiveSequence, OUT std::vector<StParticipantInfo>& participantList) = 0;

	/**
	 * @brief 获取当前会议的所有发布者信息
	 * @param[out] publisherList: order<角色阈值的与会者信息列表
	 * @param[out] lecturer: 发言者信息
	 * @param[out] partShared: 共享者信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getAllPublishers(OUT std::vector<StParticipantInfo>& publisherList,
		OUT StParticipantInfo& lecturer, OUT StParticipantInfo& partShared) = 0;

	/**
	 * @brief 获取当前会议的所有举手人信息
	 * @param[out] participantList: 举手人信息列表
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getPartOfParticpantWhoRaiseHand(OUT std::vector<StParticipantInfo>& participantList) = 0;

    /**
     * @brief 获取当前会议的所有轮询者信息
     * @param[out] pollerList: 轮询者账号列表
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getAllPollers(OUT std::vector<std::string>& pollerList) = 0;

	/**
	 * @brief 获取当前会议指定账号的与会者信息
	 * @param[in] account 目标用户账号
	 * @param[out] participant 与会者信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getParticipant(std::string account, OUT StParticipantInfo& participant) = 0;

	/**
	 * @brief 获取当前会议名称包含指定字符串的与会者信息
	 * @param[in] name: 目标用户昵称
	 * @param[out] participants: 与会者信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getParticipantByName(std::string name, OUT std::vector<StParticipantInfo>& participants) = 0;

	/**
	 * @brief 获取当前会议指定账号的订阅者(墙下与会者)信息
	 * @param[in] account 目标用户账号
	 * @param[out] participant 订阅者信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getSubscriber(std::string account, OUT StParticipantInfo& participant) = 0;

	/**
	 * @brief 获取当前会议的所有未入会与会者列表
	 * @param[out] participantList 与会者信息列表
	 *			 : account 与会者账号
	 *			 : nickName 与会者昵称
	 *			 : accountType 与会者账号类型
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getAllParticipantsHaveNotJoined(OUT std::vector<StParticipantInfo>& participantList) = 0;

	/**
	 * @brief 自未入会与会者列表批量删除指定与会者
	 * @param[in] account 与会者账号列表
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int delParticipantHaveNotJoined(std::vector<std::string> accounts) = 0;

	/**
	 * @brief 批量邀请与会者（邀请者调用）
	 * @param[in] roomId 邀请会议ID
	 * @param[in] accountToList 目标用户账号列表
	 * @param[in] expireTime 邀请与会者入会响铃截至时间，unix时间戳(毫秒，如1585229311000)
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int inviteParticipant(std::string roomId, std::vector<std::string> accountToList, long long expireTime) = 0;

    /**
     * @brief 取消邀请（邀请者调用）
	 * @param[in] roomId 邀请会议ID
	 * @param[in] accountToList 目标用户账号列表
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int cancelInvite(std::string roomId, std::vector<std::string> accountToList) = 0;

    /**
     * @brief 获取呼叫列表
	 * @param[in] calleeList: 被邀请用户列表
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getCalleeList(OUT std::vector<StCalleeInfo>& calleeList) = 0;

    /**
     * @brief 移除指定被呼叫者
	 * @param[in] calleeList: 被邀请用户列表
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int removeCallee(std::vector<StCalleeInfo> calleeList) = 0;

    /**
     * @brief 确认响铃（受邀者调用）
	 * @param[in] roomId 邀请会议ID
	 * @param[in] accountTo 目标用户账号
     * @return CODE_SUCCESS表示成功，否则失败
     */
	virtual int ringing(std::string roomId, std::string accountTo) = 0;

    /**
     * @brief 拒绝邀请（受邀者调用）
     * @param[in] roomId 受邀会议ID
 	 * @param[in] accountTo 邀请人账号
 	 * @param[in] reason 拒绝邀请原因
    * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int refuseInvite(std::string roomId, std::string accountTo, EnRefuseInviteReason reason) = 0;

    /**
     * @brief 开关视频（摄像机）
     * @param[in] accountToList 目标用户账号列表
     * @param[in] action 开关动作，true表示打开，false表示关闭
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int switchVideo(std::vector<std::string> accountToList, bool action) = 0;

    /**
     * @brief 开关声音输入（麦克风）
     * @param[in] accountToList 目标用户账号列表，值为空表示控制全体与会者
     * @param[in] action 开关动作，true表示打开，false表示关闭
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int switchAudioIn(std::vector<std::string> accountToList, bool action) = 0;

    /**
     * @brief 开关声音输出（扬声器）
     * @param[in] accountToList 目标用户账号列表，值为空表示控制全体与会者
     * @param[in] action 开关动作，true表示打开，false表示关闭
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int switchAudioOut(std::vector<std::string> accountToList, bool action) = 0;

	/**
	 * @brief 设置是否允许参会者自主开启扬声器（主持人权限）
	 * @param[in] roomId 会议室ID
	 * @param[in] permitted 是否允许，true表示允许，false表示不允许
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setSpeakerPermission(std::string roomId, bool permitted) = 0;

	/**
	 * @brief 申请打开扬声器（参会者）
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int applyOpenSpeaker() = 0;

	/**
	 * @brief 申请打开麦克风（参会者），在被禁止自主打开麦克风时使用
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int applyOpenMic() = 0;

	/**
	 * @brief 设置举手/放手状态
	 * @param[in] accountToList: 目标用户账号列表，举手时该参数无效
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setHandStatus(std::vector<std::string> accountToList, bool status) = 0;

	/**
	 * @brief 替换发言
	 * @param[in] endTargetId: 被替换目标人员account
	 * @param[in] startTargetId: 替换目标人员account
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int replaceLectrer(std::string endTargetId, std::string startTargetId) = 0;

    /**
     * @brief 获取会议室设置
     * @param[out] capacity 用户会议室容量
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getRoomSettings(int& capacity) = 0;

    /**
     * @brief 获取H5页面地址
     * @param[in] type 获取h5页面类型
     * @param[out] h5pageInfoList h5页面列表
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getH5Pages(EnH5PageType type, OUT std::vector<H5PageInfo>& h5pageInfoList) = 0;

	/**
     * @brief 游客登录
     * @param[in] username 游客昵称
	 * @param[in] mac 终端mac地址
	 * @param[out] visitorAccount 游客临时账号
	 * @param[out] serverTimestamp 服务器时间戳
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int loginAsVisitor(std::string username, std::string mac, OUT std::string& visitorAccount, OUT long long& serverTimestamp) = 0;

     /**
     * @brief 重置密码
     * @param[in] account 手机号或邮箱号
     * @param[in] validateCode 验证码
     * @param[in] newPassword 新密码
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int resetPassword(std::string account, std::string validateCode, std::string newPassword) = 0;

	/**
	 * @brief 获取指定的会议室信息
	 * @param[in] roomId 会议室ID
	 * @param[out] meetingRoom 会议室信息
	 * @param[out] ruid 在会议室忙碌时，表示正在进行中的会议ID
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getAppointedMeetingRoom(std::string roomId, OUT StMeetingRoom& meetingRoom, OUT std::string& ruid) = 0;
    
    /**
     * @brief 获取指定的会议信息
     * @param[in] ruid 会议ID
     * @param[out] meeting 会议信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getMeetSimplify(std::string ruid, OUT StMeeting& meeting) = 0;

	/**
	 * @brief 获取所有种类会议室信息
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[in] ifLimitedByPermission 是否受限于操作权限，true返回符合自己权限的固定会议室列表，false返回公司所有的固定会议室列表
	 * @param[out] meetingRooms 所有会议室信息
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getAllMeetingRooms(StDataPageInfo pageInfoIn, bool ifLimitedByPermission,
		OUT StAllMeetingRooms& meetingRooms, OUT StDataPageInfo& pageInfoOut) = 0;

	/**
     * @brief 预约会议
     * @param[in/out] conferenceInfo: 传入期望预约的会议信息，传出经平台校验补充后的会议信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int createAppointConference(StAppointConference& conferenceInfo) = 0;

     /**
	 * @brief 修改预约会议
	 * @param[in/out] conferenceInfo: 传入期望预约的会议信息，传出经平台校验补充后的会议信息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int updateAppointConference(StAppointConference& conferenceInfo) = 0;

    /**
	 * @brief 取消预约会议
	 * @param[in] ruid 预约会议id
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int cancelAppointConference(std::string ruid) = 0;

	/**
	 * @brief 删除预约会议
	 * @param[in] ruid 预约会议id
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int deleteAppointConference(std::string ruid) = 0;

	/**
	 * @brief 所有会议日程摘要分页查询
	 * @param[in] status: 会议状态（待参加：0 ，已结束：1）
	 * @param[in] date: 要查询的日期，格式为yyyy-MM-dd，如果查询所有日程则传入空字符串
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] summaries: 会议摘要信息列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getAllConferenceSummary(
		EnConferenceStatus status, std::string date, StDataPageInfo pageInfoIn,
		OUT std::vector <StAppointConference>& summaries, OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 指定时间段内会议日程摘要分页查询
	 * @param[in] status: 会议状态（待参加：0 ，已结束：1）
	 * @param[in] startDate: 要查询的开始日期，格式为yyyy-MM-dd
	 * @param[in] endDate: 要查询的截止日期，格式为yyyy-MM-dd
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] summaries: 会议摘要信息列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getAllConferenceSummaryOfPeriodOfTime(
		EnConferenceStatus status, std::string startDate, std::string endDate, StDataPageInfo pageInfoIn,
		OUT std::vector <StAppointConference>& summaries, OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 指定会议室日程摘要分页查询
	 * @param[in] roomId: 会议室ID
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] summaries: 会议摘要信息列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getAllConferenceSummaryOfSpecifiedRoom(
		std::string roomId, StDataPageInfo pageInfoIn,
		OUT std::vector <StAppointConference>& summaries, OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	* @brief 预约会议详情查询
	* @param[in] ruid 预约会议ID
	* @param[out] conferenceInfo 预约会议详情
	* @param[out] isStart 会议是否已经开始：true表示已开始，false表示未开始
	* @return CODE_SUCCESS表示成功，否则失败
	*/
	virtual int getAppointConferenceDetails(std::string ruid, OUT StAppointConference& conferenceInfo, OUT bool& isStart) = 0;

    /**
    * @brief 获取个人云会议室信息
    * @param[out] roomInfo 个人云会议室信息
    * @return CODE_SUCCESS表示成功，否则失败
    */
    virtual int getPersonalConfRoomInfo(OUT ConfRoomInfo& roomInfo) = 0;

    /**
    * @brief 修改个人云会议室信息
    * @param[in] roomInfo 预约会议信息
    * @return CODE_SUCCESS表示成功，否则失败
    */
    virtual int updatePersonalConfRoomInfo(ConfRoomInfo roomInfo) = 0;

	/**
	* @brief http接口获取H5页面地址
	* @param[in] type 获取h5页面类型
	* @param[out] h5pageInfoList h5页面列表
	* @return CODE_SUCCESS表示成功，否则失败
	*/
    virtual int getH5PagesByHttp(EnH5PageType type, OUT std::vector<H5PageInfo>& h5pageInfoList) = 0;

    /**
    * @brief 修改密码
    * @param[in] originalPassword 原密码
    * @param[in] newPassword 新密码
    * @return CODE_SUCCESS表示成功，否则失败
    */
    virtual int modifyPassword(std::string originalPassword, std::string newPassword) = 0;

    /**
    * @brief 会议中语音模式切换
    * @param[in] operation SWITCH_ON：会议中切换语音模式 SWITCH_OFF：会议中关闭语音模式
    * @return CODE_SUCCESS表示成功，否则失败
    */
    virtual int switchVoiceMode(EnSwitch operation) = 0;

    /**
    * @brief 踢出与会者,只有主持人有强制踢出与会者的权限
    * @param[in] account: 被踢出与会者的账号
    * @return CODE_SUCCESS表示成功，否则失败
    */
    virtual int evictedParticipant(std::string account) = 0;

	/**
    * @brief 判断是否需要版本升级
    * @param[out] needUpgrade: 是否需要升级（true是，false否）
    * @param[out] forceStatus: 是否强制升级（当needUpgrade为true时返回）
    * @param[out] downLoadUrl: 升级地址（当needUpgrade为true时返回）
    * @param[out] version 版本号
    * @param[out] apkSize 安装包大小
    * @param[out] details 升级详情描述
    * @return CODE_SUCCESS表示成功，否则失败
    */
    virtual int needVersionUpgrade(OUT bool& needUpgrade, OUT bool& forceStatus, OUT std::string& downLoadUrl, OUT std::string& version, OUT std::string& apkSize, OUT std::string& details) = 0;
    
    /**
    * @brief 判断是否需要版本升级
    * @param[out] needUpgrade: 是否需要升级（true是，false否）
    * @param[out] forceStatus:  安装方式 EnForceUpgrade
    * @param[out] downLoadUrl: 升级地址（当needUpgrade为true时返回）
    * @param[out] version 版本号
    * @param[out] apkSize 安装包大小
    * @param[out] details 升级详情描述
    * @return CODE_SUCCESS表示成功，否则失败
    */
    virtual int needVersionUpgradeV2(OUT bool& needUpgrade, OUT EnForceUpgrade& forceStatus, OUT std::string& downLoadUrl, OUT std::string& version, OUT std::string& apkSize, OUT std::string& details) = 0;

    /**
     * @brief 终端响应平台通知消息
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int responseNotify() = 0;

    /**
     * @brief 开始会议录制
     * @param[in] roomId: 录制会议id
     * @param[in] force: 是否强制录制
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int startConferenceRecord(std::string roomId, bool force = false) = 0;

     /**
     * @brief 停止录制
     * @param[in] roomId: 录制会议id
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int stopConferenceRecord(std::string roomId) = 0;

	/**
     * @brief 查询录制文件列表
     * @param[out] roomId: 录制会议id
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int getConferenceRecord(int size, int pageNum, OUT long& total, OUT std::vector<ConferenceRecordInfo>& recordLists) = 0;

    /**
     * @brief 回放录制文件
     * @param[in] id: 会议录制记录id
     * @param[out] recordUrl: 回放录制文件地址
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int playbackConferenceRecord(long id, std::string& recordUrl) = 0;

	/**
     * @brief 下载录制文件
     * @param[in] id: 会议录制记录id
     * @param[out] downloadUrl: 下载录制文件地址
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int downloadConferenceRecord(long id, std::string& downloadUrl) = 0;

    /**
     * @brief 删除录制文件
     * @param[in] id: 会议录制记录id
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int delConferenceRecord(long id) = 0;

    /**
     * @brief 开始直播
     * @param[in] roomId: 会议id
     * @return CODE_SUCCESS表示成功，否则失败
     */  
    virtual int startLive(std::string roomId, std::string &livingUrl) = 0;  

    /**
     * @brief 停止直播
     * @param[in] roomId: 会议id
     * @return CODE_SUCCESS表示成功，否则失败
     */  
    virtual int stopLive(std::string roomId) = 0;  

    /**
     * @brief 获取当前会议的直播状态
     * @param[in] roomId: 会议id
     * @param[in] livingUrl: 直播url地址
     * @return CODE_SUCCESS表示成功，否则失败
     */  
    virtual int getLiveStatus(std::string roomId, bool& livingStatus, std::string& livingUrl) = 0;  

	/**
	* @brief http get请求接口
	* @param[in] url: 请求url
	* @param[in] rspBody: 响应消息体
	* @return CODE_SUCCESS表示成功，否则失败
	*/  
    virtual int httpGet(std::string url, std::string& rspBody) = 0;

    /**
     * @brief HTTP下载请求
     * @param[in] requestCode 请求码，用于匹配对应下载回调
     * @param[in] downloadUrl 下载地址
     * @param[in] observer 下载回调对象
     * @param[in] savePath 下载数据保存路径
     * @return CODE_SUCCESS表示成功，否则失败(CODE_FAILED; CODE_RESOURCE_LIMITED)
     */
    virtual int httpDownload(int requestCode, std::string downloadUrl, IHttpDownloadObserver* observer, std::string savePath = "") = 0;

    /**
     * @brief 取消HTTP下载任务
     * @param[in] requestCode 请求码，对应请求下载时所带的请求码
     * @return CODE_SUCCESS表示成功，否则失败
     */
    virtual int cancelHttpDownload(int requestCode) = 0;

    /**
     * @brief 获取当前会议的录制状态
     * @param[in] roomId: 会议id
     * @param[in] conferenceRecordStatus: 是否正在录制
     * @param[in] startRecordTime: 开始录制时间
     * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getConferenceRecordStatus(std::string roomId, bool& conferenceRecordStatus, long long& startRecordTimeMs) = 0;

	/**
	 * @brief 设置实时转写、翻译状态
	 * @param[in] transcribeStatus: true表示打开转写，false表示关闭转写
	 * @param[in] translateStatus: true表示打开翻译，false表示关闭翻译；使用翻译功能必须打开转写功能
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setNLPStatus(bool transcribeStatus, bool translateStatus) = 0;

	/**
	 * @brief 设置实时转写、翻译参数
	 * @param[in] transcribeParam: 转写配置参数
	 * @param[in] translateParam: 翻译配置参数
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setNLPParams(StLanguageTranscribeParam transcribeParam, StLanguageTranslateParam translateParam) = 0;

	/**
	 * @brief 采集到的音频pcm数据输入到SDK，要求音频采样率为16k，声道数为单声道
	 * @param[in] data: 音频pcm数据
	 * @param[in] size: 数据长度
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int pushPCM(const char * data, int size) = 0;

	/**
	 * @brief 获取未完成会议
	 * @param[out] roomInfo: 最新与会者会议中状态信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getUnfinishedRoom(OUT StUnfinishedRoomInfo& roomInfo) = 0;
	
	/**
	 * @brief 硬终端获取账号
	 * @param[in] serialNumber 硬终端序列号
	 * @param[out] account 硬终端绑定的账号
	 * @param[out] password 硬终端绑定账号对应的密码
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getAccount(std::string serialNumber, std::string& account, std::string& password) = 0;

	/**
	 * @brief 点名发言/取消发言
	 * @param[in] oldAccount: 目标与会者账号，替换发言时该参数必须传入有效值
	 * @param[in] newAccount: 用于替换发言的新与会者账号
	 * @param[in] status: 主持人操作，true表示点名发言，false表示取消发言
	 * @param[in] source: 主持人点名发言的来源事件，取消发言时可选
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setRollCallStatus(std::string oldAccount, std::string newAccount, bool status, EnRollCallSource source = ROLLCALL_SOURCE_ACTIVE) = 0;

	/**
	 * @brief 更改会议布局
	 * @param[in] layoutType: 布局类型
	 * @param[in] numberOfSplitScreen: 分屏数量，0表示默认布局
	 * @param[in] streamLayoutList: 流布局列表，元素不需要对username、rect赋值
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int changeMeetingLayout(EnMeetingLayoutType layoutType, int numberOfSplitScreen, std::vector<StView> streamLayoutList) = 0;

	/**
	 * @brief 硬终端设置云台控制状态
	 * @param[in] action: true表示开始控制云台，false表示结束控制云台
	 * @param[in] param: 云台控制参数
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setPtzControlStatus(bool action, StPtzControlParam param) = 0;

	/**
	 * @brief 硬终端调整分辨率
	 * @param[in] resolution: 分辨率，枚举值为：360,720,1080
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int adjustResolution(int resolution) = 0;

	/**
	 * @brief 硬终端设置预置点位置
	 * @param[in] serialNumber: 硬终端序列号
	 * @param[in] index: 硬终端预置点索引
	 * @param[in] image: 硬终端预置点截屏base64编码字符串
	 * @param[in] configInfo: 硬终端预置点配置信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setPresetPosition(std::string serialNumber, int index, std::string image, StPresetPositionConfigInfo configInfo) = 0;

	/**
	 * @brief 获取公司资源信息
	 * @param[out] companyInfo: 公司信息，该接口仅支持资源信息返回，包括：expireDate,daysToExpiredDate
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getCompanyResourceInfo(StCompanyInfo& companyInfo) = 0;

	/**
	 * @brief 设置画面轮巡状态
	 * @param[in] roomId: 会议ID
	 * @param[in] status: 轮巡状态，true表示开始轮巡，false表示停止轮巡
	 * @param[in] timeInterval: 轮巡间隔时间，单位为秒/s
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int setPollingStatus(std::string roomId, bool status, int timeInterval = 0) = 0;

	/**
	 * @brief 获取画面轮巡状态
	 * @param[in] roomId: 会议ID
	 * @param[out] status: 轮巡状态，true表示开始轮巡，false表示停止轮巡
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getPollingStatus(std::string roomId, bool& status) = 0;

	/**
	 * @brief 获取ICE服务器地址列表
	 * @param[out] iceServerList: ICE服务器地址列表
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getIceServerList(std::vector<StIceServerInfo>& iceServerList) = 0;

	/**
	 * @brief 统计参会时长
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] roomInfos: 会议摘要信息列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int countParticipatedDuration(StDataPageInfo pageInfoIn,
		OUT std::vector <StMeeting>& meetingInfos, OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 上传会议质量
	 * @param[in] networkQuality: 网络质量
	 * @param[in] streamQualities: 流质量
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int uploadMeetingQuality(StNetworkQuality networkQuality, std::vector<StStreamQuality> streamQualities) = 0;

	/**
	 * @brief 获取滚动弹幕信息
	 * @param[out] status: 弹幕状态，true表示打开，false表示关闭
	 * @param[out] barrage: 弹幕信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getScrollBarrage(OUT bool& status, OUT StBarrage& barrage) = 0;

	/**
	 * @brief 向指定用户发送聊天消息
	 * @param[in] message: IM相关信息结构体
	 * @param[in] clientMsgId: 客户端为该条消息生成的唯一识别字符串，重发时必须赋值，其余场景可以为空
	 * @param[out] finalMsgId: 平台为该条消息分配的唯一ID
	 * @param[out] finalTimestamp: 该条消息自平台转发的有效时间戳
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int sendIMMessage(StIMMessage message, std::string clientMsgId, OUT long long& finalMsgId, OUT long long& finalTimestamp) = 0;

	/**
	 * @brief 获取当前会议聊天记录，该接口采用游标分页方案
	 * @param[in] lastIMMessage: 最后一条消息
	 * @param[in] countOfMsg: 游标前后<countOfMsg>条IM信息
	 * @param[in] isPositiveSequence: true表示查询<lastIMMessage>之后的消息，false表示查询<lastIMMessage>之前的消息
	 * @param[out] messageList: IM信息列表
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getIMMessageHistory(StIMMessage lastIMMessage, int countOfMsg, bool isPositiveSequence, OUT std::vector<StIMMessage>& messageList) = 0;

	/**
	 * @brief 检查当前是否有未读消息
	 * @param[out] existUnreadMsg: true表示有未读信息，false表示没有未读信息
	 * @param[out] countOfMsg: 未读消息数量
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int checkIfExistUnreadPushedMsg(OUT bool& existUnreadMsg, OUT int & countOfMsg) = 0;

	/**
	 * @brief 分页获取最新推送信息
	 * @param[in] pageInfoIn 传入的分页信息
	 * @param[out] departList 返回的推送信息列表
	 * @param[out] pageInfoOut 平台返回的分页信息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getPagesOfPushedMsg(
		StDataPageInfo pageInfoIn,
		OUT std::vector<StPushedMsg>& msgList,
		OUT StDataPageInfo& pageInfoOut) = 0;

	/**
	 * @brief 设置消息已读
	 * @param[in] idList: 消息ID列表
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int readPushedMsg(std::vector<long long> idList) = 0;

	/**
	 * @brief 清空推送消息
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int cleanPushedMsg() = 0;

	/**
	 * @brief 获取部署环境
	 * @param[out] isPrivateDeploy: true表示私有化部署，false表示非私有化部署
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int getDeployEnv(OUT bool& isPrivateDeploy) = 0;

	/**
	 * @brief 上传极光registrationId
	 * @param[in] registrationId: 极光设备标识码
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int uploadRegistrationId(std::string registrationId) = 0;

	/**
	 * @brief 查询当前账号的操作权限
	 * @param[in] permissions: 所有的操作权限
	 * @param[in] abilities: 该账号所拥有的能力
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int queryOperationPermission(OUT std::vector<EnOperationPermission>& permissions, OUT  std::vector<EnAccountAbility>& abilities) = 0;

	/**
	 * @brief 催促指定会议室正在进行的会议，并查询指定ruid会议的状态
	 * @param[in] roomId: 会议室ID
	 * @param[in] ruid: 会议ID
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int hurryUp(std::string roomId, std::string ruid) = 0;

	/**
	 * @brief 给指定会议换个会议室
	 * @param[in] ruid: 会议ID
	 * @param[in] roomIdType: 会议室类型
	 * @param[in] roomId: 会议室ID
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int changeMeetingRoom(std::string ruid, EnRoomIdType roomIdType, std::string roomId) = 0;

	/**
	 * @brief 延长当前会议的时长
	 * @param[in] minsNeedToProlong: 延长分钟数
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int prolongMeeting(int minsNeedToProlong) = 0;

	/**
	 * @brief 更换手机号
	 * @param[in] newPhoneNumber: 新手机号码
	 * @param[in] validateCode: 验证码
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int changePhoneNumber(std::string newPhoneNumber, std::string validateCode) = 0;

	/**
	 * @brief 注销账户
	 * @param[in] newPhoneNumber: 新手机号码
	 * @param[in] validateCode: 验证码
	 * @return CODE_SUCCESS表示成功，否则失败
	 */
	virtual int cancelAccount(std::string newPhoneNumber, std::string validateCode) = 0;

protected:
    /**
     * @brief 析构函数
     * @return 无
     */
    virtual ~INetProtocol() {}
};

}

#endif //!__cplusplus

#endif //!__SRC_INTERFACE_INETPROTOCOL_H__
