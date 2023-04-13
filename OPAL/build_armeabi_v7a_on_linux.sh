#!/bin/sh
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
    echo "Usage: $0 <ptlib_path> <clean_build>"
    # echo "Usage: $0 <ptlib_path> <do_configure> <clean_build>"
    echo
    echo "  ptlib_path: "
    echo "      Absolute path where ptlib is installed."
    # echo
    # echo "  do_configure: "
    # echo "      0 for not doing configure operation."
    # echo "      1 for doing configure operation."
    echo
    echo "  clean_build: "
    echo "      0 for incremental compile."
    echo "      1 for ordinary(fully) compile."
}

if test $# -ne $param_count; then
    fun_usage
    exit
fi

# ptlib_variables_file文件名在ptlib的构建脚本中指定
ptlib_variables_file=$1/ptlib_variables

echo "-----------------------------"
echo ${ptlib_variables_file}
echo "-----------------------------"

if test ! -e $ptlib_variables_file; then
    echo "Please specify the <ptlib_path>"
    echo 
    fun_usage
    exit
fi




# do_configure=$2
# if test $do_configure != 0 && test $do_configure != 1; then
#     echo "Please specify the <do_configure>"
#     echo 
#     fun_usage
#     exit
# fi


# 是否全量编译，1表示全量编译，0表示增量编译
clean_build=$2
if test $clean_build != 0 && test $clean_build != 1; then
    echo "Please specify the <clean_build>"
    echo 
    fun_usage
    exit
fi
#####################################               <<< 工程构建选项
##############################################################################################################################



##############################################################################################################################
#####################################               导入ptlib参数 >>>
# source 和 . 是import，类似于c预处理的导入展开

# source 是bash的命令，在sh中找不到该命令
# source $ptlib_variables_file

. $ptlib_variables_file

# sh 是开一个新的shell去处理
# sh $ptlib_variables_file

echo ptlibt_pkgconfig_path:$ptlibt_pkgconfig_path
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$ptlibt_pkgconfig_path
#####################################               <<< 导入ptlib参数
##############################################################################################################################



##############################################################################################################################
#####################################               指定编译器、编译选项 >>>
arch=arm-linux-androideabi

# 编译opus需要用到aclocal-1.15，Ubuntu官方源中提供的automake为1.14，所以自己编译1.15版本
# url: https://ftp.gnu.org/gnu/automake/automake-1.15.tar.gz
automake_dir=/home/wuh/automake-1.15/bin

# 设置交叉编译参数
cross_compiler_dir=/opt/env/android/android-compile-tools/r16b/arm/bin
export PATH=$PATH:$cross_compiler_dir:$automake_dir

# cross_compiler_prefix=aarch64-linux-android

cross_compiler_prefix=arm-linux-androideabi

echo "-------cross_compiler_prefix--------${cross_compiler_prefix}--------\n"

# 设置编译器前缀，在bfcp中取该值用于指定编译器
export qn_cross_compiler_prefix=${cross_compiler_prefix}-
# qn_cross_compiler_prefix = "${cross_compiler_prefix}-"

# echo "------qn_cross_compiler_prefix = ${qn_cross_compiler_preifx}--------\n"

# qn_cross_compile：交叉编译的标志位
#   1表示交叉编译；0表示非交叉编译
if test ${arch}=arm-linux-androideabi; then
    export qn_cross_compile=yes
    echo "----当前android-api = 21 准备进行交叉编译-----"
    export qn_android_api=21
else
    export qn_cross_compile=no
    echo "-----没有进行交叉编译-------"
fi

# 设置一个宏定义，用于表示交叉编译
qn_macro_definition="QN_CROSS_COMPILE"
QN_CFLAGS="-D${qn_macro_definition}"
# QN_CFLAGS="-D${qn_macro_definition} -DP_ANDROID"
# QN_CFLAGS="-D${qn_macro_definition} -D__ANDROID_API__=16"
#####################################               <<< 指定编译器、编译选项
##############################################################################################################################



##############################################################################################################################
#####################################               设置工程路径相关信息 >>>
short_commit_id=`git rev-parse --short HEAD`

root_dir=`pwd`
echo root_dir: $root_dir

install_dir=$root_dir/install_$short_commit_id/$arch
# install_dir=$root_dir/install/$arch\_$short_commit_id
# install_dir=$root_dir/install/$arch
echo install_dir: $install_dir


# openssl 相关变量
OPENSSL_HOME=/home/wuh/openssl_install/arm
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OPENSSL_HOME
echo OPENSSL_HOME: $OPENSSL_HOME
#####################################               <<< 设置工程路径相关信息
##############################################################################################################################



##############################################################################################################################
#####################################               编译opal >>>
# 删除以前的安装
rm -rf $install_dir

# !!! configure:8235 会尝试进入该目录，临时创建该目录防止出错中断
mkdir -p $install_dir

echo "------------------------------------------${QN_CFLAGS}------------------------------------------------------------"
# message ("------------------------------------------${QN_CFLAGS}------------------------------------------------------------")
echo "\n------${cross_compiler_prefix}-----交叉编译前缀---------"
# ./configure \
#     --prefix=$install_dir \
#     --host=$cross_compiler_prefix \
#     --with-openssl-dir=$OPENSSL_HOME \
#     CFLAGS="${QN_CFLAGS}"  \
#     CPPFLAGS="${QN_CFLAGS}" \
#     CXXFLAGS="${QN_CFLAGS}" 
    # --enable-debug \
    # --enable-memcheck \




echo "******************************************************************************************************"
echo "***************************************EXIT***********************************************************"
echo "******************************************************************************************************"

# exit

# !!! 此处删除 $install_dir 目录，否则 make install 时会检测认为 $install_dir 目录已update，不会真正把生成物放到 $install_dir 中
rm -rf $install_dir



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

# compile and install
make -j7
make install
#####################################               <<< 编译opal
##############################################################################################################################

# 清除 opus编译过程中产生的冗余
# if test $clean_build -eq 1; then
#     make clean
#     rm -rf $install_dir

#     # clean opus，在测试脚本期间，发现opus不会被顶层make clean清除掉
#     opus_dir=$root_dir/plugins/audio/Opus/opus
#     if test -d $root_dir/plugins/audio/Opus/opus/.libs; then
#         make -C $opus_dir clean
#     fi
# fi



echo "******************************************************************************************************"
echo "***************************************START BUILD SAMPLES********************************************"
echo "******************************************************************************************************"



##############################################################################################################################
#####################################               编译samples >>>
# 如果构建samples，需要提前指定opal.pc的路径
opal_pkgconfig_path=$install_dir/lib/pkgconfig
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$opal_pkgconfig_path


# ./configure \
#     --prefix=$install_dir \
#     --host=$cross_compiler_prefix \
#     --with-openssl-dir=$OPENSSL_HOME \
#     CFLAGS="${QN_CFLAGS}" \
#     CPPFLAGS="${QN_CFLAGS}" \
#     CXXFLAGS="${QN_CFLAGS}" \
#     --enable-samples

#make -j3
#make install
#####################################               <<< 编译samples
##############################################################################################################################
echo "******************************************************************************************************"
echo "***************************************END BUILD SAMPLES********************************************"
echo "******************************************************************************************************"
