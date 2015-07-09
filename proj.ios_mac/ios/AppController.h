

#import <UIKit/UIKit.h>

#import "ALSdk.h"
#import "ALInterstitialAd.h"

#define APPLE_ID @"1011427919"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,  ALAdDisplayDelegate, ALAdLoadDelegate, ALAdUpdateObserver, ALAdVideoPlaybackDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;


-(void)setAppiraterSettings;

-(void) initApplovin;
-(void) showApplovin;

-(void) buyRemoveAds;
-(void) removeAdsWasSuccesfull;

-(void) restorePurchases;

@end

