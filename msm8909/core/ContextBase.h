/* Copyright (c) 2011-2016, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef __LOC_CONTEXT_BASE__
#define __LOC_CONTEXT_BASE__

#include <stdbool.h>
#include <ctype.h>
#include <MsgTask.h>
#include <LocApiBase.h>
#include <LBSProxyBase.h>

namespace loc_core {

class LocAdapterBase;

class ContextBase {
    static LBSProxyBase* getLBSProxy(const char* libName);
    LocApiBase* createLocApi(LOC_API_ADAPTER_EVENT_MASK_T excludedMask);
protected:
    const LBSProxyBase* mLBSProxy;
    const MsgTask* mMsgTask;
    LocApiBase* mLocApi;
    LocApiProxyBase *mLocApiProxy;
public:
    ContextBase(const MsgTask* msgTask,
                LOC_API_ADAPTER_EVENT_MASK_T exMask,
                const char* libName);
    inline virtual ~ContextBase() { delete mLocApi; delete mLBSProxy; }

    inline const MsgTask* getMsgTask() { return mMsgTask; }
    inline LocApiBase* getLocApi() { return mLocApi; }
    inline LocApiProxyBase* getLocApiProxy() { return mLocApiProxy; }
    inline bool hasAgpsExtendedCapabilities() { return mLBSProxy->hasAgpsExtendedCapabilities(); }
    inline bool hasCPIExtendedCapabilities() { return mLBSProxy->hasCPIExtendedCapabilities(); }
    inline bool hasNativeXtraClient() { return mLBSProxy->hasNativeXtraClient(); }
    inline void modemPowerVote(bool power) const { return mLBSProxy->modemPowerVote(power); }
    inline void requestUlp(LocAdapterBase* adapter,
                           unsigned long capabilities) {
        mLBSProxy->requestUlp(adapter, capabilities);
    }
    inline void sendMsg(const LocMsg *msg) { getMsgTask()->sendMsg(msg); }
};

} // namespace loc_core

#endif //__LOC_CONTEXT_BASE__
