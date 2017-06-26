//
//  LCUDIDGenerator.h
//  LCNetworking
//
//  Created by Agenric on 2017/3/1.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface LCUDIDGenerator : NSObject

+ (id)sharedInstance;

- (NSString *)UDID;
- (void)saveUDID:(NSString *)udid;

@end
