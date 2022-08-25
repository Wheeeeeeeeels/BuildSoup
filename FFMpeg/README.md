####  Centos+FFmpeg(x264,x265,opus,aac) 问题总结

##### PKG_CONFIG的问题

* PKG_CONFIG需要链接到/usr/lib64中去
* 需要将PKG_CONFIG_PATH输出到环境中去
* 需要将265内容复制到pkgconfig中去，否则编译ffmpeg过程中会提示找不到

##### FFmpeg编译中的问题

* 提示找不到nasm,yasm,或者提示过老，需要重新安装yasm
* ffmpeg的正常编译过程应该是先 make -j4 无bug的，之后使用sudo make -j4去剔除一些权限所带来的问题
