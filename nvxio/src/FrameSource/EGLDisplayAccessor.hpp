/*
# Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef EGLDISPLAYACCESSOR_HPP
#define EGLDISPLAYACCESSOR_HPP

#include <EGL/egl.h>

#include <Private/LogUtils.hpp>

namespace nvxio
{

class EGLDisplayAccessor
{
public:
    static EGLDisplay getInstance()
    {
        static EGLDisplayAccessor instance;
        return instance.eglDisplay;
    }

private:
    EGLDisplayAccessor()
    {
        // Obtain the EGL display
        if ((eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY)
        {
            NVXIO_PRINT("EGL failed to obtain display.");
        }

        // Initialize EGL
        EGLint major, minor;
        if (!eglInitialize(eglDisplay, &major, &minor))
        {
            NVXIO_PRINT("EGL failed to initialize.");

            eglTerminate(eglDisplay);
            eglDisplay = EGL_NO_DISPLAY;
        }
        else
        {
            NVXIO_PRINT("EGL API: %d.%d", major, minor);
        }
    }

    ~EGLDisplayAccessor()
    {
        if (eglDisplay != EGL_NO_DISPLAY)
        {
            eglTerminate(eglDisplay);
            eglDisplay = EGL_NO_DISPLAY;

            NVXIO_PRINT("Terminate EGL display");
            fflush(stdout);
        }
    }

    EGLDisplay eglDisplay;
};

}

#endif // EGLDISPLAYACCESSOR_HPP
