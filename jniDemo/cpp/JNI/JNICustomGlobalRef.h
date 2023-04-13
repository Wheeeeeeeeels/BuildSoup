#ifndef __JNI_CUSTOM_GLOBAL_REF_H__
#define __JNI_CUSTOM_GLOBAL_REF_H__

#include <jni.h>
#include <map>
#include <string>

namespace SDNP
{
	/*
	 * 该类用于保存自定义java类的对象，用于JNICustomGlobalRefManger获取引用
	 **/
	class JNICustomGlobalRef
	{
	public:
		static JNICustomGlobalRef* instance();

		void setJNIEnv(JNIEnv* env);

		// 设置指定全局引用
		void setGlobalRef(std::string name);
		// 设置指定全局引用
		void setGlobalRef(std::string name, jobject globalRef);

#if 0
		// 设置所有全局引用
		void setAllGlobalRef(JNICustomGlobalRef globalRef);
#endif

		// 获取指定全局引用，未保存指定全局引用返回nullptr，该引用不需调用者释放
		jobject getGlobalRef(std::string name);

#if 0
		// 获取所有全局引用
		JNICustomGlobalRef getAllGlobalRef();
#endif

		// 清除所有全局应用
		void clearAllGlobalRef();

	private:
		JNICustomGlobalRef();
		~JNICustomGlobalRef();
		void debugPrint(std::string name);

		//
		JNIEnv* m_env;

		// 保存需要用到的所有<类名称，全局引用>的映射
		std::map<std::string /*name*/, jobject /*globalRef*/> m_customJObjectMap;
	};
}


#endif /*__JNI_CUSTOM_GLOBAL_REF_H__*/
