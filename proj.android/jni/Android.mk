LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := 	hellocpp/main.cpp \
                   	../../Classes//AppDelegate.cpp \
					../../Classes//LayoutUtil/LayoutUtil.cpp \
					../../Classes//ResourceName/ResourceName.cpp \
					../../Classes//UI/ClassicGameScene.cpp \
					../../Classes//UI/CoverScene.cpp \
					../../Classes//UI/GridSprite.cpp \
					../../Classes//UI/LevelGameScene.cpp \
					../../Classes//UI/MusicBtn.cpp \
					../../Classes//UI/ReMainWaterNumSprite.cpp \
					../../Classes//UI/SelectLevelScene.cpp \
					../../Classes//UI/WaterSprite.cpp \
					../../Classes//UI/dialog/ClassicResultDialog.cpp \
					../../Classes//Utils/Constants.cpp \
					../../Classes//Utils/LevelUtil.cpp \
					../../Classes//Utils/UIUtil.cpp \
					../../Classes//Utils/AdUtil.cpp \
					../../Classes//Widgets/MenuDispatch.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/LayoutUtil \
					$(LOCAL_PATH)/../../Classes/ResourceName \
					$(LOCAL_PATH)/../../Classes/UI \
					$(LOCAL_PATH)/../../Classes/UI/dialog \
					$(LOCAL_PATH)/../../Classes/Utils \
					$(LOCAL_PATH)/../../Classes/Widgets

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static \
								PluginProtocolStatic
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)

$(call import-module,protocols/android)
