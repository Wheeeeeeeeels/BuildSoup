#include <assert.h>

#include "JNICustomGlobalRef.h"
#include "SDNPLogger.h"
#include "SDNPUtil.h"

namespace SDNP
{
	JNICustomGlobalRef * JNICustomGlobalRef::instance()
	{
		static JNICustomGlobalRef globalRef;
		return &globalRef;
	}

	void JNICustomGlobalRef::setJNIEnv(JNIEnv * env)
	{
		assert(env != NULL);

		m_env = env;
	}

	void JNICustomGlobalRef::setGlobalRef(std::string name)
	{
		CHECK_NULL(m_env, "JNIEnv is NULL", );
		assert(m_customJObjectMap.count(name) == 0);

		jclass jniClass = m_env->FindClass(name.c_str());
		if (jniClass == NULL) {
			errorf("FIND CLASS %s FAILED!!!", name.c_str());
		}
		jmethodID constructorID = m_env->GetMethodID(jniClass, "<init>", "()V");

		jobject joObject = m_env->NewObject(jniClass, constructorID);
		m_env->DeleteLocalRef(jniClass);

		jobject joGlobalRef = m_env->NewGlobalRef(joObject);
		m_env->DeleteLocalRef(joObject);

		debugf("%s name[%s]", __FUNCTION__, name.c_str());
		m_customJObjectMap[name] = joGlobalRef;
	}

	void JNICustomGlobalRef::setGlobalRef(std::string name, jobject globalRef)
	{
		assert(m_customJObjectMap.count(name) == 0);

		debugf("%s name[%s]", __FUNCTION__, name.c_str());
		m_customJObjectMap[name] = globalRef;
	}

#if 0
	void JNICustomGlobalRef::setAllGlobalRef(JNICustomGlobalRef globalRef)
	{
		assert(m_customJObjectMap.size() == 0);

		m_customJObjectMap = globalRef;
		debugf("%s size[%d]", __FUNCTION__, m_customJObjectMap.size());
	}
#endif

	jobject JNICustomGlobalRef::getGlobalRef(std::string name)
	{
		assert(m_customJObjectMap.count(name) > 0);

		return m_customJObjectMap[name];
	}

#if 0
	JNICustomGlobalRef JNICustomGlobalRef::getAllGlobalRef()
	{
		return m_customJObjectMap;
	}
#endif

	void JNICustomGlobalRef::clearAllGlobalRef()
	{
		for (auto iter : m_customJObjectMap)
		{
			m_env->DeleteGlobalRef(iter.second);
		}
		m_customJObjectMap.clear();
	}

	JNICustomGlobalRef::JNICustomGlobalRef()
	{
	}

	JNICustomGlobalRef::~JNICustomGlobalRef()
	{
		clearAllGlobalRef();
	}

	void JNICustomGlobalRef::debugPrint(std::string name)
	{
		if (m_customJObjectMap.count(name) == 0)
		{
			errorf("Can't find global reference named <%s>", name.c_str());
			int i = 0;
			for (auto ref : m_customJObjectMap)
			{
				debugf("ref[%d] name[%s]", i++, ref.first.c_str());
			}
		}
	}
}
