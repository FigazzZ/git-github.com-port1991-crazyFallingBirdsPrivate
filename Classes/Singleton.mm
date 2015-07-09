//
//  Singleton.m
//  FallingBirdsGame
//
//  Created by user on 08/07/15.
//
//

#import "Singleton.h"
#import <Foundation/Foundation.h>
#import "AppController.h"

void Singleton::showAds()
{
    /*
    if(defaults->getIntegerForKey(SDK_NUMBER_KEY, 1) % 3 == 0)
    {
        defaults->setIntegerForKey(SDK_NUMBER_KEY, 0);
        this->showApplovinBanner();
    }
    else
    {
        defaults->setIntegerForKey(SDK_NUMBER_KEY, defaults->getIntegerForKey(SDK_NUMBER_KEY, 1) + 1);
        this->showChartboostBanner();
    }*/
    this->showChartboostBanner();
}

void Singleton::showApplovinBanner()
{
    AppController *appController = (AppController*)[UIApplication sharedApplication].delegate;
    [appController showApplovin];
}

void Singleton::showChartboostBanner()
{
    AppController *appController = (AppController*)[UIApplication sharedApplication].delegate;
    [appController.viewController showChartboost];
}

void Singleton::buyRemoveAds()
{
    AppController *appController = (AppController*)[UIApplication sharedApplication].delegate;
    [appController buyRemoveAds];
}

void Singleton::setRemoveAds()
{
    defaults->setBoolForKey(REMOVE_ADS_KEY, true);
}

bool Singleton::isAdsRemoved() const
{
    return defaults->getBoolForKey(REMOVE_ADS_KEY, false);
}

void Singleton::restorePurchases()
{
    AppController *appController = (AppController*)[UIApplication sharedApplication].delegate;
    [appController restorePurchases];
}