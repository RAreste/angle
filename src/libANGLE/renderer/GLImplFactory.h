//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// GLImplFactory.h:
//   Factory interface for OpenGL ES Impl objects.
//

#ifndef LIBANGLE_RENDERER_GLIMPLFACTORY_H_
#define LIBANGLE_RENDERER_GLIMPLFACTORY_H_

#include "libANGLE/Framebuffer.h"
#include "libANGLE/Program.h"
#include "libANGLE/Shader.h"
#include "libANGLE/VertexArray.h"

namespace gl
{
struct ContextState;
}

namespace rx
{
class BufferImpl;
class CompilerImpl;
class ContextImpl;
class FenceNVImpl;
class FenceSyncImpl;
class FramebufferImpl;
class ProgramImpl;
class QueryImpl;
class RenderbufferImpl;
class SamplerImpl;
class ShaderImpl;
class TextureImpl;
class TransformFeedbackImpl;
class VertexArrayImpl;

class GLImplFactory : angle::NonCopyable
{
  public:
    GLImplFactory() {}
    virtual ~GLImplFactory() {}

    // Context creation
    virtual ContextImpl *createContext(const gl::ContextState &state) = 0;

    // Shader creation
    virtual CompilerImpl *createCompiler() = 0;
    virtual ShaderImpl *createShader(const gl::ShaderState &data) = 0;
    virtual ProgramImpl *createProgram(const gl::ProgramState &data) = 0;

    // Framebuffer creation
    virtual FramebufferImpl *createFramebuffer(const gl::FramebufferState &data) = 0;

    // Texture creation
    virtual TextureImpl *createTexture(GLenum target) = 0;

    // Renderbuffer creation
    virtual RenderbufferImpl *createRenderbuffer() = 0;

    // Buffer creation
    virtual BufferImpl *createBuffer() = 0;

    // Vertex Array creation
    virtual VertexArrayImpl *createVertexArray(const gl::VertexArrayState &data) = 0;

    // Query and Fence creation
    virtual QueryImpl *createQuery(GLenum type) = 0;
    virtual FenceNVImpl *createFenceNV() = 0;
    virtual FenceSyncImpl *createFenceSync() = 0;

    // Transform Feedback creation
    virtual TransformFeedbackImpl *createTransformFeedback() = 0;

    // Sampler object creation
    virtual SamplerImpl *createSampler() = 0;
};

}  // namespace rx

#endif  // LIBANGLE_RENDERER_GLIMPLFACTORY_H_
