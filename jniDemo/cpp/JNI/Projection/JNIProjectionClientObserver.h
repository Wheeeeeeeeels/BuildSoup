#ifndef __SRC_JNI_PROJECTION_JNIPROJECTION_CLIENT_OBSERVER_H__
#define __SRC_JNI_PROJECTION_JNIPROJECTION_CLIENT_OBSERVER_H__

#include <jni.h>

#include "IProjection.h"
#include "../JNICustomGlobalRef.h"

namespace SDNP
{
	class CJNINativeProjectionClientObserver : public IProjectionClient::IObserver
	{
	public:
		CJNINativeProjectionClientObserver();

		virtual ~CJNINativeProjectionClientObserver();

		void setGlobalRef(JNICustomGlobalRef* globalRef);

		void setJNINativeObserver(jobject observer);

	public: //! override
		virtual void onConnectionStatusChanged(EnProjectionConnectionStatus status, int errCode = 0) override;

		virtual void onProjectionReplied(EnProjectionReply result, StProjectionInfo projectInfo) override;

		virtual void onIceCandidate(std::string sdpMid, std::string sdpMLineIndex, std::string candidate) override;

	private:
		jobject     m_jniNativeObserver;
		JNICustomGlobalRef* m_globalRef;
	};
}

#endif //! __SRC_JNI_PROJECTION_JNIPROJECTION_CLIENT_OBSERVER_H__