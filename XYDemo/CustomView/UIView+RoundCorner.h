//
//  UIView+RoundCorner.h
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIView(RoundCorner)

- (void)addRoundCorner:(CGRect)rect cornerRadius:(float)cornerRadius rectCorner:(UIRectCorner)rectCorner borderColor:(UIColor *)borderColor borderWidth:(float)borderWidth backColor:(UIColor *)backColor;

@end
