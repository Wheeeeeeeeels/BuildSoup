
#ifndef __SRC_INTERFACE_IPROJECTION_H__
#define __SRC_INTERFACE_IPROJECTION_H__

#ifdef __cplusplus

#include <vector>
#include <string>

#include "SDNPDefine.h"

namespace SDNP
{

	// 投屏信息
	struct StProjectionInfo
	{
		std::string serialNumber = "";			// 设备序列号
		std::string name = "";					// 设备名称
		std::string projectionCode = "";		// 投屏码
		std::string wsAddress = "";				// 投屏服务websocket地址
	};

	enum EnProjectionConnectionStatus
	{
		PROJECTION_CONNECTION_EXCEPTION,		// 连接异常，状态更新时机：未连接->连接异常
		PROJECTION_CONNECTION_CONNECTED,		// 已连接，状态更新时机：未连接->连接成功
		PROJECTION_CONNECTION_DISCONNECTED,		// 连接异常断开，状态更新时机：连接状态->连接断开
		PROJECTION_CONNECTION_CLOSED,			// 连接正常关闭，状态更新时机：连接状态->关闭连接
	};

	enum EnProjectionReply
	{
		PROJECTION_ACCEPTED,		// 服务端接受投屏请求
		PROJECTION_REFUSED,			// 服务端拒绝投屏请求
		PROJEDTION_WAITTING,		// 服务端阻塞30s处理投屏请求
	};


	// MARK: - // 投屏服务端
	class SD_INTERFACE_EXPORT IProjectionServer
	{
	public:
		// 投屏服务端时间观察者
		class IObserver
		{
		public:
			/**
			* @brief 客户端开始投屏通知
			* @param[in] wsUniqueIdentityCode: 投屏客户端websocket唯一标识码
			* @param[in] name: 投屏客户端主机名称
			* @return 无
			*/
			virtual void onClientStartProject(std::string wsUniqueIdentityCode, std::string name) = 0;

			/**
			* @brief 客户端结束投屏通知
			* @param[in] wsUniqueIdentityCode: 投屏客户端websocket唯一标识码
			* @param[in] name: 投屏客户端主机名称
			* @return 无
			*/
			virtual void onClientFinishProject(std::string wsUniqueIdentityCode, std::string name) = 0;

			/**
			* @brief 客户端媒体协商offer上传通知
			* @param[in] wsUniqueIdentityCode: 投屏客户端websocket唯一标识码
			* @param[in] msgId: 对应SDP Offer的消息ID
			* @param[in] sdpOffer: 媒体协商SDP offer
			* @return 无
			*/
			virtual void onSdpOffer(std::string wsUniqueIdentityCode, int msgId, std::string sdpOffer) = 0;

			/**
			* @brief 客户端候选地址上传通知
			* @param[in] wsUniqueIdentityCode: 投屏客户端websocket唯一标识码
			* @param[in] sdpMid 媒体ID
			* @param[in] sdpMLineIndex 媒体描述行索引
			* @param[in] candidate Candidate信息
			* @return 无
			*/
			virtual void onIceCandidate(std::string wsUniqueIdentityCode, std::string sdpMid, int sdpMLineIndex, std::string candidate) = 0;

		}; //! class IObserver

	public:
		/**
		* @brief 获取IProjectionServer实例
		* @return IProjectionServer实例
		*/
		static IProjectionServer* instance();

		/**
		* @brief debug
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int test() = 0;

		/**
		* @brief 注册观察者对象
		* @param[in] observer: 投屏事件观察者
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int registerObserver(IObserver* observer) = 0;

		/**
		* @brief 设置本地ipv4地址
		* @param[in] ipv4Address: 本地ipv4地址
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int setIpv4Address(std::string ipv4Address) = 0;

		/**
		* @brief 启动投屏服务
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int startProjectionService() = 0;

		/**
		* @brief 停止投屏服务
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int stopProjectionService() = 0;

		/**
		* @brief 发送SDP Answer
		* @param[in] wsUniqueIdentityCode: 投屏客户端websocket唯一标识码
		* @param[in] msgId: 对应SDP Offer的消息ID
		* @param[in] sdpAnswer: 媒体协商应答信息
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int sendSdpAnswer(std::string wsUniqueIdentityCode, int msgId, std::string sdpAnswer) = 0;

		/**
		* @brief 发送SDP Answer
		* @param[in] wsUniqueIdentityCode: 投屏客户端websocket唯一标识码
		* @param[in] sdpMid 媒体ID
		* @param[in] sdpMLineIndex 媒体描述行索引
		* @param[in] iceCandidate: 媒体协商应答信息
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int sendIceCandidate(std::string wsUniqueIdentityCode, std::string sdpMid, int sdpMLineIndex, std::string iceCandidate) = 0;

		/**
		* @brief 回复客户端申请投屏结果
		* @param[in] wsUniqueIdentityCode: 投屏客户端websocket唯一标识码
		* @param[in] result: 投屏结果，由上层指定
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int replyProjectionRequest(std::string wsUniqueIdentityCode, EnProjectionReply result) = 0;

		/**
		* @brief 结束指定客户端投屏
		* @param[in] wsUniqueIdentityCode: 投屏客户端websocket唯一标识码
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int stopProjectingFromClient(std::string wsUniqueIdentityCode) = 0;

		/**
		 * @brief 由app层设置投屏相关属性
		 *		  该接口不可与applyForProjectionCode同时使用
		 * @param[in] name: 设备名称
		 * @param[in] serialNumber: 设备序列号
		 * @param[out] projectionCode: 投屏码
		 * @param[in] wsAddress: 投屏服务websocket服务地址
		 * @return CODE_SUCCESS表示成功，否则失败
		 */
		virtual int setProjectPropertiesByApp(std::string name, std::string serialNumber, std::string projectionCode, std::string wsAddress) = 0;

		/**
		 * @brief 投屏服务端申请投屏码
		 * @param[in] ipv4Address: 设备IPV4地址
		 * @param[in] name: 设备名称
		 * @param[in] serialNumber: 设备序列号
		 * @param[out] projectionCode: 投屏码
		 * @return CODE_SUCCESS表示成功，否则失败
		 */
		virtual int applyForProjectionCode(std::string ipv4Address, std::string name, std::string serialNumber, OUT std::string& projectionCode) = 0;

		/**
		 * debug
		 */
		virtual int applyForProjectionCode(std::string ipv4Address, std::string name, std::string serialNumber) = 0;

	}; //! class IProjectionServer


    // MARK: - // 投屏客户端
	class SD_INTERFACE_EXPORT IProjectionClient
	{
	public:
		// 投屏客户端事件观察者
		class IObserver
		{
		public:
			/**
			* @brief 连接状态变更通知
			* @param[in] status: 连接状态
			* @param[in] errCode: 错误码，在连接异常(status == PROJECTION_CONNECTION_EXCEPTION)时使用
			* @return 无
			*/
			virtual void onConnectionStatusChanged(EnProjectionConnectionStatus status, int errCode = 0) = 0;

			/**
			* @brief 申请投屏结果回复通知
			* @param[in] result: 投屏结果
			* @param[in] projectInfo: 投屏信息
			* @return 无
			*/
			virtual void onProjectionReplied(EnProjectionReply result, StProjectionInfo projectInfo) = 0;

			/**
			 * @brief 收到ICE Candidate信息通知
			 * @param[in] sdpMid 媒体ID
			 * @param[in] sdpMLineIndex 媒体描述行索引
			 * @param[in] candidate Candidate信息
			 * @return 无
			 */
			virtual void onIceCandidate(std::string sdpMid, std::string sdpMLineIndex, std::string candidate) = 0;
		}; //! class IObserver

	public:
		/**
		* @brief 获取IProjectionClient实例
		* @return IProjectionClient实例
		*/
		static IProjectionClient* instance();

//		/**
//		* @brief 创建IProjectionClient实例，非单例
//		* @return IProjectionClient实例
//		*/
//		static IProjectionClient* createInstance();

		/**
		* @brief 销毁IProjectionClient实例
		* @param[in] client: IProjectionClient实例，要求该实例调用createInstance创建
		* @return 无
		*/
		static void destoryInstance(IProjectionClient** client);

		/**
		* @brief 【Android】设置本地ipv4地址
		* @param[in] ipv4Address: 本地ipv4地址
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int setIpv4Address(std::string ipv4Address) = 0;

		/**
		* @brief 注册观察者对象
		* @param[in] observer: 投屏事件观察者
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int registerObserver(IObserver* observer) = 0;

		/**
		* @brief 客户端请求投屏
		* @param[in] projectionCode: 投屏码
		* @param[in] name: 设备名称
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int startProject(std::string projectionCode, std::string name) = 0;

		/**
		* @brief 客户端结束投屏
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int finishProject() = 0;

		/**
		* @brief 发送SDP Offer
		* @param[in] sdpOffer 媒体描述信息
		* @param[out] sdpAnswer 媒体描述应答信息
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int sendSdpOffer(std::string sdpOffer, OUT std::string& sdpAnswer) = 0;

		/**
		* @brief 发送ICE Candidate信息
		* @param[in] sdpMid 媒体ID
		* @param[in] sdpMLineIndex 媒体描述行索引
		* @param[in] candidate Candidate信息
		* @return CODE_SUCCESS表示成功，否则失败
		*/
		virtual int sendIceCandidate(std::string sdpMid, std::string sdpMLineIndex, std::string candidate) = 0;

	protected:
		/**
		 * @brief 析构函数
		 * @return 无
		 */
		virtual ~IProjectionClient() {}

	}; //! class IProjectionClient

    // MARK: -
	class SD_INTERFACE_EXPORT IProjectDebugHttpServer
	{
	public:
		/**
		 * debug
		 * @param[in] isProjectServer: true表示由投屏客户端调用，false表示由投屏服务端调用
		 * @param[in] projectObject: isProjectServer == true时，必须传入
		 * @param[in] port: debug http server 监听端口
		 */
		static void start(bool isProjectServer, IProjectionClient * projectObject = nullptr, int port = 8899);
		static void stop();
	}; //! class IProjectDebugHttpServer

} //! namespace SDNP

#endif //!__cplusplus

#endif //!__SRC_INTERFACE_IPROJECTION_H__
