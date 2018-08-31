//
//  UIView+RoundCorner.m
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import "UIView+RoundCorner.h"

//iOS中drawRect方法实现画圆角矩形，顺时针和逆时针
//
//2014-05-09 20:10 本站整理 浏览(5849)
//iOS中drawRect方法实现画圆角矩形，顺时针和逆时针，有需要的朋友可以参考下。
//
//在iOS中创建自己独特的UIView，需要从UIView继承一个子类，然后重写drawRect方法，里面用GC画自己想要的效果即可。我们这里实现一个圆角矩形的绘制。
//
//注意在画圆弧的时候，用到了CGContextAddArc方法，
//
//CGContextAddArc(CGContextRef c,
//
//                CGFloat x, CGFloat y, CGFloat radius,
//
//                CGFloat startAngle, CGFloat endAngle, int clockwise)
//
//CGContextRef: 图形上下文
//
//x,y: 弧线的原点坐标
//
//radius: 半径
//
//startAngle, endAngle: 开始的弧度,结束的弧度
//
//clockwise: 画弧线的方向(0是逆时针，1是顺时针)
//
//这个方法使用起来还是比较容易混乱的，完全是因为在iOS中y坐标系是进行了反转的，坐标原点在左上角，向下是增长方向（书本上的坐标系y轴方向向上）。注意弧度的正负永远是我们学习数学时的认识，即y坐标系方向向上，x坐标系方向向右，角度是逆时针方向为正。不管顺时针还是逆时针画，最后都是要沿着y坐标系进行一次镜像反转。
//
//好了，直接上代码，先逆时针方向，注意为了更好的坐标点的衔接，逆时针时先画线，再画弧线。从左上角(radius,0)点开始画。
//
//- (void)drawRect:(CGRect)rect
//
//{
//
//    CGFloat width = rect.size.width;
//
//    CGFloat height = rect.size.height;
//
//    // 简便起见，这里把圆角半径设置为长和宽平均值的1/10
//
//    CGFloat radius = (width + height) *
//
//    0.05;
//
//    // 获取CGContext，注意UIKit里用的是一个专门的函数
//
//    CGContextRef context =UIGraphicsGetCurrentContext();
//
//    // 移动到初始点
//
//    CGContextMoveToPoint(context, radius,
//
//                         0);
//
//    // 绘制第1条线和第1个1/4圆弧，右上圆弧
//
//    CGContextAddLineToPoint(context, width - radius,0);
//
//    CGContextAddArc(context, width - radius, radius, radius, -0.5 *M_PI,0.0,
//
//                    0);
//
//    // 绘制第2条线和第2个1/4圆弧，右下圆弧
//
//    CGContextAddLineToPoint(context, width, height - radius);
//
//    CGContextAddArc(context, width - radius, height - radius, radius,0.0,0.5 *
//
//                    M_PI,0);
//
//    // 绘制第3条线和第3个1/4圆弧，左下圆弧
//
//    CGContextAddLineToPoint(context, radius, height);
//
//    CGContextAddArc(context, radius, height - radius, radius,0.5 *M_PI,
//
//                    M_PI,0);
//
//    // 绘制第4条线和第4个1/4圆弧，左上圆弧
//
//    CGContextAddLineToPoint(context,
//
//                            0, radius);
//
//    CGContextAddArc(context, radius, radius, radius,M_PI,1.5 *
//
//                    M_PI,0);
//
//    // 闭合路径
//
//    CGContextClosePath(context);
//
//    // 填充半透明红色
//
//    CGContextSetRGBFillColor(context,1.0,0.0,0.0,0.5);
//
//    CGContextDrawPath(context,kCGPathFill);
//
//}
//
//下面是顺时针方向的实现，注意这时候是先画弧线，再画直线，另外注意CGContextAddArc方法中start弧度和end弧度以及原点的变化。这里也是从左上角(radius,0)点开始画。
//
//- (void)drawRect:(CGRect)rect
//
//{
//
//    CGFloat width = rect.size.width;
//
//    CGFloat height = rect.size.height;
//
//    // 简便起见，这里把圆角半径设置为长和宽平均值的1/10
//
//    CGFloat radius = (width + height) *
//
//    0.05;
//
//    // 获取CGContext，注意UIKit里用的是一个专门的函数
//
//    CGContextRef context =UIGraphicsGetCurrentContext();
//
//    // 移动到初始点
//
//    CGContextMoveToPoint(context, radius,
//
//                         0);
//
//    // 绘制第1个1/4圆弧和第1条线,左上圆弧
//
//    CGContextAddArc(context, radius, radius, radius,1.5 *M_PI,
//
//                    M_PI,1);
//
//    CGContextAddLineToPoint(context,
//
//                            0, height - radius);
//
//    // 绘制第2个1/4圆弧和第2条线，左下圆弧
//
//    CGContextAddArc(context, radius, height - radius, radius,M_PI,0.5 *
//
//                    M_PI,1);
//
//    CGContextAddLineToPoint(context, width - radius, height);
//
//    // 绘制第3个1/4圆弧和第3条线，右下圆弧
//
//    CGContextAddArc(context, width - radius, height - radius, radius,0.5 *M_PI,
//
//                    0,1);
//
//    CGContextAddLineToPoint(context, width,height - radius);
//
//    // 绘制第4个1/4圆弧和第4条线,右上圆弧
//
//    CGContextAddArc(context, width - radius, radius, radius,0, -0.5 *M_PI,1);
//
//    CGContextAddLineToPoint(context, radius,0);
//
//    // 闭合路径
//
//    CGContextClosePath(context);
//
//    // 填充半透明红色
//
//    CGContextSetRGBFillColor(context,1.0,0.0,0.0,0.5);
//
//    CGContextDrawPath(context,kCGPathFill);
//
//}

@implementation UIView(RoundCorner)

- (void)addRoundCorner:(CGRect)rect cornerRadius:(float)cornerRadius rectCorner:(UIRectCorner)rectCorner borderColor:(UIColor *)borderColor borderWidth:(float)borderWidth backColor:(UIColor *)backColor
{
    //float value = 1 + borderWidth;
    //UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:CGRectMake(-value, -value, rect.size.width + value + value, rect.size.height + value + value) cornerRadius:0];
    float value = 1 + borderWidth / 2;
    UIBezierPath *path = [UIBezierPath bezierPathWithRect:CGRectMake(-value, -value, rect.size.width + value + value, rect.size.height + value + value)];
    if(path)
    {
        if(borderWidth > 0)
        {
            value = borderWidth / 2;
            rect.origin = CGPointMake(value, value);//CGPointMake(borderWidth, borderWidth);
            rect.size = CGSizeMake(rect.size.width - value - value, rect.size.height - value - value);//CGSizeMake(rect.size.width - borderWidth - borderWidth, rect.size.height - borderWidth - borderWidth);
        }
        else
        {
            rect.origin = CGPointZero;
        }
        
        UIBezierPath *circlePath;
#if(1)
        circlePath = [UIBezierPath bezierPath];
        //        [circlePath moveToPoint:rect.origin];
        //        [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y)];
        //        [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height)];
        //        [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height)];
        //        [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y - value)];
        
        //        [circlePath moveToPoint:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y)];
        //        [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width - cornerRadius, rect.origin.y)];
        //        [circlePath addArcWithCenter:CGPointMake(rect.size.width - cornerRadius, rect.origin.y + cornerRadius) radius:cornerRadius startAngle:-0.5 * M_PI endAngle:0 clockwise:0];
        //        [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height - cornerRadius)];
        //        [circlePath addArcWithCenter:CGPointMake(rect.origin.x + rect.size.width - cornerRadius, rect.origin.y + rect.size.height - cornerRadius) radius:cornerRadius startAngle:0 endAngle:0.5 * M_PI clockwise:0];
        //        [circlePath addLineToPoint:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + rect.size.height)];
        //        [circlePath addArcWithCenter:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + rect.size.height - cornerRadius) radius:cornerRadius startAngle:0.5 * M_PI endAngle:M_PI clockwise:0];
        //        [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + cornerRadius)];
        //        [circlePath addArcWithCenter:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + cornerRadius) radius:cornerRadius startAngle:M_PI endAngle:1.5 * M_PI clockwise:0];
        
        //NSInteger cornerType = UIRectCornerAllCorners;
        if(rectCorner & UIRectCornerTopLeft)
        {
            [circlePath moveToPoint:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y)];
        }
        else
        {
            [circlePath moveToPoint:rect.origin];
        }
        
        if(rectCorner & UIRectCornerTopRight)
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width - cornerRadius, rect.origin.y)];
            [circlePath addArcWithCenter:CGPointMake(rect.origin.x + rect.size.width - cornerRadius, rect.origin.y + cornerRadius) radius:cornerRadius startAngle:-0.5 * M_PI endAngle:0 clockwise:1];//右上圆弧
        }
        else
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y)];
        }
        
        if(rectCorner & UIRectCornerBottomRight)
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height - cornerRadius)];
            [circlePath addArcWithCenter:CGPointMake(rect.origin.x + rect.size.width - cornerRadius, rect.origin.y + rect.size.height - cornerRadius) radius:cornerRadius startAngle:0 endAngle:0.5 * M_PI clockwise:1];//右下圆弧
        }
        else
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height)];
        }
        
        if(rectCorner & UIRectCornerBottomLeft)
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + rect.size.height)];
            [circlePath addArcWithCenter:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + rect.size.height - cornerRadius) radius:cornerRadius startAngle:0.5 * M_PI endAngle:M_PI clockwise:1];//左下圆弧
        }
        else
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height)];
        }
        
        if(rectCorner & UIRectCornerTopLeft)
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + cornerRadius)];
            [circlePath addArcWithCenter:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + cornerRadius) radius:cornerRadius startAngle:M_PI endAngle:1.5 * M_PI clockwise:1];//左上圆弧
        }
        else
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y - value)];
        }
#else
        //镂空
        //circlePath = [UIBezierPath bezierPathWithRoundedRect:rect cornerRadius:cornerRadius];//[UIBezierPath bezierPathWithOvalInRect:rect];
        circlePath = [UIBezierPath bezierPathWithRoundedRect:rect byRoundingCorners:UIRectCornerTopLeft | UIRectCornerBottomRight cornerRadii:CGSizeMake(20, 20)];//[UIBezierPath bezierPathWithOvalInRect:rect];
#endif
        
        if(circlePath)
        {
            [path appendPath:circlePath];
            //[path setUsesEvenOddFillRule:YES];
            
            CAShapeLayer *fillLayer = [CAShapeLayer layer];
            if(fillLayer)
            {
                if(borderColor)
                {
                    fillLayer.lineWidth = borderWidth;
                    fillLayer.strokeColor = borderColor.CGColor;
                }
                fillLayer.path = path.CGPath;
                fillLayer.fillRule = kCAFillRuleEvenOdd;
                if(backColor)
                {
                    fillLayer.fillColor = backColor.CGColor;
                }
                else
                {
                    fillLayer.fillColor = [UIColor clearColor].CGColor;
                }
                fillLayer.opacity = 1.0;//0.5;
                
                [self.layer addSublayer:fillLayer];
                
                self.clipsToBounds = YES;
            }
        }
    }
}

@end
