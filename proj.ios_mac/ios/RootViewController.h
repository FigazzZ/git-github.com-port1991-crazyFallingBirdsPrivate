/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>
#import <Chartboost/Chartboost.h>
#import <Chartboost/CBNewsfeed.h>
#import <CommonCrypto/CommonCrypto.h>
#import <AdSupport/AdSupport.h>

#define CHARTBOOST_APP_ID @"559d217a43150f600d559fd7"
#define CHARTBOOST_APP_SIGN @"110b58790deffeba97ed3d7f6c06054c990b113a"

//#define CHARTBOOST_APP_ID @"4f21c409cd1cb2fb7000001b"
//#define CHARTBOOST_APP_SIGN @"92e2de2fd7070327bdeb54c15a5295309c6fcd2d"

@interface RootViewController : UIViewController <GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, ChartboostDelegate> {

}
- (BOOL) prefersStatusBarHidden;

-(void) initChartboost;
-(void) showChartboost;

@end
