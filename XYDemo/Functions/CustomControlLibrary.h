//
//  CustomControlLibrary.h
//  CustomControlLibrary
//
//  Created by luck on 2018/5/11.
//  Copyright © 2018年 luck. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CustomControlDefine.h"

@interface CustomControlLibrary : NSObject

+ (id)performTarget:(NSString *)targetName action:(NSString *)actionName params:(NSArray *)params additionParams:(NSDictionary *)additionParams isClassAction:(BOOL)isClassAction shouldCacheTarget:(BOOL)shouldCacheTarget;

@end
