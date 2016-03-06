/***************************************************************
 * Name:      CellCounterMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Nghia Ho (nghiaho12@yahoo.com)
 * Created:   2011-11-20
 * Copyright: Nghia Ho (http://nghiaho.com)
 * License:
 **************************************************************/

#include "CellCounterMain.h"
#include <wx/msgdlg.h>
#include <wx/icon.h>

//(*InternalHeaders(CellCounterFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

#include <vector>
#include <string>
#include <sstream>
//#include <boost/algorithm/string.hpp>
#include <GL/glu.h>
#include <opencv2/opencv.hpp>

#include "Defines.h"
#include "icon.xpm"

using namespace std;

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    wxbuild << _T("\n\n");
    wxbuild << _T("CellCounter by Nghia Ho\n");
    char str[128];
    sprintf(str, "Version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_SUB);
    wxbuild << wxString::FromAscii(str) << _T("\n\n");

    wxbuild << _T("Email: nghiaho12@yahoo.com\n");
    wxbuild << _T("Website: http://nghiaho.com\n");

    return wxbuild;
}

//(*IdInit(CellCounterFrame)
const long CellCounterFrame::ID_GLCANVAS1 = wxNewId();
const long CellCounterFrame::ID_STATICBITMAP1 = wxNewId();
const long CellCounterFrame::ID_STATICTEXT1 = wxNewId();
const long CellCounterFrame::ID_SPINCTRL4 = wxNewId();
const long CellCounterFrame::ID_STATICTEXT2 = wxNewId();
const long CellCounterFrame::ID_SPINCTRL5 = wxNewId();
const long CellCounterFrame::ID_STATICTEXT3 = wxNewId();
const long CellCounterFrame::ID_SPINCTRL6 = wxNewId();
const long CellCounterFrame::ID_STATICTEXT5 = wxNewId();
const long CellCounterFrame::ID_SPINCTRL1 = wxNewId();
const long CellCounterFrame::ID_STATICTEXT7 = wxNewId();
const long CellCounterFrame::ID_SPINCTRL2 = wxNewId();
const long CellCounterFrame::ID_STATICTEXT8 = wxNewId();
const long CellCounterFrame::ID_TEXTCTRL1 = wxNewId();
const long CellCounterFrame::ID_STATICTEXT4 = wxNewId();
const long CellCounterFrame::ID_SPINCTRL3 = wxNewId();
const long CellCounterFrame::ID_BUTTON1 = wxNewId();
const long CellCounterFrame::ID_BUTTON2 = wxNewId();
const long CellCounterFrame::ID_STATICTEXT6 = wxNewId();
const long CellCounterFrame::ID_TEXTCTRL5 = wxNewId();
const long CellCounterFrame::ID_BUTTON4 = wxNewId();
const long CellCounterFrame::ID_BUTTON3 = wxNewId();
const long CellCounterFrame::ID_TEXTCTRL2 = wxNewId();
const long CellCounterFrame::ID_PANEL1 = wxNewId();
const long CellCounterFrame::idMenuOpem = wxNewId();
const long CellCounterFrame::idMenuQuit = wxNewId();
const long CellCounterFrame::idMenuHowTo = wxNewId();
const long CellCounterFrame::idMenuAbout = wxNewId();
//*)

BEGIN_EVENT_TABLE(CellCounterFrame,wxFrame)
    //(*EventTable(CellCounterFrame)
    //*)
END_EVENT_TABLE()

CellCounterFrame::CellCounterFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(CellCounterFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer4;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("CellCounter by Nghia Ho"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(104,88), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    GLCanvas1 = new wxGLCanvas(Panel1, ID_GLCANVAS1, NULL);//, 0, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
    GLCanvas1->SetForegroundColour(wxColour(0,49,255));
    GLCanvas1->SetBackgroundColour(wxColour(0,84,255));
    BoxSizer1->Add(GLCanvas1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    m_histogram_bmp = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
    m_histogram_bmp->SetMaxSize(wxSize(256,100));
    m_histogram_bmp->SetToolTip(_("Histogram for greyscale image.\nUse the left and right mouse click to adjust the thresholds."));
    BoxSizer2->Add(m_histogram_bmp, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1 = new wxFlexGridSizer(10, 2, 0, 0);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Well radius"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    m_well_radius_ctrl = new wxSpinCtrl(Panel1, ID_SPINCTRL4, _T("195"), wxDefaultPosition, wxDefaultSize, 0, 0, 5000, 195, _T("ID_SPINCTRL4"));
    m_well_radius_ctrl->SetValue(_T("195"));
    FlexGridSizer1->Add(m_well_radius_ctrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Colony radius"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    m_cell_radius_start_ctrl = new wxSpinCtrl(Panel1, ID_SPINCTRL5, _T("1"), wxDefaultPosition, wxSize(50,21), 0, 1, 1000, 1, _T("ID_SPINCTRL5"));
    m_cell_radius_start_ctrl->SetValue(_T("1"));
    BoxSizer4->Add(m_cell_radius_start_ctrl, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("to"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_cell_radius_end_ctrl = new wxSpinCtrl(Panel1, ID_SPINCTRL6, _T("5"), wxDefaultPosition, wxSize(50,21), 0, 1, 5000, 5, _T("ID_SPINCTRL6"));
    m_cell_radius_end_ctrl->SetValue(_T("5"));
    BoxSizer4->Add(m_cell_radius_end_ctrl, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Image threshold"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText5->SetToolTip(_("Pixels that are between these values will be thresholded to white."));
    FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    m_min_ctrl = new wxSpinCtrl(Panel1, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 255, 0, _T("ID_SPINCTRL1"));
    m_min_ctrl->SetValue(_T("0"));
    BoxSizer3->Add(m_min_ctrl, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(Panel1, ID_STATICTEXT7, _("to"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer3->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_max_ctrl = new wxSpinCtrl(Panel1, ID_SPINCTRL2, _T("80"), wxDefaultPosition, wxSize(50,21), 0, 0, 255, 80, _T("ID_SPINCTRL2"));
    m_max_ctrl->SetValue(_T("80"));
    BoxSizer3->Add(m_max_ctrl, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText8 = new wxStaticText(Panel1, ID_STATICTEXT8, _("Circleness factor"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StaticText8->SetToolTip(_("Filters out colonies that aren\'t circular in shape.\nA low value eg. 2.0 will keep only very circular cells.\nGood values are between 2 and 3.\nA value higher than 5.0 will disable this check."));
    FlexGridSizer1->Add(StaticText8, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    m_circleness_txt = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("99.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer1->Add(m_circleness_txt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Keep all colonies\nless than or equal to"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText4->SetToolTip(_("All cells below or equal to this value are automatically kept.\nNo filtering will be done to them."));
    FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    m_keep_cells_ctrl = new wxSpinCtrl(Panel1, ID_SPINCTRL3, _T("5"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 5, _T("ID_SPINCTRL3"));
    m_keep_cells_ctrl->SetValue(_T("5"));
    FlexGridSizer1->Add(m_keep_cells_ctrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_select_plate_btn = new wxButton(Panel1, ID_BUTTON1, _("Select well"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer1->Add(m_select_plate_btn, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_count_cells_btn = new wxButton(Panel1, ID_BUTTON2, _("Count colonies"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer1->Add(m_count_cells_btn, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _("Total cells"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    m_total_cells_txt = new wxTextCtrl(Panel1, ID_TEXTCTRL5, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    FlexGridSizer1->Add(m_total_cells_txt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_clear_btn = new wxButton(Panel1, ID_BUTTON4, _("Clear results"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer1->Add(m_clear_btn, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_save_results_btn = new wxButton(Panel1, ID_BUTTON3, _("Save results"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    m_save_results_btn->SetToolTip(_("First column is an incrementing number. Next two columns are the centre of the well. Last is the count results."));
    m_save_results_btn->SetHelpText(_("First column is an incrementing number. Next two columns are the centre of the well. Last is the count results."));
    FlexGridSizer1->Add(m_save_results_btn, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(FlexGridSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    m_output_txt = new wxTextCtrl(Panel1, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer2->Add(m_output_txt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer1);
    BoxSizer1->Fit(Panel1);
    BoxSizer1->SetSizeHints(Panel1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuOpem, _("Open\tCtrl-O"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem4 = new wxMenuItem(Menu2, idMenuHowTo, _("How to use"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem4);
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE|wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    GLCanvas1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1Paint,0,this);
    GLCanvas1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1LeftDown,0,this);
    GLCanvas1->Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1LeftUp,0,this);
    GLCanvas1->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1LeftDClick,0,this);
    GLCanvas1->Connect(wxEVT_MIDDLE_DOWN,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1MiddleDown,0,this);
    GLCanvas1->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1RightDown,0,this);
    GLCanvas1->Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1RightUp,0,this);
    GLCanvas1->Connect(wxEVT_MOTION,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1MouseMove,0,this);
    GLCanvas1->Connect(wxEVT_MOUSEWHEEL,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1MouseWheel,0,this);
    GLCanvas1->Connect(wxEVT_SIZE,(wxObjectEventFunction)&CellCounterFrame::OnGLCanvas1Resize,0,this);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&CellCounterFrame::OnMinCtrlChange);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&CellCounterFrame::OnMaxCtrlChange);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CellCounterFrame::OnSelectWellClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CellCounterFrame::OnCountCellsClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CellCounterFrame::OnClearClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CellCounterFrame::OnSaveResultsClick);
    Connect(idMenuOpem,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CellCounterFrame::OnMenuItemOpenSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CellCounterFrame::OnQuit);
    Connect(idMenuHowTo,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CellCounterFrame::OnHowToUseSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CellCounterFrame::OnAbout);
    //*)

    // Custom event
    m_histogram_bmp->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&CellCounterFrame::OnHistogramClick,0,this);
    m_histogram_bmp->Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&CellCounterFrame::OnHistogramClick,0,this);

	m_context = new wxGLContext(GLCanvas1);

    m_init_gl = false;
    m_left_mouse_down = false;
    m_right_mouse_down = false;
    m_well.x = -1.0f;
    m_well.y = -1.0f;

	m_mode = NORMAL;
	m_view = COLOUR;
    m_tile_size = 128;

    for(int i=0; i < 360; i++) {
        m_sin[i] = sin(i*M_PI/180);
        m_cos[i] = cos(i*M_PI/180);
    }

    m_last_image = NULL;

    char str[128];
    sprintf(str, "CellCounter v%d.%d.%d by Nghia Ho", VERSION_MAJOR, VERSION_MINOR, VERSION_SUB);
    SetTitle(wxString::FromAscii(str));

	// Add a blank image to the histogram box
    wxImage blank(m_hist_width, m_hist_height);
    m_histogram_bmp->SetBitmap(wxBitmap(blank));

	SetIcon(wxIcon(icon_xpm));
    Maximize();
}

CellCounterFrame::~CellCounterFrame()
{
    //(*Destroy(CellCounterFrame)
    //*)
}

void CellCounterFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void CellCounterFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("CellCounter"));
}

void CellCounterFrame::OnGLCanvas1Paint(wxPaintEvent& event)
{
    RenderScene();
}

bool CellCounterFrame::InitGL()
{
    m_context->SetCurrent(*GLCanvas1);

    glGenTextures(2, m_tex); assert(glGetError() == GL_NO_ERROR);

	// Main image
    glBindTexture(GL_TEXTURE_2D, m_tex[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Thresholded image
    glBindTexture(GL_TEXTURE_2D, m_tex[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    m_init_gl = true;

    return true;
}

void CellCounterFrame::Resize()
{
    // Can't call this until GLCanvas appears
//	m_context->SetCurrent(*GLCanvas1);

	static int last_w = 0;
	static int last_h = 0;

    int w, h;

    GLCanvas1->GetSize(&w, &h);

	last_w = w;
	last_h = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CellCounterFrame::RenderScene()
{
    if(!m_init_gl) {
        if(!InitGL())
            return;
    }

	m_context->SetCurrent(*GLCanvas1);

	// Only need to call this once, but can't seem to get it to call at the right time, so call it all the time.
	//Resize();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!m_input_image.data) {
        GLCanvas1->SwapBuffers();
        return;
    }

    m_opengl_pan_zoom.Update();

    glColor3f(1,1,1); // white, prevents mixing the texture with a prevously used colour

    // Draw the image
    {
        glEnable(GL_TEXTURE_2D);

        if(m_tile_image[0].tiles.size()) {
            int k = 0;
            for(int i=0; i < m_tile_image[0].height; i++) {
                for(int j=0; j < m_tile_image[0].width; j++) {
                    int y = i*m_tile_size;
                    int x = j*m_tile_size;

                    if(m_view == COLOUR) {
                        glBindTexture(GL_TEXTURE_2D, m_tile_image[0].tiles[k]);
                    }
                    else {
                        glBindTexture(GL_TEXTURE_2D, m_tile_image[1].tiles[k]);
                    }

                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f); glVertex2i(x, y);
                    glTexCoord2f(1.0f, 0.0f); glVertex2i(x + m_tile_size, y);
                    glTexCoord2f(1.0f, 1.0f); glVertex2i(x + m_tile_size, y + m_tile_size);
                    glTexCoord2f(0.0f, 1.0f); glVertex2i(x, y + m_tile_size);
                    glEnd();

                    k++;
                }
            }
        }
        else {
            if(m_view == COLOUR) {
                glBindTexture(GL_TEXTURE_2D, m_tex[0]);
            }
            else {
                glBindTexture(GL_TEXTURE_2D, m_tex[1]);
            }

            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
            glTexCoord2f(1.0f, 0.0f); glVertex2i(m_input_image.cols, 0);
            glTexCoord2f(1.0f, 1.0f); glVertex2i(m_input_image.cols, m_input_image.rows);
            glTexCoord2f(0.0f, 1.0f); glVertex2i(0, m_input_image.rows);
            glEnd();
        }

        glDisable(GL_TEXTURE_2D);
    }

    for(size_t i=0; i < m_results.size(); i++) {
        DrawCircle(m_results[i].x, m_results[i].y, 2.0f, 0.0f, 1.0f, 0.0f);
    }

    float x, y;
    m_opengl_pan_zoom.GetPos(x, y);

    if(m_mode == SELECT_WELL) {
        float radius = (float)m_well_radius_ctrl->GetValue();
        DrawCircle(x, y, radius, 1.0f, 0.0f, 0.0f);
    }
    else {
        // Draw cursor
        /*
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x - m_mouse_selector_radius, y - m_mouse_selector_radius);
        glVertex2f(x + m_mouse_selector_radius, y - m_mouse_selector_radius);
        glVertex2f(x + m_mouse_selector_radius, y + m_mouse_selector_radius);
        glVertex2f(x - m_mouse_selector_radius, y + m_mouse_selector_radius);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(x, y - m_mouse_selector_radius - 5);
        glVertex2f(x, y + m_mouse_selector_radius + 5);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(x - m_mouse_selector_radius - 5, y);
        glVertex2f(x + m_mouse_selector_radius + 5, y);
        glEnd();
        */
    }

    if(m_well.x > 0 && m_well.y > 0) {
        DrawCircle(m_well.x, m_well.y, m_well.radius, 1.0f, 0.0f, 0.0f);
    }

    GLCanvas1->SwapBuffers();
}

void CellCounterFrame::DrawCircle(float x, float y, float radius, float r, float g, float b)
{
    glColor3f(r, g, b);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i < 360; i++) {
        float xpos = x + radius*m_cos[i];
        float ypos = y + radius*m_sin[i];
        glVertex2f(xpos, ypos);
    }
    glEnd();
}

void CellCounterFrame::OnGLCanvas1Resize(wxSizeEvent& event)
{
    Resize();
}

void CellCounterFrame::OnMenuItemOpenSelected(wxCommandEvent& event)
{
	const wxString filter(
	_T("Image files|*.jpg;*.jpeg;*.png;*.tif;*.tiff;*.bmp;*.gif|")
	_T("All files|*.*")
	);

	FileDialog1->SetWildcard(filter);

	if(FileDialog1->ShowModal() == wxID_OK ) {
	    wxString f = FileDialog1->GetPath();
	    LoadImage(f.mb_str());
	    Reset();
	}
}

void CellCounterFrame::LoadImage(const char *filename)
{
	m_last_image = cv::imread(filename, 1 /* force RGB */);
	m_input_image = m_last_image;

	// OpenGL does not like width that aren't multiple of 4, so resize as required
	int width_remainder = m_input_image.cols % 4;

	int new_width = (m_input_image.cols/4 + (width_remainder?1:0) ) * 4;

	if(new_width != m_input_image.cols) {
		cv::Mat new_image = cv::Mat(m_input_image.rows, new_width, CV_8UC3);

		cv::Mat sub_image = new_image(cv::Rect(0, 0, m_input_image.cols, m_input_image.rows));
		m_input_image.copyTo(sub_image);

		m_input_image = new_image;
	}

    cv::flip(m_input_image, m_input_image, 0);

	cv::cvtColor(m_input_image, m_grey_image, CV_BGR2GRAY);
	m_threshold_image = cv::Mat::zeros(m_input_image.size(), CV_8UC3);

    if(!m_input_image.data) {
        wxMessageBox(wxT("Can't open image file"), wxT("Error"),  wxICON_ERROR);
        return;
    }

	m_context->SetCurrent(*GLCanvas1);

    // To cater for non multiple of 4 width, re-create the buffer, minus the padding
    vector <unsigned char> buffer(m_input_image.cols*m_input_image.rows*3);

    unsigned char *ptr = &buffer[0];
    for(int y=0; y < m_input_image.rows; y++) {
        for(int x=0; x < m_input_image.cols; x++) {
            *(ptr++) = m_input_image.at<cv::Vec3b>(y,x)[0];
            *(ptr++) = m_input_image.at<cv::Vec3b>(y,x)[1];
            *(ptr++) = m_input_image.at<cv::Vec3b>(y,x)[2];
        }
    }

    int max_tex_size = 0;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);

    cout << "max_tex_size: " << max_tex_size << endl;
   // max_tex_size = 256;

    if((m_input_image.cols > max_tex_size) || (m_input_image.rows > max_tex_size)) {
        CreateTileImage(m_input_image, m_tile_image[0]);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, m_tex[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, m_input_image.cols, m_input_image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, &buffer[0]);
    }

    m_opengl_pan_zoom.SetImageWidth(m_input_image.cols, m_input_image.rows); // Used to centre the image
    m_opengl_pan_zoom.Centre();

	UpdateThresholdImage();
	InitialiseHistogram();
    UpdateHistogram();

    RenderScene();
}

void CellCounterFrame::CreateTileImage(cv::Mat &img, TileImage &tile_image)
{
    tile_image.width = (float)img.cols / m_tile_size + 0.5f;
    tile_image.height = (float)img.rows / m_tile_size + 0.5f;

    if((int)tile_image.tiles.size() != tile_image.width*tile_image.height) {
        if(tile_image.tiles.size()) {
            glDeleteTextures(tile_image.tiles.size(), &tile_image.tiles[0]);
        }

        tile_image.tiles.resize(tile_image.width*tile_image.height);
        glGenTextures(tile_image.tiles.size(), &tile_image.tiles[0]);
    }

    int k=0;

    for(int i=0; i < tile_image.height; i++) {
        for(int j=0; j < tile_image.width; j++) {
            vector <unsigned char> tile_buf(m_tile_size*m_tile_size*3);

            for(int y=0; y < m_tile_size; y++) {
                for(int x=0; x < m_tile_size; x++) {
                    int yy = i*m_tile_size + y;
                    int xx = j*m_tile_size + x;

                    if(xx >= img.cols) continue;
                    if(yy >= img.rows) continue;

                    tile_buf[(y*m_tile_size+x)*3] = img.at<cv::Vec3b>(yy,xx)[0];
                    tile_buf[(y*m_tile_size+x)*3+1] = img.at<cv::Vec3b>(yy,xx)[1];
                    tile_buf[(y*m_tile_size+x)*3+2] = img.at<cv::Vec3b>(yy,xx)[2];
                }
            }

            glBindTexture(GL_TEXTURE_2D, tile_image.tiles[k]);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, m_tile_size, m_tile_size, 0, GL_BGR, GL_UNSIGNED_BYTE, &tile_buf[0]);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            k++;
        }
    }
}

void CellCounterFrame::OnGLCanvas1LeftDown(wxMouseEvent& event)
{
    m_left_mouse_down = true;

	GLCanvas1->SetFocus(); // On Windows the scrollwheel gets lost

    if(event.ControlDown()) {
        if(m_mode == NORMAL) {
            AddCell();
			RenderScene();
        }
    }
	else if(m_mode == SELECT_WELL) {
        m_opengl_pan_zoom.GetPos(m_well.x, m_well.y);
        m_well.radius = m_well_radius_ctrl->GetValue();
        m_mode = NORMAL;
		m_view = THRESHOLD;
    }
}

void CellCounterFrame::OnGLCanvas1LeftUp(wxMouseEvent& event)
{
    m_left_mouse_down = false;
}

void CellCounterFrame::OnGLCanvas1RightDown(wxMouseEvent& event)
{
    m_right_mouse_down = true;

	GLCanvas1->SetFocus(); // On Windows the scrollwheel gets lost

    if(m_mode == NORMAL) {
        int best_idx = -1;
        float best_dist = FLT_MAX;
        float x, y;

        m_opengl_pan_zoom.GetPos(x,y);

        for(size_t i=0; i < m_results.size(); i++) {
            float dx = x - m_results[i].x;
            float dy = y - m_results[i].y;

            float d = dx*dx + dy*dy;

            if(d < best_dist && d < m_mouse_selector_radius*m_mouse_selector_radius) {
                best_dist = d;
                best_idx = i;
            }
        }

        if(best_idx != -1) {
            swap(m_results[best_idx], m_results.back());
            m_results.pop_back();
        }
    }

	UpdateCellCount();
    RenderScene();
}

void CellCounterFrame::OnGLCanvas1RightUp(wxMouseEvent& event)
{
    m_right_mouse_down = false;
}

void CellCounterFrame::OnGLCanvas1MouseMove(wxMouseEvent& event)
{
    int w, h;

    GLCanvas1->GetSize(&w, &h);

    int x = event.GetX();
    int y = h - event.GetY() - 1;

    m_opengl_pan_zoom.SetMouse((float)x, (float)y);

    if(m_left_mouse_down && !event.ControlDown() && m_mode == NORMAL) {
        m_opengl_pan_zoom.Move();
    }

    RenderScene();
}

void CellCounterFrame::OnGLCanvas1MouseWheel(wxMouseEvent& event)
{
    if(event.GetWheelRotation() > 0) {
        m_opengl_pan_zoom.ZoomIn();
    }
    else {
        m_opengl_pan_zoom.ZoomOut();
    }

    RenderScene();
}

void CellCounterFrame::OnGLCanvas1LeftDClick(wxMouseEvent& event)
{
    m_opengl_pan_zoom.Centre();
    RenderScene();
}

void CellCounterFrame::OnCountCellsClick(wxCommandEvent& event)
{
    int x1 = (int)(m_well.x - m_well.radius);
    int y1 = (int)(m_well.y - m_well.radius);
    int x2 = (int)(m_well.x + m_well.radius);
    int y2 = (int)(m_well.y + m_well.radius);

    int w = x2 - x1 + 1;
    int h = y2 - y1 + 1;

    w = (w/4)*4;
    h = (h/4)*4;

    if(x1 < 0 || x1 >= m_input_image.cols || y1 < 0 || y1 >= m_input_image.rows) {
        return;
    }

    if(x2 < 0 || x2 >= m_input_image.cols || y2 < 0 || y2 >= m_input_image.rows) {
        return;
    }

    cv::Mat well = m_input_image(cv::Rect(x1, y1, w, h));

	int radius_start = m_cell_radius_start_ctrl->GetValue();
	int radius_end = m_cell_radius_end_ctrl->GetValue();
    int lower = m_min_ctrl->GetValue();
    int upper = m_max_ctrl->GetValue();
    int keep_cell_size = m_keep_cells_ctrl->GetValue();
	float circle_threshold = atof(m_circleness_txt->GetValue().mb_str());

    m_cell_counter.Run(well, radius_start, radius_end, lower, upper, keep_cell_size, circle_threshold);

    m_results = m_cell_counter.GetResults();

    for(size_t i=0; i < m_results.size(); i++) {
        m_results[i].x += m_well.x - m_well.radius;
        m_results[i].y += m_well.y - m_well.radius;
    }

    UpdateCellCount();

    RenderScene();
}

void CellCounterFrame::OnGLCanvas1MiddleDown(wxMouseEvent& event)
{
	GLCanvas1->SetFocus(); // On Windows the scrollwheel gets lost

    if(m_mode == SELECT_WELL) {
        m_opengl_pan_zoom.GetPos(m_well.x, m_well.y);
        m_well.radius = (float)m_well_radius_ctrl->GetValue();
        m_mode = NORMAL;
		m_view = THRESHOLD;
    }
    else {
        AddCell();
    }

    RenderScene();
}

void CellCounterFrame::AddCell()
{
    float x, y;

    m_opengl_pan_zoom.GetPos(x,y);

    m_results.push_back(cv::Point2f(x,y));

    UpdateCellCount();
}

void CellCounterFrame::UpdateCellCount()
{
    stringstream str;
    str << m_results.size();

    m_total_cells_txt->SetValue(wxString::FromAscii(str.str().c_str()));
}

void CellCounterFrame::UpdateThresholdImage()
{
	m_context->SetCurrent(*GLCanvas1);

    int lower = m_min_ctrl->GetValue();
    int upper = m_max_ctrl->GetValue();

	m_threshold_image = cv::Mat::zeros(m_grey_image.size(), CV_8UC3);

	for(int y=0; y < m_grey_image.rows; y++) {
		for(int x=0; x < m_grey_image.cols; x++) {
			if(m_grey_image.at<uchar>(y,x) >= lower && m_grey_image.at<uchar>(y,x) <= upper) {
				m_threshold_image.at<cv::Vec3b>(y,x)[0] = 255;
				m_threshold_image.at<cv::Vec3b>(y,x)[1] = 255;
				m_threshold_image.at<cv::Vec3b>(y,x)[2] = 255;
			}
		}
	}

    if(m_tile_image[0].tiles.size()) {
        CreateTileImage(m_threshold_image, m_tile_image[1]);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, m_tex[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, m_threshold_image.cols, m_threshold_image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, m_threshold_image.data);
    }

	RenderScene();
}

void CellCounterFrame::SwitchViews()
{
	if(m_view == COLOUR) {
		m_view = THRESHOLD;
	}
	else {
		m_view = COLOUR;
	}

	RenderScene();
}

void CellCounterFrame::OnMinCtrlChange(wxSpinEvent& event)
{
    UpdateHistogram();
	UpdateThresholdImage();
}

void CellCounterFrame::OnMaxCtrlChange(wxSpinEvent& event)
{
    UpdateHistogram();
	UpdateThresholdImage();
}

void CellCounterFrame::OnSelectWellClick(wxCommandEvent& event)
{
    m_well.x = -1;
    m_well.y = -1;

    m_mode = SELECT_WELL;
}

void CellCounterFrame::OnSaveResultsClick(wxCommandEvent& event)
{
	// Check if the current selected well coincides with any existing one
	// A coincide is defined if the current well's centre lies within another one

	if(m_well.x < 0 && m_well.y < 0) {
		return;
	}

	int found_idx = -1;

	for(size_t i=0; i < m_wells_added.size(); i++) {
		float dx = m_well.x - m_wells_added[i].x;
		float dy = m_well.y - m_wells_added[i].y;
		float r = dx*dx + dy*dy;

		if(r < m_wells_added[i].radius*m_wells_added[i].radius) {
			found_idx = i;
			break;
		}
	}

	if(found_idx != -1) {
		m_wells_added[found_idx].x = m_well.x;
		m_wells_added[found_idx].y = m_well.y;
		m_wells_added[found_idx].radius = m_well.radius;
		m_wells_added[found_idx].cell_count = atoi(m_total_cells_txt->GetValue().mb_str());
	}
	else {
		m_well.cell_count = atoi(m_total_cells_txt->GetValue().mb_str());

		m_wells_added.push_back(m_well);
	}

	UpdateResults();
}

void CellCounterFrame::UpdateResults()
{
	wxString txt;

	for(size_t i=0; i < m_wells_added.size(); i++) {
		char str[256];

		float y = m_input_image.rows - m_wells_added[i].y - 1;

		sprintf(str, "%d\t%.0f %.0f\t%d\n", (int)i+1, m_wells_added[i].x, y, m_wells_added[i].cell_count);

		txt += wxString::FromAscii(str);
	}

	m_output_txt->SetValue(txt);
}

void CellCounterFrame::Reset()
{
    m_well.x = -1.0f;
    m_well.y = -1.0f;
    m_well.radius = 0.0f;

	m_results.clear();
    m_wells_added.clear();

	UpdateCellCount();
	UpdateResults();

	Resize();
	RenderScene();
}

void CellCounterFrame::OnClearClick(wxCommandEvent& event)
{
    wxMessageDialog dialog(this, _T("Are you sure you want to clear the results?"), _T("CellCounter"), wxYES_NO);

    if(dialog.ShowModal() == wxID_YES) {
        Reset();
    }
}

void CellCounterFrame::OnHowToUseSelected(wxCommandEvent& event)
{
	wxString str;

	str += _T("Mouse actions:\n");
	str += _T("Left down + move - pan the image\n");
	str += _T("Scrollwheel - zoom in/out\n");
	str += _T("Left double click - centre the image\n");
	str += _T("Left click - select well\n");
	str += _T("Ctrl + left click - add colony\n");
	str += _T("Right click - remove colony\n\n");
	str += _T("Keyboard actions:\n");
	str += _T("s - switch between binary and colour image\n");

	wxMessageDialog dialog(this, str, _T("CellCounter"), wxOK | wxICON_INFORMATION);

	dialog.ShowModal();
}

void CellCounterFrame::InitialiseHistogram()
{
    int histogram[256];
    int max_height = 0;
    memset(histogram, 0, sizeof(histogram));

    for(int y=0; y < m_grey_image.rows; y++) {
        for(int x=0; x < m_grey_image.cols; x++) {
            histogram[m_grey_image.at<uchar>(y,x)]++;
            max_height = max(max_height, histogram[m_grey_image.at<uchar>(y,x)]);
        }
    }

    // Use the default size
    wxImage img(m_hist_width, m_hist_height);

    for(int i=0; i < 256; i++) {
        int bar_height = histogram[i]*m_hist_height/max_height;

        for(int j=0; j < bar_height; j++) {
            img.SetRGB(i, m_hist_height-j-1, 255, 255, 255);
        }
    }

    m_histogram_cache = img;
}

void CellCounterFrame::UpdateHistogram()
{
    wxImage img = m_histogram_cache.Copy();

    //Draw the threshold bar
    int lower = m_min_ctrl->GetValue();
    int upper = m_max_ctrl->GetValue();

    for(int j=0; j < m_hist_height; j++) {
        img.SetRGB(lower, j, 0, 255, 0);
        img.SetRGB(upper, j, 255, 0, 0);
    }

    m_histogram_bmp->SetBitmap(wxBitmap(img));
    //BoxSizer1->Layout();
}

void CellCounterFrame::OnHistogramClick(wxMouseEvent &event)
{
    if(!m_grey_image.data) {
        return;
    }

    int x = event.GetX();

    cout << x << endl;

    int lower = m_min_ctrl->GetValue();
    int upper = m_max_ctrl->GetValue();

    // See where the click is closest to

    if(event.LeftDown()) {
        if(x < upper) {
            m_min_ctrl->SetValue(x);
        }
    }
    else if(event.RightDown()) {
        if(x > lower) {
            m_max_ctrl->SetValue(x);
        }
    }

    UpdateHistogram();
	UpdateThresholdImage();
}
