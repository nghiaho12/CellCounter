/***************************************************************
 * Name:      CellCounterMain.h
 * Purpose:   Defines Application Frame
 * Author:    Nghia Ho (nghiaho12@yahoo.com)
 * Created:   2011-11-20
 * Copyright: Nghia Ho (http://nghiaho.com)
 * License:
 **************************************************************/

#ifndef CELLCOUNTERMAIN_H
#define CELLCOUNTERMAIN_H

#include <opencv2/opencv.hpp>

//(*Headers(CellCounterFrame)
#include <wx/glcanvas.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbmp.h>
//*)

#include "OpenGLPanZoom.h"
#include "CellCounter.h"

struct Well
{
	float x, y;
	float radius;
	int cell_count;
};

struct TileImage
{
    int width, height;
    std::vector <GLuint> tiles;
};

class CellCounterFrame: public wxFrame
{
    public:
        enum Mode {NORMAL, SELECT_WELL};
		enum View {COLOUR, THRESHOLD};

        CellCounterFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CellCounterFrame();

        void Resize();
        bool InitGL();
        void RenderScene();
        void LoadImage(const char *filename);
        void DrawCircle(float x, float y, float radius, float r, float g, float b);
        void UpdateCellCount();
        void AddCell();
		void UpdateThresholdImage();
		void UpdateResults();
		void InitialiseHistogram();
		void UpdateHistogram();
		void SwitchViews();
        void Reset();
        void CreateTileImage(cv::Mat &img, TileImage &tile_image);
        void OnHistogramClick(wxMouseEvent &event);

    public:
        static const int m_hist_width = 256;
        static const int m_hist_height = 100;
        static const int m_mouse_selector_radius = 9;
		wxGLContext *m_context;

        cv::Mat m_last_image; // bug with the Windows version of OpenCV, imread doesn't work
        cv::Mat m_input_image, m_threshold_image, m_grey_image;
        bool m_init_gl;
        GLuint m_tex[2];
        bool m_left_mouse_down;
        bool m_right_mouse_down;
        OpenGLPanZoom m_opengl_pan_zoom;
        Mode m_mode;
		View m_view;
        Well m_well; // curent selected well
        float m_cos[360], m_sin[360]; // lookup table
        CellCounter m_cell_counter;
        std::vector <cv::Point2f> m_results;
		std::vector <Well> m_wells_added;
        wxImage m_histogram_cache;

        // For low memory graphics card
        TileImage m_tile_image[2]; // color and threshold image
        int m_tile_size;

    private:

        //(*Handlers(CellCounterFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnGLCanvas1Paint(wxPaintEvent& event);
        void OnGLCanvas1Resize(wxSizeEvent& event);
        void OnMenuItemOpenSelected(wxCommandEvent& event);
        void OnGLCanvas1LeftDown(wxMouseEvent& event);
        void OnGLCanvas1LeftUp(wxMouseEvent& event);
        void OnGLCanvas1RightDown(wxMouseEvent& event);
        void OnGLCanvas1RightUp(wxMouseEvent& event);
        void OnGLCanvas1MouseMove(wxMouseEvent& event);
        void OnGLCanvas1MouseWheel(wxMouseEvent& event);
        void OnGLCanvas1LeftDClick(wxMouseEvent& event);
        void Onm_select_plate_btnClick(wxCommandEvent& event);
        void Onm_count_cells_btnClick(wxCommandEvent& event);
        void OnGLCanvas1MiddleDown(wxMouseEvent& event);
        void Onm_min_ctrlChange(wxSpinEvent& event);
        void Onm_max_ctrlChange(wxSpinEvent& event);
        void OnMinCtrlChange(wxSpinEvent& event);
        void OnMaxCtrlChange(wxSpinEvent& event);
        void OnSelectWellClick(wxCommandEvent& event);
        void OnCountCellsClick(wxCommandEvent& event);
        void OnSaveResultsClick(wxCommandEvent& event);
        void OnHowToUseSelected(wxCommandEvent& event);
        void OnClearClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(CellCounterFrame)
        static const long ID_GLCANVAS1;
        static const long ID_STATICBITMAP1;
        static const long ID_STATICTEXT1;
        static const long ID_SPINCTRL4;
        static const long ID_STATICTEXT2;
        static const long ID_SPINCTRL5;
        static const long ID_STATICTEXT3;
        static const long ID_SPINCTRL6;
        static const long ID_STATICTEXT5;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT7;
        static const long ID_SPINCTRL2;
        static const long ID_STATICTEXT8;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT4;
        static const long ID_SPINCTRL3;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL5;
        static const long ID_BUTTON4;
        static const long ID_BUTTON3;
        static const long ID_TEXTCTRL2;
        static const long ID_PANEL1;
        static const long idMenuOpem;
        static const long idMenuQuit;
        static const long idMenuHowTo;
        static const long idMenuAbout;
        //*)

        //(*Declarations(CellCounterFrame)
        wxButton* m_count_cells_btn;
        wxSpinCtrl* m_cell_radius_end_ctrl;
        wxTextCtrl* m_circleness_txt;
        wxPanel* Panel1;
        wxTextCtrl* m_output_txt;
        wxSpinCtrl* m_keep_cells_ctrl;
        wxSpinCtrl* m_max_ctrl;
        wxSpinCtrl* m_min_ctrl;
        wxButton* m_save_results_btn;
        wxStaticText* StaticText1;
        wxTextCtrl* m_total_cells_txt;
        wxStaticText* StaticText3;
        wxButton* m_select_plate_btn;
        wxMenuItem* MenuItem3;
        wxGLCanvas* GLCanvas1;
        wxStaticText* StaticText8;
        wxFileDialog* FileDialog1;
        wxStaticText* StaticText7;
        wxSpinCtrl* m_well_radius_ctrl;
        wxStaticText* StaticText4;
        wxStaticBitmap* m_histogram_bmp;
        wxBoxSizer* BoxSizer1;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxMenuItem* MenuItem4;
        wxStaticText* StaticText6;
        wxSpinCtrl* m_cell_radius_start_ctrl;
        wxButton* m_clear_btn;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // CELLCOUNTERMAIN_H
