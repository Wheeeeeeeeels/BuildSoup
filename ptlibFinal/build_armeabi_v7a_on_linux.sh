#!/bin/bash
##############################################################################################################################
#####################################               预留 >>>

# 若指令传回值不等于0，则立即退出shell
fun_enable_break(){
    set -e
}

fun_disable_break(){
    set +e
}

#####################################               <<< 预留
##############################################################################################################################



##############################################################################################################################
#####################################               工程构建选项 >>>
param_count=2
fun_usage(){
    echo "Usage: $0 <do_configure> <clean_build>"
    echo "  e.g. $0 0 0"
    echo
    echo "  do_configure: "
    echo "      0 for not doing configure operation."
    echo "      1 for doing configure operation."
    echo
    echo "  clean_build: "
    echo "      0 for incremental compile."
    echo "      1 for ordinary(fully) compile."
}

if test $# -ne $param_count; then
    fun_usage
    exit
fi

do_configure=$1
if test $1 -ne 0 && test $1 -ne 1; then
    echo "Please specify the <do_configure>"
    echo 
    fun_usage
    exit
fi


# 是否全量编译，1表示全量编译，0表示增量编译
clean_build=$2
if test $2 -ne 0 && test $2 -ne 1; then
    echo "Please specify the <clean_build>"
    echo 
    fun_usage
    exit
fi
#####################################               <<< 工程构建选项
##############################################################################################################################



##############################################################################################################################
#####################################               设置工程路径相关信息 >>>
arch=armeabi-v7a
short_commit_id=`git rev-parse --short HEAD`

root_dir=`pwd`
echo root_dir: $root_dir

install_dir=$root_dir/install_$short_commit_id/$arch
# install_dir=$root_dir/install/$arch\_$short_commit_id
# install_dir=$root_dir/install/$arch
echo install_dir: $install_dir
#####################################               <<< 设置工程路径相关信息
##############################################################################################################################



##############################################################################################################################
#####################################               指定编译器、编译选项 >>>
# 设置交叉编译参数
cross_compiler_dir=/opt/env/android/android-compile-tools/r16b/arm/bin
# cross_compiler_dir=/home/guol/Downloads/ndk/android-ndk-r23b/toolchains/llvm/prebuilt/linux-x86_64/bin
# cross_compiler_dir=/home/guol/Downloads/ndk/android-ndk-r18b/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin
export PATH=$PATH:$cross_compiler_dir
#cross_compiler_prefix=aarch64-linux-android
cross_compiler_prefix=arm-linux-androideabi

# qn_cross_compile：交叉编译的标志位
#   1表示交叉编译；0表示非交叉编译
if test ${arch} =armeabi-v7a; then
    export qn_cross_compile=yes
    export qn_android_api=21
else
    export qn_cross_compile=no
fi

# 设置一个宏定义，用于表示交叉编译
qn_macro_definition="QN_CROSS_COMPILE"
QN_CFLAGS="-D${qn_macro_definition} -DGUOL"
# QN_CFLAGS="-D${qn_macro_definition} -D__ANDROID_API__=16"
#####################################               <<< 指定编译器、编译选项
##############################################################################################################################



##############################################################################################################################
#####################################               编译 >>>
if test $do_configure -eq 1; then
    # 删除以前的构建
    rm -rf $install_dir

    # !!! configure:8235 会尝试进入该目录，临时创建该目录防止出错中断
    mkdir -p $install_dir

    # ./configure \
    #     --prefix=$install_dir \
    #     --host=$cross_compiler_prefix \
    #     CFLAGS="${QN_CFLAGS}   -march=armv7-a" \
    #     CPPFLAGS="${QN_CFLAGS} -march=armv7-a" \
    #     CXXFLAGS="${QN_CFLAGS} -march=armv7-a" 
        #-lOpenSLES
    #    # LIBS = -lOpenSLES
    #     # --target=$arch \
    #     # --enable-debug \
    #     # --enable-memcheck \
    #     # --enable-samples

    # !!! 此处删除 $install_dir 目录，否则 make install 时会检测认为 $install_dir 目录已update，不会真正把生成物放到 $install_dir 中
    rm -rf $install_dir
fi

# exit

# echo CC: $CC
# echo CFLAGS: $CFLAGS
# echo CXX: $CXX
# echo CXXFLAGS: $CXXFLAGS
# echo CPPFLAGS: $CPPFLAGS
# echo LDFLAGS: $LDFLAGS
# echo LIBS: $LIBS

if test $clean_build -eq 1; then
    make clean
fi

fun_enable_break

make -j3
make install

#####################################               <<< 编译
##############################################################################################################################



##############################################################################################################################
#####################################               生成配置文件，opal编译导入使用 >>>
ptlib_variables_file=$install_dir/ptlib_variables
echo "#!/usr/bin/sh" >> $ptlib_variables_file
echo "# Generated by ptlib build script." > $ptlib_variables_file
echo "# Please don't edit it." > $ptlib_variables_file
echo > $ptlib_variables_file
echo "PKG_CONFIG_PATH=$install_dir/lib/pkgconfig" > $ptlib_variables_file

echo "ptlibt_pkgconfig_path=$install_dir/lib/pkgconfig"
#####################################               <<< 生成配置文件，opal编译导入使用
##############################################################################################################################



#./configure \
#    --prefix=$install_dir \
#    --host=$cross_compiler_prefix \
#    --with-openssl-dir=$OPENSSL_HOME \
#    CFLAGS="${QN_CFLAGS}" \
#    CPPFLAGS="${QN_CFLAGS}" \
#    CXXFLAGS="${QN_CFLAGS}" \
#    --enable-samples

#make -j3
#make install
