#ifndef __JNI_NATIVE_OBSERVER_H__
#define __JNI_NATIVE_OBSERVER_H__

#include <jni.h>
#include "INetProtocol.h"
#include "JNICustomGlobalRef.h"

namespace SDNP
{

class CJNINativeObserver : public IObserver
{
public:
    CJNINativeObserver();

    virtual ~CJNINativeObserver();

	virtual EnDeviceNetState onFetchDeviceNetState() override;

    virtual void onTokenBecameInvalid() override;

    virtual void onOthersLogin() override;

	virtual void onServiceAvailableChange(bool state, int code, std::string message) override;

	virtual void onNetworkConnectStatusChange(EnNetState state, int code, std::string message) override;

    virtual void onOnlineStateChange(bool online) override;

	virtual void onVersionUpgrade(bool foreStatus, std::string downLoadUrl, std::string version, std::string details) override;

	virtual void onVersionUpgrade(std::string serialNumber, bool foreStatus, std::string downLoadUrl, std::string version, std::string details) override;

	virtual void onPushLog(PushLogStrategy strategy) override;

	virtual void onPushLogResult(bool result) override;

	virtual void onServiceExpired(bool isExpired, std::string expiredDate, int daysToExpiredDate) override;

	virtual void onConversationDurationStatus(EnConversationDuration duration, int hours, int minutes) override;

	virtual void onTimeSynchronization(long long serverTimestamp) override;

	virtual void onEvictedByCorp() override;
	
	virtual void onHardTerminalDeviceInfoChanged(StHardTerminalDeviceInfo deviceInfo) override;

	virtual void onConferenceToBegin(std::string username, std::string subject, long long startTime, long long endTime) override;

	virtual void onConferenceCreated(std::string username, std::string subject, long long startTime, long long endTime) override;
	
	virtual void onConferenceCanceled(std::string roomId, std::string ruid, std::string subject, EnConferenceCanceledReason reason) override;

    void setJNIJavaObserver(jobject& observer);

public:
	void setGlobalRef(JNICustomGlobalRef* globalRef);

private:
	jobject m_jniJavaObserver;
	JNICustomGlobalRef* m_globalRef;
};

}   // end namespace SDP

#endif