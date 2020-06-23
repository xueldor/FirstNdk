生成android上面的可执行程序：
Android.mk里面用include $(BUILD_EXECUTABLE)生成可执行文件。
build\intermediates\ndkBuild\debug\obj\local\目录找到对应的平台，比如我的手机是armeabi-v7a。
将可执行文件push到/data.
chmod a+x 赋予执行权限。
运行文件。