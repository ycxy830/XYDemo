//
//  ShapeView.h
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ShapeView : UIView

- (ShapeView *)initWithFrame:(CGRect)frame shapeRect:(CGRect)shapeRect shapeType:(int)shapeType lineWidth:(int)lineWidth lineColor:(UIColor *)lineColor fillColor:(UIColor *)fillColor backColor:(UIColor *)backColor;

@end
