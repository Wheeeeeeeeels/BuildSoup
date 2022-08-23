#!/bin/bash

echo "Welcome to the FFmpeg build process [With x264,x265,aac,opus] base on Centos8"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Copyright © 2022 wheels.All Rights Reserved.>>>>>>>>>>>"
echo "      ___           ___           ___           ___                         ___
     /__/\         /__/\         /  /\         /  /\                       /  /\\
    _\_ \:\        \  \:\       /  /:/_       /  /:/_                     /  /:/_
   /__/\ \:\        \__\:\     /  /:/ /\     /  /:/ /\    ___     ___    /  /:/ /\\
  _\_ \:\ \:\   ___ /  /::\   /  /:/ /:/_   /  /:/ /:/_  /__/\   /  /\  /  /:/ /::\\
 /__/\\ \\:\\ \\:\\ /__/\\  /:/\\:\\ /__/:/ /:/ /\\ /__/:/ /:/ /\\ \\  \\:\\ /  /:/ /__/:/ /:/\\:\\
 \\  \\:\\ \\:\\/:/ \\  \\:\\/:/__\\/ \\  \\:\\/:/ /:/ \\  \\:\\/:/ /:/  \\  \\:\\  /:/  \\  \\:\\/:/~/:/
  \  \:\ \::/   \  \::/       \  \::/ /:/   \  \::/ /:/    \  \:\/:/    \  \::/ /:/
   \  \:\/:/     \  \:\        \  \:\/:/     \  \:\/:/      \  \::/      \__\/ /:/
    \  \::/       \  \:\        \  \::/       \  \::/        \__\/         /__/:/
     \__\/         \__\/         \__\/         \__\/                       \__\/   "
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ALL Build Start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"


# 1. Choose the directory that you want to install.
read -p "Please input the HOME Directory that you want install("/[INPUT]"> " HOME_DIRECTORY
echo $HOME_DIRECTORY
cd $HOME_DIRECTORY
printf "The Current DIRECTORY is> "
pwd
printf "\n"

# 2. Create the directory to install

# ffmpeg_source: include all the souce code about the ffmpeg
if [ ! -d "/ffmpeg_sources/" ];then
mkdir ffmpeg_sources
else echo "The Folder already exists"
fi

# ffmpeg_build: Use to generate files and libraries
if [ ! -d "/ffmpeg_build/" ];then
mkdir ffmpeg_build
else echo "The Folder already exists"
fi
# ffmpeg_bin: Used to generated binary files, including ffmpeg, ffprobe, x264, x265
if [ ! -d "/bin/" ];then
mkdir bin
else echo "The Folder already exists"
fi

# Show All the Sub-directory
ls -l

# TODO: Compare the sub directory and the number of the directory

echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>1. The Directory Create Success.>>>>>>>>>>>>>>>>>>>>>>>>"


# 3. Modify, Change the mirror source about the yum

sudo sed -i -e "s|mirrorlist=|#mirrorlist=|g" /etc/yum.repos.d/CentOS-*
sudo sed -i -e "s|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g" /etc/yum.repos.d/CentOS-*

# 4. Install the base dependency
sudo yum -y install autoconf automake bzip2 bzip2-devel cmake freetype-devel gcc gcc-c++ git libtool make mercurial pkgconfig nasm zlib-devel

echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>2. The Base Dependency Success.>>>>>>>>>>>>>>>>>>>>>>>>>"

# 5. Add the nasm Assembler and accelerates the build
echo -e "\033[5;34m-----------------------------INSTALL NASM--------------------------------------------\033[0m"
if [ $(pwd) != $HOME_DIRECTORY/ffmpeg_sources ];then
cd $HOME_DIRECTORY/ffmpeg_sources
curl -O -L https://www.nasm.us/pub/nasm/releasebuilds/2.15.05/nasm-2.15.05.tar.bz2
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>3.1 The nasm download Success.>>>>>>>>>>>>>>>>>>>>>>>>>>"

tar xjvf nasm-2.15.05.tar.bz2
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>3.2 The nasm decompression Success.>>>>>>>>>>>>>>>>>>>>>"

cd nasm-2.15.05
sudo bash autogen.sh
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>3.3 The nasm build start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
./configure --prefix="$HOME_DIRECTORY/ffmpeg_build" --bindir="$HOME_DIRECTORY/bin"

sudo make -j4
sudo make install

echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>3.4 The nasm build finish.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
fi
echo "-------------------------------------------------------------------------------------"


# 6. Add the yasm: Use to support compilation optimization
echo -e "\033[5;34m-----------------------------INSTALL YASM--------------------------------------------\033[0m"
if [ $(pwd) != $HOME_DIRECTORY/ffmpeg_sources ];then
cd $HOME_DIRECTORY/ffmpeg_sources
curl -O -L https://www.tortall.net/projects/yasm/releases/yasm-1.3.0.tar.gz
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>4.1 The yasm download Success.>>>>>>>>>>>>>>>>>>>>>>>>>>"
tar xzvf yasm-1.3.0.tar.gz
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>4.2 The yasm decompression Success.>>>>>>>>>>>>>>>>>>>>>"
cd yasm-1.3.0
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>4.3 The yasm build start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
./configure --prefix="$HOME_DIRECTORY/ffmpeg_build" --bindir="$HOME_DIRECTORY/bin"
sudo make -j4
sudo make install
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>4.4 The yasm build finish.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
fi
echo "-------------------------------------------------------------------------------------"


# 7. Add pkg-config
echo -e "\033[5;34m-----------------------------INSTALL PKG CONFIG--------------------------------------\033[0m"
if [ $(pwd) != $HOME_DIRECTORY/ffmpeg_sources ];then
cd $HOME_DIRECTORY/ffmpeg_sources
curl -O -L https://pkg-config.freedesktop.org/releases/pkg-config-0.29.2.tar.gz
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>5.1 The pkg-config download Success.>>>>>>>>>>>>>>>>>>>>"
tar xzvf pkg-config-0.29.2.tar.gz
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>5.2 The pkg-config decompression Success.>>>>>>>>>>>>>>>"
cd pkg-config-0.29.2
./configure --with-internal-glib
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>5.3 The pkg-config build start>>>>>>>>>>>>>>>>>>>>>>>>>>"
sudo make -j4
sudo make install
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>5.4 The pkg-config build finish.>>>>>>>>>>>>>>>>>>>>>>>>"
fi
echo "-------------------------------------------------------------------------------------"

# install the x264.pc
#sudo touch $HOME_DIRECTORY/ffmpeg_build/lib/pkgconfig/x264.pc

#echo "prefix=$HOME_DIRECTORY/ffmpeg_build
#exec_prefix=${prefix}
#libdir=${exec_prefix}/lib
#includedir=${prefix}/include
#Name: x264
#Description: H.264 (MPEG AVC) encoder library
#Version: 0.164.x
#Libs: -L${exec_prefix}/lib -lx264 -lpthread -lm -ldl
#Libs.private:
#Cflags: -I${prefix}/include" > $HOME_DIRECTORY/ffmpeg_build/lib/pkgconfig/x264.pc
# Test the x264 install process
#cat $HOME_DIRECTORY/ffmpeg_build/lib/pkgconfig/x264.pc
#echo "-----------------------------X264.PC CREATE SUCCESS----------------------------------"
# 8. Add x264
echo -e "\033[5;33m-----------------------------INSTALL X264--------------------------------------------\033[0m"
if [ $(pwd) != $HOME_DIRECTORY/ffmpeg_sources ];then
cd $HOME_DIRECTORY/ffmpeg_sources
git clone --depth 1 https://code.videolan.org/videolan/x264.git
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>7.1 The x264 download Success.>>>>>>>>>>>>>>>>>>>>"
cd x264
PKG_CONFIG_PATH="$HOME_DIRECTORY/ffmpeg_build/lib/pkgconfig" && \
./configure --prefix="$HOME_DIRECTORY/ffmpeg_build" --bindir="$HOME_DIRECTORY/bin" --enable-static --disable-asm
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>7.2 The x264 build start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
sudo make -j4
sudo make install
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>7.3 The x264 build finish.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
fi
echo "-------------------------------------------------------------------------------------"

echo -e "\033[5;34m-----------------------------INSTALL X265--------------------------------------------\033[0m"

if [ $(pwd) != $HOME_DIRECTORY/ffmpeg_sources ];then
cd $HOME_DIRECTORY/ffmpeg_sources
git clone https://bitbucket.org/multicoreware/x265_git --depth 1
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>6.1 The x265 download Success.>>>>>>>>>>>>>>>>>>>>>>>>>>"
cd ./x265_git/build/linux
sudo cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX="$HOME_DIRECTORY/ffmpeg_build" -DENABLE_SHARED:bool=off ../../source
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>6.2 The x265 build start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
sudo make -j4
sudo make install
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>6.3 The x265 build finish.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
fi
echo "-------------------------------------------------------------------------------------"
# install the x265.pc
cd $HOME_DIRECTORY/ffmpeg_build/lib/pkgconfig/
sudo touch x265.pc
echo "prefix=$HOME_DIRECTORY/ffmpeg_build
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

Name: x265
Description: H.265/HEVC encoder library
Version: 3.5
Libs: -L${libdir} -lx265
Libs.private: -lstdc++ -lm -ldl -lpthread
Cflags: -I${includedir}" > x265.pc
# Test the x265 install process
cat x265.pc
echo "-----------------------------X265.PC CREATE SUCCESS---------------------------------"




echo -e "\033[5;34m-----------------------------INSTALL AAC--------------------------------------------\033[0m"
if [ $(pwd) != $HOME_DIRECTORY/ffmpeg_sources ];then
cd $HOME_DIRECTORY/ffmpeg_sources
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>7.1 The AAC download Success.>>>>>>>>>>>>>>>>>>>>>>>>>>"
git clone --depth 1 https://github.com/mstorsjo/fdk-aac
cd fdk-aac
# Fast Download Method
# wget https://downloads.sourceforge.net/opencore-amr/fdk-aac-2.0.1.tar.gz
# tar xzvf fdk-aac-2.0.1.tar.gz
# cd fdk-aac-2.0.1
autoreconf -fiv
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>7.2 The AAC build start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
./configure --prefix="$HOME_DIRECTORY/ffmpeg_build" --disable-shared
sudo make -j4
sudo make install
fi
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>7.3 The AAC build finish.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"

#echo -e "\033[5;34m-----------------------------INSTALL OPUS-------------------------------------------\033[0m"
#if [ $(pwd) != $HOME_DIRECTORY/ffmpeg_sources ];then
#cd $HOME_DIRECTORY/ffmpeg_sources
# curl -O -L https://archive.mozilla.org/pub/opus/opus-1.3.1.tar.gz
#echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>8.1 The OPUS download Success.>>>>>>>>>>>>>>>>>>>>>>>>>>"
#tar xzvf opus-1.3.1.tar.gz
#cd opus-1.3.1
#echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>8.2 The OPUS build start>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
#./configure --prefix="$HOME_DIRECTORY/ffmpeg_build" --disable-shared
#sudo make -j4
#sudo make install
#echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>8.3 The OPUS build finish.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
#fi

echo -e "\033[5;34m-----------------------------INSTALL FFmpeg------------------------------------------\033[0m"
if [ $(pwd) != $HOME_DIRECTORY/ffmpeg_sources ];then
cd $HOME_DIRECTORY/ffmpeg_sources
# Now the version of the FFmpeg is 5.1
curl -O -L https://ffmpeg.org/releases/ffmpeg-snapshot.tar.bz2
tar xjvf ffmpeg-snapshot.tar.bz2
cd ffmpeg
PATH="$HOME_DIRECTORY/bin:$PATH" PKG_CONFIG_PATH="$HOME_DIRECTORY/ffmpeg_build/lib/pkgconfig" ./configure \
  --prefix="$HOME_DIRECTORY/ffmpeg_build" \
  --pkg-config-flags="--static" \
  --extra-cflags="-I$HOME_DIRECTORY/ffmpeg_build/include" \
  --extra-ldflags="-L$HOME_DIRECTORY/ffmpeg_build/lib" \
  --extra-libs=-lpthread \
  --extra-libs=-lm \
  --bindir="$HOME_DIRECTORY/bin" \
  --enable-gpl \
  --enable-libfdk_aac \
 # --enable-libopus \
  --enable-libx264 \
  --enable-libx265 \
  --enable-nonfree
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>9.1 The Path Set Success.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
sudo make -j4
sudo make install
ffmpeg -version
echo  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>9.2 The FFmpeg install Success.>>>>>>>>>>>>>>>>>>>>>>>>>"
hash -d ffmpeg
echo -e "\033[5;34m>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ALL Build Finish>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m"
echo "


███████╗███████╗███╗   ███╗██████╗ ███████╗ ██████╗
██╔════╝██╔════╝████╗ ████║██╔══██╗██╔════╝██╔════╝
█████╗  █████╗  ██╔████╔██║██████╔╝█████╗  ██║  ███╗
██╔══╝  ██╔══╝  ██║╚██╔╝██║██╔═══╝ ██╔══╝  ██║   ██║
██║     ██║     ██║ ╚═╝ ██║██║     ███████╗╚██████╔╝
╚═╝     ╚═╝     ╚═╝     ╚═╝╚═╝     ╚══════╝ ╚═════╝
"
fi
