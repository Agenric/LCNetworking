//
//  LCCachedObject.h
//  LCNetworking
//
//  Created by Agenric on 2017/3/2.
//  Copyright © 2017年 LeCarShare. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LCCachedObject : NSObject

@property (nonatomic, copy, readonly) NSData *content;
@property (nonatomic, copy, readonly) NSDate *lastUpdateTime;

@property (nonatomic, assign, readonly) BOOL isOutdated;
@property (nonatomic, assign, readonly) BOOL isEmpty;

- (instancetype)initWithContent:(NSData *)content;
- (void)updateContent:(NSData *)content;


@end
