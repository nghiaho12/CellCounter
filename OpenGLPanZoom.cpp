#include <cmath>
#include <cstdio>

#ifdef _WIN32
#include <windows.h> // This needs to preceed the GL includes
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "OpenGLPanZoom.h"

OpenGLPanZoom::OpenGLPanZoom()
{
    m_tx = 0.0f;
    m_ty = 0.0f;
    m_scale = 1.0f;
    m_zoom_level = 0;
    m_image_x = 0.0f;
    m_image_y = 0.0f;
    m_zoom_x = 0.0f;
    m_zoom_y = 0.0f;
}

void OpenGLPanZoom::SetMouse(float x, float y)
{
    m_last_mouse_x = m_cur_mouse_x;
    m_last_mouse_y = m_cur_mouse_y;

    m_cur_mouse_x = x;
    m_cur_mouse_y = y;
}

void OpenGLPanZoom::SetImageWidth(int width, int height)
{
    m_image_width = width;
    m_image_height = height;
}

void OpenGLPanZoom::GetWorldPos(float screen_x, float screen_y, float &world_x, float &world_y)
{
    GLdouble model[16];
    GLdouble proj[16];
    GLint view[4];
    GLdouble x, y, z;

    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, view);

    gluUnProject((GLdouble)screen_x, (GLdouble)screen_y, 0.0,  model, proj, view, &x, &y, &z);

    world_x = (float)x;
    world_y = (float)y;
}

void OpenGLPanZoom::UpdateZoom()
{
    GetWorldPos(m_cur_mouse_x, m_cur_mouse_y,m_image_x, m_image_y);

    m_zoom_x = m_cur_mouse_x;
    m_zoom_y = m_cur_mouse_y;

    // We don't need the extra translation from mouse moving anymore, taken care of by m_zoom_x/y
    m_tx = 0;
    m_ty = 0;
}

void OpenGLPanZoom::Move()
{
    float dx = m_cur_mouse_x - m_last_mouse_x;
    float dy = m_cur_mouse_y - m_last_mouse_y;

    m_tx += dx;
    m_ty += dy;
}

void OpenGLPanZoom::ZoomIn()
{
    m_zoom_level++;
    m_scale = powf(1.5f, (float)m_zoom_level);
    UpdateZoom();
}

void OpenGLPanZoom::ZoomOut()
{
    m_zoom_level--;
    m_scale = powf(1.5f, (float)m_zoom_level);
    UpdateZoom();
}

void OpenGLPanZoom::Centre()
{
    GLint view[4];
    glGetIntegerv(GL_VIEWPORT, view);

    int view_width = view[2];
    int view_height = view[3];

    if(view_width < view_height) {
        m_scale = (float)view_width/m_image_width;
    }
    else {
        m_scale = (float)view_height/m_image_height;
    }

    // Round to the nearest zoom level
    m_zoom_level = (int)(logf(m_scale)/logf(1.5f) + 0.5f);

    m_zoom_x = view[2] * 0.5f;
    m_zoom_y = view[3] * 0.5f;

    m_image_x = m_image_width * 0.5f;
    m_image_y = m_image_height * 0.5f;

    m_tx = 0;
    m_ty = 0;
}

void OpenGLPanZoom::Update()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(m_tx, m_ty, 0.0f);

    glTranslatef(m_zoom_x, m_zoom_y, 0.0f);
    glScalef(m_scale, m_scale, 1.0f);
    glTranslatef(-m_image_x, -m_image_y, 0.0f);
}

void OpenGLPanZoom::GetPos(float &x, float &y)
{
    GetWorldPos(m_cur_mouse_x, m_cur_mouse_y, x, y);
}

float OpenGLPanZoom::GetScale()
{
    return m_scale;
}
