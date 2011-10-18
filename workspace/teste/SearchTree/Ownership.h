class Ownership
{
    bool isOwner;
protected:
    Ownership () : isOwner (true)
	{}
    Ownership (Ownership& arg) : isOwner (arg.isOwner)
	{ arg.isOwner = false; }
public:
    void AssertOwnership ()
	{ isOwner = true; }
    void RescindOwnership ()
	{ isOwner = false; }
    bool IsOwner () const
	{ return isOwner; }
};
