#ifndef __ALPHA_INTERFACE_SDP_NEGOTIATOR_H__
#define __ALPHA_INTERFACE_SDP_NEGOTIATOR_H__

#ifdef __cplusplus

#include <string>
#include <vector>

#include "SDNPDefine.h"

namespace alpha {

/**
 * @brief Sdp协商流程
 *
 * [1] PeerConnection.createOffer()
 * [2] ISdpNegotiator.SetLocalSdpOffer()
 *
 * [3] ISdpNegotiator.GetLocalSdpOffer()
 * [4] PeerConnection.setLocalDescription()
 *
 * [5] ISdpNegotiator.GetLocalJsonOffer()
 * [6] INetProtocol.publishVideo()
 *   / INetProtocol.createMediaChannel()
 *   / INetProtocol.addMediaTrack()
 *
 * [7] INetProtocol response
 * [8] ISdpNegotiator.AddRemoteJsonAnswer()
 *
 * [9] ISdpNegotiator.CreateRemoteSdpAnswer()
 * [10] PeerConnection.setRemoteDescription()
 */

class SD_INTERFACE_EXPORT ISdpNegotiator {
   public:
    /**
     * @brief 创建sdp协商器
     *        注意：每次调用返回一个新的sdp协商器，需要调用Destroy销毁
     * @return ISdpNegotiator* sdp协商器对象
     */
    static ISdpNegotiator* Create();

    /**
     * @brief 销毁sdp协商器
     * @param negotiator sdp协商器对象
     */
    static void Destroy(ISdpNegotiator* negotiator);

   public:
    /**
     * @brief 设置本地原生SdpOffer
     *
     * @param sdp_offer 本地原生SdpOffer，由PeerConnection.createOffer()生成
     * @return int 0表示成功，非0表示失败
     */
    virtual int SetLocalSdpOffer(std::string sdp_offer) = 0;

    /**
     * @brief 获取本地处理后的SdpOffer
     *
     * @param vcodec_selected 指定视频编码类型，若为空表示全部
     * @param acodec_selected 指定音频编码类型，若为空表示全部
     * @return std::string 本地处理后的SdpOffer
     */
    virtual std::string GetLocalSdpOffer(std::string vcodec_selected = "",
                                         std::string acodec_selected = "") = 0;

    /**
     * @brief 获取转为Json格式后的本地SdpOffer
     *
     * @param transport_need 是否需要传输通道信息
     * @param mids 需要的媒体信息mid列表，若为空表示不需要媒体信息
     * @return std::string Json格式的本地SdpOffer
     */
    virtual std::string GetLocalJsonOffer(bool transport_need,
                                          std::vector<std::string> mids) = 0;

    /**
     * @brief 添加对端回复的Json格式的SdpAnswer
     *
     * @param sdp_answer 对端回复的Json格式的SdpAnswer
     * @return int 0表示成功，非0表示失败
     */
    virtual int AddRemoteJsonAnswer(std::string sdp_answer) = 0;

    /**
     * @brief 移除对端回复的Json格式的SdpAnswer
     *
     * @param mids 需要移除的媒体信息mid列表
     * @return int 0表示成功，非0表示失败
     */
    virtual int RemoveRemoteJsonAnswer(std::vector<std::string> mids) = 0;

    /**
     * @brief 创建SdpAnswer
     *
     * @return std::string SdpAnswer
     */
    virtual std::string CreateRemoteSdpAnswer() = 0;

   protected:
    /**
     * @brief 析构函数
     */
    virtual ~ISdpNegotiator() {}
};

}  // namespace alpha

#endif  //__cplusplus

#endif  //__ALPHA_INTERFACE_SDP_NEGOTIATOR_H__
