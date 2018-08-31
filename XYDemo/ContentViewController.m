//
//  ContentViewController.m
//  XYDemo
//
//  Created by luck on 2018/5/11.
//  Copyright © 2018年 luck. All rights reserved.
//

#import "ContentViewController.h"
#import "CustomControlLibrary.h"
#import "CubeView.h"
#import "XYChartView.h"
#import "XYGlobalFunctions.h"
#import "FlipView.h"
#import "UIView+RoundCorner.h"

@interface ContentViewController ()<UIScrollViewDelegate>

@property(nonatomic, strong)CubeView *cubeView;

//控制器翻页滚动视图
@property(nonatomic, strong)UIScrollView *scrollView;

//视图数组
@property(nonatomic, strong)NSArray *viewArray;

//当前页
@property(nonatomic, assign)NSInteger currentPage;

@end

@implementation ContentViewController

//3D透视函数
CATransform3D CATransform3DMakePerspective2(CGPoint center, float disZ)
{
    CATransform3D transToCenter = CATransform3DMakeTranslation(-center.x, -center.y, 0);
    CATransform3D transBack = CATransform3DMakeTranslation(center.x, center.y, 0);
    CATransform3D scale = CATransform3DIdentity;
    scale.m34 = -1.0f / disZ;
    return CATransform3DConcat(CATransform3DConcat(transToCenter, scale), transBack);
}

CATransform3D CATransform3DPerspect2(CATransform3D t, CGPoint center, float disZ)
{
    return CATransform3DConcat(t, CATransform3DMakePerspective2(center, disZ));
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.view.backgroundColor = [UIColor whiteColor];
    
//    NSString *bundlePath = [[NSBundle mainBundle] pathForResource:@"MyBundle" ofType:@"bundle"];
//    if(bundlePath)
//    {
//        NSBundle *bundle = [NSBundle bundleWithPath:bundlePath];
//        if(bundle)
//        {
//            NSString *imagePath = [bundle pathForResource:@"icon_016" ofType:@"png"];
//            //NSString *imagePath = [bundlePath stringByAppendingPathComponent:@"icon_016"];
//            if(imagePath)
//            {
//                UIImage *image = [UIImage imageWithContentsOfFile:imagePath];
//                if(image)
//                {
//
//                }
//            }
//        }
//        UIImage *image = [UIImage imageNamed:@"icon_016" inBundle:bundle compatibleWithTraitCollection:nil];
//        //UIImage *image = [UIImage imageNamed:@"MyBundle.bundle/icon_016"];
//        if(image)
//        {
//            UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(30, 30, 200, 200)];
//            if(imageView)
//            {
//                imageView.image = image;
//
//                [self.view addSubview:imageView];
//
//                return;
//            }
//        }
//    }
    
    CGRect rect = CGRectMake(30, 30, 500, 400);
    
    switch(_contentType)
    {
        case 0:
        {
            XYLineChartView *chartView = [[XYLineChartView alloc] initWithFrame:rect contentEdgeInsets:UIEdgeInsetsMake(30, 30, 30, 30) contentBackColor:[UIColor yellowColor]];
            if(chartView)
            {
                [self.view addSubview:chartView];
                
                //chartView.backgroundColor = [UIColor redColor];
                
                UIColor *baseLineColor = [UIColor redColor];
                UIColor *lineColor = [UIColor blackColor];
                
                int baseLineWidth = 2;
                int lineWidth = 1;
                
                [chartView setAxesStyle:5 xAxisDrawCount:5 xAxisBaseIndex:0 xAxisBaseLineWidth:baseLineWidth xAxisBaseLineColor:baseLineColor xAxisLineStyle:1 xAxisLineWidth:lineWidth xAxisLineColor:lineColor yAxisCount:5 yAxisDrawCount:5 yAxisBaseIndex:0 yAxisBaseLineWidth:baseLineWidth yAxisBaseLineColor:baseLineColor yAxisLineStyle:1 yAxisLineWidth:lineWidth yAxisLineColor:lineColor axesEdgeInsets:UIEdgeInsetsMake(30, 50, 50, 30)];
                
                UIFont *textFont = [UIFont systemFontOfSize:14];
                UIColor *textColor = [UIColor blueColor];
                
                NSArray *dataArray = @[@60, @90, @130, @160, @180];
                NSArray *timeArray = @[@"08-09", @"08-10", @"08-11", @"08-12", @"08-13"];
                NSArray *colorArray = @[[UIColor grayColor], [UIColor greenColor], [UIColor orangeColor], [UIColor yellowColor], [UIColor purpleColor]];
                
                NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithObject:textFont forKey:NSFontAttributeName];
                CGSize size = [@"180.00"/*timeArray[0]*/ boundingRectWithSize:CGSizeMake(MAXFLOAT, 0.0) options:NSStringDrawingUsesLineFragmentOrigin attributes:dic context:nil].size;
                
                [chartView setAxesTextStyle:size.width xAxisTextMargin:10 xAxisTextFont:textFont xAxisTextColor:textColor xAxisTextPos:0 yAxisTextWidth:size.width yAxisTextMargin:10 yAxisTextFont:textFont yAxisTextColor:textColor yAxisTextPos:0];
                
                [chartView setAxesTextData:YES maxAxisData:280 baseAxisDataArray:timeArray axisDataArray:nil];
                
                [chartView setLineData:1 lineDataArray:dataArray lineColor:colorArray[0] fillColor:colorArray[0] fillAlpha:0.5 valueRadius:4 valueLineWidth:1 valueLineColor:colorArray[0] valueFillColor:colorArray[0] andBlock:^(XYChartViewSetLineChartDataBlock setLineChartDataBlock) {
                    if(setLineChartDataBlock)
                    {
                        //NSArray *dataArray = @[@20, @80, @30, @50, @10];
                        //setLineChartDataBlock(dataArray, colorArray[1], colorArray[1], colorArray[1], colorArray[1]);
                    }
                }];
            }
            //    XYChartViewType chartType = XYChartViewTypeBar;
            //    XYChartView *chartView = [[XYChartView alloc] initWithFrame:rect chartType:chartType contentEdgeInsets:UIEdgeInsetsMake(30, 30, 30, 30)/*UIEdgeInsetsMake(10, 20, 10, 20)*/];
            //    if(chartView)
            //    {
            //        NSArray *dataArray = @[@10, @20, @30, @10, @20];
            //        NSArray *colorArray = @[[UIColor grayColor], [UIColor greenColor], [UIColor orangeColor], [UIColor yellowColor], [UIColor purpleColor]];
            //        NSArray *timeArray = @[@"08-13", @"08-12", @"08-11", @"08-10", @"08-09"];
            //
            //        switch(chartType)
            //        {
            //            case XYChartViewTypeLine:
            //            {
            //                [chartView setChartParam:0 xAxisRightMargin:20 yAxisTopMargin:20 yAxisBottomMargin:0 axesLineWidth:1 axesLineColor:[UIColor blackColor] axesTextColor:[UIColor blackColor] axesFontHeight:14 xAxisTextHeight:30 xAxisTextTopMargin:10 yAxisTextWidth:40 yAxisTextRightMargin:10 valueDotDadius:4 valueDotLineWidth:1 valueDotLineColor:[UIColor redColor] valueDotFillColor:[UIColor blueColor]];
            //            }
            //                break;
            //            case XYChartViewTypePie:
            //            {
            //                [chartView setChartParam:100 xAxisRightMargin:100 yAxisTopMargin:30 yAxisBottomMargin:30 axesLineWidth:1 axesLineColor:[UIColor blackColor] axesTextColor:[UIColor blackColor] axesFontHeight:14 xAxisTextHeight:20 xAxisTextTopMargin:20 yAxisTextWidth:60 yAxisTextRightMargin:10 valueDotDadius:4 valueDotLineWidth:1 valueDotLineColor:[UIColor redColor] valueDotFillColor:[UIColor blueColor]];
            //            }
            //                break;
            //            case XYChartViewTypeBar:
            //            {
            //                [chartView setChartParam:0 xAxisRightMargin:20 yAxisTopMargin:20 yAxisBottomMargin:0 axesLineWidth:1 axesLineColor:[UIColor blackColor] axesTextColor:[UIColor blackColor] axesFontHeight:14 xAxisTextHeight:30 xAxisTextTopMargin:10 yAxisTextWidth:40 yAxisTextRightMargin:10 valueDotDadius:4 valueDotLineWidth:1 valueDotLineColor:[UIColor redColor] valueDotFillColor:[UIColor blueColor]];
            //            }
            //                break;
            //        }
            //
            //        NSArray* (^getChartDataBlock) (NSInteger index, NSInteger dataType) = ^(NSInteger index, NSInteger dataType) {
            //            NSArray *dataArray = nil;
            //            switch(dataType)
            //            {
            //                case 1:
            //                {
            //                }
            //                    break;
            //                default:
            //                {
            //                    switch(index)
            //                    {
            //                        case 1:
            //                        {
            //                            dataArray = @[@20, @80, @30, @50, @10];
            //                        }
            //                            break;
            //                        case 2:
            //                        {
            //                            dataArray = @[@60, @180, @130, @160, @90];
            //                        }
            //                            break;
            //                    }
            //                }
            //                    break;
            //            }
            //
            //            return dataArray;
            //        };
            //
            //        [chartView setChartData:dataArray chartColorArray:colorArray chartTimeArray:timeArray backColor:nil/*[UIColor redColor]*/ contentBackColor:[UIColor brownColor]/*[UIColor blueColor]*/ xIsTime:NO andBlock:chartType == XYChartViewTypeLine ? getChartDataBlock : nil];
            //
            //        [self.view addSubview:chartView];
            //    }
            
            rect.origin.y += rect.size.height + 100;
            rect.size = CGSizeMake(50, 30);
            UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
            if(button)
            {
                button.frame = rect;
                button.backgroundColor = [UIColor grayColor];
                
                [button setBlock:^(UIButton *sender) {
                    NSArray *dataArray = @[@20, @80, @30, @50, @10];
                    NSArray *colorArray = @[[UIColor orangeColor], [UIColor grayColor], [UIColor greenColor], [UIColor yellowColor], [UIColor purpleColor]];
                    //NSArray *timeArray = @[@"09-13", @"09-12", @"09-11", @"09-10", @"09-09"];
                    
                    //[chartView setChartData:dataArray chartColorArray:colorArray chartTimeArray:timeArray backColor:nil/*[UIColor redColor]*/ contentBackColor:nil/*[UIColor blueColor]*/ xIsTime:YES andBlock:nil];
                    
                    [chartView setLineData:1 lineDataArray:dataArray lineColor:colorArray[0] fillColor:colorArray[0] fillAlpha:0.5 valueRadius:4 valueLineWidth:1 valueLineColor:colorArray[0] valueFillColor:colorArray[0] andBlock:^(XYChartViewSetLineChartDataBlock setLineChartDataBlock) {
                        if(setLineChartDataBlock)
                        {
                            //NSArray *dataArray = @[@20, @80, @30, @50, @10];
                            //setLineChartDataBlock(dataArray, colorArray[1], colorArray[1], colorArray[1], colorArray[1]);
                        }
                    }];
                }];
                
                [self.view addSubview:button];
            }
        }
            break;
        case 1:
        {
            //*******添加scrollView*******
            [self createScrollView];
            
            //******创建立方体视图组******
            [self createCubicViewArray];
        }
            break;
        case 2:
        {
            rect = CGRectMake(60, 80, 200, 280);
            FlipView *flipView = [[FlipView alloc] initWithFrame:rect offset:40];
            if(flipView)
            {
                //flipView.backgroundColor = [UIColor grayColor];
                
                [self.view addSubview:flipView];
                
                NSTimer *timer = [NSTimer timerWithTimeInterval:3.0 repeats:YES block:^(NSTimer * _Nonnull timer) {
                    int m = 0;
                    if(m)
                    {
                        [flipView doFlip:3.0 text:[NSString stringWithFormat:@"%02i", arc4random() % 99]];
                    }
                }];
                [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
            }
        }
            break;
        case 3:
        {
            rect = CGRectMake(60, 60, 200, 280);
            UIView *backView = [[UIView alloc] initWithFrame:rect];
            if(backView)
            {
                backView.backgroundColor = [UIColor grayColor];
                
                [self.view addSubview:backView];
                
                rect.origin = CGPointZero;
                rect.size.height /= 2;
                
                UIView *view1 = [[UIView alloc] initWithFrame:rect];
                if(view1)
                {
                    view1.backgroundColor = [UIColor blueColor];
                    
                    CALayer *layer = view1.layer;
                    //layer.position = CGPointMake(layer.position.x - rect.size.width / 2, layer.position.y + rect.size.height / 2);
                    layer.anchorPoint = CGPointMake(0, 1);
                    
                    [backView addSubview:view1];
                }
                
                rect.origin.y += rect.size.height;
                UIView *view2 = [[UIView alloc] initWithFrame:rect];
                if(view2)
                {
                    view2.backgroundColor = [UIColor redColor];
                    
                    //                CALayer *layer = view2.layer;
                    //                layer.position = CGPointMake(layer.position.x - rect.size.width / 2, layer.position.y - rect.size.height / 2);
                    //                layer.anchorPoint = CGPointMake(0, 0);
                    
                    [backView addSubview:view2];
                }
                
                //            CATransform3D sublayerTransform = CATransform3DIdentity;
                //            sublayerTransform.m34 = -1.0 / 420.0;
                //            [backView.layer setSublayerTransform:sublayerTransform];
                //
                //            [UIView animateWithDuration:3.0 animations:^{
                //                view1.layer.transform = CATransform3DMakeRotation(M_PI_2, -1.0, 0.0, 0.0);
                //            } completion:^(BOOL finished) {
                //                view1.layer.transform = CATransform3DIdentity;
                //
                //                view2.layer.transform = CATransform3DMakeRotation(M_PI_2, 1.0, 0.0, 0.0);
                //
                //                [UIView animateWithDuration:3.0 animations:^{
                //                    view2.layer.transform = CATransform3DIdentity;
                //                } completion:^(BOOL finished) {
                //
                //                }];
                //            }];
            }
        }
            break;
        case 4:
        {
            float width = 150;
            float height = 150;
            CGSize frameSize = self.view.frame.size;
            rect = CGRectMake(80 + (frameSize.width - width) / 2, rect.origin.y + rect.size.height + 80, width, height);
            
            UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
            if(button)
            {
                button.frame = rect;
                button.backgroundColor = [UIColor clearColor];
                
                [button addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
                
                [self.view addSubview:button];
            }
            
            //背景
            [button addRoundCorner:rect cornerRadius:20 rectCorner:UIRectCornerAllCorners borderColor:[UIColor redColor] borderWidth:10 backColor:nil/*self.view.backgroundColor*/];
            
            rect.origin.y += rect.size.height;
            button = [UIButton buttonWithType:UIButtonTypeCustom];
            if(button)
            {
                button.frame = rect;
                button.backgroundColor = [UIColor blueColor];

                [button addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
                
                [self.view addSubview:button];
            }
        }
            break;
    }

#if(0)
    CGSize frameSize = self.view.frame.size;
    
    rect = self.view.frame;
    rect.origin.y = 30;
    rect.size.height = 30;
    
    CustomControlTextParam *titleParam;
    CustomControlTextParam *valueParam;
    //CustomControlTextParam *mustFlagParam;
    CustomControlDivideLineParam *divideLineParam;
    CustomControlMarginParam *marginParam;
    //CustomControlIconParam *iconParam;

    titleParam = [[CustomControlTextParam alloc] init];
    if(titleParam)
    {
        titleParam.text = @"测试";
        titleParam.textColor = [UIColor blackColor];
        titleParam.textFont = [UIFont systemFontOfSize:14];
        titleParam.textAlignment = NSTextAlignmentLeft;
    }
    
    valueParam = [[CustomControlTextParam alloc] init];
    if(valueParam)
    {
        valueParam.text = @"测试";
        valueParam.textColor = [UIColor blackColor];
        valueParam.textFont = [UIFont systemFontOfSize:14];
        valueParam.textAlignment = NSTextAlignmentRight;
    }
    
    divideLineParam = [[CustomControlDivideLineParam alloc] init];
    if(divideLineParam)
    {
        divideLineParam.lineType = 1;
        divideLineParam.lineWidth = 1;
        
        divideLineParam.leftMargin = 10;
        divideLineParam.rightMargin = 10;
        
        divideLineParam.lineColor = [UIColor blueColor];
    }
    
    marginParam = [[CustomControlMarginParam alloc] init];
    if(marginParam)
    {
        marginParam.leftMargin = 10;
        marginParam.topMargin = 10;
        marginParam.topMargin = 10;
        marginParam.bottomMargin = 10;
        
        marginParam.valueMargin = 10;
        marginParam.mustFlagMargin = 10;
    }
    
//        rect.size.width = 50;
//        rect.size.height = 50;
//        int margin = 14;
//        CGRect shapRect = CGRectMake(margin, margin, rect.size.width - margin - margin, rect.size.height - margin - margin);
//        NSArray *params = @[@(rect), @(shapRect), @(1), @(4), [UIColor redColor], [NSNull null], [UIColor whiteColor]];
//
//        UIView *view = [CustomControlLibrary performTarget:@"ShapeView" action:@"initWithFrame:shapeRect:shapeType:lineWidth:lineColor:fillColor:backColor:" params:params additionParams:nil isClassAction:NO shouldCacheTarget:NO];
//        if(view)
//        {
//            //view.frame = rect;
//
//            [self.view addSubview:view];
//        }

//        rect.size.width = 280;
//        rect.size.height = 280;
//        NSArray *params = @[@(rect), @(-0.8), @(1.0), @(8)];
//
//        UIView *view = [CustomControlLibrary performTarget:@"CarouselView" action:@"initWithFrame:inclination:backItemAlpha:itemCount:" params:params additionParams:nil isClassAction:NO shouldCacheTarget:NO];
//        if(view)
//        {
//            //view.backgroundColor = [UIColor blueColor];
//
//            [self.view addSubview:view];
//        }
//
//        return;
        
//        rect.origin.y += 60;
//        CGPoint point = {-100, -60};
//        NSArray *params = @[@(rect), @(90.0), @(point)];//@[@(rect), @(45.0), @(point)];
//
//        //UIView *view = [CustomControlLibrary performTarget:@"CubeView" action:@"initWithFrame:degrees:rotatePoint:" params:params additionParams:nil isClassAction:NO shouldCacheTarget:NO];
//        UIView *view = [CustomControlLibrary performTarget:@"CubeView" action:@"initWithFrame:degrees:rotatePoint:" params:params additionParams:nil isClassAction:NO shouldCacheTarget:NO];
//        if(view)
//        {
//            [self.view addSubview:view];
//        }
#endif
    
#if(0)
    //NSDictionary *params = nil;
    //[NSValue valueWithBytes:&titleParam objCType:@encode(CustomControlTextParam)
    //NSArray *params = @[self.view, @(rect), @(1), (__bridge id)&titleParam, (__bridge id)&valueParam, (__bridge id)&mustFlagParam, (__bridge id)&divideLineParam, @(0), @(0), (__bridge id)&marginParam, (__bridge id)&iconParam];
    NSArray *params = @[self.view, @(rect), @(1), titleParam, valueParam, [NSNull null], divideLineParam, @(0), @(0), marginParam, [NSNull null]];

    [CustomControlLibrary performTarget:@"NormalLineView" action:@"createNormalLineView:frame:lineViewType:titleParam:valueParam:mustFlagParam:divideLineParam:titleWidth:rightWidth:marginParam:iconParam:" params:params additionParams:nil isClassAction:YES shouldCacheTarget:NO];

    float width = 150;
    float height = 150;
    rect = CGRectMake(80 + (frameSize.width - width) / 2, rect.origin.y + rect.size.height + 80, width, height);
    
    CGPoint point = {-100, -60};
    params = @[@(rect), @(90.0), @(point)];//@[@(rect), @(45.0), @(point)];
    
    //UIView *view = [CustomControlLibrary performTarget:@"CubeView" action:@"initWithFrame:degrees:rotatePoint:" params:params additionParams:nil isClassAction:NO shouldCacheTarget:NO];
    UIView *view = [CustomControlLibrary performTarget:@"CubeView" action:@"initWithFrame:itemWidth:itemSpace:" params:@[@(rect), @(90.0), @(0)] additionParams:nil isClassAction:NO shouldCacheTarget:NO];
    //CubeView *view = [[CubeView alloc] initWithFrame:rect degrees:90 rotatePoint:point];
    if(view)
    {
        //self.cubeView = view;
        
        [self.view addSubview:view];
    }

    //[CustomControlLibrary performTarget:@"NormalLineView" action:@"updateValue:middleText:value:" params:params isClassAction:NO shouldCacheTarget:NO];
    
//    rect.origin.y += rect.size.height + 100;
//    rect.size.height = 30;
//    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
//    if(button)
//    {
//        button.frame = rect;
//        button.backgroundColor = [UIColor grayColor];
//
//        [button addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
//
//        [self.view addSubview:button];
//    }
#endif
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)buttonClicked:(id)sender
{
    //[self.cubeView doRotate];
}

- (NSArray *)getCircleApproximationTimingFunctions
{
    // The following CAMediaTimingFunction mimics zPosition = sin(t)
    // Empiric (possibly incorrect, but it does the job) implementation based on the circle approximation with bezier cubic curves
    // ( http://www.whizkidtech.redprince.net/bezier/circle/ )
    // sin(t) tangent for t=0 is a diagonal. But we have to remap x=[0;PI/2] to t=[0;1]. => scale with M_PI/2.0f factor
    
    const double kappa = 4.0/3.0 * (sqrt(2.0)-1.0) / sqrt(2.0);
    CAMediaTimingFunction *firstQuarterCircleApproximationFuction = [CAMediaTimingFunction functionWithControlPoints:kappa / (M_PI / 2.0f) :kappa :1.0 - kappa :1.0];
    CAMediaTimingFunction * secondQuarterCircleApproximationFuction = [CAMediaTimingFunction functionWithControlPoints:kappa :0.0 :1.0 - (kappa / (M_PI / 2.0f)) :1.0 - kappa];
    return @[firstQuarterCircleApproximationFuction, secondQuarterCircleApproximationFuction];
}

#pragma mark - 添加scrollView
- (void)createScrollView
{
    CGFloat contentW = 4 * self.view.bounds.size.width;
    CGFloat contentH = self.view.bounds.size.height;
    
    //scrollView的尺寸占据整个屏幕（可实现透视效果）
    self.scrollView = [[UIScrollView alloc] initWithFrame:self.view.bounds];
    
    //内容物大小
    _scrollView.contentSize = CGSizeMake(contentW, contentH);
    _scrollView.bounces = NO;
    _scrollView.backgroundColor = [UIColor orangeColor];
    
    _scrollView.pagingEnabled = YES;
    
    _scrollView.delegate = self;
    
    [self.view addSubview:_scrollView];
}

#pragma mark - 创建立方体视图组
- (void)createCubicViewArray
{
    //创建子视图
    
    UIImageView *imageView1 = [[UIImageView alloc] initWithFrame:self.view.frame];
    //imageView1.image = [UIImage imageNamed:@"1.jpeg"];
    imageView1.backgroundColor = [UIColor blueColor];
    
    UIImageView *imageView2 = [[UIImageView alloc] initWithFrame:self.view.frame];
    //imageView2.image = [UIImage imageNamed:@"2.jpeg"];
    imageView2.backgroundColor = [UIColor redColor];

    UIImageView *imageView3 = [[UIImageView alloc] initWithFrame:self.view.frame];
    //imageView3.image = [UIImage imageNamed:@"3.jpeg"];
    imageView3.backgroundColor = [UIColor greenColor];

    UIImageView *imageView4 = [[UIImageView alloc] initWithFrame:self.view.frame];
    //imageView4.image = [UIImage imageNamed:@"4.jpeg"];
    imageView4.backgroundColor = [UIColor yellowColor];

    //添加各视图到scrollView上面
    [self.scrollView addSubview:imageView1];
    [self.scrollView addSubview:imageView2];
    [self.scrollView addSubview:imageView3];
    [self.scrollView addSubview:imageView4];
    
    self.viewArray = @[imageView1, imageView2, imageView3, imageView4];
    
    //添加视图到scrollView上
    for(int i = 0; i < _viewArray.count; i++)
    {
        UIImageView *transView = _viewArray[i];
        
        //视图在scrollView上对应的位置
        CGRect frame = transView.frame;
        frame.origin.x = self.view.bounds.size.width * i;
        transView.frame = frame;
    }
}

#pragma mark - scrollView滑动事件
- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    //当前页数
    NSInteger currentPage = _currentPage;
    
    //当前视图
    UIView *currentView = _viewArray[currentPage];
    
    //上一个视图
    UIView *lastView = nil;
    
    if(currentPage - 1 >= 0)
    {
        lastView = _viewArray[currentPage - 1];
    }
    
    //下一个视图控制器视图
    UIView *nextView = nil;
    
    if(currentPage + 1 <= 3)
    {
        nextView = _viewArray[currentPage + 1];
    }
    
    //本次偏移距离
    CGFloat currentOffset = scrollView.contentOffset.x - currentPage * self.view.bounds.size.width;
    
    //本次偏移角度
    CGFloat deltaAngle = currentOffset / self.view.bounds.size.width * M_PI_2;
    
    CATransform3D (^makeTransformBlock)(CALayer *layer, CGPoint anchorPoint, float zPosition, float rotateAngle, float xMoveOffset, CGPoint perspectiveCenter) = ^(CALayer *layer, CGPoint anchorPoint, float zPosition, float rotateAngle, float xMoveOffset, CGPoint perspectiveCenter) {
//        //设置锚点
//        currentView.layer.anchorPoint = CGPointMake(0.5, 0.5);
//
//        //向屏幕前方移动
//        CATransform3D move = CATransform3DMakeTranslation(0, 0, self.view.bounds.size.width / 2);
//
//        //旋转
//        CATransform3D rotate = CATransform3DMakeRotation(-deltaAngle, 0, 1, 0);
//
//        //平移
//        CATransform3D plaintMove = CATransform3DMakeTranslation(currentOffset, 0, 0);
//
//        //向屏幕后方移动
//        CATransform3D back = CATransform3DMakeTranslation(0, 0, -self.view.bounds.size.width / 2);
//
//        //连接
//        CATransform3D concat = CATransform3DConcat(CATransform3DConcat(move, CATransform3DConcat(rotate, plaintMove)), back);
//
//        CATransform3D transform = CATransform3DPerspect2(concat, CGPointMake(currentOffset / 2, self.view.bounds.size.height), 5000.0f);
//
//        //添加变幻特效
//        currentView.layer.transform = transform;
        
        //向屏幕前方移动
        CATransform3D move = CATransform3DMakeTranslation(0, 0, zPosition);
        
        //旋转
        CATransform3D rotate = CATransform3DMakeRotation(rotateAngle, 0, 1, 0);
        
        //平移
        CATransform3D plaintMove = CATransform3DMakeTranslation(xMoveOffset, 0, 0);
        
        //向屏幕后方移动
        CATransform3D back = CATransform3DMakeTranslation(0, 0, -zPosition);
        
        //连接
        CATransform3D concat = CATransform3DConcat(CATransform3DConcat(move, CATransform3DConcat(rotate, plaintMove)), back);
        
        CATransform3D transform = CATransform3DPerspect2(concat, perspectiveCenter, 5000.0f);
        
        if(layer)
        {
            //设置锚点
            layer.anchorPoint = anchorPoint;
            
            //添加变幻特效
            layer.transform = transform;
        }
        
        return transform;
    };
    
    CGSize boundsSize = self.view.bounds.size;
    //****************当前视图移动变幻***************
    makeTransformBlock(currentView.layer, CGPointMake(0.5, 0.5), boundsSize.width / 2, -deltaAngle, currentOffset, CGPointMake(currentOffset / 2, boundsSize.height));
    
    if(nextView)
    {
        //****************下一个视图移动变幻***************
        //makeTransformBlock(nextView.layer, CGPointMake(0.5, 0.5), boundsSize.width / 2, -deltaAngle + M_PI_2, currentOffset - boundsSize.width, CGPointMake(boundsSize.width / 2 + currentOffset / 2, boundsSize.height));
        makeTransformBlock(nextView.layer, CGPointMake(0.5, 0.5), boundsSize.width / 2, -deltaAngle + M_PI_2, (currentOffset - boundsSize.width) - (currentOffset) * sin(-deltaAngle + M_PI_2), CGPointMake(boundsSize.width / 2 + currentOffset / 2, boundsSize.height));
    }
    else
    {
        if(lastView)
        {
            //****************上一个视图移动变幻***************
            makeTransformBlock(lastView.layer, CGPointMake(0.5, 0.5), boundsSize.width / 2, -deltaAngle - M_PI_2, currentOffset + boundsSize.width, CGPointMake(-boundsSize.width / 2 + currentOffset / 2, boundsSize.height));
        }
    }
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView
{
    //改变选中页序号
    [self changeIndex];
    
    //3D变幻恢复原状态
    for(UIView * view in _viewArray)
    {
        view.layer.transform = CATransform3DIdentity;
    }
}

- (void)changeIndex
{
    //改变选中的标签
    _currentPage = _scrollView.contentOffset.x / self.view.bounds.size.width;
}

@end
