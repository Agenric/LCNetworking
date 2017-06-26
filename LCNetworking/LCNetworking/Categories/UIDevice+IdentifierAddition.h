//
//  UIDevice+IdentifierAddition.h
//  LCNetworking
//
//  Created by Agenric on 2017/2/28.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIDevice (IdentifierAddition)

- (NSString *)LC_uuid;
- (NSString *)LC_udid;
- (NSString *)LC_macaddress;
- (NSString *)LC_macaddressMD5;
- (NSString *)LC_machineType;
- (NSString *)LC_ostype;//显示“ios6，ios5”，只显示大版本号
- (NSString *)LC_createUUID;

@end
