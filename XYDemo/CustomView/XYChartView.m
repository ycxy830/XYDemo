//
//  XYChartView.m
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2018年 xy. All rights reserved.
//

#import "XYChartView.h"

#define kDegree2Radians(degrees) (degrees) * M_PI / 180.0
#define kRadians2Degree(radians) (radians) * 180.0 / M_PI

#define kOffsetRadius 10//偏移距离
#define kHollowCircleRadius 0//中间空心圆半径，默认为0实心

//#define kStrockWidth 5

@interface XYShapeLayer : CAShapeLayer

@property(nonatomic, assign)CGFloat startAngle; //开始角度
@property(nonatomic, assign)CGFloat endAngle;   //结束角度
@property(nonatomic, assign)BOOL    isSelected; //是否已经选中

@end

@implementation XYShapeLayer

- (void)dealloc
{
}

@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface XYChartView ()

@property(nonatomic, assign)XYChartViewType chartType;
@property(nonatomic, assign)CGRect contentRect;
@property(nonatomic, strong)CALayer *contentLayer;

@property(nonatomic, strong)NSArray *chartDataArray;
@property(nonatomic, strong)NSArray *chartColorArray;

@property(nonatomic, strong)UIColor *contentBackColor;

@property(nonatomic, strong)NSArray *chartPathArray;

@property(nonatomic, strong)NSArray *chartShapeArray;

//@property(nonatomic, strong)CAShapeLayer *gridLayer;

@property(nonatomic, strong)CAShapeLayer *maskLayer;

@property(nonatomic, strong)CAShapeLayer *selectedLayer;

@property(nonatomic, strong)NSArray *textShapeArray;

@property(nonatomic, assign)float xAxisLeftMargin;
@property(nonatomic, assign)float xAxisRightMargin;

@property(nonatomic, assign)float yAxisTopMargin;
@property(nonatomic, assign)float yAxisBottomMargin;

@property(nonatomic, assign)float axesLineWidth;
@property(nonatomic, strong)UIColor *axesLineColor;
@property(nonatomic, strong)UIColor *axesTextColor;
@property(nonatomic, assign)float axesFontHeight;

@property(nonatomic, assign)float xAxisTextHeight;
@property(nonatomic, assign)float xAxisTextTopMargin;

@property(nonatomic, assign)float yAxisTextWidth;
@property(nonatomic, assign)float yAxisTextRightMargin;

@property(nonatomic, assign)float valueDotDadius;
@property(nonatomic, assign)float valueDotLineWidth;
@property(nonatomic, strong)UIColor *valueDotLineColor;
@property(nonatomic, strong)UIColor *valueDotFillColor;

@property(nonatomic, assign)BOOL fillValuePath;

@end

@implementation XYChartView

+ (void)doAnimation:(CAShapeLayer *)layer keyPath:(NSString *)keyPath fromValue:(float)fromValue toValue:(float)toValue duration:(float)duration delegate:(id <CAAnimationDelegate>)delegate
{
    if(layer)
    {
        CABasicAnimation *animation = [CABasicAnimation animationWithKeyPath:keyPath];
        if(animation)
        {
            animation.delegate = delegate;
            
            animation.duration = duration;
            
            animation.fromValue = [NSNumber numberWithFloat:fromValue];
            animation.toValue = [NSNumber numberWithFloat:toValue];
            //animation.fromValue = [NSValue valueWithCGPoint:CGPointMake(-self.bounds.size.width, 0)];
            //animation.toValue = [NSValue valueWithCGPoint:CGPointZero];
            
            //禁止还原
            animation.autoreverses = NO;
            //禁止完成即移除
            animation.removedOnCompletion = NO;
            //让动画保持在最后状态
            animation.fillMode = kCAFillModeForwards;
            animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
            
            [layer addAnimation:animation forKey:keyPath];
        }
    }
}

- (XYChartView *)initWithFrame:(CGRect)frame chartType:(XYChartViewType)chartType contentEdgeInsets:(UIEdgeInsets)contentEdgeInsets
{
    self = [super initWithFrame:frame];
    if(self)
    {
        self.backgroundColor = [UIColor whiteColor];
        
        _chartType = chartType;
        _fillValuePath = YES;
        
        CGSize frameSize = frame.size;
        _contentRect = CGRectMake(contentEdgeInsets.left, contentEdgeInsets.top, frameSize.width - contentEdgeInsets.left - contentEdgeInsets.right, frameSize.height - contentEdgeInsets.top - contentEdgeInsets.bottom);
        
        if(chartType == XYChartViewTypeLine)
        {
            [self setChartParam:0 xAxisRightMargin:20 yAxisTopMargin:20 yAxisBottomMargin:0 axesLineWidth:1 axesLineColor:[UIColor blackColor] axesTextColor:[UIColor blackColor] axesFontHeight:14 xAxisTextHeight:30 xAxisTextTopMargin:10 yAxisTextWidth:40 yAxisTextRightMargin:10 valueDotDadius:4 valueDotLineWidth:1 valueDotLineColor:[UIColor redColor] valueDotFillColor:[UIColor blueColor]];
        }
        
        _contentLayer = [CALayer layer];
        if(_contentLayer)
        {
            _contentLayer.frame = _contentRect;
            _contentRect.origin = CGPointZero;
            
            [self.layer addSublayer:_contentLayer];
        }
    }
    
    return self;
}

- (void)dealloc
{
}

- (void)setMask:(CALayer *)layer
{
    //通过mask来控制显示区域
    self.maskLayer = [CAShapeLayer layer];
    if(_maskLayer)
    {
        //UIBezierPath *maskPath = [UIBezierPath bezierPathWithArcCenter:_center radius:self.bounds.size.width/4.f startAngle:-M_PI_2 endAngle:M_PI_2*3 clockwise:YES];
        //UIBezierPath *piePath = [UIBezierPath bezierPathWithArcCenter:_center radius:_radius + Hollow_Circle_Radius startAngle:-M_PI_2 endAngle:M_PI_2*3 clockwise:YES];
        
        UIBezierPath *maskPath = nil;
        
        float lineWidth = 0;
        CGSize rectSize = self.bounds.size;
        switch(_chartType)
        {
            case XYChartViewTypeLine:
            {
                maskPath = [UIBezierPath bezierPathWithRect:self.bounds];
                
                _maskLayer.position = CGPointMake(-rectSize.width, 0);
                //_maskLayer.anchorPoint = CGPointZero;
                
                _maskLayer.path = maskPath.CGPath;
            }
                break;
            case XYChartViewTypePie:
            {
                CGPoint arcCenter = CGPointMake(rectSize.width / 2, rectSize.height / 2);//CGPointMake(_contentRect.origin.x + rectSize.width / 2, _contentRect.origin.y + rectSize.height / 2);
                
                float radius = MIN(rectSize.width / 2, rectSize.height / 2);
                maskPath = [UIBezierPath bezierPathWithArcCenter:arcCenter radius:radius startAngle:0 endAngle:M_PI + M_PI clockwise:YES];
                
                lineWidth = 2 * (radius - kHollowCircleRadius);//self.bounds.size.width / 2.f;
                
                _maskLayer.strokeEnd = 0;

                //设置边框颜色为不透明，则可以通过边框的绘制来显示整个view
                _maskLayer.strokeColor = [UIColor greenColor].CGColor;
                _maskLayer.lineWidth = lineWidth;
                //设置填充颜色为透明，可以通过设置半径来设置中心透明范围
                _maskLayer.fillColor = [UIColor clearColor].CGColor;
                _maskLayer.path = maskPath.CGPath;
            }
                break;
            case XYChartViewTypeBar:
            {
                maskPath = [UIBezierPath bezierPathWithRect:self.bounds];
                
                _maskLayer.position = CGPointMake(-rectSize.width, 0);
                //_maskLayer.anchorPoint = CGPointZero;

                _maskLayer.path = maskPath.CGPath;
            }
                break;
        }
        
        if(layer)
        {
            layer.mask = _maskLayer;
        }
        else
        {
            self.layer.mask = _maskLayer;
        }
    }
}

- (void)stroke
{
    if(_maskLayer)
    {
        float fromValue = 0;
        float toValue = 0;
        NSString *keyPath = nil;
        
        switch(_chartType)
        {
            case XYChartViewTypeLine:
            {
                keyPath = @"position.x";
                
                fromValue = -self.bounds.size.width;
                toValue = 0.f;
            }
                break;
            case XYChartViewTypePie:
            {
                keyPath = @"strokeEnd";

                fromValue = 0.f;
                toValue = 1.f;
            }
                break;
            case XYChartViewTypeBar:
            {
                keyPath = @"position.x";

                fromValue = -self.bounds.size.width;
                toValue = 0.f;
            }
                break;
        }
        
        CABasicAnimation *animation = [CABasicAnimation animationWithKeyPath:keyPath];
        if(animation)
        {
            animation.duration = 1.f;
            
            animation.fromValue = [NSNumber numberWithFloat:fromValue];
            animation.toValue = [NSNumber numberWithFloat:toValue];
            //animation.fromValue = [NSValue valueWithCGPoint:CGPointMake(-self.bounds.size.width, 0)];
            //animation.toValue = [NSValue valueWithCGPoint:CGPointZero];
            
            //禁止还原
            animation.autoreverses = NO;
            //禁止完成即移除
            animation.removedOnCompletion = NO;
            //让动画保持在最后状态
            animation.fillMode = kCAFillModeForwards;
            animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
            
            [_maskLayer addAnimation:animation forKey:keyPath];
        }
    }
}

- (void)setChartParam:(float)xAxisLeftMargin xAxisRightMargin:(float)xAxisRightMargin yAxisTopMargin:(float)yAxisTopMargin yAxisBottomMargin:(float)yAxisBottomMargin axesLineWidth:(float)axesLineWidth axesLineColor:(UIColor *)axesLineColor axesTextColor:(UIColor *)axesTextColor axesFontHeight:(float)axesFontHeight xAxisTextHeight:(float)xAxisTextHeight xAxisTextTopMargin:(float)xAxisTextTopMargin yAxisTextWidth:(float)yAxisTextWidth yAxisTextRightMargin:(float)yAxisTextRightMargin valueDotDadius:(float)valueDotDadius valueDotLineWidth:(float)valueDotLineWidth valueDotLineColor:(UIColor *)valueDotLineColor valueDotFillColor:(UIColor *)valueDotFillColor
{
    self.xAxisLeftMargin = xAxisLeftMargin;
    self.xAxisRightMargin = xAxisRightMargin;

    self.yAxisTopMargin = yAxisTopMargin;
    self.yAxisBottomMargin = yAxisBottomMargin;
    
    self.axesLineWidth = axesLineWidth;
    self.axesLineColor = axesLineColor;
    self.axesTextColor = axesTextColor;
    self.axesFontHeight = axesFontHeight;
    
    self.xAxisTextHeight = xAxisTextHeight;
    self.xAxisTextTopMargin = xAxisTextTopMargin;
    
    self.yAxisTextWidth = yAxisTextWidth;
    self.yAxisTextRightMargin = yAxisTextRightMargin;
    
    self.valueDotDadius = valueDotDadius;
    self.valueDotLineWidth = valueDotLineWidth;
    self.valueDotLineColor = valueDotLineColor;
    self.valueDotFillColor = valueDotFillColor;
}

- (void)setChartData:(NSArray *)chartDataArray chartColorArray:(NSArray *)chartColorArray chartTimeArray:(NSArray *)chartTimeArray backColor:(UIColor *)backColor contentBackColor:(UIColor *)contentBackColor xIsTime:(BOOL)xIsTime andBlock:(XYChartViewGetChartDataBlock)block
{
    self.chartDataArray = chartDataArray;
    self.chartColorArray = chartColorArray;
    
    if(backColor)
    {
        self.backgroundColor = backColor;
    }
    
    if(contentBackColor)
    {
        self.contentBackColor = contentBackColor;
    }
    
    if(_contentLayer)
    {
        NSArray<CALayer *> *sublayers = _contentLayer.sublayers;
        while([sublayers count])
        {
            [sublayers[0] removeFromSuperlayer];
            
            sublayers = _contentLayer.sublayers;
        }
        
        if(contentBackColor)
        {
            _contentLayer.backgroundColor = contentBackColor.CGColor;
        }
    }
    
    switch(_chartType)
    {
        case XYChartViewTypeLine:
        {
            NSInteger dataCount = [chartDataArray count];
            NSInteger timeCount = [chartTimeArray count];
            
            if(dataCount > 1 && timeCount > 1)
            {
                NSInteger lastDataIndex = dataCount - 1;

                float gridWidth = _contentRect.size.width - _xAxisLeftMargin - _xAxisRightMargin - _yAxisTextWidth - _yAxisTextRightMargin;
                float gridHeight = _contentRect.size.height - _yAxisTopMargin - _yAxisBottomMargin - _xAxisTextHeight - _xAxisTextTopMargin;

                //xIsTime为YES表示X为时间，Y为值
                NSInteger xAxisCount;
                NSInteger yAxisCount;
                
                if(xIsTime)
                {
                    xAxisCount = timeCount;
                    yAxisCount = dataCount;
                }
                else
                {
                    xAxisCount = dataCount;
                    yAxisCount = timeCount;
                }
                
                float gridItemWidth = gridWidth / (xAxisCount - 1);
                float gridItemHeight = gridHeight / (yAxisCount - 1);
                
                float maxData = 0;
                CGPoint startPoint = {_contentRect.origin.x + _xAxisLeftMargin + _yAxisTextWidth + _yAxisTextRightMargin, _contentRect.origin.y + _yAxisTopMargin};
                
                float fontHeight = _axesFontHeight;
                UIFont *textFont = [UIFont systemFontOfSize:fontHeight];
                UIColor *textColor = _axesTextColor;
                
                UIBezierPath *linePath = [UIBezierPath bezierPath];
                if(linePath)
                {
                    CATextLayer* (^createTextBlock)(CGRect rect, NSString *text) = ^(CGRect rect, NSString *text) {
                        CATextLayer *layer = [CATextLayer layer];
                        if(layer)
                        {
                            layer.frame = rect;
                            layer.string = text;
                            //layer.font = (__bridge CTFontRef)[UIFont systemFontOfSize:14];
                            layer.fontSize = fontHeight;//textFont.lineHeight;
                            layer.foregroundColor = textColor.CGColor;
                        }
                        
                        return layer;
                    };
                    
                    //画X坐标
                    CGPoint point = startPoint;
                    for(int i = 0; i < xAxisCount; i++)
                    {
                        [linePath moveToPoint:point];
                        [linePath addLineToPoint:CGPointMake(point.x + gridWidth, point.y)];
                        
                        point.y += gridItemHeight;
                    }

                    //画Y坐标
                    point = startPoint;
                    for(int i = 0; i < yAxisCount; i++)
                    {
                        [linePath moveToPoint:point];
                        [linePath addLineToPoint:CGPointMake(point.x, point.y + gridHeight)];

                        point.x += gridItemWidth;
                    }
                    
                    //设置值的最大值
                    for(int i = 0; i < dataCount; i++)
                    {
                        float value = ((NSNumber *)chartDataArray[i]).floatValue;
                        if(value > maxData)
                        {
                            maxData = value;
                        }
                    }
                    
                    if(block)
                    {
                        for(int i = 1; i < [chartColorArray count]; i++)
                        {
                            NSArray *chartDataArray = block(i, 0);
                            if(chartDataArray)
                            {
                                for(int i = 0; i < [chartDataArray count]; i++)
                                {
                                    float value = ((NSNumber *)chartDataArray[i]).floatValue;
                                    if(value > maxData)
                                    {
                                        maxData = value;
                                    }
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                    //画坐标轴的值和具体的值
                    CAShapeLayer *shapeLayer = [CAShapeLayer layer];
                    if(shapeLayer)
                    {
                        NSString* (^getValueBlock)(BOOL isXValue, NSArray *dataArray, NSInteger dataCount, NSInteger index) = ^(BOOL isXValue, NSArray *dataArray, NSInteger dataCount, NSInteger index) {
                            NSString *value = @"";
                            if((xIsTime && isXValue) || (!xIsTime && !isXValue))
                            {
                                //显示坐标时间
                                if(isXValue)
                                {
                                    index = dataCount - 1 - index;//日期最新的显示在后面
                                }
                                
                                if([dataArray[index] isKindOfClass:[NSNumber class]])
                                {
                                    value = [NSString stringWithFormat:@"%.2f", ((NSNumber *)dataArray[index]).floatValue];
                                }
                                else if([dataArray[index] isKindOfClass:[NSString class]])
                                {
                                    value = dataArray[index];
                                }
                            }
                            else
                            {
                                //显示坐标值
                                NSInteger count = dataCount;
                                if(dataCount > 1)
                                {
                                    count--;
                                }
                                
                                if(isXValue)
                                {
                                    value = [NSString stringWithFormat:@"%.2f", maxData / count * index];
                                }
                                else
                                {
                                    //value = [NSString stringWithFormat:@"%.2f", maxData / count * index];//上面值最小
                                    value = [NSString stringWithFormat:@"%.2f", maxData - maxData / count * index];//上面值最大
                                }
                            }
                            
                            return value;
                        };
                        
                        //X坐标值
                        NSArray *dataArray = xIsTime ? chartTimeArray : chartDataArray;
                        
                        CGRect rect = CGRectMake(startPoint.x - gridItemWidth / 2, startPoint.y + gridHeight + _xAxisTextTopMargin, gridItemWidth, _xAxisTextHeight);
                        for(int i = 0; i < xAxisCount; i++)
                        {
                            NSString *value = getValueBlock(YES, dataArray, xAxisCount, i);

                            CATextLayer *textLayer = createTextBlock(rect, value);
                            if(textLayer)
                            {
                                textLayer.alignmentMode = kCAAlignmentCenter;//@"center";

                                [shapeLayer addSublayer:textLayer];
                            }
                            
                            rect.origin.x += gridItemWidth;
                        }
                        
                        //Y坐标值
                        dataArray = xIsTime ? chartDataArray : chartTimeArray;
                        
                        float yTextHeight = textFont.lineHeight;
                        rect = CGRectMake(_contentRect.origin.x + _xAxisLeftMargin, startPoint.y - yTextHeight / 2, _yAxisTextWidth, yTextHeight);
                        for(int i = 0; i < yAxisCount; i++)
                        {
                            NSString *value = getValueBlock(NO, dataArray, yAxisCount, i);

                            CATextLayer *textLayer = createTextBlock(rect, value);
                            if(textLayer)
                            {
                                textLayer.alignmentMode = kCAAlignmentRight;//@"right";
                                //if(i % 2)
                                //{
                                //    textLayer.backgroundColor = [UIColor redColor].CGColor;
                                //}
                                //else
                                //{
                                //    textLayer.backgroundColor = [UIColor blueColor].CGColor;
                                //}
                                ////textLayer.contentsGravity = kCAGravityCenter;//@"center";

                                [shapeLayer addSublayer:textLayer];
                            }
                            
                            rect.origin.y += gridItemHeight;
                        }
                        
                        startPoint.y += gridHeight;//从下往上画
                        
                        CAShapeLayer *animLayer = [CAShapeLayer layer];

                        //画具体的值
                        for(int i = 0; i < [chartColorArray count]; i++)
                        {
                            UIColor *color = chartColorArray[i];
                            
                            CAShapeLayer *valueLayer = [CAShapeLayer layer];
                            if(valueLayer)
                            {
                                UIBezierPath *dotPath = nil;
                                UIBezierPath *fillPath = nil;

                                UIBezierPath *linePath = [UIBezierPath bezierPath];
                                if(linePath)
                                {
                                    float dotDadius = _valueDotDadius;
                                    void (^darwDotBlock)(UIBezierPath *dotPath, CGPoint point) = ^(UIBezierPath *dotPath, CGPoint point) {
                                        [dotPath addArcWithCenter:point radius:dotDadius startAngle:0 endAngle:M_PI + M_PI clockwise:YES];
                                    };
                                    
                                    CGPoint point;
                                    if(xIsTime)
                                    {
                                        //值最新的显示在后面
                                        point = CGPointMake(startPoint.x, startPoint.y - ((NSNumber *)chartDataArray[lastDataIndex]).floatValue / maxData * gridHeight);
                                    }
                                    else
                                    {
                                        //值最新的显示在上面
                                        point = CGPointMake(startPoint.x + ((NSNumber *)chartDataArray[lastDataIndex]).floatValue / maxData * gridWidth, startPoint.y);
                                    }
                                    [linePath moveToPoint:point];

                                    dotPath = [UIBezierPath bezierPath];
                                    if(dotPath)
                                    {
                                        [dotPath moveToPoint:CGPointMake(point.x + dotDadius, point.y)];
                                        darwDotBlock(dotPath, point);
                                    }

                                    fillPath = [UIBezierPath bezierPath];
                                    if(fillPath)
                                    {
                                        [fillPath moveToPoint:startPoint];
                                        [fillPath addLineToPoint:point];
                                    }
                                    
                                    if(timeCount > 1 && maxData > 0)
                                    {
                                        CGPoint endPoint = CGPointZero;
                                        
                                        for(int i = 1; i < timeCount; i++)
                                        {
                                            if(xIsTime)
                                            {
                                                //值最新的显示在后面
                                                endPoint = CGPointMake(startPoint.x + i * gridItemWidth, startPoint.y - ((NSNumber *)chartDataArray[lastDataIndex - i]).floatValue / maxData * gridHeight);
                                            }
                                            else
                                            {
                                                //值最新的显示在上面
                                                endPoint = CGPointMake(startPoint.x + ((NSNumber *)chartDataArray[lastDataIndex - i]).floatValue / maxData * gridWidth, startPoint.y - i * gridItemHeight);
                                            }
                                            [linePath addLineToPoint:endPoint];

                                            if(dotPath)
                                            {
                                                [dotPath moveToPoint:CGPointMake(endPoint.x + dotDadius, endPoint.y)];
                                                darwDotBlock(dotPath, endPoint);
                                            }
                                            
                                            if(fillPath)
                                            {
                                                [fillPath addLineToPoint:endPoint];
                                            }
                                        }
                                        
                                        if(fillPath)
                                        {
                                            if(xIsTime)
                                            {
                                                [fillPath addLineToPoint:CGPointMake(endPoint.x, startPoint.y)];
                                            }
                                            else
                                            {
                                                [fillPath addLineToPoint:CGPointMake(startPoint.x, endPoint.y)];
                                            }
                                        }
                                    }
                                }

                                if(_fillValuePath)
                                {
                                    CAShapeLayer *valueFillLayer = [CAShapeLayer layer];
                                    if(valueFillLayer)
                                    {
                                        //填充值包含的区域
                                        valueFillLayer.path = fillPath.CGPath;
                                        
                                        //UIColor *color = [UIColor purpleColor];
                                        valueFillLayer.fillColor = color.CGColor;
                                        valueFillLayer.opacity = 0.5;
                                        
                                        if(animLayer)
                                        {
                                            [animLayer addSublayer:valueFillLayer];
                                        }
                                        else
                                        {
                                            [shapeLayer addSublayer:valueFillLayer];
                                        }
                                    }
                                }

                                valueLayer.path = linePath.CGPath;
                                
                                valueLayer.lineWidth = 1;
                                valueLayer.strokeColor = color.CGColor;
                                valueLayer.fillColor = [UIColor clearColor].CGColor;
                                
                                if(animLayer)
                                {
                                    [animLayer addSublayer:valueLayer];
                                }
                                else
                                {
                                    [shapeLayer addSublayer:valueLayer];
                                }
                                
                                if(dotPath)
                                {
                                    CAShapeLayer *dotFillLayer = [CAShapeLayer layer];
                                    if(dotFillLayer)
                                    {
                                        dotFillLayer.path = dotPath.CGPath;
                                        
                                        dotFillLayer.lineWidth = _valueDotLineWidth;
                                        dotFillLayer.strokeColor = color.CGColor;//_valueDotLineColor.CGColor;
                                        dotFillLayer.fillColor = color.CGColor;//_valueDotFillColor.CGColor;
                                        
                                        if(animLayer)
                                        {
                                            [animLayer addSublayer:dotFillLayer];
                                        }
                                        else
                                        {
                                            [shapeLayer addSublayer:dotFillLayer];
                                        }
                                    }
                                }
                                
                                if(animLayer)
                                {
                                    [shapeLayer addSublayer:animLayer];
                                }
                            }
                            
                            if(block)
                            {
                                chartDataArray = block(i + 1, 0);
                                if(!chartDataArray)
                                {
                                    break;
                                }
                            }
                        }
                        
                        shapeLayer.path = linePath.CGPath;
                        
                        shapeLayer.lineWidth = _axesLineWidth;
                        shapeLayer.strokeColor = _axesLineColor.CGColor;
                        
                        [_contentLayer addSublayer:shapeLayer];
                        
                        [self setMask:animLayer];
                        [self stroke];
                    }
                }
            }
        }
            break;
        case XYChartViewTypePie:
        {
            CGSize rectSize = CGSizeMake(_contentRect.size.width - _xAxisLeftMargin - _xAxisRightMargin, _contentRect.size.height - _yAxisTopMargin - _yAxisBottomMargin);
            CGPoint arcCenter = CGPointMake(_contentRect.origin.x + _xAxisLeftMargin + rectSize.width / 2, _contentRect.origin.y + _yAxisTopMargin + rectSize.height / 2);
            
            float radius = MIN(rectSize.width / 2, rectSize.height / 2);
            float startAngle = 0;
            
            float totalValue = 0;
            NSInteger count = [chartDataArray count];
            for(int i = 0; i < count; i++)
            {
                NSNumber *value = [chartDataArray objectAtIndex:i];
                if([value isKindOfClass:[NSNumber class]] || [value isKindOfClass:[NSString class]])
                {
                    totalValue += value.floatValue;
                }
            }
            
            float fontHeight = _axesFontHeight;
            UIFont *textFont = [UIFont systemFontOfSize:fontHeight];
            //UIColor *textColor = _axesTextColor;
            float textWidth = _yAxisTextWidth;
            float textHeight = textFont.lineHeight;
            float textMargin = _yAxisTextRightMargin;
            float radiusLineWidth = _xAxisTextTopMargin;
            float textLineWidth = _xAxisTextHeight;

            UIBezierPath* (^addLineAndTextBlock)(float angle, CAShapeLayer *shapeLayer, NSString *text, UIColor *textColor) = ^(float angle, CAShapeLayer *shapeLayer, NSString *text, UIColor *textColor) {
                UIBezierPath *path = [UIBezierPath bezierPath];
                if(path)
                {
                    float x = arcCenter.x + radius * cos(angle);
                    float y = arcCenter.y + radius * sin(angle);
                    
                    float value = radiusLineWidth;//20;//扇形角度直线长度
                    [path moveToPoint:CGPointMake(x, y)];
                    x += value * cos(angle);
                    y += value * sin(angle);
                    [path addLineToPoint:CGPointMake(x, y)];
                    
                    value = textLineWidth;//40;//值的直线长度
                    float textX = x;
                    int align = 0;
                    
                    if(angle > M_PI_2 && angle < M_PI_2 + M_PI)
                    {
                        //值显示在左边
                        x -= value;
                        
                        textX = x - textWidth - textMargin;
                    }
                    else
                    {
                        //值显示在右边
                        x += value;
                        
                        textX = x + textMargin;
                        align = 1;
                    }
                    [path addLineToPoint:CGPointMake(x, y)];
                    
                    CGRect rect = CGRectMake(textX, y - textHeight / 2, textWidth, textHeight);
                    if(shapeLayer)
                    {
                        CATextLayer *layer = [CATextLayer layer];
                        if(layer)
                        {
                            layer.frame = rect;
                            layer.string = text;
                            //layer.font = (__bridge CTFontRef)[UIFont systemFontOfSize:14];
                            layer.fontSize = fontHeight;
                            layer.foregroundColor = textColor.CGColor;
                            
                            if(align == 1)
                            {
                                layer.alignmentMode = kCAAlignmentLeft;
                            }
                            else
                            {
                                layer.alignmentMode = kCAAlignmentRight;//@"right";
                            }

                            [shapeLayer addSublayer:layer];
                        }
                    }
                    //else
                    //{
                    //    UILabel *label = [[UILabel alloc] initWithFrame:rect];
                    //    if(label)
                    //    {
                    //        label.text = text;
                    //
                    //        [self addSubview:label];
                    //    }
                    //}
                }
                
                return path;
            };

            if(totalValue > 0)
            {
#if(1)
                //UIBezierPath *piePath = [UIBezierPath bezierPathWithArcCenter:arcCenter radius:radius startAngle:0 endAngle:M_PI + M_PI clockwise:YES];

                for(int i = 0; i < count; i++)
                {
                    NSNumber *value = [chartDataArray objectAtIndex:i];
                    if([value isKindOfClass:[NSNumber class]] || [value isKindOfClass:[NSString class]])
                    {
                        //画对应的扇形
                        float percent = value.floatValue / totalValue;
                        float angle = percent * (M_PI + M_PI);
                        float endAngle = startAngle + angle;
                        
                        UIBezierPath *path = [UIBezierPath bezierPath];//[UIBezierPath bezierPathWithArcCenter:arcCenter radius:radius startAngle:startAngle endAngle:endAngle clockwise:NO];
                        [path moveToPoint:arcCenter];
                        [path addArcWithCenter:arcCenter radius:radius startAngle:startAngle endAngle:endAngle clockwise:YES];
                        [path addLineToPoint:arcCenter];
                        [path closePath];

                        //CAShapeLayer *shapeLayer = [CAShapeLayer layer];
                        XYShapeLayer *shapeLayer = [XYShapeLayer layer];
                        if(shapeLayer)
                        {
                            //shapeLayer.strokeStart = startAngle;
                            //shapeLayer.strokeEnd = endAngle;
                            shapeLayer.startAngle = startAngle;
                            shapeLayer.endAngle = endAngle;
                            
                            shapeLayer.path = path.CGPath;
                            
                            UIColor *color = [chartColorArray objectAtIndex:i];
                            shapeLayer.lineWidth = _axesLineWidth;
                            shapeLayer.strokeColor = color.CGColor;//[UIColor purpleColor].CGColor;
                            shapeLayer.fillColor = color.CGColor;
                            
                            //显示对应的值
                            CAShapeLayer *valueLayer = [CAShapeLayer layer];
                            if(valueLayer)
                            {
                                angle = startAngle + angle / 2;
                                NSString *text = [NSString stringWithFormat:@"%@:%.2f%%", @""/*chartTimeArray[i]*/, 100.0 * percent];
                                UIBezierPath *path = addLineAndTextBlock(angle, valueLayer, text, color);
                                if(path)
                                {
                                    valueLayer.path = path.CGPath;

                                    valueLayer.lineWidth = _axesLineWidth;
                                    valueLayer.strokeColor = color.CGColor;
                                    valueLayer.fillColor = [UIColor clearColor].CGColor;
                                }
                                
                                [shapeLayer addSublayer:valueLayer];
                            }
                            
                            [_contentLayer addSublayer:shapeLayer];
                        }
                        startAngle = endAngle;
                    }
                }

                [self setMask:nil];
                [self stroke];
#else
                NSMutableArray *pathArray = [NSMutableArray array];
                if(pathArray)
                {
                    NSMutableArray *textArray = [NSMutableArray array];

                    for(int i = 0; i < count; i++)
                    {
                        NSNumber *value = [chartDataArray objectAtIndex:i];
                        if([value isKindOfClass:[NSNumber class]] || [value isKindOfClass:[NSString class]])
                        {
                            float percent = value.floatValue / totalValue;
                            float angle = percent * (M_PI + M_PI);
                            float endAngle = startAngle + angle;

                            UIBezierPath *path = [UIBezierPath bezierPath];//[UIBezierPath bezierPathWithArcCenter:arcCenter radius:radius startAngle:startAngle endAngle:endAngle clockwise:NO];
                            [path moveToPoint:arcCenter];
                            [path addArcWithCenter:arcCenter radius:radius startAngle:startAngle endAngle:endAngle clockwise:YES];
                            [path addLineToPoint:arcCenter];
                            [path closePath];
                            
                            if(path)
                            {
                                [pathArray addObject:path];
                                
                                angle = startAngle + angle / 2;
                                NSString *text = [NSString stringWithFormat:@"%@:%.2f%%", @""/*chartTimeArray[i]*/, 100.0 * percent];
                                path = addLineAndTextBlock(angle, nil, text, chartColorArray[i]);
                                if(path)
                                {
                                    [textArray addObject:path];
                                }
                            }
                            startAngle = endAngle;
                        }
                    }
                    
                    if([pathArray count])
                    {
                        self.chartPathArray = [NSArray arrayWithArray:pathArray];
                        
                        [self setMask:nil];
                        [self stroke];
                        
                        if([textArray count])
                        {
                            self.textShapeArray = [NSArray arrayWithArray:textArray];
                        }
                    }
                }
#endif
            }
        }
            break;
        case XYChartViewTypeBar:
        {
#if(1)
            NSInteger dataCount = [chartDataArray count];
            NSInteger timeCount = [chartTimeArray count];
            
            float maxData = 0;
            
            //设置值的最大值
            for(int i = 0; i < dataCount; i++)
            {
                float value = ((NSNumber *)chartDataArray[i]).floatValue;
                if(value > maxData)
                {
                    maxData = value;
                }
            }
            
            if(block)
            {
                //可能画多组数据
                for(int i = 1; i < [chartColorArray count]; i++)
                {
                    NSArray *chartDataArray = block(i, 0);
                    if(chartDataArray)
                    {
                        for(int i = 0; i < [chartDataArray count]; i++)
                        {
                            float value = ((NSNumber *)chartDataArray[i]).floatValue;
                            if(value > maxData)
                            {
                                maxData = value;
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            CALayer *axesLayer = [self createAxes:xIsTime dataCount:dataCount timeCount:timeCount maxValue:maxData chartTimeArray:chartTimeArray xAxisDrawCount:1 yAxisDrawCount:1];
            if(axesLayer)
            {
                [_contentLayer addSublayer:axesLayer];
            }

            if(maxData > 0)
            {
                CALayer *valueLayer = [self createValue:xIsTime dataCount:dataCount maxValue:maxData chartDataArray:chartDataArray chartColorArray:chartColorArray];
                if(valueLayer)
                {
                    [_contentLayer addSublayer:valueLayer];
                }
                
                if(block)
                {
                }
                
                [self setMask:valueLayer];
                [self stroke];
            }
#else
            NSMutableArray *pathArray = [NSMutableArray array];
            if(pathArray)
            {
                CGSize rectSize = _contentRect.size;
                
                NSInteger count = [chartDataArray count];
                
                float maxValue = 0;
                for(int i = 0; i < count; i++)
                {
                    NSNumber *value = [chartDataArray objectAtIndex:i];
                    if([value isKindOfClass:[NSNumber class]] || [value isKindOfClass:[NSString class]])
                    {
                        if(value.floatValue > maxValue)
                        {
                            maxValue = value.floatValue;
                        }
                    }
                }

                if(maxValue > 0)
                {
                    float valueWidth = rectSize.width / (count + count - 1);
                    CGRect rect = CGRectMake(_contentRect.origin.x, _contentRect.origin.y, valueWidth, rectSize.height);
                    
                    for(int i = 0; i < count; i++)
                    {
                        NSNumber *value = [chartDataArray objectAtIndex:i];
                        if([value isKindOfClass:[NSNumber class]] || [value isKindOfClass:[NSString class]])
                        {
                            rect.size.height = rectSize.height * value.floatValue / maxValue;
                            rect.origin.y = _contentRect.origin.y + rectSize.height - rect.size.height;
                            
                            UIBezierPath *path = [UIBezierPath bezierPathWithRect:rect];
                            if(path)
                            {
                                [pathArray addObject:path];
                            }
                            
                            rect.origin.x += valueWidth + valueWidth;
                        }
                    }

                    if([pathArray count])
                    {
                        self.chartPathArray = [NSArray arrayWithArray:pathArray];
                        
                        [self setMask:nil];
                        [self stroke];
                    }
                }
            }
#endif
        }
            break;
    }
}

- (CAShapeLayer *)createAxes:(BOOL)xIsTime dataCount:(NSInteger)dataCount timeCount:(NSInteger)timeCount maxValue:(float)maxValue chartTimeArray:(NSArray *)chartTimeArray xAxisDrawCount:(NSInteger)xAxisDrawCount yAxisDrawCount:(NSInteger)yAxisDrawCount
{
    //生成坐标轴
    CAShapeLayer *axesLayer = nil;
    
    float gridWidth = _contentRect.size.width - _xAxisLeftMargin - _xAxisRightMargin - _yAxisTextWidth - _yAxisTextRightMargin;
    float gridHeight = _contentRect.size.height - _yAxisTopMargin - _yAxisBottomMargin - _xAxisTextHeight - _xAxisTextTopMargin;
    
    //xIsTime为YES表示X为时间，Y为值
    NSInteger xAxisCount;
    NSInteger yAxisCount;
    
    if(xIsTime)
    {
        xAxisCount = timeCount;
        yAxisCount = dataCount;
    }
    else
    {
        xAxisCount = dataCount;
        yAxisCount = timeCount;
    }
    
    if(xAxisDrawCount < 1)
    {
        xAxisDrawCount = xAxisCount;
    }
    
    if(yAxisDrawCount < 1)
    {
        yAxisDrawCount = yAxisCount;
    }

    float gridItemWidth = gridWidth / (xAxisCount - 1);
    float gridItemHeight = gridHeight / (yAxisCount - 1);
    
    float maxData = maxValue;
    NSArray *chartDataArray = nil;
    
    CGPoint startPoint = {_contentRect.origin.x + _xAxisLeftMargin + _yAxisTextWidth + _yAxisTextRightMargin, _contentRect.origin.y + _yAxisTopMargin};
    
    float fontHeight = _axesFontHeight;
    UIFont *textFont = [UIFont systemFontOfSize:fontHeight];
    UIColor *textColor = _axesTextColor;
    
    UIBezierPath *linePath = [UIBezierPath bezierPath];
    if(linePath)
    {
        CATextLayer* (^createTextBlock)(CGRect rect, NSString *text) = ^(CGRect rect, NSString *text) {
            CATextLayer *layer = [CATextLayer layer];
            if(layer)
            {
                layer.frame = rect;
                layer.string = text;
                //layer.font = (__bridge CTFontRef)[UIFont systemFontOfSize:14];
                layer.fontSize = fontHeight;//textFont.lineHeight;
                layer.foregroundColor = textColor.CGColor;
            }
            
            return layer;
        };
        
        //画X坐标
        CGPoint point = startPoint;
        point.y += gridHeight;
        for(int i = 0; i < xAxisDrawCount; i++)
        {
            [linePath moveToPoint:point];
            [linePath addLineToPoint:CGPointMake(point.x + gridWidth, point.y)];
            
            point.y -= gridItemHeight;
        }
        
        //画Y坐标
        point = startPoint;
        for(int i = 0; i < yAxisDrawCount; i++)
        {
            [linePath moveToPoint:point];
            [linePath addLineToPoint:CGPointMake(point.x, point.y + gridHeight)];
            
            point.x += gridItemWidth;
        }
        
        //画坐标轴的值
        axesLayer = [CAShapeLayer layer];
        if(axesLayer)
        {
            NSString* (^getValueBlock)(BOOL isXValue, NSArray *dataArray, NSInteger dataCount, NSInteger index) = ^(BOOL isXValue, NSArray *dataArray, NSInteger dataCount, NSInteger index) {
                NSString *value = @"";
                if((xIsTime && isXValue) || (!xIsTime && !isXValue))
                {
                    //显示坐标时间
                    if(isXValue)
                    {
                        index = dataCount - 1 - index;//日期最新的显示在后面
                    }
                    
                    if([dataArray[index] isKindOfClass:[NSNumber class]])
                    {
                        value = [NSString stringWithFormat:@"%.2f", ((NSNumber *)dataArray[index]).floatValue];
                    }
                    else if([dataArray[index] isKindOfClass:[NSString class]])
                    {
                        value = dataArray[index];
                    }
                }
                else
                {
                    //显示坐标值
                    NSInteger count = dataCount;
                    if(dataCount > 1)
                    {
                        count--;
                    }
                    
                    if(isXValue)
                    {
                        value = [NSString stringWithFormat:@"%.2f", maxData / count * index];
                    }
                    else
                    {
                        //value = [NSString stringWithFormat:@"%.2f", maxData / count * index];//上面值最小
                        value = [NSString stringWithFormat:@"%.2f", maxData - maxData / count * index];//上面值最大
                    }
                }
                
                return value;
            };
            
            //X坐标值
            NSArray *dataArray = xIsTime ? chartTimeArray : chartDataArray;
            
            CGRect rect = CGRectMake(startPoint.x - gridItemWidth / 2, startPoint.y + gridHeight + _xAxisTextTopMargin, gridItemWidth, _xAxisTextHeight);
            for(int i = 0; i < xAxisCount; i++)
            {
                NSString *value = getValueBlock(YES, dataArray, xAxisCount, i);
                
                CATextLayer *textLayer = createTextBlock(rect, value);
                if(textLayer)
                {
                    textLayer.alignmentMode = kCAAlignmentCenter;//@"center";
                    
                    [axesLayer addSublayer:textLayer];
                }
                
                rect.origin.x += gridItemWidth;
            }
            
            //Y坐标值
            dataArray = xIsTime ? chartDataArray : chartTimeArray;
            
            float yTextHeight = textFont.lineHeight;
            rect = CGRectMake(_contentRect.origin.x + _xAxisLeftMargin, startPoint.y - yTextHeight / 2, _yAxisTextWidth, yTextHeight);
            for(int i = 0; i < yAxisCount; i++)
            {
                NSString *value = getValueBlock(NO, dataArray, yAxisCount, i);
                
                CATextLayer *textLayer = createTextBlock(rect, value);
                if(textLayer)
                {
                    textLayer.alignmentMode = kCAAlignmentRight;//@"right";
                    //if(i % 2)
                    //{
                    //    textLayer.backgroundColor = [UIColor redColor].CGColor;
                    //}
                    //else
                    //{
                    //    textLayer.backgroundColor = [UIColor blueColor].CGColor;
                    //}
                    ////textLayer.contentsGravity = kCAGravityCenter;//@"center";
                    
                    [axesLayer addSublayer:textLayer];
                }
                
                rect.origin.y += gridItemHeight;
            }
            
            axesLayer.path = linePath.CGPath;
            
            axesLayer.lineWidth = _axesLineWidth;
            axesLayer.strokeColor = _axesLineColor.CGColor;
        }
    }

    return axesLayer;
}

- (CAShapeLayer *)createValue:(BOOL)xIsTime dataCount:(NSInteger)dataCount maxValue:(float)maxValue chartDataArray:(NSArray *)chartDataArray chartColorArray:(NSArray *)chartColorArray
{
    //生成具体的值
    CAShapeLayer *valueLayer = [CAShapeLayer layer];
    if(valueLayer)
    {
        float gridWidth = _contentRect.size.width - _xAxisLeftMargin - _xAxisRightMargin - _yAxisTextWidth - _yAxisTextRightMargin;
        float gridHeight = _contentRect.size.height - _yAxisTopMargin - _yAxisBottomMargin - _xAxisTextHeight - _xAxisTextTopMargin;
        
        float valueWidth;
        float valueHeight;
        
        if(xIsTime)
        {
            valueWidth = gridWidth / (dataCount + dataCount - 1);
            valueHeight = gridHeight;
        }
        else
        {
            valueWidth = gridWidth;
            valueHeight = gridHeight / (dataCount + dataCount - 1);
        }

        CGPoint startPoint = {_contentRect.origin.x + _xAxisLeftMargin + _yAxisTextWidth + _yAxisTextRightMargin, _contentRect.origin.y + _yAxisTopMargin};

        float lastIndex = dataCount - 1;
        
        CGRect rect;
        rect.origin = startPoint;
        rect.size = CGSizeMake(valueWidth, valueHeight);

        for(int i = 0; i < dataCount; i++)
        {
            CAShapeLayer *oneLayer = [CAShapeLayer layer];
            if(oneLayer)
            {
                NSInteger index;
                if(xIsTime)
                {
                    index = lastIndex - i;
                }
                else
                {
                    index = i;
                }
                
                NSNumber *value = [chartDataArray objectAtIndex:index];
                if([value isKindOfClass:[NSNumber class]] || [value isKindOfClass:[NSString class]])
                {
                    if(xIsTime)
                    {
                        rect.size.height = gridHeight * value.floatValue / maxValue;
                        rect.origin.y = startPoint.y + gridHeight - rect.size.height;
                    }
                    else
                    {
                        rect.size.width = gridWidth * value.floatValue / maxValue;
                    }
                    
                    UIBezierPath *path = [UIBezierPath bezierPathWithRect:rect];
                    if(path)
                    {
                        oneLayer.path = path.CGPath;
                        
                        UIColor *color = chartColorArray[index];
                        oneLayer.lineWidth = _axesLineWidth;
                        oneLayer.strokeColor = color.CGColor;
                        oneLayer.fillColor = color.CGColor;
                        
                        [valueLayer addSublayer:oneLayer];
                    }
                    
                    if(xIsTime)
                    {
                        rect.origin.x += valueWidth + valueWidth;
                    }
                    else
                    {
                        rect.origin.y += valueHeight + valueHeight;
                    }
                }
            }
        }
    }

    return valueLayer;
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
//
//    if(_contentBackColor)
//    {
//        CGContextSetFillColorWithColor(currentContext, _contentBackColor.CGColor);
//        //填充矩形
//        CGContextFillRect(currentContext, _contentRect);
//    }
//
//    for(int i = 0; i < [_chartPathArray count]; i++)
//    {
//        UIBezierPath *path = [_chartPathArray objectAtIndex:i];
//        CGContextAddPath(currentContext, path.CGPath);
//
//        UIColor *color = [_chartColorArray objectAtIndex:i];
//        CGContextSetFillColorWithColor(currentContext, color.CGColor);
//        CGContextFillPath(currentContext);
//    }
//
//    for(int i = 0; i < [_textShapeArray count]; i++)
//    {
//        UIBezierPath *path = [_textShapeArray objectAtIndex:i];
//        CGContextAddPath(currentContext, path.CGPath);
//
//        UIColor *color = [UIColor redColor];//[_chartColorArray objectAtIndex:[_textShapeArray count] - 1 - i];
//        CGContextSetStrokeColorWithColor(currentContext, color.CGColor);
//        CGContextStrokePath(currentContext);
//    }
//}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    CGPoint point = [touches.anyObject locationInView:self];
    
    if(_contentLayer)
    {
        CGPoint layerPoint = _contentLayer.frame.origin;
        point.x -= layerPoint.x;
        point.y -= layerPoint.y;
    }
    
    [self upDateLayersWithPoint:point];
}

- (void)upDateLayersWithPoint:(CGPoint)point
{
    //遍历查找点击的是哪一个layer
    for(XYShapeLayer *layer in self.chartShapeArray)
    {
#if(0)
        BOOL isSelected = layer == self.selectedLayer;
        
        if(CGPathContainsPoint(layer.path, &CGAffineTransformIdentity, point, 0))
        {
            if(_selectedLayer)
            {
                _selectedLayer.position = CGPointMake(0, 0);
                
                if(_selectedLayer == layer)
                {
                    self.selectedLayer = nil;
                    
                    break;
                }
            }

            self.selectedLayer = layer;
            
            //原始中心点为（0，0），扇形所在圆心、原始中心点、偏移点三者是在一条直线，通过三角函数即可得到偏移点的对应x，y。
            CGPoint currPos = layer.position;
            double middleAngle = (layer.strokeStart + layer.strokeEnd) / 2.0;
            
            CGPoint newPos = CGPointMake(currPos.x + kOffsetRadius * cos(middleAngle), currPos.y + kOffsetRadius * sin(middleAngle));
            layer.position = newPos;
            
            break;
        }
        else
        {
            if(isSelected)
            {
                layer.position = CGPointMake(0, 0);
                self.selectedLayer = nil;
            }
        }
#else
        if(CGPathContainsPoint(layer.path, &CGAffineTransformIdentity, point, 0) && !layer.isSelected)
        {
            layer.isSelected = YES;
            
            //原始中心点为（0，0），扇形所在圆心、原始中心点、偏移点三者是在一条直线，通过三角函数即可得到偏移点的对应x，y。
            CGPoint currPos = layer.position;
            double middleAngle = (layer.startAngle + layer.endAngle) / 2.0;
            
            CGPoint newPos = CGPointMake(currPos.x + kOffsetRadius * cos(middleAngle), currPos.y + kOffsetRadius * sin(middleAngle));
            layer.position = newPos;
        }
        else
        {
            layer.position = CGPointMake(0, 0);
            layer.isSelected = NO;
        }
#endif
    }
}

@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface XYLineChartView()

@property(nonatomic, strong)CALayer *contentLayer;

@property(nonatomic, strong)CAShapeLayer *axesLayer;
@property(nonatomic, strong)CAShapeLayer *axesTextLayer;
@property(nonatomic, strong)CAShapeLayer *linesLayer;

@property(nonatomic, strong)CAShapeLayer *maskLayer;

@property(nonatomic, assign)NSInteger xAxisCount;
@property(nonatomic, assign)NSInteger yAxisCount;

@property(nonatomic, assign)NSInteger xAxisBaseIndex;
@property(nonatomic, assign)NSInteger yAxisBaseIndex;

@property(nonatomic, assign)BOOL xAxisIsBase;
@property(nonatomic, assign)float maxAxisData;
@property(nonatomic, assign)float minAxisData;

@end

@implementation XYLineChartView

- (XYLineChartView *)initWithFrame:(CGRect)frame contentEdgeInsets:(UIEdgeInsets)contentEdgeInsets contentBackColor:(UIColor *)contentBackColor
{
    self = [super initWithFrame:frame];
    if(self)
    {
        self.backgroundColor = [UIColor whiteColor];
        
        CGSize frameSize = frame.size;
        CGRect contentRect = CGRectMake(contentEdgeInsets.left, contentEdgeInsets.top, frameSize.width - contentEdgeInsets.left - contentEdgeInsets.right, frameSize.height - contentEdgeInsets.top - contentEdgeInsets.bottom);
        
        _contentLayer = [CALayer layer];
        if(_contentLayer)
        {
            _contentLayer.frame = contentRect;
            if(contentBackColor)
            {
                _contentLayer.backgroundColor = contentBackColor.CGColor;
            }
            
            [self.layer addSublayer:_contentLayer];
        }
    }
    
    return self;
}

- (void)dealloc
{
}

- (void)setAxesStyle:(NSInteger)xAxisCount xAxisDrawCount:(NSInteger)xAxisDrawCount xAxisBaseIndex:(NSInteger)xAxisBaseIndex xAxisBaseLineWidth:(NSInteger)xAxisBaseLineWidth xAxisBaseLineColor:(UIColor *)xAxisBaseLineColor xAxisLineStyle:(NSInteger)xAxisLineStyle xAxisLineWidth:(NSInteger)xAxisLineWidth xAxisLineColor:(UIColor *)xAxisLineColor yAxisCount:(NSInteger)yAxisCount yAxisDrawCount:(NSInteger)yAxisDrawCount yAxisBaseIndex:(NSInteger)yAxisBaseIndex yAxisBaseLineWidth:(NSInteger)yAxisBaseLineWidth yAxisBaseLineColor:(UIColor *)yAxisBaseLineColor yAxisLineStyle:(NSInteger)yAxisLineStyle yAxisLineWidth:(NSInteger)yAxisLineWidth yAxisLineColor:(UIColor *)yAxisLineColor axesEdgeInsets:(UIEdgeInsets)axesEdgeInsets
{
    if(_contentLayer)
    {
        _xAxisCount = xAxisCount;
        _yAxisCount = yAxisCount;
        
        _xAxisBaseIndex = xAxisBaseIndex;
        _yAxisBaseIndex = yAxisBaseIndex;
        
        if(!_axesLayer)
        {
            CAShapeLayer *layer = [CAShapeLayer layer];
            if(layer)
            {
                _axesLayer = layer;
                
                [_contentLayer addSublayer:layer];
                
                CGRect rect = _contentLayer.frame;
                
                float gridWidth = rect.size.width - axesEdgeInsets.left - axesEdgeInsets.right;
                float gridHeight = rect.size.height - axesEdgeInsets.top - axesEdgeInsets.bottom;

                rect = CGRectMake(axesEdgeInsets.left, axesEdgeInsets.top, gridWidth, gridHeight);
                layer.frame = rect;
                
                CGPoint startPoint = CGPointZero;//rect.origin;

                float gridItemWidth = gridWidth / (xAxisCount - 1);
                float gridItemHeight = gridHeight / (yAxisCount - 1);
                
                UIBezierPath *linePath;
                
                UIBezierPath *xAxisBaseLinePath = [UIBezierPath bezierPath];
                UIBezierPath *yAxisBaseLinePath = [UIBezierPath bezierPath];

                UIBezierPath *xAxisLinePath = [UIBezierPath bezierPath];
                UIBezierPath *yAxisLinePath = [UIBezierPath bezierPath];
                
                if(xAxisDrawCount > xAxisCount)
                {
                    xAxisDrawCount = xAxisCount;
                }
                
                //画X坐标(从下往上)
                CGPoint point = startPoint;
                point.y += gridHeight;
                for(int i = 0; i < xAxisDrawCount; i++)
                {
                    if(i != xAxisBaseIndex)
                    {
                        linePath = xAxisLinePath;
                    }
                    else
                    {
                        linePath = xAxisBaseLinePath;
                    }
                    [linePath moveToPoint:point];
                    [linePath addLineToPoint:CGPointMake(point.x + gridWidth, point.y)];
                    
                    point.y -= gridItemHeight;
                }

                if(xAxisLinePath)
                {
                    layer = [CAShapeLayer layer];
                    if(layer)
                    {
                        [_axesLayer addSublayer:layer];
                        
                        layer.path = xAxisLinePath.CGPath;
                        
                        layer.lineWidth = xAxisLineWidth;
                        layer.strokeColor = xAxisLineColor.CGColor;
                    }
                }

                if(xAxisBaseLinePath)
                {
                    layer = [CAShapeLayer layer];
                    if(layer)
                    {
                        [_axesLayer addSublayer:layer];
                        
                        layer.path = xAxisBaseLinePath.CGPath;
                        
                        layer.lineWidth = xAxisBaseLineWidth;
                        layer.strokeColor = xAxisBaseLineColor.CGColor;
                    }
                }
                
                if(yAxisDrawCount > yAxisCount)
                {
                    yAxisDrawCount = yAxisCount;
                }

                //画Y坐标
                point = startPoint;
                for(int i = 0; i < yAxisDrawCount; i++)
                {
                    if(i != yAxisBaseIndex)
                    {
                        linePath = yAxisLinePath;
                    }
                    else
                    {
                        linePath = yAxisBaseLinePath;
                    }
                    [linePath moveToPoint:point];
                    [linePath addLineToPoint:CGPointMake(point.x, point.y + gridHeight)];
                    
                    point.x += gridItemWidth;
                }
                
                if(yAxisLinePath)
                {
                    layer = [CAShapeLayer layer];
                    if(layer)
                    {
                        [_axesLayer addSublayer:layer];
                        
                        layer.path = yAxisLinePath.CGPath;
                        
                        layer.lineWidth = yAxisLineWidth;
                        layer.strokeColor = yAxisLineColor.CGColor;
                    }
                }

                if(yAxisBaseLinePath)
                {
                    layer = [CAShapeLayer layer];
                    if(layer)
                    {
                        [_axesLayer addSublayer:layer];
                        
                        layer.path = yAxisBaseLinePath.CGPath;
                        
                        layer.lineWidth = yAxisBaseLineWidth;
                        layer.strokeColor = yAxisBaseLineColor.CGColor;
                    }
                }
            }
        }
    }
}

- (void)setAxesTextStyle:(float)xAxisTextWidth xAxisTextMargin:(float)xAxisTextMargin xAxisTextFont:(UIFont *)xAxisTextFont xAxisTextColor:(UIColor *)xAxisTextColor xAxisTextPos:(int)xAxisTextPos yAxisTextWidth:(float)yAxisTextWidth yAxisTextMargin:(float)yAxisTextMargin yAxisTextFont:(UIFont *)yAxisTextFont yAxisTextColor:(UIColor *)yAxisTextColor yAxisTextPos:(int)yAxisTextPos
{
    if(_contentLayer && _axesLayer)
    {
        if(!_axesTextLayer)
        {
            CAShapeLayer *layer = [CAShapeLayer layer];
            if(layer)
            {
                _axesTextLayer = layer;
                
                [_contentLayer addSublayer:layer];
                
                CATextLayer* (^createTextBlock)(CGRect rect, NSString *text, UIFont *textFont, UIColor *textColor) = ^(CGRect rect, NSString *text, UIFont *textFont, UIColor *textColor) {
                    CATextLayer *layer = [CATextLayer layer];
                    if(layer)
                    {
                        layer.frame = rect;
                        layer.string = text;
                        layer.fontSize = textFont.pointSize;
                        layer.foregroundColor = textColor.CGColor;
                        
                        CFStringRef fontName = (__bridge CFStringRef)textFont.fontName;
                        CGFontRef fontRef = CGFontCreateWithFontName(fontName);
                        layer.font = fontRef;
                        CGFontRelease(fontRef);
                    }
                    
                    return layer;
                };
                
                CGRect rect = _axesLayer.frame;
                
                float gridWidth = rect.size.width;
                float gridHeight = rect.size.height;
                
                float gridItemWidth = gridWidth / (_xAxisCount - 1);
                float gridItemHeight = gridHeight / (_yAxisCount - 1);
                
                float textXPos;
                float textYPos;
                
                float textHeight = xAxisTextFont.lineHeight;
                
                textXPos = rect.origin.x;
                
                if(xAxisTextPos == 1)
                {
                    //显示在上面
                    textYPos = rect.origin.y - xAxisTextMargin;
                }
                else
                {
                    //显示在下面
                    textYPos = rect.origin.y + rect.size.height + xAxisTextMargin;
                }
                
                NSInteger xAxisCount = _xAxisCount;
                
                //显示X轴坐标值
                for(int i = 0; i < xAxisCount; i++)
                {
                    CGRect rect = CGRectMake(textXPos - xAxisTextWidth / 2, textYPos, xAxisTextWidth, textHeight);
                    CATextLayer *layer = createTextBlock(rect, @"", xAxisTextFont, xAxisTextColor);
                    if(layer)
                    {
                        [_axesTextLayer addSublayer:layer];
                        
                        layer.alignmentMode = kCAAlignmentCenter;
                    }
                    
                    textXPos += gridItemWidth;
                }
                
                /////////////////////////////////////////////////////////////////////////////////////////////////////
                NSString *alignmentMode;
                
                textHeight = yAxisTextFont.lineHeight;
                
                if(yAxisTextPos == 1)
                {
                    //显示在右边
                    textXPos = rect.origin.x + yAxisTextMargin;
                    
                    alignmentMode = kCAAlignmentLeft;
                }
                else
                {
                    //显示在左边
                    textXPos = rect.origin.x - xAxisTextMargin - yAxisTextWidth;
                    
                    alignmentMode = kCAAlignmentRight;
                }
                
                textYPos = rect.origin.y + gridHeight;
                
                NSInteger yAxisCount = _yAxisCount;
                
                //显示Y轴坐标值(从下往上)
                for(int i = 0; i < yAxisCount; i++)
                {
                    CGRect rect = CGRectMake(textXPos, textYPos - textHeight / 2, yAxisTextWidth, textHeight);
                    CATextLayer *layer = createTextBlock(rect, @"", yAxisTextFont, yAxisTextColor);
                    if(layer)
                    {
                        [_axesTextLayer addSublayer:layer];
                        
                        layer.alignmentMode = kCAAlignmentCenter;
                    }
                    
                    textYPos -= gridItemHeight;
                }
            }
        }
    }
}

- (void)setAxesTextData:(BOOL)xAxisIsBase maxAxisData:(float)maxAxisData baseAxisDataArray:(NSArray *)baseAxisDataArray axisDataArray:axisDataArray
{
    if(_contentLayer && _axesLayer && _axesTextLayer)
    {
        _xAxisIsBase = xAxisIsBase;
        _maxAxisData = maxAxisData;
        _minAxisData = 0;
        
        NSInteger axisDataCount = [axisDataArray count];
        if(axisDataCount)
        {
            NSString *value = axisDataArray[axisDataCount - 1];
            if([value isKindOfClass:[NSString class]] || [value isKindOfClass:[NSNumber class]])
            {
                _maxAxisData = value.floatValue;
            }
            
            value = axisDataArray[0];
            if([value isKindOfClass:[NSString class]] || [value isKindOfClass:[NSNumber class]])
            {
                _minAxisData = value.floatValue;
            }
        }
        
        NSArray<CALayer *> *subLayers = _axesTextLayer.sublayers;
        if([subLayers count])
        {
            NSInteger (^getAxisCount)(BOOL isBaseAxis, NSInteger axisCount) = ^(BOOL isBaseAxis, NSInteger axisCount) {
                NSInteger count = 0;
                
                if(isBaseAxis)
                {
                    count = [baseAxisDataArray count];
                    if(count > axisCount)
                    {
                        count = axisCount;
                    }
                }
                else
                {
                    count = [axisDataArray count];
                    if(count == 0 || count > axisCount)
                    {
                        count = axisCount;
                    }
                }
                
                return count;
            };
            
            NSString* (^getAxisText)(BOOL isBaseAxis, NSInteger axisIndex, float gridItemValue) = ^(BOOL isBaseAxis, NSInteger axisIndex, float gridItemValue) {
                NSString *text;
                
                if(isBaseAxis)
                {
                    text = baseAxisDataArray[axisIndex];
                    if(![text isKindOfClass:[NSString class]])
                    {
                        text = @"";
                    }
                }
                else
                {
                    if([axisDataArray count])
                    {
                        //直接取设置的值
                        text = axisDataArray[axisIndex];
                        if([text isKindOfClass:[NSNumber class]])
                        {
                            text = [NSString stringWithFormat:@"%.2f", text.floatValue];
                        }
                        else if(![text isKindOfClass:[NSString class]])
                        {
                            text = @"";
                        }
                    }
                    else
                    {
                        //通过最大值计算的值
                        text = [NSString stringWithFormat:@"%.2f", gridItemValue * axisIndex];
                    }
                }
                
                return text;
            };

            NSInteger axisCount = getAxisCount(xAxisIsBase, _xAxisCount);
            
            float gridItemValue = 0;
            if(axisDataCount == 0)
            {
                gridItemValue = maxAxisData / (axisCount - 1);
            }
            
            BOOL isXvalue = YES;
            NSInteger index = 0;
            
            for(CATextLayer *layer in subLayers)
            {
                if([layer isKindOfClass:[CATextLayer class]])
                {
                    layer.string = getAxisText(isXvalue ? xAxisIsBase : !xAxisIsBase, index, gridItemValue);
                    
                    if(++index == axisCount)
                    {
                        if(isXvalue)
                        {
                            isXvalue = NO;
                            index = 0;
                            
                            axisCount = getAxisCount(!xAxisIsBase, _yAxisCount);
                            if(axisDataCount == 0)
                            {
                                gridItemValue = maxAxisData / (axisCount - 1);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}

- (void)setLineData:(float)lineWidth lineDataArray:(NSArray *)lineDataArray lineColor:(UIColor *)lineColor fillColor:(UIColor *)fillColor fillAlpha:(float)fillAlpha valueRadius:(float)valueRadius valueLineWidth:(float)valueLineWidth valueLineColor:(UIColor *)valueLineColor valueFillColor:(UIColor *)valueFillColor andBlock:(XYChartViewGetLineChartDataBlock)block
{
    NSInteger dataCount = [lineDataArray count];
    if(_contentLayer && _axesLayer && dataCount)
    {
        if(!_linesLayer)
        {
            _linesLayer = [CAShapeLayer layer];
            
            [_axesLayer addSublayer:_linesLayer];
        }
        else
        {
            NSArray<CALayer *> *sublayers = _linesLayer.sublayers;
            while([sublayers count])
            {
                [sublayers[0] removeFromSuperlayer];
                
                sublayers = _linesLayer.sublayers;
            }
        }
        
        if(_linesLayer)
        {
            CAShapeLayer *linesLayer = _linesLayer;
            
            CGRect rect = _axesLayer.frame;
            rect.origin = CGPointZero;
            
            float gridWidth = rect.size.width;
            float gridHeight = rect.size.height;
            
            float gridItemWidth = gridWidth / (_xAxisCount - 1);
            float gridItemHeight = gridHeight / (_yAxisCount - 1);
            
            BOOL xAxisIsBase = _xAxisIsBase;
            float maxAxisData = _maxAxisData;
            //float minAxisData = _minAxisData;

            void (^createLineDataBlock) (NSArray *lineDataArray, UIColor *lineColor, UIColor *fillColor, UIColor *valueLineColor, UIColor *valueFillColor) = ^(NSArray *lineDataArray, UIColor *lineColor, UIColor *fillColor, UIColor *valueLineColor, UIColor *valueFillColor) {
                CAShapeLayer *lineLayer = [CAShapeLayer layer];
                if(lineLayer)
                {
                    UIBezierPath *dotPath = nil;
                    UIBezierPath *fillPath = nil;
                    
                    UIBezierPath *linePath = [UIBezierPath bezierPath];
                    if(linePath)
                    {
                        dotPath = [UIBezierPath bezierPath];

                        void (^setDotBlock) (UIBezierPath *dotPath, CGPoint point) = ^(UIBezierPath *dotPath, CGPoint point) {
                            [dotPath addArcWithCenter:point radius:valueRadius startAngle:0 endAngle:M_PI + M_PI clockwise:YES];
                        };
                        
                        __block CGPoint point;
                        CGPoint startPoint = rect.origin;
                        startPoint.y += gridHeight;//从下往上画
                        
                        void (^setPointBlock) (NSInteger dataIndex) = ^(NSInteger dataIndex) {
                            float value = 0;
                            NSString *data = lineDataArray[dataIndex];
                            if([data isKindOfClass:[NSString class]] || [data isKindOfClass:[NSNumber class]])
                            {
                                value = data.floatValue;// - minAxisData;
                            }
                            
                            if(xAxisIsBase)
                            {
                                point = CGPointMake(startPoint.x + dataIndex * gridItemWidth, startPoint.y - value / maxAxisData * gridHeight);
                            }
                            else
                            {
                                point = CGPointMake(startPoint.x + value / maxAxisData * gridWidth, startPoint.y - dataIndex * gridItemHeight);
                            }
                            
                            if(dotPath)
                            {
                                [dotPath moveToPoint:CGPointMake(point.x + valueRadius, point.y)];
                                setDotBlock(dotPath, point);
                            }
                        };
                        
                        setPointBlock(0);
                        [linePath moveToPoint:point];
                        
                        if(fillColor)
                        {
                            fillPath = [UIBezierPath bezierPath];
                            if(fillPath)
                            {
                                [fillPath moveToPoint:startPoint];
                                [fillPath addLineToPoint:point];
                            }
                        }

                        for(int i = 1; i < dataCount; i++)
                        {
                            setPointBlock(i);
                            [linePath addLineToPoint:point];
                            
                            if(fillPath)
                            {
                                [fillPath addLineToPoint:point];
                            }
                        }
                        
                        if(fillPath)
                        {
                            if(xAxisIsBase)
                            {
                                [fillPath addLineToPoint:CGPointMake(point.x, startPoint.y)];
                            }
                            else
                            {
                                [fillPath addLineToPoint:CGPointMake(startPoint.x, point.y)];
                            }
                            
                            CAShapeLayer *valueFillLayer = [CAShapeLayer layer];
                            if(valueFillLayer)
                            {
                                //填充值包含的区域
                                valueFillLayer.path = fillPath.CGPath;
                                
                                //UIColor *color = [UIColor purpleColor];
                                valueFillLayer.fillColor = fillColor.CGColor;
                                valueFillLayer.opacity = fillAlpha;
                                
                                [linesLayer addSublayer:valueFillLayer];
                            }
                        }
                        
                        lineLayer.path = linePath.CGPath;
                        
                        lineLayer.lineWidth = lineWidth;
                        lineLayer.strokeColor = lineColor.CGColor;
                        lineLayer.fillColor = [UIColor clearColor].CGColor;
                        
                        [linesLayer addSublayer:lineLayer];
                        
                        if(dotPath)
                        {
                            CAShapeLayer *dotFillLayer = [CAShapeLayer layer];
                            if(dotFillLayer)
                            {
                                dotFillLayer.path = dotPath.CGPath;
                                
                                dotFillLayer.lineWidth = valueLineWidth;
                                dotFillLayer.strokeColor = valueLineColor.CGColor;
                                dotFillLayer.fillColor = valueFillColor.CGColor;
                                
                                [linesLayer addSublayer:dotFillLayer];
                            }
                        }
                    }
                }
            };
            
            createLineDataBlock(lineDataArray, lineColor, fillColor, valueLineColor, valueFillColor);
            
            if(block)
            {
                //显示多组数据
                XYChartViewSetLineChartDataBlock setLineChartDataBlock = ^(NSArray *lineDataArray, UIColor *lineColor, UIColor *fillColor, UIColor *valueLineColor, UIColor *valueFillColor) {
                    createLineDataBlock(lineDataArray, lineColor, fillColor, valueLineColor, valueFillColor);
                };
                
                block(setLineChartDataBlock);
            }
            
            [self setMask:_linesLayer valueRadius:valueRadius];
            
            [XYChartView doAnimation:_maskLayer keyPath:@"position.x" fromValue:-self.bounds.size.width toValue:0 duration:1 delegate:nil];
        }
    }
}

- (void)setMask:(CALayer *)layer valueRadius:(float)valueRadius
{
    //通过mask来控制显示区域
    if(!_maskLayer)
    {
        self.maskLayer = [CAShapeLayer layer];
    }
    
    if(_maskLayer)
    {
        //UIBezierPath *maskPath = [UIBezierPath bezierPathWithArcCenter:_center radius:self.bounds.size.width/4.f startAngle:-M_PI_2 endAngle:M_PI_2*3 clockwise:YES];
        //UIBezierPath *piePath = [UIBezierPath bezierPathWithArcCenter:_center radius:_radius + Hollow_Circle_Radius startAngle:-M_PI_2 endAngle:M_PI_2*3 clockwise:YES];
        
        CGSize rectSize = self.bounds.size;
        rectSize.width += valueRadius + valueRadius;
        rectSize.height += valueRadius + valueRadius;
        
        UIBezierPath *maskPath = [UIBezierPath bezierPathWithRect:CGRectMake(-valueRadius, -valueRadius, rectSize.width, rectSize.height)];//self.bounds
        
        _maskLayer.position = CGPointMake(-rectSize.width, 0);
        //_maskLayer.anchorPoint = CGPointZero;
        
        _maskLayer.path = maskPath.CGPath;
        
        if(layer)
        {
            layer.mask = _maskLayer;
        }
        else
        {
            self.layer.mask = _maskLayer;
        }
    }
}

@end
