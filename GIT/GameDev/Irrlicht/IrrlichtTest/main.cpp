#include <iostream>
#include <irrlicht.h>

#pragma comment (lib, "Irrlicht.lib") // объ€вл€ем библиотеку Irrlicht.lib
#pragma warning(disable : 4996)

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//int resX=1280;
//int resY=800;
f32 resX=640;
f32 resY=480;

float FPSspeed = 1.0f;
int farValueVariable = 10000;

struct SAppContext
{
    IrrlichtDevice *device;
    s32        counter;
    IGUIListBox*  listbox;
};

enum
{
    ID_IsNotPickable = 0,
    
    IDFlag_IsPickable = 1 << 0,
    
    IDFlag_IsHighlightable = 1 << 1
};

enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_NEW_WINDOW_BUTTON,
    GUI_ID_FAR,
    GUI_ID_TRANSPARENCY_SCROLL_BAR
};

class MyEventReceiver : public IEventReceiver
{
public:
    MyEventReceiver(SAppContext & context) : Context(context) { }
    
    
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
        
        // Remember whether each key is down or up
        if (event.EventType == EET_KEY_INPUT_EVENT)
            
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();
            
            switch(event.GUIEvent.EventType)
            {
                case EGET_SCROLL_BAR_CHANGED:
                    if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                    {
                        s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                        
                        for (u32 i=0; i<EGDC_COUNT ; ++i)
                        {
                            SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
                            col.setAlpha(pos);
                            env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
                        }
                        
                    }
                    if (id == GUI_ID_FAR)
                    {
                        s32 farpos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                        
                        for (u32 i=0; i<EGUIET_SCROLL_BAR; ++i)
                        {
                            farValueVariable = farpos;
                        }
                    }
                    break;
            }
            
        }
        return false;
    }
    
    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    SAppContext & Context;
};

int main()
{
    IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(resX,resY),32,false,false,false);
    
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment *env=device ->getGUIEnvironment();
    IGUISkin* skin = env->getSkin();
    IGUIFont* font = env->getFont("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/font.bmp");
    if (font) skin->setFont(font);
    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
    
    ISceneNode* skydome = smgr->addSkyDomeSceneNode(driver->getTexture("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/skydome2.jpg"),16,8,0.95f,2.0f);
    skydome->setVisible(false);
    
    ISceneNode* cube = smgr->addCubeSceneNode();
    cube->setPosition(vector3df(1500,550,1500));
    cube->setScale(vector3df(50,50,50));
    cube->setMaterialFlag(EMF_LIGHTING,false);
    
    IAnimatedMeshSceneNode* faerie = smgr->addAnimatedMeshSceneNode(smgr->getMesh("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/faerie.md2"));
    faerie->setMaterialTexture(0, driver->getTexture("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/faerie.bmp"));
    faerie->setMaterialFlag(EMF_LIGHTING, false);
    faerie->setPosition(vector3df(250.0,335.0,250.0));
    faerie->setScale(vector3df(4.0,4.0,4.0));
    faerie->setVisible(false);
    
    // добавл€ем узел(ноду) ландшафта
    ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
                                                           "/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/terrain-heightmap.bmp",
                                                           0, // родительский узел
                                                           -1, // id узла
                                                           vector3df(0.f, 0.f, 0.f), // позици€
                                                           vector3df(0.f, 0.f, 0.f), // поворот
                                                           vector3df(40.f, 4.4f, 40.f), // маштаб
                                                           SColor ( 255, 255, 255, 255 ), // цвет вершин
                                                           5, // максимум LOD
                                                           ETPS_17, // размер патча
                                                           4 // коэф-т размыти€
                                                           );
    terrain->setMaterialFlag(EMF_LIGHTING, false);
    terrain->setMaterialTexture(0,
                                driver->getTexture("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/terrain-texture.jpg"));
    terrain->setMaterialTexture(1,
                                driver->getTexture("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/detailmap3.jpg"));
    terrain->setMaterialType(EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f, 20.0f);
    terrain->setVisible(false);
    
    //Create button on main menu
    IGUIButton *Continue=env->addButton (rect<s32>(resX/2-(resX/100*10),resY/2-170,(resX/2)+(resX/100*10),(resY/2)-140), 0, 105, L"Continue");
    IGUIButton *Game=env->addButton (rect<s32>(resX/2-(resX/100*10),resY/2-170,(resX/2)+(resX/100*10),(resY/2)-140), 0, 101, L"Game",L"Start a new game");
    IGUIButton *Options=env->addButton (rect<s32>(resX/2-(resX/100*10),resY/2-130,(resX/2)+(resX/100*10),(resY/2)-100), 0, 102, L"Options");
    IGUIButton *Credits=env->addButton (rect<s32>(resX/2-(resX/100*10),resY/2-90,(resX/2)+(resX/100*10),(resY/2)-60), 0, 103, L"Credits", L"all about creators");
    IGUIButton *Quit=env->addButton (rect<s32>(resX/2-(resX/100*10),resY/2-50,(resX/2)+(resX/100*10),(resY/2)-20), 0, 104, L"Quit",L"exits Programm");
    
    IGUICheckBox* fullscreen = env->addCheckBox (false, rect<s32>(80,45,160,200),0,-1,L"fullscreen");
    fullscreen->setVisible(false);
    
    IGUIStaticText* FarValue = env->addStaticText(L"Far Value", rect<s32>(435,20,490,40), false);
    FarValue->setVisible(false);
    
    IGUIScrollBar* far = env->addScrollBar(true, rect<s32>(360,45,560,60),0,GUI_ID_FAR);
    far->setVisible(false);
    far->setMin(1000);
    far->setMax(15000);
    far->setPos(farValueVariable);
    
    //Create button on Options
    IGUIButton *Cancel=env->addButton (rect<s32>(20,440,60,460), 0, 101, L"OK");
    Cancel->setVisible (false);
    Continue->setVisible(false);
    
    IGUIStaticText* brightness = env->addStaticText (L"brightness",rect<s32>(150,20,205,40), false,false, 0,-1,false);
    brightness->setVisible(false);
    
    int fps = driver->getFPS();
    
    IGUIScrollBar* scrollbar = env->addScrollBar (true, rect<s32>(80, 45, 280, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
    scrollbar->setMin(55);
    scrollbar->setMax(255);
    scrollbar->setVisible(false);
    scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());
    
    IGUIStaticText* creditsText = env->addStaticText (L"The TO-14 company. Vladik and Dimka Production. all right reserved. Game desigh and SFX by Rodinov Dmitri. Programming by Rodinov Dmitri. 3ds models by Tobolov Vladislav. Graphics by Rodinov Dmitri. Testing by Tobolov Vladislav. Hardware by Rodinov Dmitri. Software by Rodinov Dmitri. Art by Tobolov Vladislav. Support by Tobolov Vladislav.", rect<s32>(resX/2-300,resY/2-220,resX/2+300,resY/2+180),true);
    creditsText->setVisible(false);
    
    ICameraSceneNode* cameranode = smgr->addCameraSceneNode();
    
    ICameraSceneNode* cameraFPS = smgr->addCameraSceneNodeFPS(0,100.0f,FPSspeed, ID_IsNotPickable, 0, 0, true, 3.f);
    cameraFPS->setPosition(vector3df(100,1000,100));
    //cameraFPS->setPosition(vector3df(470.0,2250.0,250.0));
    cameraFPS->setTarget(vector3df(0.0,0.0,0.0));
    cameraFPS->setVisible(false);
    
    IBillboardSceneNode* bill = smgr->addBillboardSceneNode();
    bill->setMaterialType(EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/particle.bmp"));
    bill->setMaterialFlag(EMF_LIGHTING, false);
    bill->setMaterialFlag(EMF_ZBUFFER, false);
    bill->setSize(dimension2d<f32>(5.0f,5.0f));
    bill->setParent(cameraFPS);
    bill->setPosition(vector3df(0.0,0.0,30.0));
    
    SAppContext context;
    context.device = device;
    context.counter = 0;
    
    MyEventReceiver receiver(context);
    device->setEventReceiver(&receiver);
    
    /*IGUIImage* img = env->addImage(driver->getTexture("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/1.png"), vector2d<s32>(200,200));
    img->setRelativePosition(rect<s32>(0,0,250,200));
    img->setVisible(false);
    */
    
    /*device->getFileSystem()->addFileArchive("/Users/Dmitri/Desktop/Programming/irrlicht-1.8.4/IRRLICHT_PROJECTS/IrrlichtTest/dist/map-20kdm2.pk3");
    
    scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
    scene::IMeshSceneNode* q3node = 0;
    
    // The Quake mesh is pickable, but doesn't get highlighted.
    if (q3levelmesh)
        q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
    
    
    scene::ITriangleSelector* selector = 0;
    
    if (q3node)
    {
        q3node->setPosition(core::vector3df(-1350,-130,-1400));
        
        selector = smgr->createOctreeTriangleSelector(
                                                      q3node->getMesh(), q3node, 128);
        q3node->setTriangleSelector(selector);
        // We're not done with this selector yet, so don't drop it.
    }
    
    if (selector)
    {
        scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
                                                                                selector, cameraFPS, core::vector3df(30,50,30),
                                                                                core::vector3df(0,-10,0), core::vector3df(0,30,0));
        selector->drop(); // As soon as we're done with the selector, drop it.
        cameraFPS->addAnimator(anim);
        anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }*/
    
    while
        
        (device->run())
    {
        if (device->isWindowActive())
        {
        f32 CamPosFPS_X = cameraFPS->getPosition().X;
        f32 CamPosFPS_Z = cameraFPS->getPosition().Z;
        cameraFPS->setFarValue(farValueVariable);
            
        ICameraSceneNode* cameramap = smgr->addCameraSceneNode(0, cameraFPS->getPosition(),vector3df(CamPosFPS_X,0.0,CamPosFPS_Z));
        cameramap->setVisible(false);
        cameramap->setFarValue(42000);
        
        driver->setViewPort(rect<s32>(0,0,resX,resY));
        driver->beginScene(true, true, SColor(0,200,200,200));
        
        smgr->setActiveCamera(cameraFPS);
        smgr->drawAll();
        device->getGUIEnvironment()->drawAll();
        driver->setViewPort(rect<s32>(0,resY-(0.25*resY),resX-(0.75*resX),resY));
        smgr->setActiveCamera(cameramap);
        smgr->drawAll();
        smgr->setActiveCamera(cameraFPS);
        
        stringw str = L"My First Game";
        str += " FPS:";
        str += fps;
        device->setWindowCaption(str.c_str());
        
            driver->draw2DRectangle(SColor(150,255,0,0), rect<s32>());
            
        
        if (fullscreen->isChecked())
        {
            
        }
        
        f32 camPosX = cameraFPS->getAbsolutePosition().X;
        f32 camPosZ = cameraFPS->getAbsolutePosition().Z;
        f32 camPosY = cameraFPS->getAbsolutePosition().Y;
            
            
        if (receiver.IsKeyDown(KEY_KEY_V))
        {
            cameraFPS->setPosition(vector3df(camPosX,camPosY+10,camPosZ));
        }
            
            
           // cout << "CamPosX="<<camPosX<<"\tCamPosZ="<<camPosZ<<endl;
            

        
        if (receiver.IsKeyDown(KEY_ESCAPE))
        {
            Continue->setVisible (true);
            Options->setVisible (true);
            Credits->setVisible (false);
            Quit->setVisible (true);
            Cancel->setVisible(false);
            device->getCursorControl()->setVisible(true);
            cameraFPS->setVisible(false);
            //img->setVisible(false);
        }
        
        //Click on button
        if (Game->isPressed ())
        {
            faerie->setVisible(true);
            cameraFPS->setVisible(true);
            cameramap->setVisible(true);
            //img->setVisible(true);
            //q3node->setVisible(true);
            
            skydome->setVisible(true);
            terrain->setVisible(true);
            Game->setVisible (false);
            Options->setVisible (false);
            Credits->setVisible (false);
            Quit->setVisible (false);
            device ->getCursorControl()->setVisible (false);
            
            // создаем селектор дл€ ландшафта
            ITriangleSelector* selector
            = smgr->createTerrainTriangleSelector(terrain, 0);
            terrain->setTriangleSelector(selector);
            
            // создаем аниматор, определ€ющий столкновени€ и цепл€ем его к камере
            ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
                                                                             selector, cameraFPS, vector3df(60,100,60),
                                                                             vector3df(0,-9.8,0),
                                                                             vector3df(0,50,0));
            selector->drop();
            cameraFPS->addAnimator(anim);
            anim->drop();
            
            
            /*
            int X = pos2d.X; //левый верхний угол
            int Y = pos2d.Y; //левый верхний угол
            int width = 3; //ширина
            int length = 40; //длина полного здоровья
            
            int hitpoint = 100; //длина по максимально возможному кол-во здоровья
            int health = 50; //сколько здоровья осталось (длина)
            
            //driver->draw2DRectangle(video::SColor(250,57,224,100), imp1, &imp2); //рисуем
            
            
            core::rect< s32 > imp1false(X,Y,X+length,Y+width);
            X = X - imp1false.getWidth()/2;
            core::rect< s32 > imp1(X-1,Y-1,X+length+1,Y+width+1); //максимально возможное кол-во здоровья
            
            int rests = health*(length)/hitpoint; //третий класс школололо
            core::rect< s32 > imp2(X,Y,X+rests,Y+width); //область обрезания
            
            driver->draw2DRectangle(video::SColor(250,0,0,0), imp1);
            driver->draw2DRectangle(video::SColor(250,57,224,100), imp2);*/
            
            Game->setPressed (0);
        }
        
        if (Options->isPressed())
        {
            Game->setVisible (false); 
            Options->setVisible (false); 
            Credits->setVisible (false); 
            Quit->setVisible (false);
            Cancel->setVisible(true);
            scrollbar->setVisible(true);
            brightness->setVisible(true);
            Continue->setVisible(false);
            fullscreen->setVisible(true);
            far->setVisible(true);
            FarValue->setVisible(true);
            
            Options->setPressed(0);
        }
        
        if (Cancel->isPressed())
        {
            Game->setVisible (true); 
            Options->setVisible (true); 
            Credits->setVisible (true); 
            Quit->setVisible (true);
            Cancel->setVisible(false);
            scrollbar->setVisible(false);
            brightness->setVisible(false);
            creditsText->setVisible(false);
            fullscreen->setVisible(false);
            far->setVisible(false);
            FarValue->setVisible(false);
            
            Cancel->setPressed (0);
        }
        
        if (Credits->isPressed())
        {
            Game->setVisible (false); 
            Options->setVisible (false); 
            Credits->setVisible (false); 
            Quit->setVisible (false);
            creditsText->setVisible(true);
            Cancel->setVisible(true);
            
            Credits->setPressed (0);
        }
        
        if (Quit->isPressed())
        {
            Quit->setPressed(0);
            device->closeDevice();
        }
        
        if (Continue->isPressed())
        {
            Game->setVisible (false); 
            Options->setVisible (false); 
            Credits->setVisible (false); 
            Quit->setVisible (false);
            Continue->setVisible(false);
            device->getCursorControl()->setVisible (false);
            cameraFPS->setVisible(true);
            //img->setVisible(true);
            
            Continue->setPressed(0);
        }
        
        driver->endScene();
        }
    }
    
    device->drop();
    
    return 0;
}
