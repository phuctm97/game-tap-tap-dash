LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/TestScene/TestMapScene.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_GameMap.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_GameMapGenerator.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_TxtGameMapGenerator.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_GameMapNode.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_FlyGameMapNode.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_ForwardGameMapNode.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_TurnLeftGameMapNode.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_TurnRightGameMapNode.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_FlyGameMapNode2.cpp \
				   ../../Classes/PlayScene/Maps/PlayScene_ForwardGameMapNodeWithRest.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
