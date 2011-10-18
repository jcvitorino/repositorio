class Tree : public virtual Container
{
    class Iter;
public:
    virtual Object& Key () const = 0;
    virtual Tree& Subtree (unsigned int) const = 0;
    virtual bool IsEmpty () const = 0;
    virtual bool IsLeaf () const = 0;
    virtual unsigned int Degree () const = 0;
    virtual int Height () const;
    virtual void DepthFirstTraversal (PrePostVisitor&) const;
    virtual void BreadthFirstTraversal (Visitor&) const;
    void Accept (Visitor&) const;
};
