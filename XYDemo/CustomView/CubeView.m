//
//  CubeView.m
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import "CubeView.h"

//DEGREES_TO_RADIANS
#define kDegree2Radians(degrees) degrees * 0.0174532925199432//M_PI / 180.0
#define kRadians2Degree(radians) radians * 57.295779513082325//180.0 / M_PI

//// 弧度转角度
//#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / M_PI))
//// 角度转弧度
//#define DEGREES_TO_RADIANS(angle) ((angle) / 180.0 * M_PI)

const CGFloat kPanScale = 1./100.;

@interface CubeView ()

@property(nonatomic, readwrite, strong)UIView *topView;
@property(nonatomic, readwrite, strong)UIView *bottomView;
@property(nonatomic, readwrite, strong)UIView *leftView;
@property(nonatomic, readwrite, strong)UIView *rightView;
@property(nonatomic, readwrite, strong)UIView *frontView;
@property(nonatomic, readwrite, strong)UIView *backView;

@property(nonatomic, assign)float degrees;

@property(nonatomic, assign)float itemWidth;
@property(nonatomic, assign)float itemSpace;

@property(nonatomic, assign)NSInteger numberOfItems;
@property(nonatomic, assign)BOOL wrapEnabled;

@end

@implementation CubeView

static CATransform3D MakePerspetiveTransform()
{
    CATransform3D perspective = CATransform3DIdentity;
    perspective.m34 = -1./2000.;
    return perspective;
}

//这个函数的实现原理要参考计算机图形学的3D变换部分，以后再做解释。现在只需要了解接口的含义，center指的是相机 的位置，相机的位置是相对于要进行变换的CALayer的来说的，原点是CALayer的anchorPoint在整个CALayer的位置，例如CALayer的大小是(100, 200), anchorPoint值为(0.5, 0.5)，此时anchorPoint在整个CALayer中的位置就是(50, 100)，正中心的位置。传入透视变换的相机位置为(0, 0)，那么相机所在的位置相对于CALayer就是(50, 100)。如果希望相机在左上角，则需要传入(-50, -100)。disZ表示的是相机离z=0平面（也可以理解为屏幕）的距离。
CATransform3D CATransform3DMakePerspective(CGPoint center, float disZ)
{
    CATransform3D transToCenter = CATransform3DMakeTranslation(-center.x, -center.y, 0);
    CATransform3D transBack = CATransform3DMakeTranslation(center.x, center.y, 0);
    CATransform3D scale = CATransform3DIdentity;
    scale.m34 = -1.0f / disZ;
    
    return CATransform3DConcat(CATransform3DConcat(transToCenter, scale), transBack);
}

CATransform3D CATransform3DPerspect(CATransform3D t, CGPoint center, float disZ)
{
    return CATransform3DConcat(t, CATransform3DMakePerspective(center, disZ));
}

//- (CALayer *)layerWithColor:(UIColor *)color transform:(CATransform3D)transform
//{
//    CALayer *layer = [CALayer layer];
//    layer.backgroundColor = [color CGColor];
//    layer.bounds = CGRectMake(0, 0, kSize, kSize);
//    layer.position = self.view.center;
//    layer.transform = transform;
//    [self.view.layer addSublayer:layer];
//    return layer;
//}

- (UIView *)viewWithRect:(CGRect)rect backColor:(UIColor *)color transform:(CATransform3D)transform
{
    UIView *view = [[UIView alloc] initWithFrame:rect];
    if(view)
    {
        view.alpha = 0.5;
        view.backgroundColor = color;
        view.layer.transform = transform;
        
        [self addSubview:view];
    }
    
    return view;
}

- (CubeView *)initWithFrame:(CGRect)frame degrees:(float)degrees rotatePoint:(CGPoint)rotatePoint
{
    self = [super initWithFrame:frame];
    if(self)
    {
        self.frame = frame;//通过runtime调用initWithFrame并没有成功设置frame
        //self.backgroundColor = [UIColor grayColor];
        
        CGRect rect = frame;
        rect.origin = CGPointZero;
        
        float translate = frame.size.width / 2;

#if(1)
        [self cubeTest:rect];
        
        return self;
#if(0)
        translate = 0;
        self.degrees = degrees;
        
//        CATransform3D transform;
//        transform = CATransform3DMakeTranslation(0, -translate, 0);
//        transform = CATransform3DRotate(transform, kDegree2Radians(degrees), 0, 1.0, 0);
//        self.topView = [self viewWithRect:rect backColor:[UIColor redColor] transform:transform];
//
//        transform = CATransform3DMakeTranslation(0, translate, 0);
//        transform = CATransform3DRotate(transform, kDegree2Radians(degrees), 0, 1.0, 0);
//        self.bottomView = [self viewWithRect:rect backColor:[UIColor greenColor] transform:transform];
//
//        self.layer.sublayerTransform = MakePerspetiveTransform();
//
//        NSTimer *timer = [NSTimer timerWithTimeInterval:1.0 repeats:YES block:^(NSTimer * _Nonnull timer) {
//            float angle = self.degrees + 10;
//            if(angle > 360)
//            {
//                angle = 0;
//            }
//            self.degrees = angle;
//
//            CATransform3D transform;
//            transform = CATransform3DMakeTranslation(0, -translate, 0);
//            transform = CATransform3DRotate(transform, angle, 0, 1, 0);
//            //self.layer.sublayerTransform = transform;
//            //self.topView.layer.transform = transform;
//            //self.bottomView.layer.transform = transform;
//            self.layer.transform = transform;
//
//            self.topView.backgroundColor = [UIColor greenColor];
//            self.bottomView.backgroundColor = [UIColor redColor];
//
//            //[self setNeedsDisplay];
//            //[self.topView setNeedsDisplay];
//            //[self.bottomView setNeedsDisplay];
//        }];
//        [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
        
        //因为翻转，使图片的不同部分离屏幕距离不同，近大远小的效果使立体感大大提升。饶Z轴的旋转不因为透视产生变化，因为所有的点离屏幕距离相同，所以不会产生近大远小的透视感。
//        CATransform3D rotate = CATransform3DMakeRotation(M_PI / 6, 1, 0, 0);
//        rotate = CATransform3DMakeRotation(M_PI / 6, 0, 1, 0);
//        CATransform3D transform = CATransform3DPerspect(rotate, CGPointMake(0, 0), 200);
//        self.topView = [self viewWithRect:rect backColor:[UIColor redColor] transform:transform];
        
        float angle = kDegree2Radians(degrees);
        translate = rect.size.width / 2;
        
        //使用四张同样大小的图片围成一个框，让这个框动画旋转。
        CATransform3D move = CATransform3DMakeTranslation(0, 0, translate);
        CATransform3D back = CATransform3DMakeTranslation(0, 0, -translate);

        CATransform3D rotate0 = CATransform3DMakeRotation(-angle, 0, 1, 0);
        CATransform3D rotate1 = CATransform3DMakeRotation(M_PI_2 - angle, 0, 1, 0);
        CATransform3D rotate2 = CATransform3DMakeRotation(M_PI_2 * 2 - angle, 0, 1, 0);
        CATransform3D rotate3 = CATransform3DMakeRotation(M_PI_2 * 3 - angle, 0, 1, 0);

        CATransform3D mat0 = CATransform3DConcat(CATransform3DConcat(move, rotate0), back);
        CATransform3D mat1 = CATransform3DConcat(CATransform3DConcat(move, rotate1), back);
        CATransform3D mat2 = CATransform3DConcat(CATransform3DConcat(move, rotate2), back);
        CATransform3D mat3 = CATransform3DConcat(CATransform3DConcat(move, rotate3), back);

        self.topView = [self viewWithRect:rect backColor:[UIColor redColor] transform:CATransform3DPerspect(mat0, CGPointZero, 500)];
        self.bottomView = [self viewWithRect:rect backColor:[UIColor greenColor] transform:CATransform3DPerspect(mat1, CGPointZero, 500)];
        self.rightView = [self viewWithRect:rect backColor:[UIColor blueColor] transform:CATransform3DPerspect(mat2, CGPointZero, 500)];
        self.leftView = [self viewWithRect:rect backColor:[UIColor cyanColor] transform:CATransform3DPerspect(mat3, CGPointZero, 500)];
        
//        float rands = 2 * M_PI / 6;
//        CATransform3D rotate0 = CATransform3DMakeRotation(-angle, 0, 1, 0);
//        CATransform3D rotate1 = CATransform3DMakeRotation(rands - angle, 0, 1, 0);
//        CATransform3D rotate2 = CATransform3DMakeRotation(rands * 2 - angle, 0, 1, 0);
//        CATransform3D rotate3 = CATransform3DMakeRotation(rands * 3 - angle, 0, 1, 0);
//
//        CATransform3D mat0 = CATransform3DConcat(CATransform3DConcat(move, rotate0), back);
//        CATransform3D mat1 = CATransform3DConcat(CATransform3DConcat(move, rotate1), back);
//        CATransform3D mat2 = CATransform3DConcat(CATransform3DConcat(move, rotate2), back);
//        CATransform3D mat3 = CATransform3DConcat(CATransform3DConcat(move, rotate3), back);
//
//        self.topView = [self viewWithRect:rect backColor:[UIColor redColor] transform:CATransform3DPerspect(mat0, CGPointZero, 500)];
//        self.bottomView = [self viewWithRect:rect backColor:[UIColor greenColor] transform:CATransform3DPerspect(mat1, CGPointZero, 500)];
//        self.rightView = [self viewWithRect:rect backColor:[UIColor blueColor] transform:CATransform3DPerspect(mat2, CGPointZero, 500)];
//        self.leftView = [self viewWithRect:rect backColor:[UIColor cyanColor] transform:CATransform3DPerspect(mat3, CGPointZero, 500)];
//
//        CATransform3D rotate4 = CATransform3DMakeRotation(rands * 4 - angle, 0, 1, 0);
//        CATransform3D rotate5 = CATransform3DMakeRotation(rands * 5 - angle, 0, 1, 0);
//
//        CATransform3D mat4 = CATransform3DConcat(CATransform3DConcat(move, rotate4), back);
//        CATransform3D mat5 = CATransform3DConcat(CATransform3DConcat(move, rotate5), back);
//
//        self.backView = [self viewWithRect:rect backColor:[UIColor yellowColor] transform:CATransform3DPerspect(mat4, CGPointZero, 500)];
//        self.frontView = [self viewWithRect:rect backColor:[UIColor magentaColor] transform:CATransform3DPerspect(mat5, CGPointZero, 500)];
        
        //[NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector:@selector(rotateView:) userInfo:nil repeats:YES];
        
        NSTimer *timer = [NSTimer timerWithTimeInterval:1.0 repeats:YES block:^(NSTimer * _Nonnull timer) {
            float angle = self.degrees + 10;
            if(angle > 360)
            {
                angle = 30;
            }
            self.degrees = angle;
            
            CATransform3D rotate0 = CATransform3DMakeRotation(-angle, 0, 1, 0);
            CATransform3D rotate1 = CATransform3DMakeRotation(M_PI_2 - angle, 0, 1, 0);
            CATransform3D rotate2 = CATransform3DMakeRotation(M_PI_2 * 2 - angle, 0, 1, 0);
            CATransform3D rotate3 = CATransform3DMakeRotation(M_PI_2 * 3 - angle, 0, 1, 0);
            
            CATransform3D mat0 = CATransform3DConcat(CATransform3DConcat(move, rotate0), back);
            CATransform3D mat1 = CATransform3DConcat(CATransform3DConcat(move, rotate1), back);
            CATransform3D mat2 = CATransform3DConcat(CATransform3DConcat(move, rotate2), back);
            CATransform3D mat3 = CATransform3DConcat(CATransform3DConcat(move, rotate3), back);

            self.topView.layer.transform = CATransform3DPerspect(mat0, CGPointZero, 500);
            self.bottomView.layer.transform = CATransform3DPerspect(mat1, CGPointZero, 500);
            self.rightView.layer.transform = CATransform3DPerspect(mat2, CGPointZero, 500);
            self.leftView.layer.transform = CATransform3DPerspect(mat3, CGPointZero, 500);
        }];
        [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];

        //普通界面的立体翻转效果
//        float dis = 10;//160 * 1.732f;
//        CATransform3D move = CATransform3DMakeTranslation(0, 0, dis);
//        CATransform3D back = CATransform3DMakeTranslation(0, 0, -dis);
//
////        CATransform3D rotate0 = CATransform3DMakeRotation(-angle, 0, 1, 0);
////        CATransform3D rotate1 = CATransform3DMakeRotation(-angle + M_PI / 3.0f, 0, 1, 0);
//        CATransform3D rotate0 = CATransform3DMakeRotation(angle, 0, 1, 0);
//        CATransform3D rotate1 = CATransform3DMakeRotation(-angle, 0, 1, 0);
//
//        CATransform3D mat0 = CATransform3DConcat(CATransform3DConcat(move, rotate0), back);
//        CATransform3D mat1 = CATransform3DConcat(CATransform3DConcat(move, rotate1), back);
//
//        self.topView = [self viewWithRect:rect backColor:[UIColor redColor] transform:CATransform3DPerspect(mat0, CGPointZero, 500)];
//        self.bottomView = [self viewWithRect:rect backColor:[UIColor greenColor] transform:CATransform3DPerspect(mat1, CGPointZero, 500)];
        
        /* 初始化一个CATransform3D的实例，默认的值是[1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1]*/
        //public let CATransform3DIdentity: CATransform3D
        
        /* 判断一个CATransform3D的实例是否是初始化值。*/
        //public func CATransform3DIsIdentity(_ t: CATransform3D) -> Bool
        
        /* 判断两个CATransform3D的实例的值是否相等。*/
        //public func CATransform3DEqualToTransform(_ a: CATransform3D, _ b: CATransform3D) -> Bool
        /* 以默认值为基准，返回一个平移'(tx, ty, tz)'后的CATransform3D实例t':
         * t' =  [1 0 0 0; 0 1 0 0; 0 0 1 0; tx ty tz 1]
         * tx, ty, tz分别代表在x方向、y方向、z方向的位移量 */
        //public func CATransform3DMakeTranslation(_ tx: CGFloat, _ ty: CGFloat, _ tz: CGFloat) -> CATransform3D
        
        /* 以默认值为基准，返回一个缩放'(sx, sy, sz)'后的CATransform3D实例t':
         * t' = [sx 0 0 0; 0 sy 0 0; 0 0 sz 0; 0 0 0 1]
         * sx, sy, sz分别代表在x方向、y方向、z方向的缩放比例，缩放是以layer的中心对称变化
         * 当sx < 0时，layer会在缩放的基础上沿穿过其中心的竖直线翻转
         * 当sy < 0时，layer会在缩放的基础上沿穿过其中心的水平线翻转 */
        //public func CATransform3DMakeScale(_ sx: CGFloat, _ sy: CGFloat, _ sz: CGFloat) -> CATransform3D
        
        /* 以默认值为基准，返回一个沿矢量'(x, y, z)'轴线，逆时针旋转'angle'弧度后的CATransform3D实例
         * 弧度 = π / 180 × 角度，'M_PI'代表180角度
         * x,y,z决定了旋转围绕的轴线，取值为[-1, 1]。例如(1,0,0)是绕x轴旋转，(0.5,0.5,0)是绕x轴与y轴夹角45°为轴线旋转 */
        //public func CATransform3DMakeRotation(_ angle: CGFloat, _ x: CGFloat, _ y: CGFloat, _ z: CGFloat) -> CATransform3D
#else
        float degree = degrees;//45;//M_PI_2
        
        CATransform3D transform;
        transform = CATransform3DMakeTranslation(0, -translate, 0);
        transform = CATransform3DRotate(transform, kDegree2Radians(degree), 1.0, 0, 0);
        self.topView = [self viewWithRect:rect backColor:[UIColor redColor] transform:transform];

        transform = CATransform3DMakeTranslation(0, translate, 0);
        transform = CATransform3DRotate(transform, kDegree2Radians(degree), 1.0, 0, 0);
        self.bottomView = [self viewWithRect:rect backColor:[UIColor greenColor] transform:transform];

        transform = CATransform3DMakeTranslation(translate, 0, 0);
        transform = CATransform3DRotate(transform, kDegree2Radians(-degree), 0, 1, 0);
        self.rightView = [self viewWithRect:rect backColor:[UIColor blueColor] transform:transform];

        transform = CATransform3DMakeTranslation(-translate, 0, 0);
        transform = CATransform3DRotate(transform, kDegree2Radians(degree), 0, 1, 0);
        self.leftView = [self viewWithRect:rect backColor:[UIColor cyanColor] transform:transform];

        transform = CATransform3DMakeTranslation(0, 0, -translate);
        transform = CATransform3DRotate(transform, kDegree2Radians(degree), 0, 0, 0);
        self.backView = [self viewWithRect:rect backColor:[UIColor yellowColor] transform:transform];

        transform = CATransform3DMakeTranslation(0, 0, translate);
        transform = CATransform3DRotate(transform, kDegree2Radians(degree), 0, 0, 0);
        self.frontView = [self viewWithRect:rect backColor:[UIColor magentaColor] transform:transform];

        //self.layer.sublayerTransform = MakePerspetiveTransform();
        
        transform = MakePerspetiveTransform();
        transform = CATransform3DRotate(transform, kPanScale * rotatePoint.x/*frame.origin.x*/, 0, 1, 0);
        transform = CATransform3DRotate(transform, -kPanScale * rotatePoint.y/*frame.origin.y*/, 1, 0, 0);
        self.layer.sublayerTransform = transform;
        
        __block CGPoint pt = rotatePoint;
        NSTimer *timer = [NSTimer timerWithTimeInterval:1.0 repeats:YES block:^(NSTimer * _Nonnull timer) {
            CGPoint point = pt;
            if(point.x > 100)
            {
                point = rotatePoint;
            }
            else
            {
                point.x += 10;
                point.y += 10;
            }
            pt = point;
            
            CATransform3D transform;
            transform = MakePerspetiveTransform();
            transform = CATransform3DRotate(transform, kPanScale * point.x/*frame.origin.x*/, 0, 1, 0);
            transform = CATransform3DRotate(transform, -kPanScale * point.y/*frame.origin.y*/, 1, 0, 0);
            
            self.layer.sublayerTransform = transform;
        }];
        [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];

#endif
#else
        CATransformLayer *cube = [CATransformLayer layer];
        //第一个面
        //+z方向平移
        CATransform3D t = CATransform3DMakeTranslation(0, 0, translate);
        [cube addSublayer:[self diceFaceWithTransform:t withIndex:1]];
        
        //第二个面
        //+x方向平移
        t = CATransform3DMakeTranslation(translate, 0, 0);
        //y轴旋转90度
        t = CATransform3DRotate(t, 90 * (M_PI / 180), 0, 1, 0);
        [cube addSublayer:[self diceFaceWithTransform:t withIndex:2]];
        
        //第三面
        //+y方向平移
        t = CATransform3DMakeTranslation(0, translate, 0);//CATransform3D CATransform3DInvert (CATransform3D t);
        //x轴旋转90度
        t = CATransform3DRotate(t, 90 * (M_PI / 180), -1, 0, 0);
        [cube addSublayer:[self diceFaceWithTransform:t withIndex:3]];
        
        //第四面
        //-x方向平移
        t = CATransform3DMakeTranslation(-translate, 0, 0);
        //y轴旋转90度
        t = CATransform3DRotate(t, 90 * (M_PI / 180), 0, -1, 0);
        [cube addSublayer:[self diceFaceWithTransform:t withIndex:4]];
        
        //第五面
        //-y方向平移
        t = CATransform3DMakeTranslation(0, -translate, 0);
        //x轴旋转90度
        t = CATransform3DRotate(t, 90 * (M_PI / 180), 1, 0, 0);
        [cube addSublayer:[self diceFaceWithTransform:t withIndex:5]];
        
        //第六面
        //-z方向平移
        t = CATransform3DMakeTranslation(0, 0, -translate);
        t = CATransform3DRotate(t, 180 * (M_PI / 180), 1, 0, 0);
        [cube addSublayer:[self diceFaceWithTransform:t withIndex:6]];
        
        //设置中心点的位置
        cube.position = CGPointMake(rect.size.width / 2, rect.size.height / 2);
        cube.transform = MakePerspetiveTransform();
        [self.layer addSublayer:cube];
#endif
    }
    
    return self;
}

- (CubeView *)initWithFrame:(CGRect)frame itemWidth:(float)itemWidth itemSpace:(float)itemSpace
{
    self = [super initWithFrame:frame];
    if(self)
    {
        self.frame = frame;//通过runtime调用initWithFrame并没有成功设置frame
        //self.backgroundColor = [UIColor grayColor];
        
        CGRect rect = CGRectMake(0, 0, itemWidth, itemWidth);
        
        self.wrapEnabled = YES;
        self.itemWidth = itemWidth;
        self.itemSpace = itemSpace;

        self.numberOfItems = 10;//[self calcItemCount];
        
        int m = 0;
        int _numberOfPlaceholdersToShow = 0;
        NSInteger min = -(NSInteger)(ceil((CGFloat)_numberOfPlaceholdersToShow / 2.0));
        NSInteger max = _numberOfItems - 1 + _numberOfPlaceholdersToShow / 2;
        NSInteger offset = 0 - _numberOfItems / 2;
        if(!_wrapEnabled)
        {
            offset = MAX(min, MIN(max - _numberOfItems + 1, offset));
        }

        for(int i = 0; i < self.numberOfItems; i++)
        {
            UILabel *view = [[UILabel alloc] initWithFrame:rect];
            if(view)
            {
                view.tag = i + 1;
                view.textAlignment = NSTextAlignmentCenter;
                view.text = [NSString stringWithFormat:@"View_%d", i + 1];
                view.backgroundColor = [UIColor colorWithRed:(20 * i) / 255.0 green:(20 * i) / 255.0 blue:(20 * i) / 255.0 alpha:1];
                
                NSInteger index = i + offset;
                if(_wrapEnabled)
                {
                    index = [self clampedIndex:index];
                }

                [self transformItemView:view atIndex:index];
                
                [self addSubview:view];
            }
        }
        
        if(m)
        {
            CATransform3D transform = self.layer.transform;
            transform = CATransform3DRotate(transform, kDegree2Radians(m), 0, 1, 0);
            self.layer.transform = transform;
        }
        __block float angle = 10;
        NSTimer *timer = [NSTimer timerWithTimeInterval:1.0 repeats:YES block:^(NSTimer * _Nonnull timer) {
//            if(angle > 360)
//            {
//                angle = 0;
//            }
//            else
//            {
//                angle += 10;
//            }
            
//            CATransform3D transform = self.layer.sublayerTransform;
//            transform = CATransform3DRotate(transform, kDegree2Radians(angle), 0, 1, 0);
//            //self.layer.transform = transform;
//
//            self.layer.sublayerTransform = transform;
            for(int i = 0; i < self.numberOfItems; i++)
            {
                UIView *view = [self viewWithTag:i + 1];
                if(view)
                {
                    CATransform3D transform = view.layer.transform;
                    transform = CATransform3DRotate(transform, kDegree2Radians(angle), 0, 1, 0);
                    view.layer.transform = transform;
                }
            }
        }];
        [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
    }
    
    return self;
}

- (void)dealloc
{
}

- (NSInteger)calcItemCount
{
    NSInteger count = MIN(20, MAX(8, ceil(self.frame.size.width / (self.itemWidth + self.itemSpace)) * M_PI));

    return count;
}

- (void)transformItemView:(UIView *)view atIndex:(NSInteger)index
{
    //calculate offset
    CGFloat offset = [self offsetForItemAtIndex:index];
    
    //update alpha
    view./*superview.*/layer.opacity = [self alphaForItemWithOffset:offset];
    
#ifdef ICAROUSEL_MACOS
    
    //center view
    [view.superview setFrameOrigin:NSMakePoint(self.bounds.size.width / 2.0 + _contentOffset.width, self.bounds.size.height / 2.0 + _contentOffset.height)];
    view.superview.layer.anchorPoint = CGPointMake(0.5, 0.5);
    
    //account for retina
    view.superview.layer.rasterizationScale = view.window.screen.backingScaleFactor;
    
#else
    
    //center view
    view./*superview.*/center = CGPointMake(self.bounds.size.width / 2.0, self.bounds.size.height / 2.0);//CGPointMake(self.bounds.size.width/2.0 + _contentOffset.width, self.bounds.size.height/2.0 + _contentOffset.height);
    
    //enable/disable interaction
    //view.superview.userInteractionEnabled = (!_centerItemWhenSelected || index == self.currentItemIndex);
    
    //account for retina
    view./*superview.*/layer.rasterizationScale = [UIScreen mainScreen].scale;
    
    [view layoutIfNeeded];

#endif
    
    //special-case logic for iCarouselTypeCoverFlow2
//    CGFloat clampedOffset = MAX(-1.0, MIN(1.0, offset));
//    if (_decelerating || (_scrolling && !_dragging && !_didDrag) || (_autoscroll && !_dragging) ||
//        (!_wrapEnabled && (_scrollOffset < 0 || _scrollOffset >= _numberOfItems - 1)))
//    {
//        if (offset > 0)
//        {
//            _toggle = (offset <= 0.5)? -clampedOffset: (1.0 - clampedOffset);
//        }
//        else
//        {
//            _toggle = (offset > -0.5)? -clampedOffset: (- 1.0 - clampedOffset);
//        }
//    }
    
    //calculate transform
    CATransform3D transform = [self transformForItemViewWithOffset:offset];
    
    //transform view
    view./*superview.*/layer.transform = transform;
    
    //backface culling
    BOOL showBackfaces = YES;//view.layer.doubleSided;
    //showBackfaces = !![self valueForOption:iCarouselOptionShowBackfaces withDefault:showBackfaces];
    
    //we can't just set the layer.doubleSided property because it doesn't block interaction
    //instead we'll calculate if the view is front-facing based on the transform
    view./*superview.*/hidden = !(showBackfaces ?: (transform.m33 > 0.0));
}

- (CATransform3D)transformForItemViewWithOffset:(CGFloat)offset
{
    //set up base transform
    CATransform3D transform = CATransform3DIdentity;
    transform.m34 = -1./500.;//-1./2000.;
    transform = CATransform3DTranslate(transform, -0, -0, 0.0);//transform = CATransform3DTranslate(transform, -_viewpointOffset.width, -_viewpointOffset.height, 0.0);
    
    //perform transform
    CGFloat count = _numberOfItems;//[self calcItemCount];
    CGFloat spacing = self.itemWidth + self.itemSpace;
    CGFloat arc = M_PI + M_PI;//M_PI * 2.0;
    CGFloat radius = MAX(0.01, spacing / 2.0 / tan(arc / 2.0 / count));
    CGFloat angle = offset / count * arc;
    
    //if(_type == iCarouselTypeInvertedCylinder)
    //{
    //    radius = -radius;
    //    angle = -angle;
    //}
    
    //if(_vertical)
    //{
    //    transform = CATransform3DTranslate(transform, 0.0, 0.0, -radius);
    //    transform = CATransform3DRotate(transform, angle, -1.0, 0.0, 0.0);
    //    return CATransform3DTranslate(transform, 0.0, 0.0, radius + 0.01);
    //}
    //else
    {
        transform = CATransform3DTranslate(transform, 0.0, 0.0, -radius);
        transform = CATransform3DRotate(transform, angle, 0.0, 1.0, 0.0);
        return CATransform3DTranslate(transform, 0.0, 0.0, radius + 0.01);
    }
}

- (NSInteger)clampedIndex:(NSInteger)index
{
    if (_numberOfItems == 0)
    {
        return -1;
    }
    else if (_wrapEnabled)
    {
        return index - floor((CGFloat)index / (CGFloat)_numberOfItems) * _numberOfItems;
    }
    else
    {
        return MIN(MAX(0, index), MAX(0, _numberOfItems - 1));
    }
}

- (CGFloat)clampedOffset:(CGFloat)offset
{
    if(_numberOfItems == 0)
    {
        return -1.0;
    }
    else if(_wrapEnabled)
    {
        return offset - floor(offset / (CGFloat)_numberOfItems) * _numberOfItems;
    }
    else
    {
        return MIN(MAX(0.0, offset), MAX(0.0, (CGFloat)_numberOfItems - 1.0));
    }
}

- (NSInteger)minScrollDistanceFromIndex:(NSInteger)fromIndex toIndex:(NSInteger)toIndex
{
    NSInteger directDistance = toIndex - fromIndex;
    if(_wrapEnabled)
    {
        NSInteger wrappedDistance = MIN(toIndex, fromIndex) + _numberOfItems - MAX(toIndex, fromIndex);
        if(fromIndex < toIndex)
        {
            wrappedDistance = -wrappedDistance;
        }
        return (ABS(directDistance) <= ABS(wrappedDistance))? directDistance: wrappedDistance;
    }
    return directDistance;
}

- (CGFloat)minScrollDistanceFromOffset:(CGFloat)fromOffset toOffset:(CGFloat)toOffset
{
    CGFloat directDistance = toOffset - fromOffset;
    if (_wrapEnabled)
    {
        CGFloat wrappedDistance = MIN(toOffset, fromOffset) + _numberOfItems - MAX(toOffset, fromOffset);
        if (fromOffset < toOffset)
        {
            wrappedDistance = -wrappedDistance;
        }
        return (fabs(directDistance) <= fabs(wrappedDistance))? directDistance: wrappedDistance;
    }
    return directDistance;
}

- (CGFloat)offsetForItemAtIndex:(NSInteger)index
{
    //calculate relative position
    CGFloat offset = index - 0;//_scrollOffset;
    if(_wrapEnabled)
    {
        if(offset > _numberOfItems / 2.0)
        {
            offset -= _numberOfItems;
        }
        else if(offset < -_numberOfItems / 2.0)
        {
            offset += _numberOfItems;
        }
    }
    
#ifdef ICAROUSEL_MACOS
    
    if(_vertical)
    {
        //invert transform
        offset = -offset;
    }
    
#endif
    
    return offset;
}

- (CGFloat)alphaForItemWithOffset:(CGFloat)offset
{
    CGFloat fadeMin = (CGFloat)-INFINITY;
    CGFloat fadeMax = (CGFloat)INFINITY;
    CGFloat fadeRange = 1.0;
    CGFloat fadeMinAlpha = 0.0;
    
#ifdef ICAROUSEL_MACOS
    
    if (_vertical)
    {
        //invert
        offset = -offset;
    }
    
#endif
    
    CGFloat factor = 0.0;
    if (offset > fadeMax)
    {
        factor = offset - fadeMax;
    }
    else if (offset < fadeMin)
    {
        factor = fadeMin - offset;
    }
    return 1.0 - MIN(factor, fadeRange) / fadeRange * (1.0 - fadeMinAlpha);
}

//- (void)drawRect:(CGRect)rect
//{
//    //[super drawRect:rect];
//    CGContextRef currentContext = UIGraphicsGetCurrentContext();
//
//    //设置矩形填充颜色：红色
//    //CGContextSetRGBFillColor(currentContext, 1.0, 0.0, 0.0, 1.0);
//    CGContextSetFillColorWithColor(currentContext, self.backgroundColor.CGColor);
//    //填充矩形
//    CGContextFillRect(currentContext, rect);
//}

//- (CALayer *)diceFaceWithTransform:(CATransform3D)transform withIndex:(NSInteger)index
//{
//    CATextLayer *face = [CATextLayer layer];
//    face.bounds = CGRectMake(0, 0, self.frame.size.width, self.frame.size.height);
//    face.string = [NSString stringWithFormat:@"第%zd面", index];
//    face.fontSize = 20;
//    face.contentsScale = 2;
//    face.alignmentMode = @"center";
//    face.truncationMode = @"middle";
//    face.transform = transform;
//
//    CGFloat red = (rand() / (double)INT_MAX);
//    CGFloat green = (rand() / (double)INT_MAX);
//    CGFloat blue = (rand() / (double)INT_MAX);
//    face.backgroundColor = [UIColor colorWithRed:red green:green blue:blue alpha:1.0].CGColor;
//
//    return face;
//}

//- (void)rotateView:(id)userInfo
//{
//    float degrees = self.degrees + 10;
//    if(degrees > 360)
//    {
//        degrees = 0;
//    }
//    self.degrees = degrees;
//
//    CATransform3D transform;
//    transform = CATransform3DMakeTranslation(0, 0, 0);
//    transform = CATransform3DRotate(transform, kDegree2Radians(degrees), 0, 1.0, 0);
//    self.topView.layer.transform = transform;
//    self.topView.backgroundColor = [UIColor greenColor];
//
//    transform = CATransform3DMakeTranslation(0, 0, 0);
//    transform = CATransform3DRotate(transform, kDegree2Radians(degrees), 0, 1.0, 0);
//    self.bottomView.layer.transform = transform;
//    self.bottomView.backgroundColor = [UIColor redColor];
//
//    [self setNeedsDisplay];
//    [self.topView setNeedsDisplay];
//    [self.bottomView setNeedsDisplay];
//}

//- (void)rotateView:(id)userInfo
//{
//    float angle = self.degrees + 10;
//    if(angle > 360)
//    {
//        angle = 0;
//    }
//    self.degrees = angle;
//
//    angle = kDegree2Radians(30);
//    float translate = self.frame.size.width;
//
//    //使用四张同样大小的图片围成一个框，让这个框动画旋转。
//    CATransform3D move = CATransform3DMakeTranslation(0, 0, translate);
//    CATransform3D back = CATransform3DMakeTranslation(0, 0, -translate);
//
//    CATransform3D rotate0 = CATransform3DMakeRotation(-angle, 0, 1, 0);
//    CATransform3D rotate1 = CATransform3DMakeRotation(M_PI_2 - angle, 0, 1, 0);
//    CATransform3D rotate2 = CATransform3DMakeRotation(M_PI_2 * 2 - angle, 0, 1, 0);
//    CATransform3D rotate3 = CATransform3DMakeRotation(M_PI_2 * 3 - angle, 0, 1, 0);
//
//    CATransform3D mat0 = CATransform3DConcat(CATransform3DConcat(move, rotate0), back);
//    CATransform3D mat1 = CATransform3DConcat(CATransform3DConcat(move, rotate1), back);
//    CATransform3D mat2 = CATransform3DConcat(CATransform3DConcat(move, rotate2), back);
//    CATransform3D mat3 = CATransform3DConcat(CATransform3DConcat(move, rotate3), back);
//
//    //            self.topView.layer.transform = CATransform3DPerspect(mat0, CGPointZero, 500);
//    //            self.bottomView.layer.transform = CATransform3DPerspect(mat1, CGPointZero, 500);
//    //            self.rightView.layer.transform = CATransform3DPerspect(mat2, CGPointZero, 500);
//    //            self.leftView.layer.transform = CATransform3DPerspect(mat3, CGPointZero, 500);
//
//    [self.topView removeFromSuperview];
//    [self.bottomView removeFromSuperview];
//    [self.rightView removeFromSuperview];
//    [self.leftView removeFromSuperview];
//
//    CGRect frame = self.frame;
//    static int i = 0;
//    if(i == 0)
//    {
//        frame.origin.x += 10;
//        i = 1;
//    }
//    else
//    {
//        frame.origin.x -= 10;
//        i = 0;
//    }
//    self.frame = frame;
//    self.backgroundColor = [UIColor whiteColor];
//    self.layer.transform = CATransform3DIdentity;
//    [self setNeedsDisplay];
//}

- (void)update
{
    //CALayer的旋转和缩放是绕anchorPoint点的，改变anchorPoint的值，可以使Layer绕不同的点而不只是中心点旋转缩放。在构造透视投影矩阵的例子中就可以看到，CATransform3D可以使用CATransform3DConcat函数连接起来以构造更复杂的变换。
    //翻转的动画
    static float angle = 0;
    angle += 0.05f;
    
    CATransform3D transloate = CATransform3DMakeTranslation(0, 0, -200);
    CATransform3D rotate = CATransform3DMakeRotation(angle, 0, 1, 0);
    CATransform3D mat = CATransform3DConcat(rotate, transloate);
    self.layer.transform = CATransform3DPerspect(mat, CGPointMake(0, 0), 500);
}

- (void)cubeTest:(CGRect)rect
{
    float size = 100.0;
    
    CATransformLayer *transformLayer = [CATransformLayer layer];
    transformLayer.position = CGPointMake(rect.size.width / 2, rect.size.height / 2);
    
    CGRect layerRect = CGRectMake(0.0, 0.0, size, size); //frame rect for cube sides
    CGPoint screenCenter = CGPointMake(transformLayer.bounds.size.width / 2, transformLayer.bounds.size.height / 2);
    
    //side1
    CALayer *side1 = [CALayer layer];
    side1.borderColor = [UIColor colorWithHue:0.6 saturation:1.0 brightness:1.0 alpha:1.0].CGColor;
    side1.backgroundColor = [UIColor colorWithHue:0.6 saturation:1.0 brightness:1.0 alpha:0.8].CGColor;
    side1.borderWidth = 2.0;
    side1.cornerRadius = 30.0;
    side1.frame = layerRect;
    side1.position = screenCenter;
    [transformLayer addSublayer:side1];
    
    //side2
    CALayer *side2 = [CALayer layer];
    side2.borderColor = [UIColor colorWithHue:0.25 saturation:1.0 brightness:1.0 alpha:1.0].CGColor;
    side2.backgroundColor = [UIColor colorWithHue:0.25 saturation:1.0 brightness:1.0 alpha:0.8].CGColor;
    side2.borderWidth = 2.0;
    side2.cornerRadius = 30.0;
    side2.frame = layerRect;
    side2.position = screenCenter;
    //positioning
    CATransform3D rotation = CATransform3DMakeRotation(M_PI / 2, 0.0, 1.0, 0.0);
    CATransform3D translation = CATransform3DMakeTranslation(size / 2, 0.0, size / -2 );
    CATransform3D position = CATransform3DConcat(rotation, translation);
    side2.transform = position;
    [transformLayer addSublayer:side2];
    
    //side3
    CALayer *side3 = [CALayer layer];
    side3.borderColor = [UIColor colorWithHue:0.0 saturation:1.0 brightness:1.0 alpha:1.0].CGColor;
    side3.backgroundColor = [UIColor colorWithHue:0.0 saturation:1.0 brightness:1.0 alpha:0.8].CGColor;
    side3.borderWidth = 2.0;
    side3.cornerRadius = 30.0;
    side3.frame = layerRect;
    side3.position = screenCenter;
    //positioning
    translation = CATransform3DMakeTranslation(0.0, 0.0, -size); //size
    side3.transform = translation;
    [transformLayer addSublayer:side3];
    
    //side4
    CALayer *side4 = [CALayer layer];
    side4.borderColor = [UIColor colorWithHue:0.2 saturation:1.0 brightness:1.0 alpha:1.0].CGColor;
    side4.backgroundColor = [UIColor colorWithHue:0.2 saturation:1.0 brightness:1.0 alpha:0.8].CGColor;
    side4.borderWidth = 2.0;
    side4.cornerRadius = 30.0;
    side4.frame = layerRect;
    side4.position = screenCenter;
    //positioning
    rotation = CATransform3DMakeRotation(M_PI / 2, 0.0, 1.0, 0.0);
    translation = CATransform3DMakeTranslation(size / -2, 0.0, size / -2);
    side4.transform = CATransform3DConcat(rotation, translation);
    [transformLayer addSublayer:side4];
    
    //side5
    CALayer *side5 = [CALayer layer];
    side5.borderColor = [UIColor colorWithHue:0.8 saturation:1.0 brightness:1.0 alpha:1.0].CGColor;
    side5.backgroundColor = [UIColor colorWithHue:0.8 saturation:1.0 brightness:1.0 alpha:0.8].CGColor;
    side5.borderWidth = 2.0;
    side5.cornerRadius = 30.0;
    side5.frame = layerRect;
    side5.position = screenCenter;
    //positioning
    rotation = CATransform3DMakeRotation(M_PI / 2, 1.0, .0, 0.0);
    translation = CATransform3DMakeTranslation(0.0, size / -2, size / -2);
    side5.transform = CATransform3DConcat(rotation, translation);
    [transformLayer addSublayer:side5];
    
    //side6
    CALayer *side6 = [CALayer layer];
    side6.borderColor = [UIColor colorWithHue:0.0845 saturation:1.0 brightness:1.0 alpha:1.0].CGColor;
    side6.backgroundColor = [UIColor colorWithHue:0.0845 saturation:1.0 brightness:1.0 alpha:0.8].CGColor;
    side6.borderWidth = 2.0;
    side6.cornerRadius = 30.0;
    side6.frame = layerRect;
    side6.position = screenCenter;
    //positioning
    rotation = CATransform3DMakeRotation(M_PI / 2, 1.0, .0, 0.0);
    translation = CATransform3DMakeTranslation(0.0, size / 2, size / -2);
    side6.transform = CATransform3DConcat(rotation, translation);
    [transformLayer addSublayer:side6];
    
    transformLayer.anchorPointZ = -size / 2;
    //[self setWantsLayer:YES];
    [self.layer addSublayer:transformLayer];
    
//    float angle = 20;
//    //transformLayer.position = CGPointMake(size / 2, size / 2);
//    transformLayer.transform = MakePerspetiveTransform();
//    transformLayer.transform = CATransform3DRotate(transformLayer.transform, angle, 0, 1, 0);
//    transformLayer.transform = CATransform3DRotate(transformLayer.transform, -angle, 1, 0, 0);

    //animate
    int i = 0;
    if(i == 0)
    {
        CGFloat perspective = -1.0/10000.0;
        CABasicAnimation *transformAnimation = [CABasicAnimation animationWithKeyPath:@"transform"];
        
        CATransform3D transform = CATransform3DIdentity;
        transform.m34 = perspective;
        transformAnimation.fromValue = [NSValue valueWithCATransform3D:transform];
        
        transform.m34 = perspective;
        transform = CATransform3DRotate(transform, kDegree2Radians(90), 1, 0, 0);
        
        transformAnimation.toValue = [NSValue valueWithCATransform3D:transform];
        
        transformAnimation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
        transformAnimation.repeatCount = INFINITY;
        transformAnimation.duration = 10.0;
        [transformLayer addAnimation:transformAnimation forKey:@"RotateTheBox"];
        
        [self sideAnimation:side1 transform:CATransform3DTranslate(CATransform3DRotate(side1.transform, kDegree2Radians(90), 1, 0, 0), 0, size / 2, size / 2)];
        [self sideAnimation:side3 transform:CATransform3DTranslate(CATransform3DRotate(side3.transform, kDegree2Radians(-90), 1, 0, 0), 0, size / 2, -size / 2)];
        [self sideAnimation:side2 transform:CATransform3DTranslate(CATransform3DRotate(side2.transform, kDegree2Radians(90), 1, 0, 0), 0, size / 2, size / 2)];
        [self sideAnimation:side4 transform:CATransform3DTranslate(CATransform3DRotate(side4.transform, kDegree2Radians(-90), 1, 0, 0), 0, size / 2, -size / 2)];
        [self sideAnimation:side6 transform:CATransform3DTranslate(side6.transform, 0, 0, size)];//lower cap
    }
}

- (void)sideAnimation:(CALayer*)side transform:(CATransform3D)transform
{
    CABasicAnimation *transformAnimation = [CABasicAnimation animationWithKeyPath:@"transform"];
    transformAnimation.toValue = [NSValue valueWithCATransform3D:transform];
    transformAnimation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
    transformAnimation.repeatCount = INFINITY;
    transformAnimation.duration = 10.0;
    [side addAnimation:transformAnimation forKey:@"rotateSide"];
}

@end


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef CGFloat (*ViewEasingFunctionPointerType)(CGFloat);

static const NSUInteger KeyframeCount = 60;

CAKeyframeAnimation *AnimationWithCGFloat(NSString *keyPath, ViewEasingFunctionPointerType function, CGFloat fromValue, CGFloat toValue)
{
    NSMutableArray *values = [NSMutableArray arrayWithCapacity:KeyframeCount];
    
    CGFloat t = 0.0;
    CGFloat dt = 1.0 / (KeyframeCount - 1);
    
    for(size_t frame = 0; frame < KeyframeCount; ++frame, t += dt)
    {
        CGFloat value = fromValue + function(t) * (toValue - fromValue);
        [values addObject:[NSNumber numberWithFloat:value]];
    }
    
    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:keyPath];
    [animation setValues:values];
    
    return animation;
}

CAKeyframeAnimation *AnimationWithCGPoint(NSString *keyPath, ViewEasingFunctionPointerType function, CGPoint fromPoint, CGPoint toPoint)
{
    NSMutableArray *values = [NSMutableArray arrayWithCapacity:KeyframeCount];
    
    CGFloat t = 0.0;
    CGFloat dt = 1.0 / (KeyframeCount - 1);
    
    for(size_t frame = 0; frame < KeyframeCount; ++frame, t += dt)
    {
        float fValue = function(t);
        CGFloat x = fromPoint.x + fValue/*function(t)*/ * (toPoint.x - fromPoint.x);
        CGFloat y = fromPoint.y + fValue/*function(t)*/ * (toPoint.y - fromPoint.y);
        
        [values addObject:[NSValue valueWithCGPoint:CGPointMake(x, y)]];
    }
    
    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:keyPath];
    [animation setValues:values];
    
    return animation;
}

CAKeyframeAnimation *AnimationWithCGRect(NSString *keyPath, ViewEasingFunctionPointerType function, CGRect fromRect, CGRect toRect)
{
    NSMutableArray *values = [NSMutableArray arrayWithCapacity:KeyframeCount];
    
    CGFloat t = 0.0;
    CGFloat dt = 1.0 / (KeyframeCount - 1);
    
    for(size_t frame = 0; frame < KeyframeCount; ++frame, t += dt)
    {
        float fValue = function(t);
        CGFloat x = fromRect.origin.x + fValue/*function(t)*/ * (toRect.origin.x - fromRect.origin.x);
        CGFloat y = fromRect.origin.y + fValue/*function(t)*/ * (toRect.origin.y - fromRect.origin.y);
        
        CGFloat width = fromRect.size.width + fValue/*function(t)*/ * (toRect.size.width - fromRect.size.width);
        CGFloat height = fromRect.size.height + fValue/*function(t)*/ * (toRect.size.height - fromRect.size.height);
        
        [values addObject:[NSValue valueWithCGRect:CGRectMake(x, y, width, height)]];
    }
    
    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:keyPath];
    [animation setValues:values];
    
    return animation;
}

CAKeyframeAnimation *AnimationWithCATransform3D(NSString *keyPath, ViewEasingFunctionPointerType function, CATransform3D fromMatrix, CATransform3D toMatrix)
{
    NSMutableArray *values = [NSMutableArray arrayWithCapacity:KeyframeCount];
    
    CGFloat t = 0.0;
    CGFloat dt = 1.0 / (KeyframeCount - 1);
    
    for(size_t frame = 0; frame < KeyframeCount; ++frame, t += dt)
    {
        CATransform3D value;
        float fValue = function(t);

        value.m11 = fromMatrix.m11 + fValue/*function(t)*/ * (toMatrix.m11 - fromMatrix.m11);
        value.m12 = fromMatrix.m12 + fValue/*function(t)*/ * (toMatrix.m12 - fromMatrix.m12);
        value.m13 = fromMatrix.m13 + fValue/*function(t)*/ * (toMatrix.m13 - fromMatrix.m13);
        value.m14 = fromMatrix.m14 + fValue/*function(t)*/ * (toMatrix.m14 - fromMatrix.m14);
        
        value.m21 = fromMatrix.m21 + fValue/*function(t)*/ * (toMatrix.m21 - fromMatrix.m21);
        value.m22 = fromMatrix.m22 + fValue/*function(t)*/ * (toMatrix.m22 - fromMatrix.m22);
        value.m23 = fromMatrix.m23 + fValue/*function(t)*/ * (toMatrix.m23 - fromMatrix.m23);
        value.m24 = fromMatrix.m24 + fValue/*function(t)*/ * (toMatrix.m24 - fromMatrix.m24);
        
        value.m31 = fromMatrix.m31 + fValue/*function(t)*/ * (toMatrix.m31 - fromMatrix.m31);
        value.m32 = fromMatrix.m32 + fValue/*function(t)*/ * (toMatrix.m32 - fromMatrix.m32);
        value.m33 = fromMatrix.m33 + fValue/*function(t)*/ * (toMatrix.m33 - fromMatrix.m33);
        value.m34 = fromMatrix.m34 + fValue/*function(t)*/ * (toMatrix.m34 - fromMatrix.m34);
        
        value.m41 = fromMatrix.m41 + fValue/*function(t)*/ * (toMatrix.m41 - fromMatrix.m41);
        value.m42 = fromMatrix.m42 + fValue/*function(t)*/ * (toMatrix.m42 - fromMatrix.m42);
        value.m43 = fromMatrix.m43 + fValue/*function(t)*/ * (toMatrix.m43 - fromMatrix.m43);
        value.m44 = fromMatrix.m44 + fValue/*function(t)*/ * (toMatrix.m44 - fromMatrix.m44);
        
        [values addObject:[NSValue valueWithCATransform3D:value]];
    }
    
    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:keyPath];
    [animation setValues:values];
    
    return animation;
}

CAKeyframeAnimation *AnimationWithCGColor(NSString *keyPath, ViewEasingFunctionPointerType function, CGColorRef fromColor, CGColorRef toColor)
{
    NSMutableArray *values = [NSMutableArray arrayWithCapacity:KeyframeCount];
    
    CGFloat t = 0.0;
    CGFloat dt = 1.0 / (KeyframeCount - 1);
    
    CGColorSpaceRef colorSpace = CGColorGetColorSpace(toColor);
    
    size_t numberOfComponents = CGColorGetNumberOfComponents(toColor);
    const CGFloat *fromComponents = CGColorGetComponents(fromColor);
    const CGFloat *toComponents = CGColorGetComponents(toColor);
    
    CGFloat components[numberOfComponents];
    
    for(size_t frame = 0; frame < KeyframeCount; ++frame, t += dt)
    {
        for (size_t c = 0; c < numberOfComponents; ++c)
        {
            components[c] = fromComponents[c] + function(t) * (toComponents[c] - fromComponents[c]);
        }
        
        CGColorRef value = CGColorCreate(colorSpace, components);
        
        [values addObject:CFBridgingRelease(value)];
    }
    
    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:keyPath];
    [animation setValues:values];
    
    return animation;
}
