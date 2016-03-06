#ifndef __OPENGLPANZOOM_H__
#define __OPENGLPANZOOM_H__

class OpenGLPanZoom
{
public:
    OpenGLPanZoom();

    void SetMouse(float x, float y); // Call this everytime the mouse moves
    void SetImageWidth(int width, int height); // Used to centre the image

    void Move(); // call this when you want to move the image
    void ZoomIn();
    void ZoomOut();
    void Centre();
    void Update(); // call this in the rendering section at the top, replaces glLoadIdentity() bit

    // Useful feedback values
    void GetPos(float &x, float &y); // get world position
    float GetScale();

private:
    void UpdateZoom();
    void GetWorldPos(float screen_x, float screen_y, float &world_x, float &world_y);

private:
    int m_image_width, m_image_height;

    // mouse history
    float m_cur_mouse_x, m_cur_mouse_y;
    float m_last_mouse_x, m_last_mouse_y;

    float m_zoom_x, m_zoom_y; // where the zoom takes place, screen co-ordinate
    float m_image_x, m_image_y;  // where abouts on the image is the mouse currently on
    float m_tx, m_ty; // translation
    int m_zoom_level;
    float m_scale;
};

#endif
