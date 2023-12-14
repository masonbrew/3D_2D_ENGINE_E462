//Sources
// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixel
// https://docs.microsoft.com/en-us/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-170&viewFallbackFrom=vs-2019
// https://www.geeksforgeeks.org/vector-in-cpp-stl/
// https://www.includehelp.com/stl/appending-a-vector-to-a-vector.aspx#:~:text=Appending%20a%20vector%20elements%20to,vector%3A%3Ainsert()%20function.&text=Syntax%3A,iterator%20start_position%2C%20iterator%20end_position)%3B
//https://docs.microsoft.com/en-us/windows/win32/gdi/colorref
// https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
// https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
// https://opentextbc.ca/calculusv3openstax/chapter/vectors-in-three-dimensions/
// https://academo.org/demos/rotation-about-point/
// HelloWindowsDesktop.cpp
// I pledge my honor that I have abided by the Stevens Honor Code - Mason Brewster Ryan Potenza
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
//Camera - This has the location and angle of viewing
class camera {
private:
    double xCord = 0;
    double yCord = 0;
    double zCord = 0;
    double angleX = 0;
    double angleY = 0;
public:
    camera(double x, double y, double z, double viewX, double viewY) {
        xCord = x;
        yCord = y;
        zCord = z;
        angleX = viewX;
        angleY = viewY;
    }
    camera() {
        cout << "Camera Created" << endl;
    }
    double getX() {
        return xCord;
    }
    double getY() {
        return yCord;
    }
    double getZ() {
        return zCord;
    }
    double getViewX() {
        return angleX;
    }
    double getViewY() {
        return angleY;
    }
};
//Face
class face {
public:
    COLORREF color;
    float oneX;
    float twoX;
    float threeX;
    float oneY;
    float twoY;
    float threeY;
    float oneZ;
    float twoZ;
    float threeZ;
    face(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, COLORREF faceColor) {
        oneX = x1;
        oneY = y1;
        oneZ = z1;
        twoX = x2;
        twoY = y2;
        twoZ = z2;
        threeX = x3;
        threeY = y3;
        threeZ = z3;
        color = faceColor;
    }
    void translate(double xPos, double yPos, double zPos) {
        oneX = oneX + xPos;
        twoX = twoX + xPos;
        threeX = threeX + xPos;
        oneY = oneY + yPos;
        twoY = twoY + yPos;
        threeY = threeY + yPos;
        oneZ = oneZ + zPos;
        twoZ = twoZ + zPos;
        threeZ = threeZ + zPos;
    }
    void rotate(double horizontal, double vertical) {
        //horizontal (left/right)
        oneX = oneX * cos(horizontal * 3.14 / 180) - (oneY * sin(horizontal * 3.14 / 180));
        oneY = oneX * sin(horizontal * 3.14 / 180) + (oneY * cos(horizontal * 3.14 / 180));
        twoX = twoX * cos(horizontal * 3.14 / 180) - (twoY * sin(horizontal * 3.14 / 180));
        twoY = twoX * sin(horizontal * 3.14 / 180) + (twoY * cos(horizontal * 3.14 / 180));
        threeX = threeX * cos(horizontal * 3.14 / 180) - (threeY * sin(horizontal * 3.14 / 180));
        threeY = threeX * sin(horizontal * 3.14 / 180) + (threeY * cos(horizontal * 3.14 / 180));

        //vertical (up/down)
        vertical = vertical * -1;
        oneY = oneY * cos(vertical * 3.14 / 180) - (oneZ * sin(vertical * 3.14 / 180));
        oneZ = oneY * sin(vertical * 3.14 / 180) + (oneZ * cos(vertical * 3.14 / 180));
        twoY = twoY * cos(vertical * 3.14 / 180) - (twoZ * sin(vertical * 3.14 / 180));
        twoZ = twoY * sin(vertical * 3.14 / 180) + (twoZ * cos(vertical * 3.14 / 180));
        threeY = threeY * cos(vertical * 3.14 / 180) - (threeZ * sin(vertical * 3.14 / 180));
        threeZ = threeY * sin(vertical * 3.14 / 180) + (threeZ * cos(vertical * 3.14 / 180));


    }
    COLORREF getcolor() {
        return color;
    }
};
//Entities
class cube {
public:
    std::vector<face> faces;
    cube() {
        //Hardcodes cooridnates of all the points and faces needed to make a cube
        face face1(-1, -1, 0, -1, 1, 0, 1, -1, 0, RGB(0, 255, 255));
        face face2(1, 1, 0, -1, 1, 0, 1, -1, 0, RGB(0, 255, 255));
        face face3(-1, -1, 2, -1, 1, 2, 1, -1, 2, RGB(0, 0, 255));
        face face4(1, 1, 2, -1, 1, 2, 1, -1, 2, RGB(0, 0, 255));
        face face5(-1, -1, 0, -1, 1, 0, -1, -1, 2, RGB(255, 0, 255));
        face face6(-1, 1, 2, -1, 1, 0, -1, -1, 2, RGB(255, 0, 255));
        face face7(1, 1, 2, 1, 1, 0, 1, -1, 2, RGB(255, 0, 0));
        face face8(1, -1, 0, 1, 1, 0, 1, -1, 2, RGB(255, 0, 0));
        face face9(-1, 1, 0, 1, 1, 0, 1, 1, 2, RGB(255, 255, 0));
        face face10(-1, 1, 0, -1, 1, 2, 1, 1, 2, RGB(255, 255, 0));
        face face11(-1, -1, 0, 1, -1, 0, 1, -1, 2, RGB(0, 255, 0));
        face face12(-1, -1, 0, -1, -1, 2, 1, -1, 2, RGB(0, 255, 0));
        //Filling in the vector
        faces.push_back(face1);
        faces.push_back(face2);
        faces.push_back(face3);
        faces.push_back(face4);
        faces.push_back(face5);
        faces.push_back(face6);
        faces.push_back(face7);
        faces.push_back(face8);
        faces.push_back(face9);
        faces.push_back(face10);
        faces.push_back(face11);
        faces.push_back(face12);
    }
    void setPos(float xPos, float yPos, float zPos) {
        for (int x = 0; x < int(faces.size()); x++) {
            faces[x].translate(xPos, yPos, zPos);
        }
        cout << "position set" << endl;
    }
    int faceCount() {
        return faces.size();
    }

};
class testTriangle {
public:
    std::vector<face> faces;
    testTriangle() {
        face face1(-1, 5, 1, 1, 5, 1, 1, 5, -1, RGB(0, 255, 255));
        faces.push_back(face1);
    }
    int faceCount() {
        return faces.size();
    }
};
//Rending Logic - Mason & Ryan
class engine {
private:
    std::vector<face> faceList;
public:
    void addEntity(vector<face> entityFaces) {
        faceList.insert(faceList.end(), entityFaces.begin(), entityFaces.end());
    }
    void render(camera myCamera, HDC myhdc) {
        cout << "start rendering" << endl;
        float px;
        float py;
        float p1x;
        float p2x;
        float p3x;
        float p1y;
        float p2y;
        float p3y;
        float closest;
        float area;
        float s;
        float t;
        float a;
        float b;
        float c;
        float dist;
        //This zeros all the points

        for (int i = 0; i < faceList.size(); i++) {
            faceList[i].translate(-1 * myCamera.getX(), -1 * myCamera.getY(), -1 * myCamera.getZ());
            faceList[i].rotate(myCamera.getViewX(), myCamera.getViewY());
        }

        cout << "zeroed in rendering" << endl;
        //This renders each pixel i is x and j is y
        for (int i = 1; i <= 500; i++) {
            for (int j = 1; j <= 500; j++) {
                float fovDist = 400.00; //fov control
                px = (i - 250) / fovDist;
                py = (-1 * j + 250) / fovDist;
                closest = 0;
                COLORREF pixelColor = RGB(0, 0, 0);
                for (int k = 0; k < faceList.size(); k++) {
                    if (faceList[k].oneY > 0 && faceList[k].twoY > 0 && faceList[k].threeY > 0) {//This tests if all the point on the object are in field of view
                        p1x = faceList[k].oneX / faceList[k].oneY;
                        p2x = faceList[k].twoX / faceList[k].twoY;
                        p3x = faceList[k].threeX / faceList[k].threeY;
                        p1y = faceList[k].oneZ / faceList[k].oneY;
                        p2y = faceList[k].twoZ / faceList[k].twoY;
                        p3y = faceList[k].threeZ / faceList[k].threeY;
                        area = 0.5 * (-p1y * p2x + p3y * (-p1x + p2x) + p3x * (p1y - p2y) + p1x * p2y);
                        s = 1 / (2 * area) * (p3y * p2x - p3x * p2y + (p2y - p3y) * px + (p3x - p2x) * py);
                        t = 1 / (2 * area) * (p3x * p1y - p3y * p1x + (p3y - p1y) * px + (p1x - p3x) * py);

                        if (s > 0 && t > 0 && (1 - s - t) > 0) { //This conditions are met the then vector lies within the that triangle    
                            //This solves for the distance to the point in y to make sure it renders the closest face
                            a = ((faceList[k].oneY - faceList[k].twoY) * (faceList[k].oneZ - faceList[k].threeZ)) - ((faceList[k].oneZ - faceList[k].twoZ) * (faceList[k].oneY - faceList[k].threeY));
                            b = ((faceList[k].oneZ - faceList[k].twoZ) * (faceList[k].oneX - faceList[k].threeX)) - ((faceList[k].oneX - faceList[k].twoX) * (faceList[k].oneZ - faceList[k].threeZ));
                            c = ((faceList[k].oneX - faceList[k].twoX) * (faceList[k].oneY - faceList[k].threeY)) - ((faceList[k].oneY - faceList[k].twoY) * (faceList[k].oneX - faceList[k].threeX));
                            dist = (a * faceList[k].oneX + b * faceList[k].oneY + c * faceList[k].oneZ) / (a * px + b + c * py);

                            if (dist < closest || closest == 0) {
                                pixelColor = faceList[k].getcolor();
                                closest = dist;
                            }
                        }

                    }
                }
                SetPixel(myhdc, i, j, pixelColor);
            }
        }
    }


};

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("Rending Engine");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("E462 2D_3D_Rending_Engine");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    cout << "Please at least show this" << endl;

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 500, //Window Size
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    static COLORREF redColor = RGB(255, 0, 0);
    static COLORREF blueColor = RGB(0, 0, 255);
    static COLORREF greenColor = RGB(0, 255, 0);
    //These are here bc they won't work in a swithc idk why
    camera myCamera(10, -10, 10, -45, -45); //x y z 
    cube myCube;
    cube myCube2;
    cube myCube3;
    engine myEngine;
    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        //Start of Our Code
        myCube2.setPos(0, 0, 0);
        myCube.setPos(3, 3, 4);
        myCube3.setPos(0, 1, 2);
        myEngine.addEntity(myCube.faces);
        myEngine.addEntity(myCube2.faces);
        myEngine.addEntity(myCube3.faces);
        myEngine.render(myCamera, hdc);


        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}