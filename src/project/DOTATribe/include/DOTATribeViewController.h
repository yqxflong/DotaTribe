#ifndef  _DOTATRIBE_DOTATRIBEVIEWCONTROLLER_H_
#define  _DOTATRIBE_DOTATRIBEVIEWCONTROLLER_H_


#import <UIKit/UIKit.h>
#ifdef kSDK_CYOU_ENABEL
#import <iAd/iAd.h>
#endif

@interface DOTATribeViewController:UIViewController
#ifdef kSDK_CYOU_ENABEL
<ADBannerViewDelegate>
#endif
{
#ifdef kSDK_CYOU_ENABEL
    ADBannerView* adView;
    BOOL bannerIsVisible;
#endif
};

-(void)showAd;
-(void)hideAd;

@end


#endif
