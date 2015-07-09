
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import "MKStoreObserver.h"



@interface MKStoreManager : NSObject<SKProductsRequestDelegate> {

	NSMutableArray *purchasableObjects;
	MKStoreObserver *storeObserver;
	
}

@property (nonatomic, retain) NSMutableArray *purchasableObjects;
@property (nonatomic, retain) MKStoreObserver *storeObserver;

- (void) requestProductData;
- (void) buyFeatureRemoveAds;


// do not call this directly. This is like a private method
- (void) buyFeature:(NSString*) featureId;

- (void) failedTransaction: (SKPaymentTransaction *)transaction;
-(void) provideContent: (NSString*) productIdentifier;

+ (MKStoreManager*)sharedManager;

+ (BOOL) featureRemoveAdsPurchased;
+(void) loadPurchases;
+(void) updatePurchases;
-(void)restorePurchase;
-(void) setLockKey: (NSString*) productIdentifier;

@end
