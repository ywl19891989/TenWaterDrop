//
//  Constants.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#ifndef __TenWaterDrop__Constants__
#define __TenWaterDrop__Constants__

class Constants {
public:
    
    static bool isMusicEnabled();
    
    static void enableMusic();
    static void disableMusic();
    
    static void init();
    
private:
    static bool _isMusicEnabled;
    static const char * MUSICENABLE_KEY;
    
    static void updateConfig();
    
    Constants();
};

#endif /* defined(__TenWaterDrop__Constants__) */
