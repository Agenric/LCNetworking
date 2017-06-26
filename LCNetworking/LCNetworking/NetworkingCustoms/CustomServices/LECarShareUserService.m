//
//  LECarShareUserService.m
//  LCNetworking
//
//  Created by Agenric on 2017/3/3.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import "LECarShareUserService.h"
#import "LCAppContext.h"

@implementation LECarShareUserService

#pragma mark - CTServiceProtocal
- (BOOL)isOnline {
    return [LCAppContext sharedInstance].isOnline;
}

- (NSString *)offlineApiBaseUrl {
    return @"http://portal.lecarshare.com";
}

- (NSString *)onlineApiBaseUrl {
    return @"http://portal.lecarx.com";
}

- (NSString *)offlineApiVersion {
    return @"v3";
}

- (NSString *)onlineApiVersion {
    return @"v3";
}

- (NSString *)onlinePublicKey {
    return @"";
}

- (NSString *)offlinePublicKey {
    return @"";
}

- (NSString *)onlinePrivateKey {
    return @"";
}

- (NSString *)offlinePrivateKey {
    return @"";
}

@end
