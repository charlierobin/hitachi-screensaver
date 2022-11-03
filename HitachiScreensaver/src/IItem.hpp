#ifndef IItem_hpp
#define IItem_hpp

class IItem
{
public:
    
    virtual void update( float, std::vector<IItem *>, int ){};
    
    virtual void draw( bool ){};

};

#endif /* IItem_hpp */
