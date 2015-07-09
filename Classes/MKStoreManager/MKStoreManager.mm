

#import "MKStoreManager.h"
#import "AppController.h"

@implementation MKStoreManager

@synthesize purchasableObjects;
@synthesize storeObserver;

static NSString *featureRemoveAds = @"com.portgames.crazyfallingbirds.removeAds";
BOOL featuresRemoveAdsPurchased;


static MKStoreManager* _sharedStoreManager; // self

- (void)dealloc
{
	[_sharedStoreManager release];
	[storeObserver release];
	[super dealloc];
}

+ (BOOL) featureRemoveAdsPurchased   {
    return featuresRemoveAdsPurchased;
}

+ (MKStoreManager*)sharedManager
{
	NSLog(@"pass sharedManager");
	@synchronized(self) {
		
        if (_sharedStoreManager == nil) {
			
            
            _sharedStoreManager = [[MKStoreManager alloc] init]; // assignment not done here
			_sharedStoreManager.purchasableObjects = [[NSMutableArray alloc] init];			
			[_sharedStoreManager requestProductData];
			
			[MKStoreManager loadPurchases];
			_sharedStoreManager.storeObserver = [[MKStoreObserver alloc] init];
			[[SKPaymentQueue defaultQueue] addTransactionObserver:_sharedStoreManager.storeObserver];
        }
    }
    
    return _sharedStoreManager;
}

#pragma mark Singleton Methods

+ (id)allocWithZone:(NSZone *)zone
{
    @synchronized(self)
    {
        if (_sharedStoreManager == nil)
        {
            _sharedStoreManager = [super allocWithZone:zone];			
            return _sharedStoreManager;  // assignment and return on first allocation
        }
    }

    return nil; //on subsequent allocation attempts return nil	
}


- (id)copyWithZone:(NSZone *)zone
{
    return self;	
}

- (id)retain
{	
    return self;	
}

- (unsigned int)retainCount
{
    return UINT_MAX;  //denotes an object that cannot be released
}

- (void)release
{
    //do nothing
}

- (id)autorelease
{
    return self;	
}

- (void) requestProductData
{
    SKProductsRequest *request= [[SKProductsRequest alloc] initWithProductIdentifiers:
								 [NSSet setWithObjects:
                                  featureRemoveAds,
								  nil]]; // add any other product here
	request.delegate = self;
	[request start];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
	[purchasableObjects addObjectsFromArray:response.products];
	// populate your UI Controls here
	for(int i=0;i<[purchasableObjects count];i++)
	{
		
		SKProduct *product = [purchasableObjects objectAtIndex:i];
		NSLog(@"Feature: %@, Cost: %f, ID: %@",[product localizedTitle],
			  [[product price] doubleValue], [product productIdentifier]);
	}
	
	[request autorelease];
}

- (void) buyFeature:(NSString*) featureId
{
	if ([SKPaymentQueue canMakePayments])
	{
		SKPayment *payment = [SKPayment paymentWithProductIdentifier:featureId];
		[[SKPaymentQueue defaultQueue] addPayment:payment];
	}
	else
	{
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Falling Dragon" message:@"You are not authorized to purchase from AppStore"
													   delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
		[alert show];
		[alert release];
	}
}

- (void) buyFeatureRemoveAds
{
    [self buyFeature:featureRemoveAds];
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction
{
	NSString *messageToBeShown = [NSString stringWithFormat:@"Reason: %@, You can try: %@", [transaction.error localizedFailureReason], [transaction.error localizedRecoverySuggestion]];
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Unable to complete your purchase" message:messageToBeShown
												   delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
	[alert show];
	[alert release];
}

-(void) provideContent: (NSString*) productIdentifier
{
    if([productIdentifier isEqualToString:featureRemoveAds])
        featuresRemoveAdsPurchased = YES;
    
	[MKStoreManager updatePurchases];
    
}

+(void) loadPurchases 
{
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    
    featuresRemoveAdsPurchased = [userDefaults boolForKey:featureRemoveAds];
}

+(void) updatePurchases
{
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
	
    featuresRemoveAdsPurchased = [userDefaults boolForKey:featureRemoveAds];
}

- (void) restorePurchase
{
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];       //BE BACK!!
}

- (void) setLockKey:(NSString *)productIdentifier
{
    if([productIdentifier isEqualToString:featureRemoveAds])    {
        AppController *appController = (AppController*)[UIApplication sharedApplication].delegate;
        [appController removeAdsWasSuccesfull];
    }
}

@end
