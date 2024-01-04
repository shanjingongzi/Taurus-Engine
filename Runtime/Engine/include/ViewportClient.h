#pragma once

class ViewportClient
{
public:
    virtual ~ViewportClient(){}
    virtual void Precache(){}
    virtual void RedrawRequested(Viewport *viewport);
    virtual void RequestInvalididateHitProxy(Viewport *viepwort);
    virtual void Draw(Viewport*viewport,Canvas*canvas){}
    virtual bool ProcessScreenShots(Viewport*viewport){return false;}
    virtual World*GetWorld()const{return nullptr;}
    virtual struct EngineshowFlags *GetEngineShowFlags(){return nullptr;}

    virtual bool InputKey(const InputkeyEventArgs&eventArgs);



    //mouseEvent

    void MouseEnter(Viewport *viewport,int32 x,int32 y);
    void MouseLeave(Viewport*viewport);
    void MouseMove(Viewport*viewport,int32 x,int32 y);
}