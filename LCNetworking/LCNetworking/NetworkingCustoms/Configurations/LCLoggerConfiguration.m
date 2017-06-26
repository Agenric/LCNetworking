//
//  LCLoggerConfiguration.m
//  LCNetworking
//
//  Created by Agenric on 2017/6/26.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import "LCLoggerConfiguration.h"

@implementation LCLoggerConfiguration

- (void)configWithAppType:(LCAppType)appType
{
    switch (appType) {
        case LCAppTypexxx:
            self.appKey = @"xxxxxx";
            self.serviceType = @"xxxxx";
            self.sendLogMethod = @"xxxx";
            self.sendActionMethod = @"xxxxxx";
            self.sendLogKey = @"xxxxx";
            self.sendActionKey = @"xxxx";
            break;
    }
}

@end
