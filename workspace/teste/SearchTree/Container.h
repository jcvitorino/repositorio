class Container : public virtual Object, public virtual Ownership
{
protected:
    unsigned int count;

    Container ();
public:
    virtual unsigned int Count () const;
    virtual bool IsEmpty () const;
    virtual bool IsFull () const;
    virtual HashValue Hash () const;
    virtual void Put (ostream&) const;
    virtual Iterator& NewIterator () const;

    virtual void Purge () = 0;
    virtual void Accept (Visitor&) const = 0;
};
