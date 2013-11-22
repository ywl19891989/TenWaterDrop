//
//  AdUtil.cpp
//  TenWaterDrop
//
//  Created by wenlong on 13-11-22.
//
//

#include "AdUtil.h"
#include "cocos2d.h"

using namespace cocos2d;

const char* AdUtil::_admodID = "a1528df67decdb9";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "ProtocolAds.h"
#include "PluginManager.h"

using namespace cocos2d::plugin;

void AdUtil::showAd(){
    ProtocolAds* m_pAdmob =
    dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin(
                                                                        "AdsAdmob"));
	TAdsDeveloperInfo devInfo;
	devInfo["AdmobID"] = _admodID;
	m_pAdmob->configDeveloperInfo(devInfo);
	m_pAdmob->setAdsListener(NULL);
	m_pAdmob->showAds(ProtocolAds::kBannerAd, 0, ProtocolAds::kPosBottomRight);
}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


void AdUtil::showAd(){
    CCLOG("show admob id %s", _admodID);
}

#endif
