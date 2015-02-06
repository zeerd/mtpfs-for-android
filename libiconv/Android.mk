# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This makefile builds both for host and target, and so all the
# common definitions are factored out into a separate file to
# minimize duplication between the build rules.

LOCAL_PATH:= $(call my-dir)

#libiconv.so  
include $(CLEAR_VARS)  

LOCAL_CFLAGS := \
  -Wno-multichar \
  -DAndroid \
  -Wno-missing-field-initializers \
  -Wno-sign-compare \
  -Wno-type-limits \
  
LOCAL_SRC_FILES := \
	origin/libcharset/lib/localcharset.c \
	origin/lib/iconv.c \
	origin/lib/relocatable.c  
  
LOCAL_C_INCLUDES += \
  $(LOCAL_PATH)/config \
  $(LOCAL_PATH)/include \
  $(LOCAL_PATH)/origin/include \
  $(LOCAL_PATH)/origin/libcharset \
  $(LOCAL_PATH)/origin/lib \
  $(LOCAL_PATH)/origin/libcharset/include \
  $(LOCAL_PATH)/origin/srclib  
	
LOCAL_MODULE := libiconv
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES :=
                          
include $(BUILD_SHARED_LIBRARY)
  
##test  
#include $(CLEAR_VARS)  
#LOCAL_MODULE :=genutf8  
  
#LOCAL_SRC_FILES := origin/tests/genutf8.c  
#LOCAL_C_INCLUDES += \
  #$(LOCAL_PATH)/origin/include \
  #$(LOCAL_PATH)/origin/libcharset \
  #$(LOCAL_PATH)/origin/lib \
  #$(LOCAL_PATH)/origin/libcharset/include \
  #$(LOCAL_PATH)/origin/srclib  
#LOCAL_SHARED_LIBRARIES := libiconv  
#include $(BUILD_EXECUTABLE)  
