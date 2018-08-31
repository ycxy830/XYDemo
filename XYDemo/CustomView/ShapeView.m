//
//  ShapeView.m
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import "ShapeView.h"

////
////  RKMath.m
////
////  Created by Richard Kirk on 6/23/14.
////  Copyright (c) 2014 Richard Kirk. All rights reserved.
////
//
//#import "RKMath.h"
//
//// normalize value to [0, 1] based on its range [startValue, endValue]
//double normalize(double value, double startValue, double endValue)
//{
//    return (value - startValue) / (endValue - startValue);
//}
//
//// project a normalized value [0, 1] to a given range [start, end]
//double projectNormal(double n, double start, double end)
//{
//    return start + (n * (end - start));
//}
//
//
//double solveLinearEquation(double input, double startValue, double endValue, double outputStart, double outputEnd)
//{
//    return projectNormal(MAX(0, MIN(1, normalize(input, startValue, endValue))), outputStart, outputEnd);
//}
//
//CGSize solveLinearEquationSize(double input, double startValue, double endValue, CGSize outputStart, CGSize outputEnd)
//{
//    double normalizedInput = MAX(0, MIN(1, normalize(input, startValue, endValue)));
//    double width = projectNormal(normalizedInput, outputStart.width, outputEnd.width);
//    double height = projectNormal(normalizedInput, outputStart.height, outputEnd.height);
//    return CGSizeMake(width, height);
//}
//
//CGPoint solveLinearEquationPoint(double input, double startValue, double endValue, CGPoint outputStart, CGPoint outputEnd)
//{
//    double normalizedInput = MAX(0, MIN(1, normalize(input, startValue, endValue)));
//    double x = projectNormal(normalizedInput, outputStart.x, outputEnd.x);
//    double y = projectNormal(normalizedInput, outputStart.y, outputEnd.y);
//    return CGPointMake(x, y);
//}
//
//CGRect solveLinearEquationRect(double input, double startValue, double endValue, CGRect outputStart, CGRect outputEnd)
//{
//    CGRect rect = CGRectZero;
//    rect.size = solveLinearEquationSize(input, startValue, endValue, outputStart.size, outputEnd.size);
//    rect.origin = solveLinearEquationPoint(input, startValue, endValue, outputStart.origin, outputEnd.origin);
//    return rect;
//}
//
//CGPoint CGRectGetCenter(CGRect rect)
//{
//    return CGPointMake(CGRectGetMidX(rect), CGRectGetMidY(rect));
//}

@interface ShapeView ()

@property(nonatomic, assign)int shapeType;
@property(nonatomic, assign)CGRect shapeRect;

@property(nonatomic, assign)int lineWidth;
@property(nonatomic, strong)UIColor *lineColor;
@property(nonatomic, strong)UIColor *fillColor;

@end

@implementation ShapeView

- (ShapeView *)initWithFrame:(CGRect)frame shapeRect:(CGRect)shapeRect shapeType:(int)shapeType lineWidth:(int)lineWidth lineColor:(UIColor *)lineColor fillColor:(UIColor *)fillColor backColor:(UIColor *)backColor
{
    self = [super initWithFrame:frame];
    if(self)
    {
        self.frame = frame;
        self.backgroundColor = backColor;
        
        self.shapeType = shapeType;
        self.shapeRect = shapeRect;
        
        self.lineWidth = lineWidth;
        self.lineColor = lineColor;
        self.fillColor = fillColor;
    }
    
    return self;
}

- (void)dealloc
{
}

- (void)drawRect:(CGRect)rect
{
    [super drawRect:rect];
    
    [self drawArrow:rect];
    return;
    
    CGContextRef contextRef = UIGraphicsGetCurrentContext();
    //CGContextClearRect(contextRef, rect);
    CGContextBeginPath(contextRef);
    
    CGContextSetShouldAntialias(contextRef, YES);
    CGContextSetAllowsAntialiasing(contextRef, YES);
    
    CGContextSetLineWidth(contextRef, self.lineWidth);
    if(self.lineColor)
    {
        CGContextSetStrokeColorWithColor(contextRef, self.lineColor.CGColor);
    }

    CGPoint point = self.shapeRect.origin;
    CGSize size = self.shapeRect.size;
    
    switch(self.shapeType)
    {
        case 1://实线
        case 2://虚线
        {
            if(self.shapeType == 2)
            {
                CGFloat lengths[] = {2, 2};//{10, 10};//表示先绘制10个点，再跳过10个点，如此反复
                //如果把lengths值改为｛10, 20, 10｝，则表示先绘制10个点，跳过20个点，绘制10个点，跳过10个点，再绘制20个点，如此反复
                CGContextSetLineDash(contextRef, 0, lengths, 2);
            }
            
            CGContextMoveToPoint(contextRef, point.x, point.y);
            CGContextAddLineToPoint(contextRef, point.x + size.width, point.y);
        }
            break;
        case 3:
        {
            CGPoint center = CGPointMake(size.width / 2, size.height);
            
            if(self.fillColor)
            {
                CGContextSetFillColorWithColor(contextRef, self.fillColor.CGColor);
            }
            
            CGContextMoveToPoint(contextRef, point.x, point.y + size.height);
            CGContextAddArc(contextRef, center.x, center.y, size.width / 2/* * 0.8*/, 0, 2 * M_PI, 0);
            //CGContextMoveToPoint(contextRef, point.x + size.width, point.y + size.height);
            CGContextAddLineToPoint(contextRef, point.x + self.lineWidth, point.y + size.height);
        }
            break;
    }
    
    CGContextClosePath(contextRef);
    
    if(self.fillColor)
    {
        //CGContextFillPath(contextRef);
        //CGContextStrokePath(contextRef);
        CGContextDrawPath(contextRef, kCGPathFillStroke);
        
        //CGContextBeginPath(contextRef);
        CGContextSetStrokeColorWithColor(contextRef, self.fillColor.CGColor);
        
        CGContextMoveToPoint(contextRef, point.x + self.lineWidth, point.y + size.height);
        CGContextAddLineToPoint(contextRef, point.x + size.width - self.lineWidth, point.y + size.height);
        
        //CGContextClosePath(contextRef);
        CGContextStrokePath(contextRef);
    }
    else
    {
        CGContextStrokePath(contextRef);
    }

#if(0)
    float radius = (rect.size.width/2.0) * 0.80;
    CGPoint center = CGPointMake(rect.size.width/2.0, rect.size.height/2.0);
    
    CGContextSetLineWidth(contextRef, 2.0);
    CGContextAddArc(contextRef, center.x, center.y, radius, 0, 2*M_PI, 0);
    CGContextSetStrokeColorWithColor(contextRef, _strokeColor.CGColor);
    CGContextStrokePath(contextRef);
    
    float finalDegree = _progress * 2 * M_PI - M_PI / 2;
    CGContextSetFillColorWithColor(contextRef, _fillColor.CGColor);
    CGContextMoveToPoint(contextRef, center.x, center.y);
    CGContextAddArc(contextRef, center.x, center.y, radius, -1 * M_PI / 2, finalDegree, 0);
    CGContextClosePath(contextRef);
    CGContextFillPath(contextRef);
#endif
}

- (void)drawArrow:(CGRect)rect
{
    CGContextRef context = UIGraphicsGetCurrentContext();//获得当前context
    
    CGContextBeginPath(context);

    //设置颜色
    if(self.fillColor)
    {
        CGContextSetFillColorWithColor(context, self.fillColor.CGColor);
        //CGContextSetStrokeColorWithColor(context, [UIColor lightGrayColor].CGColor);
        //为了颜色更好区分，对矩形描边
        CGContextFillRect(context, rect);
        //CGContextStrokeRect(context, rect);
    }
    
    //实际line和point的代码
    if(self.lineColor)
    {
        CGContextSetStrokeColorWithColor(context, _lineColor.CGColor);// 设置描边颜色
    }
    CGContextSetLineWidth(context, self.lineWidth);//线的宽度
    CGContextSetLineCap(context, kCGLineCapSquare);//线的顶端
    CGContextSetLineJoin(context, kCGLineJoinRound);//线相交的模式
    
    CGContextMoveToPoint(context, _shapeRect.origin.x + _shapeRect.size.width, _shapeRect.origin.y);
    CGContextAddLineToPoint(context, _shapeRect.origin.x, _shapeRect.origin.y + _shapeRect.size.height / 2);
    CGContextAddLineToPoint(context, _shapeRect.origin.x + _shapeRect.size.width, _shapeRect.origin.y + _shapeRect.size.height);
    
    //CGContextClosePath(context);

    CGContextStrokePath(context);
}

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface UIView(RoundCorner)

@end

@implementation UIView(RoundCorner)

- (void)addRoundCorner:(CGRect)rect cornerRadius:(float)cornerRadius borderColor:(UIColor *)borderColor borderWidth:(float)borderWidth backColor:(UIColor *)backColor
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
        
        //镂空
#if(0)
        UIBezierPath *circlePath = [UIBezierPath bezierPathWithRoundedRect:rect cornerRadius:cornerRadius];//[UIBezierPath bezierPathWithOvalInRect:rect];
#else
        //UIBezierPath *circlePath = [UIBezierPath bezierPathWithRoundedRect:rect byRoundingCorners:UIRectCornerTopLeft | UIRectCornerBottomRight cornerRadii:CGSizeMake(20, 20)];//[UIBezierPath bezierPathWithOvalInRect:rect];
        UIBezierPath *circlePath = [UIBezierPath bezierPath];
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
        
        NSInteger cornerType = UIRectCornerAllCorners;
        if(cornerType & UIRectCornerTopLeft)
        {
            [circlePath moveToPoint:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y)];
        }
        else
        {
            [circlePath moveToPoint:rect.origin];
        }
        
        if(cornerType & UIRectCornerTopRight)
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width - cornerRadius, rect.origin.y)];
            [circlePath addArcWithCenter:CGPointMake(rect.origin.x + rect.size.width - cornerRadius, rect.origin.y + cornerRadius) radius:cornerRadius startAngle:-0.5 * M_PI endAngle:0 clockwise:1];//右上圆弧
        }
        else
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y)];
        }
        
        if(cornerType & UIRectCornerBottomRight)
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height - cornerRadius)];
            [circlePath addArcWithCenter:CGPointMake(rect.origin.x + rect.size.width - cornerRadius, rect.origin.y + rect.size.height - cornerRadius) radius:cornerRadius startAngle:0 endAngle:0.5 * M_PI clockwise:1];//右下圆弧
        }
        else
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height)];
        }
        
        if(cornerType & UIRectCornerBottomLeft)
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + rect.size.height)];
            [circlePath addArcWithCenter:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + rect.size.height - cornerRadius) radius:cornerRadius startAngle:0.5 * M_PI endAngle:M_PI clockwise:1];//左下圆弧
        }
        else
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height)];
        }
        
        if(cornerType & UIRectCornerTopLeft)
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + cornerRadius)];
            [circlePath addArcWithCenter:CGPointMake(rect.origin.x + cornerRadius, rect.origin.y + cornerRadius) radius:cornerRadius startAngle:M_PI endAngle:1.5 * M_PI clockwise:1];//左上圆弧
        }
        else
        {
            [circlePath addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y - value)];
        }
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
                fillLayer.opacity = 1.0;//0.5;
                
                [self.layer addSublayer:fillLayer];
                
                self.clipsToBounds = YES;
            }
        }
    }
}

@end

//UIView中间透明周围半透明(四种方法)
//
//方法一
//
//#import "DrawView.h"
//
//@implementation DrawView
//
//- (instancetype)initWithFrame:(CGRect)frame
//{
//    self = [super initWithFrame:frame];
//    if (self) {
//        //设置 背景为clear
//        self.backgroundColor = [UIColor clearColor];
//        self.opaque = NO;
//    }
//    return self;
//}
//
//- (void)drawRect:(CGRect)rect {
//    
//    [[UIColor colorWithWhite:0 alpha:0.5] setFill];
//    //半透明区域
//    UIRectFill(rect);
//    
//    //透明的区域
//    CGRect holeRection = CGRectMake(100, 200, 200, 200);
//    /** union: 并集
//     CGRect CGRectUnion(CGRect r1, CGRect r2)
//     返回并集部分rect
//     */
//    
//    /** Intersection: 交集
//     CGRect CGRectIntersection(CGRect r1, CGRect r2)
//     返回交集部分rect
//     */
//    CGRect holeiInterSection = CGRectIntersection(holeRection, rect);
//    [[UIColor clearColor] setFill];
//    
//    //CGContextClearRect(ctx, <#CGRect rect#>)
//    //绘制
//    //CGContextDrawPath(ctx, kCGPathFillStroke);
//    UIRectFill(holeiInterSection);
//    
//}
//直接添加使用就行
//
//DrawView *drawView = [[DrawView alloc] initWithFrame:[UIScreen mainScreen].bounds];
//[self.view addSubview:drawView];
//这里写图片描述
//
//方法二
//
//#import "DrawViewArc.h"
//
//@implementation DrawViewArc
//
//- (instancetype)initWithFrame:(CGRect)frame
//{
//    self = [super initWithFrame:frame];
//    if (self) {
//        self.backgroundColor = [UIColor clearColor];
//        self.opaque = NO;
//    }
//    return self;
//}
//
//- (void)drawRect:(CGRect)rect {
//    //中间镂空的矩形框
//    CGRect myRect =CGRectMake(100,100,200, 200);
//    
//    //背景
//    UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:rect cornerRadius:0];
//    //镂空
//    UIBezierPath *circlePath = [UIBezierPath bezierPathWithOvalInRect:myRect];
//    [path appendPath:circlePath];
//    [path setUsesEvenOddFillRule:YES];
//    
//    CAShapeLayer *fillLayer = [CAShapeLayer layer];
//    fillLayer.path = path.CGPath;
//    fillLayer.fillRule = kCAFillRuleEvenOdd;
//    fillLayer.fillColor = [UIColor whiteColor].CGColor;
//    fillLayer.opacity = 0.5;
//    [self.layer addSublayer:fillLayer];
//    
//}
//
//也是直接调用就行
//这里写图片描述
//
//方法三
//
//写到需要添加 透明圆的 view里
//
//- (void)addArc {
//    //中间镂空的矩形框
//    CGRect myRect =CGRectMake(100,100,200, 200);
//    
//    //背景
//    UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:[UIScreen mainScreen].bounds cornerRadius:0];
//    //镂空
//    UIBezierPath *circlePath = [UIBezierPath bezierPathWithOvalInRect:myRect];
//    [path appendPath:circlePath];
//    [path setUsesEvenOddFillRule:YES];
//    
//    CAShapeLayer *fillLayer = [CAShapeLayer layer];
//    fillLayer.path = path.CGPath;
//    fillLayer.fillRule = kCAFillRuleEvenOdd;
//    fillLayer.fillColor = [UIColor whiteColor].CGColor;
//    fillLayer.opacity = 0.5;
//    [self.view.layer addSublayer:fillLayer];
//    
//}
//
//调用
//[self addArc];
//
//方法四
//
//#import "DrawArc.h"
//
//@implementation DrawArc
//
//- (instancetype)initWithFrame:(CGRect)frame
//{
//    self = [super initWithFrame:frame];
//    if (self) {
//        self.backgroundColor = [UIColor clearColor];
//        self.opaque = NO;
//    }
//    return self;
//}
//
//- (void)drawRect:(CGRect)rect {
//    //中间镂空的矩形框
//    CGRect myRect =CGRectMake(100,100,200, 200);
//    
//    CGContextRef ctx = UIGraphicsGetCurrentContext();
//    
//    //背景色
//    //[[UIColor colorWithPatternImage:[UIImage imageNamed:@"1.jpg"]] set];
//    [[UIColor colorWithWhite:0 alpha:0.5] set];
//    CGContextAddRect(ctx, rect);
//    CGContextFillPath(ctx);
//    
//    //设置清空模式
//    /**
//     kCGBlendModeClear,
//     kCGBlendModeCopy,
//     kCGBlendModeSourceIn,
//     kCGBlendModeSourceOut,
//     kCGBlendModeSourceAtop,
//     kCGBlendModeDestinationOver,
//     kCGBlendModeDestinationIn,
//     kCGBlendModeDestinationOut,
//     kCGBlendModeDestinationAtop,
//     kCGBlendModeXOR,
//     kCGBlendModePlusDarker,
//     kCGBlendModePlusLighter
//     */
//    CGContextSetBlendMode(ctx, kCGBlendModeClear);
//    
//    //画圆
//    CGContextAddEllipseInRect(ctx, myRect);
//    
//    //填充
//    CGContextFillPath(ctx);
//    
//}

//#ifndef BASIC_MATHS_HEADER_INCLUDED
//#define BASIC_MATHS_HEADER_INCLUDED
//
//#include <limits>
//#include <math.h>
//#include <stdlib.h>
//
//namespace Geometry
//{
//    inline float Sqrt( float f )
//    {
//        return sqrtf( f );
//    }
//
//    inline double Sqrt( double f )
//    {
//        return sqrt( f );
//    }
//
//    // http://www.codecodex.com/wiki/index.php?title=Calculate_an_integer_square_root
//    inline int Sqrt( int x )
//    {
//        unsigned long op, res, one;
//        op = x;
//        res = 0;
//
//        one = 1 << 30;
//        while (one > op) one >>= 2;
//        while (one != 0) {
//            if (op >= res + one) {
//                op = op - (res + one);
//                res = res +  2 * one;
//            }
//            res >>= 1;
//            one >>= 2;
//        }
//        return(res);
//    }
//
//    inline float Sin( float f )
//    {
//        return sinf(f);
//    }
//
//    inline float Cos( float f )
//    {
//        return cosf(f);
//    }
//
//    inline double Sin( double d )
//    {
//        return sin(d);
//    }
//
//    inline double Cos( double d )
//    {
//        return cos(d);
//    }
//
//    inline int Abs( int i )
//    {
//        return abs(i);
//    }
//
//    inline float Abs( float f )
//    {
//        return fabs(f);
//    }
//
//    inline double Abs( double d )
//    {
//        return fabs(d);
//    }
//
//    inline double Pow( double b, double e )
//    {
//        return pow(b,e);
//    }
//
//    inline float Pow( float b, float e )
//    {
//        return pow(b,e);
//    }
//
//    inline int iPow( int b, int e )
//    {
//        int result = 1;
//        while (e)
//        {
//            if (e & 1)
//                result *= b;
//            e >>= 1;
//            b *= b;
//        }
//        return result;
//    }
//
//    inline int Pow( int b, int e )
//    {
//        return iPow(b,e);
//    }
//}
//
//#endif //BASIC_MATHS_HEADER_INCLUDED



//
//  insist.h
//  Flip
//
//  Created by Finucane on 5/27/14.
//  Copyright (c) 2014 David Finucane. All rights reserved.
//


/*
 easy to type macros for things that should never happen but have to be checked anyway. they can be handled
 in the main loop in a top level exception handler when we get around to it.
 */


#ifdef DEBUG

#define insist(e) if(!(e)) [NSException raise: @"assertion failed." format: @"%@:%d (%s)", [[NSString stringWithCString:__FILE__ encoding:NSUTF8StringEncoding] lastPathComponent], __LINE__, #e]

#else

#define insist(e)((void)(e))

#endif

//
//  g_geometry.h
//  Flip
//
//  Created by Finucane on 5/29/14.
//  Copyright (c) 2014 David Finucane. All rights reserved.
//

#ifndef g_geometry_h
#define g_geometry_h

#import <UIKit/UIKit.h>

CGFloat g_area (CGPoint*points, int num_points);
void g_centroid (CGPoint*points, int num_points, CGFloat*x, CGFloat*y);
void g_move (CGPoint*points, int num_points, CGFloat x, CGFloat y);
void g_rotate (CGPoint*points, int num_points, CGFloat radians);
CGFloat g_magnitude (CGPoint point);
CGFloat g_distance (CGPoint a, CGPoint b);
BOOL g_point_inside_polygon (CGPoint*points, int num_points, CGPoint out_point, CGPoint p);
CGFloat g_intersection (CGPoint a, CGPoint b, CGPoint c, CGPoint d, CGPoint*p);
BOOL g_lines_intersect (CGPoint a, CGPoint b, CGPoint c, CGPoint d);
BOOL g_line_and_circle_intersect (CGPoint a, CGPoint b, CGPoint c, CGFloat radius);
BOOL g_polygon_inside (CGPoint*a, int num_a, CGPoint*b, int num_b);
BOOL g_polygon_intersection (CGPoint*a, int num_a, CGPoint*b, int num_b, BOOL*inside);
double g_normalize_angle (double a);

#endif

//
//  g_geometry.m
//  Flip
//
//  Created by Finucane on 5/29/14.
//  Copyright (c) 2014 David Finucane. All rights reserved.
//

//#include "geometry.h"
//#include "insist.h"

CGFloat g_area (CGPoint*points, int num_points)
{
    insist (points && num_points > 0);
    
    CGFloat a = 0;
    for (int i = 0; i < num_points; i++)
    {
        int n = (i+1) % num_points;
        a += points [i].x * points [n].y - points [n].x * points [i].y;
    }
    return a / 2.0;
}

void g_centroid (CGPoint*points, int num_points, CGFloat*x, CGFloat*y)
{
    insist (points && num_points > 0 && x && y);
    
    *x = *y = 0.0;
    
    CGFloat a = 6.0 * g_area (points, num_points);
    insist (a);
    
    for (int i = 0; i < num_points; i++)
    {
        int n = (i + 1) % num_points;
        *x += (points [i].x + points [n].x) * (points [i].x * points [n].y - points [n].x * points [i].y);
        *y += (points [i].y + points [n].y) * (points [i].x * points [n].y - points [n].x * points [i].y);
    }
    
    *x /= a;
    *y /= a;
}

/*this assumes the polygon is centered at the origin*/
void g_rotate (CGPoint*points, int num_points, CGFloat radians)
{
    insist (points && num_points);
    
    /*do our trigonometry*/
    CGFloat s = sin (radians);
    CGFloat c = cos (radians);
    
    /*rotate*/
    for (int i = 0; i < num_points; i++)
    {
        CGFloat x = points [i].x;
        CGFloat y = points [i].y;
        
        points [i].x = c * x - s * y;
        points [i].y = s * x + c * y;
    }
}

void g_move (CGPoint*points, int num_points, CGFloat x, CGFloat y)
{
    insist (points && num_points > 0);
    
    for (int i = 0; i < num_points; i++)
    {
        points [i].x += x;
        points [i].y += y;
    }
}

CGFloat g_magnitude (CGPoint point)
{
    return sqrt (point.x * point.x + point.y * point.y);
}

CGFloat g_distance (CGPoint a, CGPoint b)
{
    return sqrt ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

/*return:
 < 0 if ab and cd are parallel
 > 1 if ab and cd do not intersect
 [0..1] where along ab the segments intersect
 
 optionally put in "p" the intersection point, if any
 */

CGFloat g_intersection (CGPoint a, CGPoint b, CGPoint c, CGPoint d, CGPoint*p)
{
    CGFloat tcX, tcY, scX, scY, conX, conY, det, con, s, t;
    
    tcX = b.x - a.x; tcY = b.y - a.y;
    scX = c.x - d.x; scY = c.y - d.y;
    conX = c.x - a.x; conY = c.y - a.y;
    
    det = (tcY * scX - tcX * scY);
    if (det == 0)
        return -1; //segments are parallel
    
    con = tcY * conX - tcX * conY;
    s = con/det;
    if (s < 0 || s > 1) return 2; // something > 1
    
    if (tcX != 0)
        t = (conX - s * scX) / tcX;
    else
        t = (conY - s * scY) / tcY;
    if (t < 0 || t > 1) return 2; //something > 1
    
    /*get the intersection point*/
    if (p)
    {
        p->x = a.x + t * (b.x - a.x);
        p->y = a.y + t * (b.y - a.y);
    }
    /*return [0..1]*/
    return t;
}

BOOL g_lines_intersect (CGPoint a, CGPoint b, CGPoint c, CGPoint d)
{
    if (a.x == c.x && a.y == c.y && b.x == d.x && b.y == d.y)
    {
        return YES;
    }
    if (b.x == c.x && b.y == c.y && a.x == d.x && a.y == d.y)
    {
        return YES;
    }
    
    double dd = (d.y - c.y) * (b.x - a.x) - (d.x - c.x) * (b.y - a.y);
    double an = (d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x);
    double bn = (b.x - a.x) * (a.y - c.y) - (b.y - a.y) * (a.x - c.x);
    
    if (dd == 0 && an == 0 && bn == 0) return YES;
    if (dd == 0) return NO;
    
    double ua = an / dd;
    double ub = bn / dd;
    return (ua > 0 && ua < 1 && ub > 0 && ub < 1);
}

/*
 return if ab intersects (or is inside) circle centered at c
 stolen from : http://www.openprocessing.org/sketch/65771
 
 and modified to work in the case where a = b.
 */
BOOL g_line_and_circle_intersect (CGPoint a, CGPoint b, CGPoint c, CGFloat radius)
{
    
    /*if the line is really a point, return point-inside-circle*/
    if (CGPointEqualToPoint (a, b))
    {
        return (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y) <= radius * radius;
    }
    
    /*translate everything to origin*/
    CGFloat A = b.x-a.x; // line segment end point horizontal coordinate
    CGFloat B = b.y-a.y; // line segment end point vertical coordinate
    CGFloat C = c.x-a.x; // circle center horizontal coordinate
    CGFloat D = c.y-a.y; // circle center vertical coordinate
    
    /*if collision is possible...*/
    if ((D*A - C*B)*(D*A - C*B) <= radius*radius*(A*A + B*B))
    {
        /*line segment start point is inside the circle*/
        if (C*C + D*D <= radius*radius)
            return YES;
        
        /*line segment end point is inside the circle*/
        if ((A-C)*(A-C) + (B-D)*(B-D) <= radius*radius)
            return YES;
        
        /*line segment inside circle*/
        if (C*A + D*B >= 0 && C*A + D*B <= A*A + B*B)
            return YES;
    }
    return NO;
}

BOOL g_point_inside_polygon (CGPoint*points, int num_points, CGPoint out_point, CGPoint p)
{
    /*check the point being on a vertex case*/
    for (int i = 0; i < num_points; i++)
    {
        if (p.x == points [i].x && p.y == points [i].y)
            return YES;
    }
    if (out_point.x == 0 && out_point.y == 0)
    {
        /*pick an arbitrary (but nonzero) point outside the poly*/
        CGFloat mx = points [0].x;
        for (int i = 1; i < num_points; i++)
        {
            if (mx < points [i].x)
                mx = points [i].x;
        }
        out_point = CGPointMake (mx + 10.0, 0.0);
    }
    
    /*count the number of intersections along the ray from point to outpoint*/
    int num_intersections = 0;
    for (int i = 0; i < num_points; i++)
    {
        if (g_lines_intersect (points [i], points [(i + 1) % num_points], p, out_point))
            num_intersections++;
    }
    
    /*if the ray crossed an odd number of times the point was inside*/
    return num_intersections % 2;
}


/*see if 2 polygons overlap exactly*/
BOOL polygons_coincide (CGPoint*a, int num_a, CGPoint*b, int num_b)
{
    if (num_a == num_b)
    {
        for (int i = 0; i < num_a; i++)
        {
            int j;
            for (j = 0; j < num_a; j++)
            {
                int n = (j + i) % num_a;
                if (a[j].x != b[n].x || a[j].y != b[n].y)
                    break;
            }
            if (j == num_a)
                return YES;
        }
    }
    
    /*there is no rotation of b that lines up with a*/
    return NO;
}

/*return yes if a is totally inside b. not just coincident*/
BOOL g_polygon_inside (CGPoint*a, int num_a, CGPoint*b, int num_b)
{
    /*handle the pathological case of the 2 polys being exactly stacked*/
    if (polygons_coincide (a, num_a, b, num_b))
        return NO;
    
    /*see if all points in a are inside b*/
    for (int i = 0; i < num_a; i++)
    {
        CGPoint out_point;
        out_point.x = out_point.y = 0;
        if (!g_point_inside_polygon (b, num_b, out_point, a[i]))
            return NO;
    }
    return YES;
}


/*return yes if the 2 polys intersect. assume that one is not totally inside the other
 but they can overlap exactly and this counts as an intersection. return an
 intersection point if there is one.*/


BOOL g_polygon_intersection (CGPoint*a, int num_a, CGPoint*b, int num_b, BOOL*inside)
{
    insist (a && b && num_a > 0 && num_b);
    
    /*first handle the pathological case of the 2 polys being exactly stacked*/
    if (polygons_coincide (a, num_a, b, num_b))
        return YES;
    
    /*now for each segment in a check to see if it intersects a segment in b*/
    for (int i = 0; i < num_a; i++)
    {
        for (int j = 0; j < num_b; j++)
        {
            if (g_lines_intersect (a[i], a[(i+1) % num_a], b[j], b[(j+1) % num_b]))
                return YES;
        }
    }
    return NO;
}
/*make the angle between 0 - 2PI)*/
double g_normalize_angle (double a)
{
    a = fmod (a, 2*M_PI);
    if (a < 0) a += 2*M_PI;
    return a;
}

