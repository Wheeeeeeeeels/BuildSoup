
#ifndef __SDNP_DEFINE_H__
#define __SDNP_DEFINE_H__

#ifdef __cplusplus

#include <string>
#include <sstream>
#include <vector>


#if ((defined _WIN32) || (defined _WIN64))
#define SD_INTERFACE_EXPORT _declspec(dllexport)
#else
#define SD_INTERFACE_EXPORT 
#endif


namespace SDNP
{

#define OUT
#define DEPRECATED_SDNP

	//typedef unsigned long long  uint64;
	//typedef   signed long long  int64;
	enum ErrorCode
	{
		CODE_SUCCESS = 0,                               // 成功
		CODE_FAILED = -1,                               // 失败
		CODE_INTERFACE_DEPRECATED = -2,					// 接口弃用
		CODE_NOT_CONNECTED = 4000,                      // 未与云平台建立连接
		CODE_NOT_IN_ROOM = 4001,                        // 未创建或未加入会议
		CODE_CONNECT_FAILED = 4002,                     // 无法连接到云平台
		CODE_SSL_INIT_FAILED = 4003,                    // SSL初始化失败
		CODE_NOT_FOUND_PARTICIPANT = 4004,              // 未找到与会者
		CODE_UNENABLED_TRANSCRIBE = 4005,				// 转写未开启
		CODE_ENABLED_TRANSCRIBE = 4006,					// 转写已开启
		CODE_RESPONSE_TIMEOUT = 4007,					// 请求回复超时
		CODE_ILLEGAL_ROOMID = 4008,						// 非法会议ID
		CODE_UNMATCHED_SERVER_MODE = 4009,				// 不匹配的服务器模式

        CODE_DOWNLOAD_FAILED = 4010,                    // 下载失败
        CODE_RESOURCE_LIMITED = 4011,                   // 本地资源不足，errMsg为"系统忙碌，请稍后再试"
        CODE_FILE_EXIST = 4012,                         // 文件已存在
        CODE_FILE_OPEN_ERROR = 4013,                    // 文件打开失败
		CODE_FILE_NOT_FOUND = 4014,                    	// 文件不存在
        CODE_UPLOAD_FAILED = 4015,                    	// 上传失败

		CODE_IS_RECONNECTING = 4020,					// 正在重连中
		CODE_REQUEST_EXCEPTION = 4021,					// 请求发送异常
		CODE_DEVICE_NET_FATAL = 4022,					// 网卡异常&无法访问服务器

		CODE_INVALIDE_PASSWORD = 4030,					// 非法密码

		CODE_PROJECTION_WRONG_CODE = 4040,				// 错误的投屏码
		CODE_PROJECT_FAILED = 4041,						// 投屏失败(除被拒绝之外，其他无法投屏的情况)
        
        CODE_LOGIN_REPEAT = 4050,                     // 重复登陆

		// cloud server response error code
		CODE_API_AUTH_UNKNOWN_ERROR = 10000,            // api鉴权未知错误
		CODE_API_INVALID_SIGNATURE = 10001,             // api鉴权signature错误
		CODE_API_REQUEST_EXPIRED = 10002,               // api鉴权请求过期
		CODE_API_NONCE_DUPLICATED = 10003,              // api鉴权nonce重复
		CODE_API_UNSUPPORTED = 10004,                   // api请求不支持
		CODE_API_MD5_ERROR = 10005,                     // api鉴权md5错误
		CODE_API_PARAM_ERROR = 10006,                   // api参数错误
		CODE_APT_ACCESSIN_FIRST = 10007,				// 在accessIn之前调用其他rpc接口
		CODE_API_EXPIRED_VALIDATE_CODE = 10008,         // 验证码已过期
		CODE_APT_INVALID_VALIDATE_CODE = 10009,         // 验证码错误

		CODE_SERVER_UNKNOWN_ERROR = 11000,              // 服务未知错误
		CODE_SERVER_INTERNAL_ERROR = 11001,             // 服务内部错误
		CODE_PERFORMANCE_EXCEED = 11002,                // 负载超限
		CODE_INVALID_METHOD_CALL = 11003,               // 方法调用错误
		CODE_UNRECOGNIZED_API = 11005,                  // 非法api调用
		CODE_SERVICE_EXPIRED = 11006,					// 服务已到期
		CODE_UNSUPPORTED_SERVICE = 11012,				// 当前服务暂不支持，请对平台版本进行升级
		CODE_SESSION_EXPIRED = 11100,                   // session已失效

		CODE_USERNAME_OR_PASSWORD_ERROR = 12001,        // 用户名或密码错误
		CODE_TOKEN_INVALID = 12003,                     // 无效token
		CODE_TOKEN_ERROR = 12004,                       // token错误
		CODE_PHONE_NUMBER_REGISTERED = 12005,           // 手机号已注册
		CODE_PREVIOUS_PASSWORD_ERROR = 12006,			// 修改密码时，原密码错误
		CODE_VALIDATE_CODE_ERROR = 12019,				// 短信验证码错误
		CODE_INCORRENT_FORMAT_PHONE = 12030,			// 手机号错误
		CODE_INCORRENT_HOST_PASSWD = 12051,				// 主持密码错误

		CODE_UNALLOWED_LOGIN_BY_ADMIN = 12062,			// admin账号无法登录终端
		CODE_NONEXISTENT_PHONE = 12067,					// 该手机号未绑定账号：错误描述信息为"账号不存在，请重新输入"

		CODE_CONFERENCE_ALREADY_EXIST = 13000,          // 创建会议时，会议已存在
		CODE_CONFERENCE_NOT_EXIST = 13001,              // 加入会议时，会议不存在
		CODE_CONFERENCE_IS_LOCKED = 13002,              // 会议已锁定
		CODE_CONFERENCE_WAS_CAPPED = 13003,             // 加入会议时，会议人数已达到上限
		CODE_PERMISSION_LIMITED = 13004,                // 发起会控操作时，权限不足：错误描述信息为"未添加成功，请重试"
		CODE_SCREEN_SHARING_ALREADY_EXIST = 13005,      // 屏幕分享已存在
		CODE_CONFERENCE_PASSWORD_ERROR = 13006,         // 入会密码错误
		CODE_CONFERENCE_ALREADY_CLOSED = 13007,         // 会议已关闭
		CODE_USER_NO_STREAMING = 13008,                 // 用户未发布流
		CODE_ROOM_CAPACITY_LIMITED = 13009,             // 已达会议室容纳与会者上线
		CODE_USER_ALREADY_ONLINE = 13010,               // 用户已在线
		CODE_SCREEN_SHARING_NOT_EXIST = 13012,          // sharing流不存在
		CODE_SPEAKER_ALREADY_EXIST = 13013,             // 发言者已存在
		CODE_USER_NOT_LOGIN = 13014,                    // 用户未登录
		CODE_TERMINAL_IS_NOT_MODERATOR = 13015,			// 同账号登录的硬终端非主持人
		CODE_WEB_MODERATOR_EXIST = 13016,				// 会议中已存在web会控
		CODE_PARTICIPANT_NOT_EXIST = 13017,				// 与会者不存在
		CODE_ALREADY_IN_ANOTHER_ROOM = 13018,			// 已参加其他会议
		CODE_RESERVE_CONFERENCE_CONFLICT = 13019,		// 预约会议时间冲突
		CODE_START_TIME_INVALID = 13020,				// 会议开始时间不能早于现在
		CODE_PUBLISH_SAME_TYPE_STREAM = 13021,			// 与会者重复发布相同类型码流
		CODE_CONFERENCE_DURATION_INVALID = 13022,		// 会议时长必须大于0
		CODE_RECEIVE_SAME_STREAM = 13023,				// 重复接收与会者码流
		CODE_RECEIVE_AIN_STREAM = 13024,				// 与会者接收自己的码流
		CODE_CONFERENCE_RESORD_NOT_EXIST = 13025,		// 会议记录不存在
		CODE_PARTICIPANT_NO_PUBLISH_VIDIO = 13026,		// 与会者尚未发布视频流
		CODE_CONFERENCE_NO_RECORD = 13027,				// 会议尚未开始录制
		CODE_CONFERENCE_IS_RECORDING = 13028,			// 会议正在录制中
		CODE_SHARING_IS_EXIST = 13029,					// 共享已存在
		CODE_ONLY_CONTROL_AIN_CONFERENCE_ROOM = 13030,	// 主持人仅能使用自己的云会议室
		CODE_CONFERENCE_IS_LIVINT = 13031,				// 会议正在直播中
		CODE_CONFERENCE_LIVE_NOT_START = 13032,			// 会议尚未开始直播
		CODE_CONFERENCE_COUNT_UP_TO_LIMIT = 13033,		// 会议数已达上限
		CODE_CONFERENCE_RECORD_FREQUENTLY = 13034,		// 会议录制操作频繁，请稍后再试
		CODE_JOIN_ROOM_DUPLICATELY = 13035,             // 重复入会
		CODE_ALREADY_BE_MODERATOR = 13036,				// 已经是主持人
		CODE_DENIED_TRANSFER_MODERATRO = 13037,			// 个人会议室无法转移主持人权限
		CODE_SPEAKER_ALREADY_TURN_ON = 13038,			// 扬声器已经是打开状态
		CODE_DENIED_OPEN_SPEAKER = 13039,				// 主持人禁止开启扬声器
		CODE_OUT_OF_LENGTH_LIMIT = 13040,				// 超出默认长度限制
		CODE_UP_TO_CORP_CAPACITY_LIMIT = 13041,			// 已达企业会议人数上限，请稍后再试
		CODE_UP_TO_ROOM_CAPACITY_LIMIT = 13042,			// 已达会议人数上限，请稍后再试
		CODE_PARTCIPANT_ALREADY_PUTDOWN_HAND = 13043,	// 参会者已取消举手发言
		CODE_GROUP_IS_NOT_EXIST = 13045,				// 群组不存在
		CODE_PLATFORM_FORCE_CLOSE_CONNECTION = 13046,	// 平台强制关闭链接
		CODE_REACH_TO_GROUP_MAX_CAPACITY = 13047,		// 已达群组人数上限
		CODE_APPOINTMENT_HAS_STARTED = 13048,			// 预约会议已经开始
		CODE_POLLING_HAS_STARTED = 13049,				// 轮询已经开启

		CODE_CLOUD_RECORD_STORAGE_NOT_ENOUGH = 13050,	// 存储容量不足，暂不可录制会议
		CODE_APPOINTMENT_BEFORE_EXPIRED_DATE = 13051,	// 预约会议日期必须早于服务有效期
		CODE_RECORD_STORAGE_LESS_THAN_100MB = 13052,	// 录制存储剩余容量少于100MB
		CODE_APPOINTMENT_CONFERENCE_NOT_EXIST = 13054,	// 预约会议不存在，错误描述信息为"会议不存在"
		CODE_REMAINDER_RUN_OUT = 13058,					// 通话时长已用完

		CODE_UNSUPPORTED_RECORD_OPERATION = 13061,		// 当前不支持录制服务
		CODE_RECORD_SERVICE_EXPIRED = 13062,			// 录制服务已到期，请联系管理员

		CODE_NO_RECORD_SERVICE = 13070,					// 未开通录制服务，请联系管理员
		CODE_RECORD_FAILED = 13072,						// 录制失败，请稍后重试
		CODE_FIXED_ROOM_EXPIRED = 13076,				// 固定会议室已到期，错误描述信息为"该会议号服务已到期"
		CODE_ROOM_IS_IN_USE = 13077,					// 会议室正在使用中，错误描述信息以移动端UE为准
		CODE_ADD_SAME_FREQUENT_CONTACT = 13078,			// 重复添加相同常用联系人
		CODE_CANCEL_SAME_FREQUENT_CONTACT = 13079,		// 重复取消相同常用联系人

		CODE_JOIN_ROOM_DEADLOCK = 13080,				// 入会锁死，错误描述信息为"请稍后再试"
		CODE_APPOINTMENT_STATUS_ERROR = 13081,			// 预约会议状态错误，错误描述信息为"该会议号服务已到期"
		CODE_CONCURRENCY_SERVICE_EXPIRED = 13082,		// 并发服务到期，错误描述信息为"该会议号服务已到期"
		CODE_NO_RECORD_PERMISSION = 13083,				// 没有录制权限，错误描述信息为"暂无权限"
		CODE_OTHER_CONF_ALREADY_RECORDING = 13084,		// 已有其他会议正在录制，请稍后再试
		CODE_NOT_ADMIN_OF_FIXED_ROOM = 13086,			// 进行固定会议室相关操作，但没有固定会议室管理权限，错误描述信息为"不是会议室管理员"
		CODE_LAST_MEETING_NOT_FINISHED = 13087,			// 上个会议仍未结束，请等待
		
		CODE_USER_NOT_FOUND = 13100,                    // 用户不存在
		CODE_USER_BUSY = 13101,                         // 用户忙碌中
		CODE_CONFERENCE_ROOM_NOT_EXIST = 13102,			// 云会议室不存在
		CODE_CONFERENCE_ROOM_PASSWORD_ERROR = 13103,	// 云会议室密码只能设置为6位数字
        CODE_CONFERENCE_ROOM_PARTICIPANT_JOINED = 13104,    // 参会者已入会
	};

	// 客户端网络状态
	enum EnDeviceNetState
	{
		DEVICE_NET_UNKNOWN, 				// 未知
		DEVICE_NET_CONNECTED,				// 已连接
		DEVICE_NET_DISCONNECT,				// 断开
	};

	enum EnLogLevel
	{
		LOG_LEVEL_VERBOSE,                  // 详细
		LOG_LEVEL_DEBUG,                    // 调试
		LOG_LEVEL_INFO,                     // 信息
		LOG_LEVEL_WARN,                     // 警告
		LOG_LEVEL_ERROR,                    // 错误
		LOG_LEVEL_FATAL,                    // 致命
		LOG_LEVEL_SILENT,                   // 静默
	};

	enum EnTerminalType
	{
		TMN_TYPE_MOBILE_ANDROID,            // 安卓移动手机
		TMN_TYPE_MOBILE_IOS,                // IOS移动手机
		TMN_TYPE_PC_WINDOWS,                // Windows PC
		TMN_TYPE_PC_MAC,                    // Mac PC
		TMN_TYPE_HARD_ANDROID,              // Android硬终端
		TMN_TYPE_WEB,                       // Web端
		TMN_TYPE_SIP,						// sip终端
		TMN_TYPE_UNDEFINED,                 // 未定义
	};

	enum EnTerminalStatus
	{
		TMN_STATUS_OFFLINE,                 // 离线
		TMN_STATUS_ONLINE,                  // 在线
		TMN_STATUS_MEETING,                 // 会议中
		TMN_STATUS_UPGRADING,               // 升级中
	};

	enum EnStreamType
	{
		STREAM_TYPE_MAJOR,                  // 主码流
		STREAM_TYPE_MINOR,                  // 辅码流
		STREAM_TYPE_SHARING,                // 分享码流
		STREAM_TYPE_SUPER,					// 4K超清码流
		STREAM_TYPE_MCU_MIX,				// MCU混流
		STREAM_TYPE_AUDIO_MIX,				// 音频混流
		STREAM_TYPE_MAX,					// 枚举最大值，无需关注
	};

	enum EnStreamStatus
	{
		STREAM_STATUS_PAUSE,				// 暂停码流
		STREAM_STATUS_RESUME,				// 恢复码流
	};

	enum EnMediaType
	{
		MEDIA_TYPE_AUDIO,			// 音频
		MEDIA_TYPE_VIDEO,			// 视频
	};

	enum EnRoomRole
	{
		ROLE_HOST,                          // 主持人
		ROLE_PARTICIPANT,                   // 与会者
		ROLE_AUDIENCE,                      // 观众
		ROLE_THOR,                          // 会控者
		ROLE_ONLY_SHARE,					// 屏幕入会仅共享
		ROLE_MAX,							// 枚举最大值，无需关注
	};

    enum EnSwitch
    {
        SWITCH_OFF,                         // 关
        SWITCH_ON,                          // 开
    };

	enum EnMediaMode
	{
		MEDIA_MODE_SFU,                     // SFU
		MEDIA_MODE_MCU,                     // MCU
		MEDIA_MODE_AUDIO_MIX,				// 仅音频混流
	};

	enum EnH5PageType
	{
		H5PAGE_SERVICE_AGREEMENT,           // 服务协议
		H5PAGE_PRIVACY_POLICY,              // 隐私政策
		H5PAGE_DOWNLOAD_URL,				// 分享下载链接
		H5PAGE_OPERATE_INSTRUCTION,			// 操作指南
		H5PAGE_USERGUIDE,					// 使用指南
		H5PAGE_FEEDBACK,					// 快速反馈
		H5PAGE_USER_MANUAL_CLOUD_STORE,		// 云存储空间使用说明
		H5PAGE_USER_MANUAL_CONCURRENCY,		// 会议并发方数使用说明
		H5PAGE_USER_MANUAL_FIXED_MEETING_ROOM,		// 企业固定会议室使用说明
		H5PAGE_ALL,                         // 所有H5页面
	};

	enum EnNetState
	{
        NET_UNCONNECT,                  // 未连接
        NET_CONNECTTING,                // 连接中
        NET_CONNECTED,                  // 已连接
        NET_CONNECTFAIL,                // 连接失败
        NET_DISCONNECT,                 // 断开连接
	};

	enum EnRefuseInviteReason
	{
		REASON_REFUSE,                      // 拒绝
		REASON_MEETING,                     // 会议中
	};

	enum EnParticipantLeftReason
	{
		REASON_NORMAL,                      // 正常离会
		REASON_REPLACE,                     // 相同账号被顶替离会
		REASON_EVICTED,                     // 被踢出离会
		REASON_BREAKLINE,					// 掉线离会
	};

	enum EnMeetingClosedReason
	{
		REASON_MEETING_CLOSED_NORMAL,					// 正常结束
		REASON_MEETING_CLOSED_SERVICE_EXPIRED,			// 服务到期
		REASON_MEETING_CLOSED_CALL_DURATION_USED_UP,	// 通话时长用完
		REASON_MEETING_CLOSED_FIXEDROOM_EXPIRED,		// 固定会议室到期
		REASON_MEETING_CANCELED_BY_HOST,				// 主持人取消会议
		REASON_MEETING_CLOSED_UNEXPECTED,				// 意外关闭
	};

	enum EnOrgInfoNodeType
	{
		ROOT_NODE,							// 根节点
		MEMBER_NODE,						// 成员节点
		ORGANIZATION_NODE,					// 组织节点
	};

	enum EnGroupType
	{
		GROUP_I_OWN,						// 我创建的群组
		GROUP_CORP_OWN,						// 公司创建的群组
		GROUP_ALL,							// 全部群组
	};

	enum EnLanguageType
	{
		LANGUAGE_CN,									// 汉语	
		LANGUAGE_EN,									// 英语
		LANGUAGE_ZA,									// 藏语
		LANGUAGE_UG,									// 维语
	};

	enum EnAudioCodec
	{
		AUDIO_RAW,							// raw(pcm)格式
		AUDIO_SPEEX,						// speex格式音频
	};

	enum EnRoomIdType
	{
		ROOMID_UNKNOWN = -1,				// 未知类型会议室
		ROOMID_RANDOM = 0,					// 随机会议室
		ROOMID_PERSONAL = 1,				// 个人会议室
		ROOMID_FIXED = 2,					// 固定会议室
	};

	enum EnMeetingRoomStatus
	{
		MEETING_ROOM_IS_AVAILABLE,				// 会议室空闲
		MEETING_ROOM_IS_USING,					// 会议室忙碌
		MEETING_ROOM_MAX,						// 枚举最大值，无需关注
	};

	enum EnMeetingStatus
	{
		MEETING_NOT_START,						// 未开始
		MEETING_IN_PROGRESS,					// 进行中
		MEETING_FINISHED,						// 已结束
	};

	enum EnMessageType
	{
		MESSAGE_UNKNOWN = -1,				// 未知消息
		MESSAGE_RAISE_HAND = 0,				// 与会者举手 消息
		MESSAGE_APPLY_MODERATOR = 1,		// 与会者申请成为主持人 消息
		MESSAGE_APPLY_LISTEN = 2,			// 与会者申请开启扬声器 消息
		MESSAGE_URGE_TO_STOP_MEETING = 3,	// 催促停止会议
		MESSAGE_APPLY_OPEN_MIC = 4,			// 与会者申请开启麦克风 消息
		MESSAGE_START_RECORD = 5,			// 主持人开启录制
		MESSAGE_HOST_LEFT = 6,				// 主持人离会
		MESSAGE_MAX,						// 枚举最大值，无需关注
	};

	enum EnRollCallSource
	{
		ROLLCALL_SOURCE_ACTIVE,				// 主持人主动点名发言
		ROLLCALL_SOURCE_APPLICANT,			// 有申请人申请发言
	};

	enum EnConferenceStatus
	{
		CONFERENCE_PENDING,					// 待参加的会议
		CONFERENCE_CLOSED,					// 已结束的会议
	};

	enum EnAppointProcessStatus
	{
		APPOINTMENT_PEDNING,				// 未开始
		APPOINTMENT_IN_THE_MEETING,			// 会议中
		APPOINTMENT_CLOSED,					// 已结束
	};

	enum EnMeetingInfoOption
	{
		MEETINGINFO_OPTION_NULL = -1,						// 默认无效选项
		MEETINGINFO_OPTION_isLocked,						// 会议是否锁定
		MEETINGINFO_OPTION_joinRoomMicStatus,				// 入会麦克风状态
		MEETINGINFO_OPTION_allowPartOperSpeaker,			// 是否允许与会者自主开启收听
		MEETINGINFO_OPTION_permissionShare,					// 是否允许与会者开启共享
		MEETINGINFO_OPTION_allowPartCancelMute,				// 是否允许与会者自我解除静音
		MEETINGINFO_OPTION_allowPartInviteOthers,			// 是否允许成员邀请他人
		MEETINGINFO_OPTION_allowCallInType,					// 允许呼入用户类型
		MEETINGINFO_OPTION_IMPermission,					// 会议IM权限
		MEETINGINFO_OPTION_muteMode,						// 静音模式
		MEETINGINFO_OPTION_MAX,								// 枚举最大值，无需关注
	};

	enum EnUserType
	{
		USER_TYPE_NULL = -1,					// 默认无效选项
		USER_TYPE_CORP,							// 企业通讯录用户
		USER_TYPE_ALL,							// 全部用户
	};

	enum EnJoinRoomMuteMode
	{
		JOINROOM_MUTE_OPEN_ALL_MIC,				// 入会开启全部麦克风
		JOINROOM_MUTE_CLOSE_ALL_MIC,			// 入会关闭全部麦克风
		JOINROOM_MUTE_SMART,					// 入会智能静音
	};

	enum EnAccountType
	{
		ACCOUNT_SOFT_TERMIANL,					// 软终端账号
		ACCOUNT_HARD_TERMIANL,					// 硬终端账号
		ACCOUNT_VISITOR,						// 游客账号
	};


	enum EnConferenceRecordStorageStatus
	{
		RECORD_STORAGE_LESS_THAN_10_PERCENT,		// 存储空间少于10%
		RECORD_STORAGE_RUN_OUT,						// 存储空间耗尽
	};

	enum EnStopRecordReason
	{
		STOP_RECORD_REASON_CLOSED_BY_HOST,				// 正常结束
		STOP_RECORD_REASON_LESS_THAN_10_PERCENT,		// 存储空间少于10%
		STOP_RECORD_REASON_RUN_OUT,						// 存储空间耗尽
		STOP_RECORD_REASON_SERVER_INTERNAL_ERROR,		// 服务内部错误
	};

	enum EnPollingNotify
	{
		POLLING_TO_NOTIFY,					// 轮巡到通知
		POLLING_CHECK_NOTIFY,				// 轮巡切换通知
		POLLING_OVER_NOTIFY,				// 轮巡过通知
	};

	enum EnIceServerType
	{
		ICE_SERVER_STUN,					// stun 服务器
		ICE_SERVER_TURN,					// turn 服务器
	};

	enum EnConversationDuration
	{
		CONVERSATION_EXCEPTION = -1,			// 异常情况
		CONVERSATION_MORE_THAN_10H = 0,			// 剩余通话时长大于10小时
		CONVERSATION_LESS_THAN_10H = 1,			// 剩余通话时长小于10小时
		CONVERSATION_RUN_OUT = 2,				// 剩余通话时长为0
	}; 

	enum EnIMPermission
	{
		IM_NOLIMIT,								// 允许自由聊天
		IM_PUBLIC_ONLY,							// 仅允许公开聊天
		IM_PRIVATE_CONTACT_HOST_ONLY,			// 仅允许私聊主持人
		IM_BANNED,								// 全员禁止聊天
		IM_MAX,									// 枚举最大值，无需关注
	};

	enum EnUserStatus
	{
		USER_ONLINE,						// 在线
		USER_OFFLINE,						// 离线
		USER_UPDATING,						// 升级中
		USER_MEETING,						// 会议中
	};

	enum EnValidateCodeUsage
	{
		VALIDATE_LOGIN,						// 登录
		VALIDATE_RESET_PWD,					// 重置密码
		VALIDATE_BIND_PHONE,				// 绑定手机号
		VALIDATE_CHANGE_PHONE,				// 更改手机号码
		VALIDATE_CANCEL_ACCOUNT,			// 注销账户
		VALIDATE_TOURIST,					// 游客获取验证码，或查验验证码
		VALIDATE_MAX,						// 枚举最大值，无需关注
	};

	enum EnOperationPermission
	{
		JOIN_ROOM_ALLOWED,					// 允许加入会议
		CREATE_ROOM_ALLOWED,				// 允许创建会议
		RECORD_MEETING_ALLOWED,				// 允许录制会议
	};

	enum EnAccountAbility
	{
		CONCURRENCY_ALLOWED,				// 拥有并发服务
		FIXED_ROOM_MANAGE_ALLOWED,			// 固定会议室管理权限
	};

	enum EnConferenceCanceledReason
	{
		CONF_CANCELED_BY_PROLONG,			// 因会议延长被取消
		CONF_CANCELED_BY_OWNER,				// 被拥有者取消
		CONF_CANCELED_BY_SERVER,			// 被服务器取消
		CONF_CANCELED_BY_MANAGER,			// 被管理员取消
		CONF_CANCELED_MAX,					// 枚举最大值，无需关注
	};

	enum EnMeetingLayoutType
	{
		MEETING_ROSTRUM_LAYOUT,				// 演讲布局
		MEETING_HALVE_LAYOUT,				// 等分布局
		MEETING_MAX,						// 枚举最大值，无需关注
	};

	enum EnUploadFileType
	{
		UPLOAD_LOG,							// 上传日志
		UPLOAD_USERICON,					// 上传头像
		UPLOAD_MAX,							// 枚举最大值，无需关注
	};

    enum EnForceUpgrade {
        /// N 普通升级
        FORCE_UPGRADE_N,
        /// Y 强制升级
        FORCE_UPGRADE_Y,
        /// S 静默升级-强制升级
        FORCE_UPGRADE_S,
    };

	// 网络质量结构体
	struct StNetworkQuality
	{
		std::string uploadBandwidth;		// 上行带宽
		std::string downloadBandwidth;		// 下行带宽
		int delay;						// 延迟	

		StNetworkQuality()
		{
			uploadBandwidth = "";
			downloadBandwidth = "";
			delay = 0;
		}
	};

	// 流质量结构体
	struct StStreamQuality
	{
		EnStreamType type;						// 流类型
		std::string resolution;					// 分辨率
		std::string videoBitRate;				// 视频码率
		std::string audioBitRate;				// 音频码率
		int fps;								// 帧率
		double videoPacketLostRate;				// 视频丢包率
		double audioPacketLostRate;				// 音频丢包率

		StStreamQuality()
		{
			type = STREAM_TYPE_MAJOR;
			resolution = "";
			videoBitRate = "";
			audioBitRate = "";
			fps = 0;
			videoPacketLostRate = 0.0;
			audioPacketLostRate = 0.0;
		}
	};

	struct ServerInfo
	{
		bool isProxy;						// 是否是代理服务器
		std::string host;                   // 服务器地址
		int httpPort;                       // 服务器HTTP端口
		int httpsPort;                      // 服务器HTTPS端口

		ServerInfo() :
			isProxy(false),
			host(""),
			httpPort(0),
			httpsPort(0) {}
	};

	struct StIceServerInfo
	{
		EnIceServerType type;
		std::string host;
		int port;
		std::string username;
		std::string password;
	};

	struct PushLogStrategy
	{

	};

	struct PushLogParams
	{
		std::string account;				// 用户账号
		std::string logName;				// 日志文件路径
		std::string version;				// app version
		EnTerminalType terminalType;		// 终端类型
		std::string deviceModel;			// 设备型号，终端类型为HDC时必传

		PushLogParams()
		{
			account = "";
			logName = "";
			version = "";
			terminalType = TMN_TYPE_UNDEFINED;
			deviceModel = "";
		}
	};

	// 设备本地信息
	struct StTerminalLocalInfo
	{
		std::string ability;				// 设备能力枚举值：MultiCastPlay多屏能力；ScreenShare屏幕分享
		std::string functionality;			// 设备功能：json字符串，数据内容及格式由硬终端和web端协定
	};

	struct BasicInfo
	{
		std::vector<ServerInfo> serverInfos;              // 服务器信息
		EnTerminalType terminalType;        // 终端类型
		std::string deviceModel;			// 设备型号，仅硬终端输入
		StTerminalLocalInfo localInfo;		// 硬终端使用，表示硬终端独有的能力选项
		std::string udid;                   // 设备唯一标识符
		std::string macAddr;                // 终端Mac地址
		std::string appVersion;             // 应用版本号，如"1.3.5"
		std::string appVersionCode;         // 应用版本编号，如"1351"
		std::string serialNumber;           // 终端序列号
        std::string project = "alpha";      // 项目，如"alpha"
		std::string appKey;                 // 应用AK
	};

	struct StCompanyInfo
	{
		std::string name;					// 企业名称
		std::string code;					// 企业代码

		int randomRoomCapacity;				// 企业随机会议室容量

		bool isExpired;						// 企业服务是否已到期
		std::string expireDate;				// 企业服务到期时间
		int daysToExpiredDate;				// 距到期时间天数

		int surplusConversationHours;		// 剩余通话时长小时数
		int surplusConversationMins;		// 剩余通话时长分钟数
		EnConversationDuration surplusConversationDuration;	// 剩余通话时长状态

		std::string cloudRecordUsedSpace;				// 云录制已使用空间
		std::string cloudRecordTotalSpace;				// 云录制总空间

		int fixedMeetingRoomCount;			// 企业固定会议室数量

		StCompanyInfo() 
		{
			name = "";
			code = "";

			randomRoomCapacity = 0;

			isExpired = false;
			expireDate = "";
			daysToExpiredDate = 0;

			surplusConversationHours = 0;
			surplusConversationMins = 0;

			cloudRecordUsedSpace = "";
			cloudRecordTotalSpace = "";

			fixedMeetingRoomCount = 0;
		}
	};

	struct StAccountInfo
	{
		std::string phone = "";					// 手机号
		std::string email = "";					// 邮箱号
		std::string username = "";				// 用户昵称
		std::string userOrgName = "";			// 用户所属组织名称
		std::string userIcon = "";				// 用户头像
	};

	struct StUserInfo
	{
		std::string account = "";				// 平台生成的用户唯一标识
		std::string name = "";					// 昵称
		std::string icon = "";					// 头像

		std::string department = "";			// 所属部门，游客为空
		int departmentId = -1;					// 部门id

		EnAccountType accountType = ACCOUNT_SOFT_TERMIANL;			// 账号类型
		EnTerminalType terminalType = TMN_TYPE_UNDEFINED;			// 终端类型

		// accountType == ACCOUNT_HARD_TERMIANL 时以下属性有效
		std::string serialNumber = "";				// 设备序列号
		std::string deviceModel = "";				// 硬终端型号

		// accountType == ACCOUNT_SOFT_TERMIANL 时以下属性有效
		std::string phone = "";						// 手机号
		std::string email = "";						// 邮箱

		std::string toString()
		{
			std::ostringstream ost;
			ost << "{ account: " << account;
			ost << ", accountType: " << accountType;
			ost << ", terminalType: " << terminalType;
			if (accountType == ACCOUNT_HARD_TERMIANL)
			{
				ost << ", serialNumber: " << serialNumber;
				ost << ", deviceModel: " << deviceModel;
			}
			if (accountType == ACCOUNT_SOFT_TERMIANL)
			{
				ost << ", phone: " << phone;
				ost << ", email: " << email;
			}
			ost << "}";
			return ost.str();
		}
	};

	typedef struct _loginInfo
	{
		StUserInfo userInfo;			// 自己的用户信息

		StCompanyInfo companyInfo;          // 公司信息

		std::string token = "";

		long long serverTimestamp = 0;				//服务器时间戳

		bool isFirstLogin = false;					// true表示首次登录，false表示非首次登录
		bool isPrivateDeploy = false;				// true表示私有化部署，false表示非私有化部署

		bool loginStatus = false;					// true表示已登录，false表示未登录
	}LoginInfo;

	struct OrgInfo
	{
		int orgId;                          // 组织ID
		std::string orgName;                // 组织名称
		int parentId;                       // 父组织ID
		bool hasChild;                      // 是否有子组织
		bool hasMember;						// 是否有成员
		int numOfEmp;						// 部门成员人数
	};

	struct OrgInfoNode
	{
		EnOrgInfoNodeType nodeType;					// 该节点类型
		int orgId;									// 组织ID
		int parentId;								// 父节点组织ID
		std::string orgName;						// 组织名称
		std::vector<OrgInfoNode> parentNode;		// 父节点
		std::vector<OrgInfoNode> childNodes;		// 子节点列表

		OrgInfoNode() :
			nodeType(ROOT_NODE),
			orgId(-1),
			parentId(-1),
			orgName("") {}

		bool isRoot() { return nodeType == ROOT_NODE ? true : false; }
		bool isMember() { return nodeType == MEMBER_NODE ? true : false; }
		bool isOrg() { return nodeType == ORGANIZATION_NODE ? true : false; }
		bool isNull() { return orgId == -1 ? true : false; }

		OrgInfoNode & operator = (OrgInfoNode orgInfoNode) {
			this->nodeType = orgInfoNode.nodeType;
			this->orgId = orgInfoNode.orgId;
			this->parentId = orgInfoNode.parentId;
			this->orgName = orgInfoNode.orgName;
			this->parentNode = orgInfoNode.parentNode;
			this->childNodes = orgInfoNode.childNodes;
			return *this;
		}
	};

	struct OrgMemberInfo
	{
		int orgId;                          // 成员所属组织ID
		std::string account;                // 成员账号
		std::string name;                   // 成员名称
		std::string userIcon;				// 成员头像
		EnTerminalStatus status;            // 成员状态
		EnAccountType accountType;			// 成员账号类型
		std::string serialNumber;           // 成员序列号
		std::string uuid;                   // 成员内部编号
		std::string phone;					// 用户手机号
		std::string email;					// 用户邮箱
		std::string departFullName;			// 部门名称全路径
		bool isFrequentContact;				// 是否为常用联系人
		OrgMemberInfo()
		{
			isFrequentContact = false;
		}
	};

	struct StDataPageInfo
	{
		bool upToAll;						// 是否获取全部数据，true表示一次性获取全部，false表示分页获取
		int totalDatas;						// 数据总数量
		int pageNum;						// 当前页数
		int pageSize;						// 当前页数据数量
		int totalPages;						// 页数总量
		std::string version;				// 数据版本号
		StDataPageInfo() :
			upToAll(false),
			totalDatas(0),
			pageNum(1),
			pageSize(1),
			totalPages(0),
			version("") {}
		StDataPageInfo(bool upToAll_, int totalDatas_, int pageNum_, int pageSize_, int totalPages_, std::string version_) :
			upToAll(upToAll_),
			totalDatas(totalDatas_),
			pageNum(pageNum_),
			pageSize(pageSize_),
			totalPages(totalPages_),
			version(version_) {}
	};

	struct StChatGroup
	{
		int groupId;						// 群组ID
		std::string groupName;				// 群组名称
		int numOfPeople;					// 组内人数
		std::string groupIcon;				// 群组头像
		EnGroupType type;					// 群组类型
	};

	struct StMeetingRoom
	{
		EnRoomIdType type = ROOMID_UNKNOWN;								// 会议室类型
		std::string id = "";											// 会议室ID
		std::string name = "";											// 会议室名称
		EnMeetingRoomStatus status = MEETING_ROOM_IS_AVAILABLE;			// 会议室状态
		int capacity = 0;												// 会议室方数
		std::string shortNum = "";										// 内部呼叫短号
		std::string expiredDate = "";									// 会议室到期时间，格式为"yyyy-MM-dd HH:mm:ss"
		std::string icon = "";											// 会议室头像
		bool hasAdminRights = false;									// true表示有管理员权限
	};

	struct StAllMeetingRooms
	{
		std::vector<StMeetingRoom> fixedMeetingRooms;		// 固定会议室信息
	};

	struct StConferenceLayout
	{
		bool automatically;					// true表示默认布局，false表示手动布局
		int mode;							// 布局方式枚举

		StConferenceLayout() :automatically(true), mode(0) {}
		StConferenceLayout(bool _automatically, int _mode) :automatically(_automatically), mode(_mode) {}
	};

	// 矩形结构体
	struct StRect
	{
		int x = 0;				// x坐标
		int y = 0;				// y坐标
		int width = 0;			// 宽
		int height = 0;			// 高
	};

	// joinRoom 接口参数
	struct StJoinRoomParam
	{
		std::string roomId;					// 会议ID
		std::string password;				// 入会密码
		EnMediaMode mediaMode;				// 架构类型
		int duration;						// 会议持续时长(单位为分钟)
		std::string useIdInRoom;			// 仅主持人可通过RoomID入会：onlyModerator,  全体参会人员可通过RoomID入会：allParticipants
		EnStreamType streamType;			// 码流类型
		bool videoStatus;					// 入会时视频状态
		bool audioStatus;					// 入会时麦克风状态
		bool joinType;						// true表示主动入会，false表示被邀请入会
		bool isReconnected;					// true表示断线重连入会，false表示正常入会
		std::string ruid;					// 会议记录ID，发起会议时缺省，从预约会议详情入会时必须赋值
		EnRoomRole role;					// 入会时角色
		std::string nickname;				// 与会者昵称

		StJoinRoomParam() :
			roomId(""),
			password(""),
			mediaMode(MEDIA_MODE_SFU),
			duration(120),
			useIdInRoom("allParticipants"),
			streamType(STREAM_TYPE_MAJOR),
			videoStatus(true),
			audioStatus(true),
			joinType(true),
			isReconnected(false),
			ruid(""),
			role(ROLE_PARTICIPANT) {}
	};

	struct StMediaControlParam
	{
		std::string account;				// 码流所属用户账号
		EnStreamType streamType;			// 码流类型
		EnMediaType mediaType;				// 媒体类型
	};

	struct StreamInfo
	{
		std::string id;                     // 码流ID
		EnStreamType type;                  // 码流类型
		bool hasVideo;                      // 码流是否有视频
		bool hasAudio;                      // 码流是否有音频

		StreamInfo()
			: id(""),
			type(STREAM_TYPE_MAJOR),
			hasVideo(false),
			hasAudio(false) {}

		std::string toString()
		{
			std::ostringstream ost;
			ost << "{ id: " << id;
			ost << ", type: " << type;
			ost << ", hasVideo: " << hasVideo;
			ost << ", hasAudio: " << hasAudio;
			ost << "}";
			return ost.str();
		}
	};

	struct StStreamInfo
	{
		std::string id;                     // 码流ID，格式为 "<connectionId>_<streamType>_<terminalType>_<random(6)>"，如"yhxrroewpbfzmevk_MAJOR_HARD_123456"
		EnStreamType type;                  // 码流类型
		bool hasVideo;                      // 码流是否有视频
		bool hasAudio;                      // 码流是否有音频

		EnStreamStatus pushStreamStatus;		// 推流状态
		EnStreamStatus pullStreamStatus;		// 拉流状态

		StStreamInfo()
			: id(""),
			type(STREAM_TYPE_MAJOR),
			hasVideo(true),
			hasAudio(true),
			pushStreamStatus(STREAM_STATUS_RESUME),
			pullStreamStatus(STREAM_STATUS_RESUME) {}

		std::string toString()
		{
			std::ostringstream ost;
			ost << "{ id: " << id;
			ost << ", type: " << type;
			ost << ", hasVideo: " << hasVideo;
			ost << ", hasAudio: " << hasAudio;
			ost << ", pushStreamStatus: " << pushStreamStatus;
			ost << ", pullStreamStatus: " << pullStreamStatus;
			ost << "}";
			return ost.str();
		}
	};

	struct StCalleeInfo
	{
		StUserInfo userInfo;				// 用户信息
		long long expireTime;				// 邀请有效期
	};

	struct StParticipantInfo
	{
		StUserInfo userInfo;				// 用户信息

		EnRoomRole role;                    // 与会者角色
		int order;							// 与会者顺序，主持人为0

		long long createTimeMs;             // 入会时间
		bool onlineStatus;                  // 是否在线

		bool cameraStatus;                  // 视频是否打开状态
		bool micStatus;						// 麦克风是否打开状态
		bool speakerStatus;                 // 扬声器是否打开状态

		bool handStatus;                    // 举手状态
		bool lectureStatus;					// 发言状态
		bool shareStatus;					// 共享状态

		bool isVoiceMode;                   // 是否为语音模式

		std::vector<StStreamInfo> streams;	// 流列表

		std::string appVersion;				// 与会者使用app版本号，游客入会使用
		std::string functionality;			// 设备能力属性集

		StParticipantInfo() :
			role(ROLE_PARTICIPANT),
			order(-1),
			createTimeMs(0),
			onlineStatus(true),
			cameraStatus(false),
			micStatus(false),
			speakerStatus(false),
			handStatus(false),
			lectureStatus(false),
			shareStatus(false),
			isVoiceMode(false),
			appVersion(""),
			functionality("") {}

		std::string toString()
		{
			std::ostringstream ost;
			ost << "{ userInfo: " << userInfo.toString();
			ost << ", role: " << role;
			ost << ", order: " << order;
			ost << ", createTimeMs: " << createTimeMs;
			ost << ", onlineStatus: " << onlineStatus;
			ost << ", videoStatus: " << cameraStatus;
			ost << ", audioInStatus: " << micStatus;
			ost << ", audioOutStatus: " << speakerStatus;
			ost << ", handStatus: " << handStatus;
			ost << ", lectureStatus: " << lectureStatus;
			ost << ", shareStatus: " << shareStatus;
			ost << ", isVoiceMode: " << isVoiceMode;
			for (size_t i = 0; i < streams.size(); i++)
			{
				ost << ", stream[" << i << "]: " << streams[i].toString();
			}
			ost << ", appVersion: " << appVersion;
			ost << ", functionality: " << functionality;
			ost << "}";
			return ost.str();
		}
	};

	struct StSubscribeStreamParam
	{
        // 以下属性SFU时必选
        std::string account;                // 目标流所属账号
        EnStreamType streamType;            // 目标流类型
        std::string sdpOffer;                // 媒体协商请求信息
        /// alpha， 每一个mediaType 单独拉
        EnMediaType mediaType;
        std::string transportId;
        
        /// 内部自动会管理 // 流ID = publishId
        std::string streamId;
        
        // 透传ID，用来绑定对应param
        std::string client_identifier() {
            if (!_client_identifier.empty()) {
                return _client_identifier;
            }
            std::string randomId = this->streamId;
            if (randomId.empty()) {
                std::ostringstream os;
                os << (int)this->streamType;
                randomId = this->account + "_" + os.str();
            }
            this->mediaType == MEDIA_TYPE_AUDIO ? randomId += "_A"  : randomId += "_V";
            _client_identifier = randomId;
            return randomId;
        };
        
        ///alapha 默认是SFU
        EnMediaMode mediaMode;				// 媒体模式，SFU/MCU
		StSubscribeStreamParam()
		{
			mediaMode = MEDIA_MODE_SFU;
			streamType = STREAM_TYPE_MAJOR;
            streamId = "";
            _client_identifier = "";
		}
        
    private:
        std::string _client_identifier;
	};
    
    struct StSubscribeStreamResponse
    {
		std::string sdp;
		int errorCode;
		std::string account;
		int streamType;
		int mediaType;  ///0:audio  1:video
		std::string transportId;
    };


	// 与会者view信息
	struct StView
	{
		std::string account;				// 发布者账号
		std::string username;				// 发布者昵称
		EnStreamType streamType;			// 当前位置流类型
		StRect rect;						// 布局位置
	};

	// 会议结构体
	struct StMeeting
	{
		StMeetingRoom room;								// 会议室信息

		std::string ruid = "";							// 会议ID
		std::string password = "";						// 入会密码
		std::string subject = "";						// 会议主题
		std::string detail = "";						// 会议详情

		int numberOfParticipant = 0;					// 已入会人数

		EnMediaMode subscribeMediaMode = MEDIA_MODE_SFU;		// 订阅媒体模式，根据该字段确认拉SFU/MCU流
		EnMediaMode currentMediaMode = MEDIA_MODE_SFU;			// 会议中当前媒体模式

		std::vector<StView> layout;						// 会议布局信息

		int duration = 120;								// 会议持续时长(单位为分钟)
		long long startTimeMs = 0;						// 会议开始时间
		long long endTimeMs = 0;						// 会议结束时间
		long long startRecordTimeMs = 0;				// 开始录制时间

		EnJoinRoomMuteMode joinRoomMuteMode = JOINROOM_MUTE_SMART;		// 入会静音模式

		bool allowRecordMeeting = true;					// 是否允许录制会议

		bool isRecording = false;						// 是否正在录制会议

		bool permissionJoinRoomById = true;				// 是否任何人都有通过ID入会的权限(主持人始终允许)

		bool allowPartOpenSpeaker = true;				// 是否允许与会者自主开启收听
		bool allowPartOpenMic = true;					// 是否允许与会者自主开启麦克风

		EnIMPermission imPermission;					// IM权限设置

		StUserInfo hostInfo;							// 主持人信息

		std::string inviteUrl = "";						// 邀请链接

		int roleThreshold = 0;							// 角色阈值，order > 该值默认为 subscribe 角色

		int mediaModeThreshold = 0;						// 媒体模式阈值，order > 该值默认为MCU模式
        
        /// 锁定状态，true为锁定, false为关闭锁定
        bool meetingLock = false;
	};

	//会议属性结构体
	struct StMeetingAttribute {
		bool micStatus = true;							// 入会是否打开麦克风
		bool cameraStatus = true;						// 入会是否打开摄像头
		bool speakerStatus = true;						// 入会是否打开扬声器
		bool isReconnected = false;						// true表示断线重连入会，false表示正常入会
		bool joinType = true;							// 主动入会：true(active), 被动邀请：false(invited)
		std::string touristNickname;					// 游客昵称
		bool inAdvanceToJoin = true;					// 是否提前入会，true表示提前入会，false表示正常入会 
	};

	//预约会议结构体
	struct StAppointConference
	{
		StMeeting meetingInfo;						// 会议信息

		EnMeetingStatus meetingStatus;				// 会议状态

		bool autoCall = true;						// 是否自动呼叫
		bool allowParticipantJoinInAdvance = true;	// 允许参会者提前加入会议

		std::vector<StUserInfo> participantList;	// 与会者列表

		bool moderatorVideoStatus = true;			// 主持人入会视频状态
		bool moderatorMicStatus = true;				// 主持人入会麦克风状态
		bool participantVideoStatus = true;			// 与会者入会视频状态
		bool participantMicStatus = true;			// 与会者入会麦克风状态
	};

	typedef struct _h5pageInfo
	{
		EnH5PageType type;
		std::string url;
	}H5PageInfo;

	struct ConfRoomInfo
	{
		int id;								// 会议室id
		int userId;							// 登录用户id
		std::string roomSubject;            // 会议室主题
		std::string roomId;					// 会议室id
		int roomCapacity;					// 会议室容量
		std::string  password;				// 入会密码
		std::string  moderatorPassword;		// 主持人密码
		std::string  micStatus;				// 入会静音模式（全部静音：on，不静音：off）
		std::string  videoStatus;			// 入会视频状态（开启：on，关闭：off）
		std::string  sharePower;			// 开启：on，关闭：off
		std::string allowPartOperMic;		// 是否允许用户操作静音模式（是：on，否：off）
		std::string allowPartOperShare;		//（开启：on，关闭：off）

		ConfRoomInfo()
			: id(0),
			userId(0),
			roomSubject(""),
			roomId(""),
			roomCapacity(0),
			password(""),
			moderatorPassword(""),
			micStatus(""),
			videoStatus(""),
			sharePower(""),
			allowPartOperMic(""),
			allowPartOperShare("") {}
	};


	struct ConferenceRecordInfo
	{
		std::string recordName;			//文件名
		long long recordSize;			//文件大小(byte)
		std::string thumbnailUrl;		//缩略图地址
		long long id;					//会议录制记录id
		long long startTime;			//文件录制开始时间
		long long endTime;				//文件录制结束时间
		long long requestStartTime;		//开始录制时间

		ConferenceRecordInfo()
			: recordName(""),
			recordSize(0),
			thumbnailUrl(""),
			id(0),
			startTime(0),
			endTime(0),
			requestStartTime(0) {}
	};


	struct ConferenceRecordInfoList
	{
		long total;   //录制文件总数
		std::vector<ConferenceRecordInfo>  recordInfos;

		ConferenceRecordInfoList()
			: total(0) {}
	};


	struct StLanguageTranscribeParam
	{
		EnLanguageType srcType;				// 转写源语言
		EnAudioCodec codec;					// 音频编码格式
		StLanguageTranscribeParam() {
			srcType = LANGUAGE_CN;
			codec = AUDIO_RAW;
		}
		StLanguageTranscribeParam & operator = (StLanguageTranscribeParam param) {
			this->srcType = param.srcType;
			this->codec = param.codec;
			return *this;
		}
	};


	struct StLanguageTranslateParam
	{
		EnLanguageType srcType;				// 翻译源语言
		EnLanguageType dstType;				// 翻译目标语言
		StLanguageTranslateParam() {
			srcType = LANGUAGE_CN;
			dstType = LANGUAGE_EN;
		}
		StLanguageTranslateParam & operator = (StLanguageTranslateParam param) {
			this->srcType = param.srcType;
			this->dstType = param.dstType;
			return *this;
		}
	};


	struct StSubtitle
	{
		std::string transcribeResult;		// 转写结果
		std::string translateResult;		// 翻译结果
		StSubtitle(std::string _transcribeResult, std::string _translateResult) :
			transcribeResult(_transcribeResult),
			translateResult(_translateResult) {}
	};

	// Todo(guol)
	//	How about substituting <StMeeting> for <StUnfinishedRoomInfo>
	struct StUnfinishedRoomInfo
	{
		std::string roomId;                 // 会议ID
		std::string hostAccount;			// 主持人账号
		std::string password;               // 入会密码
		std::string subject;                // 会议主题
		int remainTime;						// 剩余时间
		EnRoomRole role;					// 会议中角色
		bool audioOutStatus;				// 扬声器状态
		bool audioInStatus;					// 麦克风状态
		bool videoStatus;					// 视频状态
		bool shareStatus;					// 共享状态
		bool handStatus;                    // 是否在举手
		bool speakStatus;                   // 是否在发言
		int order;							// 与会者顺序

		StUnfinishedRoomInfo()
		{
			roomId = "";
			password = "";
			subject = "";
			remainTime = 0;
			role = ROLE_PARTICIPANT;
			audioOutStatus = true;
			audioInStatus = true;
			videoStatus = true;
			shareStatus = false;
			handStatus = false;
			speakStatus = false;
			order = 0;
		}

		StUnfinishedRoomInfo & operator = (StUnfinishedRoomInfo roomInfo)
		{
			this->roomId = roomInfo.roomId;
			this->password = roomInfo.password;
			this->subject = roomInfo.subject;
			this->remainTime = roomInfo.remainTime;
			this->role = roomInfo.role;
			this->audioOutStatus = roomInfo.audioOutStatus;
			this->audioInStatus = roomInfo.audioInStatus;
			this->videoStatus = roomInfo.videoStatus;
			this->shareStatus = roomInfo.shareStatus;
			this->handStatus = roomInfo.handStatus;
			this->speakStatus = roomInfo.speakStatus;
			this->order = roomInfo.order;

			return *this;
		}
	};

	struct StPtzControlParam
	{
		std::string targetAccount;		// 操纵的目标用户账号
		int operation;					// 操作类型枚举：1(up),2(down),3(left),4(right),5(zoom in),6(zoom out)
		int maxDuration;				// 最大持续时间（ms）

		StPtzControlParam(int opt = 0, int duration = 0)
		{
			operation = opt;
			maxDuration = duration;
		}
	};

	struct StPresetPositionConfigInfo
	{

	};

	struct StBarrage
	{
		// 弹幕显示位置
		enum EnPosition
		{
			BARRAGE_POS_TOP,				// 顶端
			BARRAGE_POS_BOTTOM,				// 底部
			BARRAGE_POS_MAX,				// 枚举最大值，无需关注
		};

		// 弹幕显示方式
		enum EnDisplayMode
		{
			BARRAGE_DISPLAY_SCROLL,			// 滚动显示
			BARRAGE_DISPLAY_FIXED,			// 固定显示
			BARRAGE_DISPLAY_MAX,			// 枚举最大值，无需关注
		};

		// 弹幕显示模式
		enum EnFontSize
		{
			BARRAGE_FONT_SMALL,				// 小
			BARRAGE_FONT_MIDDLE,			// 中
			BARRAGE_FONT_LARGE,				// 大
			BARRAGE_FONT_MAX,				// 枚举最大值，无需关注
		};

		// 弹幕颜色
		enum EnBackgroundColor
		{
			BARRAGE_COLOR_NONE,				// 无
			BARRAGE_COLOR_RED,				// 红
			BARRAGE_COLOR_BLUE,				// 蓝
			BARRAGE_COLOR_MAX,				// 枚举最大值，无需关注
		};

		std::string content;				// 弹幕内容
		EnPosition position;				// 显示位置
		EnDisplayMode displayMode;			// 显示方式
		EnFontSize fontSize;				// 字号
		std::string bgColor;				// 背景颜色，rgb值，如"#FF0000"
		float opacity;						// 不透明度
	};

	struct StIMMessage
	{
		enum EnIMMessageTarget
		{
			IM_MESSAGE_TARGET_ALL,			// 发送给：所有人
			IM_MESSAGE_TARGET_SPECIFY,		// 发送给：指定与会者
			IM_MESSAGE_TARGET_MAX,			// 枚举最大值，无需关注
		};

		enum EnIMMessageType
		{
			IM_MESSAGE_TYPE_TEXT,			// 文本信息
			IM_MESSAGE_TYPE_IMAGE,			// 图片信息
			IM_MESSAGE_TYPE_AUDIO,			// 语音信息
			IM_MESSAGE_TYPE_VIDEO,			// 视频信息
			IM_MESSAGE_TYPE_FILE,			// 文件信息
			IM_MESSAGE_TYPE_LINK,			// 链接
			IM_MESSAGE_TYPE_MAX,			// 枚举最大值，无需关注
		};

		enum EnIMMessageSendStatus
		{
			IM_MESSAGE_SEND_SUCCESSED,		// 发送成功
			IM_MESSAGE_SEND_FAILED,			// 发送失败
			IM_MESSAGE_SENDING,				// 发送中
			IM_MESSAGE_SEND_MAX,			// 枚举最大值，无需关注
		};

		bool isResend = false;									// 重发标志位，true表示重发
		EnIMMessageTarget target = IM_MESSAGE_TARGET_ALL;		// 目标与会者范围

		long long id = 0;							// 平台分配、全局唯一的消息ID
		long long timestamp = 0;					// 消息时间戳
		EnIMMessageType msgType = IM_MESSAGE_TYPE_TEXT;				// 消息类型
		std::string content = "";					// 消息内容

		std::vector<StParticipantInfo> receivers;		// 接收者信息
		std::vector<StParticipantInfo> atUsers;		// 被@的与会者信息
		StParticipantInfo sender;						// 发送者信息

		EnIMMessageSendStatus sendStatus = IM_MESSAGE_SEND_SUCCESSED;			// 发送状态

		std::string extraData;						// 额外数据，用于后续拓展或第三方自定义使用
	};

	struct StPushedMsg
	{
		enum EnPushedMsgType
		{
			TYPE_MEETING_INVITATION,				// 会议邀请
			TYPE_MEETING_NOTIFICATION,				// 会议通知
			TYPE_MEETING_MAX,						// 枚举最大值，无需关注
		};

		long long id;						// 消息ID
		long long timestamp;				// 创建时间戳
		EnPushedMsgType type;				// 消息类型
		bool unreadFlag;					// 未读标志位：true表示未读，false表示已读

		std::string content;				// 消息内容
		std::string ruid;					// 会议记录ID
	};

	struct StHardTerminalDeviceInfo
	{
		std::string nickName;		// 昵称
	};

}

#endif //!__cplusplus

#endif //!__SDNP_DEFINE_H__

