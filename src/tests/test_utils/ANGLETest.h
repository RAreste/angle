//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ANGLETest:
//   Implementation of common ANGLE testing fixture.
//

#ifndef ANGLE_TESTS_ANGLE_TEST_H_
#define ANGLE_TESTS_ANGLE_TEST_H_

#include <gtest/gtest.h>
#include <algorithm>
#include <array>

#include "angle_gl.h"
#include "angle_test_configs.h"
#include "common/angleutils.h"
#include "shader_utils.h"
#include "Vector.h"

#define EXPECT_GL_ERROR(err) EXPECT_EQ(static_cast<GLenum>(err), glGetError())
#define EXPECT_GL_NO_ERROR() EXPECT_EQ(static_cast<GLenum>(GL_NO_ERROR), glGetError())

#define ASSERT_GL_ERROR(err) ASSERT_EQ(static_cast<GLenum>(err), glGetError())
#define ASSERT_GL_NO_ERROR() ASSERT_EQ(static_cast<GLenum>(GL_NO_ERROR), glGetError())

#define EXPECT_EGL_ERROR(err) EXPECT_EQ((err), eglGetError())
#define EXPECT_EGL_SUCCESS() EXPECT_EGL_ERROR(EGL_SUCCESS)

// EGLBoolean is |unsigned int| but EGL_TRUE is 0, not 0u.
#define ASSERT_EGL_TRUE(a) ASSERT_EQ(static_cast<EGLBoolean>(EGL_TRUE), (a))
#define ASSERT_EGL_FALSE(a) ASSERT_EQ(static_cast<EGLBoolean>(EGL_FALSE), (a))
#define EXPECT_EGL_TRUE(a) EXPECT_EQ(static_cast<EGLBoolean>(EGL_TRUE), (a))
#define EXPECT_EGL_FALSE(a) EXPECT_EQ(static_cast<EGLBoolean>(EGL_FALSE), (a))

#define ASSERT_EGL_ERROR(err) ASSERT_EQ((err), eglGetError())
#define ASSERT_EGL_SUCCESS() ASSERT_EGL_ERROR(EGL_SUCCESS)

#define ASSERT_GLENUM_EQ(expected, actual) ASSERT_EQ(static_cast<GLenum>(expected), static_cast<GLenum>(actual))
#define EXPECT_GLENUM_EQ(expected, actual) EXPECT_EQ(static_cast<GLenum>(expected), static_cast<GLenum>(actual))

namespace angle
{
struct GLColor
{
    GLColor();
    GLColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
    GLColor(GLuint colorValue);

    Vector4 toNormalizedVector() const;

    GLubyte R, G, B, A;

    static const GLColor red;
    static const GLColor green;
    static const GLColor blue;
    static const GLColor cyan;
    static const GLColor black;
};

// Useful to cast any type to GLubyte.
template <typename TR, typename TG, typename TB, typename TA>
GLColor MakeGLColor(TR r, TG g, TB b, TA a)
{
    return GLColor(static_cast<GLubyte>(r), static_cast<GLubyte>(g), static_cast<GLubyte>(b),
                   static_cast<GLubyte>(a));
}

bool operator==(const GLColor &a, const GLColor &b);
std::ostream &operator<<(std::ostream &ostream, const GLColor &color);
GLColor ReadColor(GLint x, GLint y);

template <typename T>
void FillWithRGBA(size_t pixelCount, T red, T green, T blue, T alpha, T *outArray)
{
    for (size_t i = 0u; i < pixelCount; ++i)
    {
        outArray[i * 4u]      = red;
        outArray[i * 4u + 1u] = green;
        outArray[i * 4u + 2u] = blue;
        outArray[i * 4u + 3u] = alpha;
    }
}

}  // namespace angle

#define EXPECT_PIXEL_EQ(x, y, r, g, b, a) \
    EXPECT_EQ(angle::MakeGLColor(r, g, b, a), angle::ReadColor(x, y))

#define EXPECT_PIXEL_ALPHA_EQ(x, y, a) EXPECT_EQ(a, angle::ReadColor(x, y).A)

#define EXPECT_PIXEL_COLOR_EQ(x, y, angleColor) EXPECT_EQ(angleColor, angle::ReadColor(x, y))

// TODO(jmadill): Figure out how we can use GLColor's nice printing with EXPECT_NEAR.
#define EXPECT_PIXEL_NEAR(x, y, r, g, b, a, abs_error) \
{ \
    GLubyte pixel[4]; \
    glReadPixels((x), (y), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel); \
    EXPECT_GL_NO_ERROR(); \
    EXPECT_NEAR((r), pixel[0], abs_error); \
    EXPECT_NEAR((g), pixel[1], abs_error); \
    EXPECT_NEAR((b), pixel[2], abs_error); \
    EXPECT_NEAR((a), pixel[3], abs_error); \
}

class EGLWindow;
class OSWindow;

class ANGLETest : public ::testing::TestWithParam<angle::PlatformParameters>
{
  protected:
    ANGLETest();
    ~ANGLETest();

  public:
    static bool InitTestWindow();
    static bool DestroyTestWindow();
    static void SetWindowVisible(bool isVisible);
    static bool eglDisplayExtensionEnabled(EGLDisplay display, const std::string &extName);

  protected:
    virtual void SetUp();
    virtual void TearDown();

    virtual void swapBuffers();

    void setupQuadVertexBuffer(GLfloat positionAttribZ, GLfloat positionAttribXYScale);

    void drawQuad(GLuint program, const std::string &positionAttribName, GLfloat positionAttribZ);
    void drawQuad(GLuint program,
                  const std::string &positionAttribName,
                  GLfloat positionAttribZ,
                  GLfloat positionAttribXYScale);
    void drawQuad(GLuint program,
                  const std::string &positionAttribName,
                  GLfloat positionAttribZ,
                  GLfloat positionAttribXYScale,
                  bool useVertexBuffer);
    static std::array<Vector3, 6> GetQuadVertices();
    void drawIndexedQuad(GLuint program,
                         const std::string &positionAttribName,
                         GLfloat positionAttribZ);
    void drawIndexedQuad(GLuint program,
                         const std::string &positionAttribName,
                         GLfloat positionAttribZ,
                         GLfloat positionAttribXYScale);

    static GLuint compileShader(GLenum type, const std::string &source);
    static bool extensionEnabled(const std::string &extName);
    static bool eglClientExtensionEnabled(const std::string &extName);

    void setWindowWidth(int width);
    void setWindowHeight(int height);
    void setConfigRedBits(int bits);
    void setConfigGreenBits(int bits);
    void setConfigBlueBits(int bits);
    void setConfigAlphaBits(int bits);
    void setConfigDepthBits(int bits);
    void setConfigStencilBits(int bits);
    void setMultisampleEnabled(bool enabled);
    void setDebugEnabled(bool enabled);
    void setNoErrorEnabled(bool enabled);

    int getClientVersion() const;

    EGLWindow *getEGLWindow() const;
    int getWindowWidth() const;
    int getWindowHeight() const;
    bool isMultisampleEnabled() const;

    bool isOpenGL() const;
    EGLint getPlatformRenderer() const;

    void ignoreD3D11SDKLayersWarnings();

  private:
    bool createEGLContext();
    bool destroyEGLContext();

    void checkD3D11SDKLayersMessages();

    EGLWindow *mEGLWindow;
    int mWidth;
    int mHeight;

    bool mIgnoreD3D11SDKLayersWarnings;

    // Used for indexed quad rendering
    GLuint mQuadVertexBuffer;

    static OSWindow *mOSWindow;
};

class ANGLETestEnvironment : public testing::Environment
{
  public:
    virtual void SetUp();
    virtual void TearDown();
};

bool IsIntel();
bool IsAMD();
bool IsNVIDIA();
// Note: FL9_3 is explicitly *not* considered D3D11.
bool IsD3D11();
bool IsD3D11_FL93();
// Is a D3D9-class renderer.
bool IsD3D9();
// Is D3D9 or SM9_3 renderer.
bool IsD3DSM3();
bool IsLinux();
bool IsOSX();

#endif  // ANGLE_TESTS_ANGLE_TEST_H_
