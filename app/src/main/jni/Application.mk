APP_MODULES := JniLib
APP_ABI := all
APP_STL := c++_static #使用了C++ STL

#过去在eclipse上用较老版本的NDK调试时，使用以下配置。现在已经不需要
#APP_STL := stlport_static
#APP_CFLAGS += -Wno-error=format-security