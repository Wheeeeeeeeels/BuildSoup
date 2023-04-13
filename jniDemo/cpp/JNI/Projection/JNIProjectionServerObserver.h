#ifndef __SRC_JNI_PROJECTION_JNIPROJECTION_SERVER_OBSERVER_H__
#define __SRC_JNI_PROJECTION_JNIPROJECTION_SERVER_OBSERVER_H__

#include <jni.h>

#include "IProjection.h"
#include "../JNICustomGlobalRef.h"

namespace SDNP
{
	class CJNINativeProjectionServerObserver : public IProjectionServer::IObserver
	{
	public:
		CJNINativeProjectionServerObserver();

		virtual ~CJNINativeProjectionServerObserver();

		void setGlobalRef(JNICustomGlobalRef* globalRef);

		void setJNINativeObserver(jobject observer);

	public: //! override
		virtual void onClientStartProject(std::string uniqueIdentityCode, std::string name) override;

		virtual void onClientFinishProject(std::string uniqueIdentityCode, std::string name) override;

		virtual void onSdpOffer(std::string uniqueIdentityCode, int msgId, std::string sdpOffer) override;

		virtual void onIceCandidate(std::string uniqueIdentityCode, std::string sdpMid, int sdpMLineIndex, std::string candidate) override;

	private:
		jobject     m_jniNativeObserver;
		JNICustomGlobalRef* m_globalRef;
	};
}

#endif //! __SRC_JNI_PROJECTION_JNIPROJECTION_SERVER_OBSERVER_H__