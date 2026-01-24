#include <stdio.h>
#include <stdlib.h>
#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <tchar.h>
#include <Windows.h>

#define WINDOW_CLASS_NAME _T("Window Class")
#define APPLICATION_NAME _T("Test app")

EGLContext eglContext = NULL;
EGLSurface eglSurface = NULL;
EGLDisplay eglDisplay = NULL;

LRESULT CALLBACK HandleWindowMessages(HWND nativeWindow, UINT message, WPARAM windowParameters, LPARAM longWindowParameters)
{
    switch (message) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(nativeWindow, message, windowParameters, longWindowParameters);
    }
    return 0;
}

int CreateWindowAndDisplay(HINSTANCE applicationInstance, HWND* nativeWindow, HDC* deviceContext, int winW, int winH)
{
    // Describe the native window in a window class structure
    WNDCLASS nativeWindowDescription;
    nativeWindowDescription.style = CS_HREDRAW | CS_VREDRAW;
    nativeWindowDescription.lpfnWndProc = HandleWindowMessages;
    nativeWindowDescription.hInstance = applicationInstance;
    nativeWindowDescription.cbClsExtra = 0;
    nativeWindowDescription.cbWndExtra = 0;
    nativeWindowDescription.hIcon = 0;
    nativeWindowDescription.hCursor = 0;
    nativeWindowDescription.lpszMenuName = 0;
    nativeWindowDescription.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    nativeWindowDescription.lpszClassName = WINDOW_CLASS_NAME;

    // Register the windows class with the OS.
    ATOM registerClass = RegisterClass(&nativeWindowDescription);

    // Create the window from the available information
    *nativeWindow = CreateWindow(WINDOW_CLASS_NAME, APPLICATION_NAME, WS_VISIBLE | WS_SYSMENU,
                                 0, 0, winW, winH, NULL, NULL, applicationInstance, NULL);

    // Get the associated device context from the window
    *deviceContext = GetDC(*nativeWindow);
    return 0;
}

static void BindWindowAndEGL(HDC nativeDisplay, HWND* nativeWindow)
{
    EGLConfig eglConfig = NULL;

    eglDisplay = eglGetDisplay((EGLNativeDisplayType)nativeDisplay);

    EGLint eglMajorVersion, eglMinorVersion;
    eglInitialize(eglDisplay, &eglMajorVersion, &eglMinorVersion);

    const EGLint configurationAttributes[] =
    {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 16,
        EGL_SAMPLE_BUFFERS, 1,
        EGL_SAMPLES, 8,
        EGL_NONE
    };

    EGLint configsReturned;
    eglChooseConfig(eglDisplay, configurationAttributes, &eglConfig, 1, &configsReturned);

    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)*nativeWindow, NULL);

    EGLint contextAttributes[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    eglBindAPI(EGL_OPENGL_ES_API);
    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttributes);
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
}

GLuint LoadShader(EGLenum type, const char *shaderSrc)
{
    GLuint shader = 0;
    GLint compiled;
    // Create the shader object
    shader = glCreateShader(type);
    if (!shader) {
        return 0;
    }
    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, 0);
    // Compile the shader
    glCompileShader(shader);
    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            fprintf(stdout, "%s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
static int initGL(void)
{
    char vShaderStr[] =
        "attribute vec4 vPosition;                \n"
        "void main()                              \n"
        "{                                        \n"
        "   gl_Position = vPosition;              \n"
        "}                                        \n";
    char fShaderStr[] =
        "precision mediump float;                        \n"
        "void main()                                     \n"
        "{                                               \n"
        "   gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
        "}                                               \n";
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;
    // Load the vertex/fragment shaders
    vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
    fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);
    // Create the program object
    programObject = glCreateProgram();
    if (programObject == 0) {
        return 0;
    }
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    // Link the program
    glLinkProgram(programObject);
    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            fprintf(stdout, "[glError] %s\n", infoLog);
            free(infoLog);
        }
        glDeleteProgram(programObject);
        return EXIT_FAILURE;
    }
    // Store the program object
    glUseProgram(programObject);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // We don't need the shaders anymore
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    return EXIT_SUCCESS;
}
void render()
{
    EGLint surface_width;
    EGLint surface_height;
    GLfloat vTriangle[] = {
        -0.2f, -0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
        0.0f, 0.2f, 0.0f
    };
    eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &surface_width);
    eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &surface_height);
    // Set the viewport
    glViewport(0, 0, surface_width, surface_height);
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vTriangle);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int rc = 0;
    HWND nativeWindow = NULL;
    HDC deviceContext = NULL;

    int winW = 1280, winH = 720;
    CreateWindowAndDisplay(hInstance, &nativeWindow, &deviceContext, winW, winH);
    BindWindowAndEGL(deviceContext, &nativeWindow);
    initGL();

    while (1) {
        // Draw
        render();
        rc = eglSwapBuffers(eglDisplay, eglSurface);
        if (rc != EGL_TRUE) {
            fprintf(stderr, "eglSwapBuffers failed\n");
            break;
        }
    }
    // Clean up EGL related objects
    eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(eglDisplay, eglSurface);
    eglDestroyContext(eglDisplay, eglContext);
    eglTerminate(eglDisplay);
    eglReleaseThread();

    return 0;
}