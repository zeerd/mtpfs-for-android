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

LOCAL_PATH := $(call my-dir)

#=========================================================
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	androidglue/statvfs.c \
	origin/lib/buffer.c \
	origin/lib/cuse_lowlevel.c \
	origin/lib/fuse.c \
	origin/lib/fuse_kern_chan.c \
	origin/lib/fuse_loop.c \
	origin/lib/fuse_loop_mt.c \
	origin/lib/fuse_lowlevel.c \
	origin/lib/fuse_mt.c \
	origin/lib/fuse_opt.c \
	origin/lib/fuse_session.c \
	origin/lib/fuse_signals.c\
	origin/lib/helper.c \
	origin/lib/mount.c \
	origin/lib/mount_util.c 
	
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/config \
	$(LOCAL_PATH)/origin/include \
	$(LOCAL_PATH)/origin/lib \
	$(LOCAL_PATH)/origin/include/util \
	$(LOCAL_PATH)/androidglue/include \
	$(TOP)/bionic/libc/include

LOCAL_CFLAGS := -O2 -g -W -Wall \
	-D_FILE_OFFSET_BITS=64 \
	-D_REENTRANT \
	-DFUSE_USE_VERSION=26 \
    -DIGNORE_MTAB=1 \
    -D_PATH_MOUNTED=\"/etc/mtab/\" \
    -DFUSERMOUNT_DIR=\"/system/bin/\" \
    -DPTHREAD_CANCEL_ENABLE=0 \
    -DPTHREAD_CANCEL_DISABLE=1
    
LOCAL_MODULE := libfuse-origin
#LOCAL_MODULE_TAGS := eng
LOCAL_SHARED_LIBRARIES := libc libcutils libdl
include $(BUILD_SHARED_LIBRARY)

#=========================================================
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    origin/util/fusermount.c \
    origin/util/mount_util.c

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/config \
    $(LOCAL_PATH)/origin/lib \
    $(LOCAL_PATH)/origin/include

LOCAL_SHARED_LIBRARIES := libc libcutils libfuse-origin
LOCAL_STATIC_LIBRARIES := 
LOCAL_CFLAGS := \
    -DIGNORE_MTAB=1 \
    -D_PATH_MOUNTED=\"/etc/mtab/\" \

LOCAL_MODULE:= fusermount
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)


