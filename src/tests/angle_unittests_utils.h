//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// angle_unittests_utils.h:
//   Helpers for mocking and unit testing.

#ifndef TESTS_ANGLE_UNITTESTS_UTILS_H_
#define TESTS_ANGLE_UNITTESTS_UTILS_H_

#include "libANGLE/renderer/ContextImpl.h"
#include "libANGLE/renderer/EGLImplFactory.h"
#include "libANGLE/renderer/GLImplFactory.h"

namespace rx
{

// Useful when mocking a part of the GLImplFactory class
class NullFactory : public GLImplFactory
{
  public:
    NullFactory() {}

    // Shader creation
    CompilerImpl *createCompiler() override { return nullptr; }
    ShaderImpl *createShader(const gl::ShaderState &data) override { return nullptr; }
    ProgramImpl *createProgram(const gl::ProgramState &data) override { return nullptr; }

    // Framebuffer creation
    FramebufferImpl *createFramebuffer(const gl::FramebufferState &data) override
    {
        return nullptr;
    }

    // Texture creation
    TextureImpl *createTexture(GLenum target) override { return nullptr; }

    // Renderbuffer creation
    RenderbufferImpl *createRenderbuffer() override { return nullptr; }

    // Buffer creation
    BufferImpl *createBuffer() override { return nullptr; }

    // Vertex Array creation
    VertexArrayImpl *createVertexArray(const gl::VertexArrayState &data) override
    {
        return nullptr;
    }

    // Query and Fence creation
    QueryImpl *createQuery(GLenum type) override { return nullptr; }
    FenceNVImpl *createFenceNV() override { return nullptr; }
    FenceSyncImpl *createFenceSync() override { return nullptr; }

    // Transform Feedback creation
    TransformFeedbackImpl *createTransformFeedback() override { return nullptr; }

    // Sampler object creation
    SamplerImpl *createSampler() override { return nullptr; }
};

// A class with all the factory methods mocked.
class MockGLFactory : public GLImplFactory
{
  public:
    MOCK_METHOD1(createContext, ContextImpl *(const gl::ContextState &));
    MOCK_METHOD0(createCompiler, CompilerImpl *());
    MOCK_METHOD1(createShader, ShaderImpl *(const gl::ShaderState &));
    MOCK_METHOD1(createProgram, ProgramImpl *(const gl::ProgramState &));
    MOCK_METHOD1(createFramebuffer, FramebufferImpl *(const gl::FramebufferState &));
    MOCK_METHOD1(createTexture, TextureImpl *(GLenum target));
    MOCK_METHOD0(createRenderbuffer, RenderbufferImpl *());
    MOCK_METHOD0(createBuffer, BufferImpl *());
    MOCK_METHOD1(createVertexArray, VertexArrayImpl *(const gl::VertexArrayState &));
    MOCK_METHOD1(createQuery, QueryImpl *(GLenum type));
    MOCK_METHOD0(createFenceNV, FenceNVImpl *());
    MOCK_METHOD0(createFenceSync, FenceSyncImpl *());
    MOCK_METHOD0(createTransformFeedback, TransformFeedbackImpl *());
    MOCK_METHOD0(createSampler, SamplerImpl *());
};

class MockEGLFactory : public EGLImplFactory
{
  public:
    MOCK_METHOD3(createWindowSurface,
                 SurfaceImpl *(const egl::Config *,
                               EGLNativeWindowType,
                               const egl::AttributeMap &));
    MOCK_METHOD2(createPbufferSurface,
                 SurfaceImpl *(const egl::Config *, const egl::AttributeMap &));
    MOCK_METHOD3(createPbufferFromClientBuffer,
                 SurfaceImpl *(const egl::Config *, EGLClientBuffer, const egl::AttributeMap &));
    MOCK_METHOD3(createPixmapSurface,
                 SurfaceImpl *(const egl::Config *, NativePixmapType, const egl::AttributeMap &));
    MOCK_METHOD3(createImage, ImageImpl *(EGLenum, egl::ImageSibling *, const egl::AttributeMap &));
    MOCK_METHOD3(createContext,
                 gl::Context *(const egl::Config *,
                               const gl::Context *,
                               const egl::AttributeMap &));
    MOCK_METHOD2(createStreamProducerD3DTextureNV12,
                 StreamProducerImpl *(egl::Stream::ConsumerType, const egl::AttributeMap &));
};

}  // namespace rx

#endif // TESTS_ANGLE_UNITTESTS_UTILS_H_
