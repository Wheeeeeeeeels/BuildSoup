####  Centos+FFmpeg(x264,x265,opus,aac) 问题总结

##### PKG_CONFIG的问题

* PKG_CONFIG需要链接到/usr/lib64中去
* 需要将PKG_CONFIG_PATH输出到环境中去
* 需要将265内容复制到pkgconfig中去，否则编译ffmpeg过程中会提示找不到

##### FFmpeg编译中的问题

* 提示找不到nasm,yasm,或者提示过老，需要重新安装yasm
* ffmpeg的正常编译过程应该是先 make -j4 无bug的，之后使用sudo make -j4去剔除一些权限所带来的问题


#### 使用方法：

```
1. 将opus复制到你需要安装的HOME_DIRECTORY的ffmpeg_sources文件下
2. 将x265.pc同样放置在HOME_DIRECTORY文件夹下
3. 启动脚本编译 bash + 执行脚本.sh
```
