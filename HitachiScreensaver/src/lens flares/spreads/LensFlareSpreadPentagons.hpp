#ifndef LensFlareSpreadPentagons_hpp
#define LensFlareSpreadPentagons_hpp

 #include "LensFlareSpread.hpp"

class LensFlareSpreadPentagons : public LensFlareSpread
{
    
public:
    
    LensFlareSpreadPentagons( int numberOfElements ): LensFlareSpread( numberOfElements, "pentagon.jpg" ){};
    
};

#endif /* LensFlareSpreadPentagons_hpp */
