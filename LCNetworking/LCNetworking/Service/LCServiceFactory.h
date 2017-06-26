//
//  LCServiceFactory.h
//  LCNetworking
//
//  Created by Agenric on 2017/3/2.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LCService.h"

@interface LCServiceFactory : NSObject

+ (instancetype)sharedInstance;
- (LCService<LCServiceProtocol> *)serviceWithIdentifier:(NSString *)identifier;

@end
