//
//  LCLocationManager.h
//  LCNetworking
//
//  Created by Agenric on 2017/3/3.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef NS_ENUM(NSUInteger, LCLocationManagerLocationServiceStatus) {
    LCLocationManagerLocationServiceStatusDefault,               //默认状态
    LCLocationManagerLocationServiceStatusOK,                    //定位功能正常
    LCLocationManagerLocationServiceStatusUnknownError,          //未知错误
    LCLocationManagerLocationServiceStatusUnAvailable,           //定位功能关掉了
    LCLocationManagerLocationServiceStatusNoAuthorization,       //定位功能打开，但是用户不允许使用定位
    LCLocationManagerLocationServiceStatusNoNetwork,             //没有网络
    LCLocationManagerLocationServiceStatusNotDetermined          //用户还没做出是否要允许应用使用定位功能的决定，第一次安装应用的时候会提示用户做出是否允许使用定位功能的决定
};

typedef NS_ENUM(NSUInteger, LCLocationManagerLocationResult) {
    LCLocationManagerLocationResultDefault,              //默认状态
    LCLocationManagerLocationResultLocating,             //定位中
    LCLocationManagerLocationResultSuccess,              //定位成功
    LCLocationManagerLocationResultFail,                 //定位失败
    LCLocationManagerLocationResultParamsError,          //调用API的参数错了
    LCLocationManagerLocationResultTimeout,              //超时
    LCLocationManagerLocationResultNoNetwork,            //没有网络
    LCLocationManagerLocationResultNoContent             //API没返回数据或返回数据是错的
};

@interface LCLocationManager : NSObject

@property (nonatomic, assign, readonly) LCLocationManagerLocationResult locationResult;
@property (nonatomic, assign,readonly) LCLocationManagerLocationServiceStatus locationStatus;
@property (nonatomic, copy, readonly) CLLocation *currentLocation;

+ (instancetype)sharedInstance;

- (void)startLocation;
- (void)stopLocation;
- (void)restartLocation;

@end
