//
//  JHKeyframeAnimationFunctions.c
//  JHChainableAnimations
//
//  Created by Jeff Hurray on 12/21/16.
//  Copyright © 2016 jhurray. All rights reserved.
//

#include "JHKeyframeAnimationFunctions.h"
#include <math.h>
#include <stdlib.h>

// Source: http://gsgd.co.uk/sandbox/jquery/easing/jquery.easing.1.3.js
// Credits to https://github.com/NachoSoto/NSBKeyframeAnimation

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsequenced"

//#if(0)
//#define kAnimationStops 250
//
//// Thanks to http://www.dzone.com/snippets/robert-penner-easing-equations for the easing
//// equation implementations
//typedef CGFloat (^EasingFunction)(CGFloat t, CGFloat b, CGFloat c, CGFloat d);
//
//+ (CAKeyframeAnimation*)animationWithKeyPath:(NSString*)keyPath duration:(CGFloat)duration from:(CGFloat)startValue to:(CGFloat)endValue easingFunction:(CAAnimationEasingFunction)easingFunction
//{
//    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:keyPath];
//    animation.duration = duration;
//    animation.fillMode = kCAFillModeForwards;
//    animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
//    animation.removedOnCompletion = NO;
//
//    NSMutableArray *values = [NSMutableArray arrayWithCapacity:kAnimationStops];
//    CGFloat delta = endValue - startValue;
//    EasingFunction function = [CAAnimation blockForCAAnimationEasingFunction:easingFunction];
//    for(CGFloat t = 0; t < kAnimationStops; t++)
//    {
//        [values addObject:@(function(animation.duration * (t / kAnimationStops), startValue, delta, animation.duration))];
//    }
//
//    [values addObject:@(endValue)];
//    animation.values = values;
//
//    return animation;
//}
//
//+ (CAKeyframeAnimation*)transformAnimationWithDuration:(CGFloat)duration from:(CATransform3D)startValue to:(CATransform3D)endValue easingFunction:(CAAnimationEasingFunction)easingFunction
//{
//    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
//    animation.duration = duration;
//    animation.fillMode = kCAFillModeForwards;
//    animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
//    animation.removedOnCompletion = NO;
//
//    NSMutableArray *values = [NSMutableArray arrayWithCapacity:kAnimationStops];
//
//    CGFloat dm11 = endValue.m11 - startValue.m11;
//    CGFloat dm12 = endValue.m12 - startValue.m12;
//    CGFloat dm13 = endValue.m13 - startValue.m13;
//    CGFloat dm14 = endValue.m14 - startValue.m14;
//
//    CGFloat dm21 = endValue.m21 - startValue.m21;
//    CGFloat dm22 = endValue.m22 - startValue.m22;
//    CGFloat dm23 = endValue.m23 - startValue.m23;
//    CGFloat dm24 = endValue.m24 - startValue.m24;
//
//    CGFloat dm31 = endValue.m31 - startValue.m31;
//    CGFloat dm32 = endValue.m32 - startValue.m32;
//    CGFloat dm33 = endValue.m33 - startValue.m33;
//    CGFloat dm34 = endValue.m34 - startValue.m34;
//
//    CGFloat dm41 = endValue.m41 - startValue.m41;
//    CGFloat dm42 = endValue.m42 - startValue.m42;
//    CGFloat dm43 = endValue.m43 - startValue.m43;
//    CGFloat dm44 = endValue.m44 - startValue.m44;
//
//    EasingFunction function = [CAAnimation blockForCAAnimationEasingFunction:easingFunction];
//    for(CGFloat t = 0; t < kAnimationStops; t++)
//    {
//        CATransform3D tr;
//        tr.m11 = function(animation.duration * (t / kAnimationStops), startValue.m11, dm11, animation.duration);
//        tr.m12 = function(animation.duration * (t / kAnimationStops), startValue.m12, dm12, animation.duration);
//        tr.m13 = function(animation.duration * (t / kAnimationStops), startValue.m13, dm13, animation.duration);
//        tr.m14 = function(animation.duration * (t / kAnimationStops), startValue.m14, dm14, animation.duration);
//
//        tr.m21 = function(animation.duration * (t / kAnimationStops), startValue.m21, dm21, animation.duration);
//        tr.m22 = function(animation.duration * (t / kAnimationStops), startValue.m22, dm22, animation.duration);
//        tr.m23 = function(animation.duration * (t / kAnimationStops), startValue.m23, dm23, animation.duration);
//        tr.m24 = function(animation.duration * (t / kAnimationStops), startValue.m24, dm24, animation.duration);
//
//        tr.m31 = function(animation.duration * (t / kAnimationStops), startValue.m31, dm31, animation.duration);
//        tr.m32 = function(animation.duration * (t / kAnimationStops), startValue.m32, dm32, animation.duration);
//        tr.m33 = function(animation.duration * (t / kAnimationStops), startValue.m33, dm33, animation.duration);
//        tr.m34 = function(animation.duration * (t / kAnimationStops), startValue.m34, dm34, animation.duration);
//
//        tr.m41 = function(animation.duration * (t / kAnimationStops), startValue.m41, dm41, animation.duration);
//        tr.m42 = function(animation.duration * (t / kAnimationStops), startValue.m42, dm42, animation.duration);
//        tr.m43 = function(animation.duration * (t / kAnimationStops), startValue.m43, dm43, animation.duration);
//        tr.m44 = function(animation.duration * (t / kAnimationStops), startValue.m44, dm44, animation.duration);
//        [values addObject:[NSValue valueWithCATransform3D:tr]];
//    }
//
//    [values addObject:[NSValue valueWithCATransform3D:endValue]];
//    animation.values = values;
//
//    return animation;
//}
//#endif

// Generally:
//  t: current time
//  b: beginning value
//  c: change in value(end value - beginning value)
//  d: duration
//
// Each of these equations returns the animated property's value at time t

double JHKeyframeAnimationFunctionLinear(double t, double b, double c, double d)
{
    return c * (t /= d) + b;
}

double JHKeyframeAnimationFunctionEaseInQuad(double t, double b, double c, double d)
{
    return c * (t /= d) * t + b;
}

double JHKeyframeAnimationFunctionEaseOutQuad(double t, double b, double c, double d)
{
    return -c * (t /= d) * (t - 2) + b;
}

double JHKeyframeAnimationFunctionEaseInOutQuad(double t, double b, double c, double d)
{
    if((t /= d / 2) < 1)
        return c / 2 * t * t + b;
    
    return -c / 2 * ((--t) * (t - 2) - 1) + b;
}

double JHKeyframeAnimationFunctionEaseInCubic(double t, double b, double c, double d)
{
    return c * (t /= d) * t * t + b;
}

double JHKeyframeAnimationFunctionEaseOutCubic(double t, double b, double c, double d)
{
    return c * ((t = t / d - 1) * t * t + 1) + b;
}

double JHKeyframeAnimationFunctionEaseInOutCubic(double t, double b, double c, double d)
{
    if((t /= d / 2) < 1)
        return c / 2 * t * t * t + b;
    
    return c / 2 * ((t -= 2) * t * t + 2) + b;
}

double JHKeyframeAnimationFunctionEaseInQuart(double t, double b, double c, double d)
{
    return c * (t /= d) * t * t * t + b;
}

double JHKeyframeAnimationFunctionEaseOutQuart(double t, double b, double c, double d)
{
    return -c * ((t = t / d - 1) * t * t * t - 1) + b;
}

double JHKeyframeAnimationFunctionEaseInOutQuart(double t, double b, double c, double d)
{
    if((t /= d / 2) < 1)
        return c / 2 * t * t * t * t + b;
    
    return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
}

double JHKeyframeAnimationFunctionEaseInQuint(double t, double b, double c, double d)
{
    return c * (t /= d) * t * t * t * t + b;
}

double JHKeyframeAnimationFunctionEaseOutQuint(double t, double b, double c, double d)
{
    return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
}

double JHKeyframeAnimationFunctionEaseInOutQuint(double t, double b, double c, double d)
{
    if((t /= d / 2) < 1)
        return c / 2 * t * t * t * t * t + b;
    
    return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
}

double JHKeyframeAnimationFunctionEaseInSine(double t, double b, double c, double d)
{
    return -c * cos(t / d * (M_PI_2)) + c + b;
}

double JHKeyframeAnimationFunctionEaseOutSine(double t, double b, double c, double d)
{
    return c * sin(t / d * (M_PI_2)) + b;
}

double JHKeyframeAnimationFunctionEaseInOutSine(double t, double b, double c, double d)
{
    return -c / 2 * (cos(M_PI * t / d) - 1) + b;
}

double JHKeyframeAnimationFunctionEaseInExpo(double t, double b, double c, double d)
{
    return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}

double JHKeyframeAnimationFunctionEaseOutExpo(double t, double b, double c, double d)
{
    return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}

double JHKeyframeAnimationFunctionEaseInOutExpo(double t, double b, double c, double d)
{
    if(t == 0)
        return b;
    
    if(t == d)
        return b + c;
    
    if((t /= d / 2) < 1)
        return c / 2 * pow(2, 10 * (t - 1)) + b;
    
    return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

double JHKeyframeAnimationFunctionEaseInCirc(double t, double b, double c, double d)
{
    return -c * (sqrt(1 - (t /= d) * t) - 1) + b;
}

double JHKeyframeAnimationFunctionEaseOutCirc(double t, double b, double c, double d)
{
    return c * sqrt(1 - (t = t / d - 1) * t) + b;
}

double JHKeyframeAnimationFunctionEaseInOutCirc(double t, double b, double c, double d)
{
    if((t /= d / 2) < 1)
        return -c / 2 * (sqrt(1 - t * t) - 1) + b;
    
    return c / 2 * (sqrt(1 - (t -= 2) * t) + 1) + b;
}

double JHKeyframeAnimationFunctionEaseInElastic(double t, double b, double c, double d)
{
    double s = 1.70158;
    double p = 0;
    double a = c;
    
    if(t == 0)
        return b;
    
    if((t /= d) == 1)
        return b + c;
    
    if(!p)
        p = d * .3;
    
    if(a < fabs(c))
    {
        a = c;
        s = p / 4;
        
    }
    else
    {
        s = p / (2 * M_PI) * asin(c / a);
    }
    
    return -(a * pow(2, 10 * (t -= 1)) * sin((t * d - s) * (2 * M_PI) / p)) + b;
}

double JHKeyframeAnimationFunctionEaseOutElastic(double t, double b, double c, double d)
{
    double s=1.70158, p=0, a=c;
    if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
    if (a < fabs(c)) { a=c; s=p/4; }
    else s = p/(2*M_PI) * asin (c/a);
    return a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p ) + c + b;
}

double JHKeyframeAnimationFunctionEaseInOutElastic(double t, double b, double c, double d)
{
    double s=1.70158, p=0, a=c;
    if (t==0) return b;  if ((t/=d/2)==2) return b+c;  if (!p) p=d*(.3*1.5);
    if (a < fabs(c)) { a=c; s=p/4; }
    else s = p/(2*M_PI) * asin(c/a);
    if (t < 1) return -.5*(a*pow(2,10*(t-=1)) * sin( (t*d-s)*(2*M_PI)/p )) + b;
    return a*pow(2,-10*(t-=1)) * sin( (t*d-s)*(2*M_PI)/p )*.5 + c + b;
}

double JHKeyframeAnimationFunctionEaseInBack(double t, double b, double c, double d)
{
    const double s = 1.70158;
    return c*(t/=d)*t*((s+1)*t - s) + b;
}

double JHKeyframeAnimationFunctionEaseOutBack(double t, double b, double c, double d)
{
    const double s = 1.70158;
    return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
}

double JHKeyframeAnimationFunctionEaseInOutBack(double t, double b, double c, double d)
{
    double s = 1.70158;
    if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525))+1)*t - s)) + b;
    return c/2*((t-=2)*t*(((s*=(1.525))+1)*t + s) + 2) + b;
}

#if(0)
double JHKeyframeAnimationFunctionEaseInBounce(double t, double b, double c, double d)
{
    return c - JHKeyframeAnimationFunctionEaseOutBounce(d-t, 0, c, d) + b;
}

double JHKeyframeAnimationFunctionEaseOutBounce(double t, double b, double c, double d)
{
    if ((t/=d) < (1/2.75)) {
        return c*(7.5625*t*t) + b;
    } else if (t < (2/2.75)) {
        return c*(7.5625*(t-=(1.5/2.75))*t + .75) + b;
    } else if (t < (2.5/2.75)) {
        return c*(7.5625*(t-=(2.25/2.75))*t + .9375) + b;
    } else {
        return c*(7.5625*(t-=(2.625/2.75))*t + .984375) + b;
    }
}

double JHKeyframeAnimationFunctionEaseInOutBounce(double t, double b, double c, double d)
{
    if (t < d/2)
        return JHKeyframeAnimationFunctionEaseInBounce (t*2, 0, c, d) * .5 + b;
    else
        return JHKeyframeAnimationFunctionEaseOutBounce(t*2-d, 0, c, d) * .5 + c*.5 + b;
}
#endif

//#pragma clang diagnostic pop
//
////#define kFPS 60
////
////- (NSArray *)valueArrayForStartValue:(CGFloat)startValue endValue:(CGFloat)endValue
////{
////    NSUInteger steps = ceil(kFPS * self.duration) + 2;
////    NSMutableArray *valueArray = [NSMutableArray arrayWithCapacity:steps];
////    
////    const double increment = 1.0 / (double)(steps - 1);
////    double progress = 0.0,
////    v = 0.0,
////    value = 0.0;
////    
////    NSUInteger i;
////    for (i = 0; i < steps; i++)
////    {
////        v = self.functionBlock(self.duration * progress * 1000, 0, 1, self.duration * 1000);
////        value = startValue + v * (endValue - startValue);
////        [valueArray addObject:@(value)];
////        progress += increment;
////    }
////    
////    return [NSArray arrayWithArray:valueArray];
////}
//
//// Linear interpolation (no easing)
//extern INTUEasingFunction INTULinear;
//
//// Sine wave easing; sin(p * PI/2)
//extern INTUEasingFunction INTUEaseInSine;
//extern INTUEasingFunction INTUEaseOutSine;
//extern INTUEasingFunction INTUEaseInOutSine;
//
//// Quadratic easing; p^2
//extern INTUEasingFunction INTUEaseInQuadratic;
//extern INTUEasingFunction INTUEaseOutQuadratic;
//extern INTUEasingFunction INTUEaseInOutQuadratic;
//
//// Cubic easing; p^3
//extern INTUEasingFunction INTUEaseInCubic;
//extern INTUEasingFunction INTUEaseOutCubic;
//extern INTUEasingFunction INTUEaseInOutCubic;
//
//// Quartic easing; p^4
//extern INTUEasingFunction INTUEaseInQuartic;
//extern INTUEasingFunction INTUEaseOutQuartic;
//extern INTUEasingFunction INTUEaseInOutQuartic;
//
//// Quintic easing; p^5
//extern INTUEasingFunction INTUEaseInQuintic;
//extern INTUEasingFunction INTUEaseOutQuintic;
//extern INTUEasingFunction INTUEaseInOutQuintic;
//
//// Exponential easing, base 2
//extern INTUEasingFunction INTUEaseInExponential;
//extern INTUEasingFunction INTUEaseOutExponential;
//extern INTUEasingFunction INTUEaseInOutExponential;
//
//// Circular easing; sqrt(1 - p^2)
//extern INTUEasingFunction INTUEaseInCircular;
//extern INTUEasingFunction INTUEaseOutCircular;
//extern INTUEasingFunction INTUEaseInOutCircular;
//
//// Overshooting cubic easing;
//extern INTUEasingFunction INTUEaseInBack;
//extern INTUEasingFunction INTUEaseOutBack;
//extern INTUEasingFunction INTUEaseInOutBack;
//
//// Exponentially-damped sine wave easing
//extern INTUEasingFunction INTUEaseInElastic;
//extern INTUEasingFunction INTUEaseOutElastic;
//extern INTUEasingFunction INTUEaseInOutElastic;
//
//// Exponentially-decaying bounce easing
//extern INTUEasingFunction INTUEaseInBounce;
//extern INTUEasingFunction INTUEaseOutBounce;
//extern INTUEasingFunction INTUEaseInOutBounce;
//
////
////  INTUEasingFunctions.m
////  https://github.com/intuit/AnimationEngine
////
////  Copyright (c) 2014-2015 Intuit Inc.
////
////  Permission is hereby granted, free of charge, to any person obtaining
////  a copy of this software and associated documentation files (the
////  "Software"), to deal in the Software without restriction, including
////  without limitation the rights to use, copy, modify, merge, publish,
////  distribute, sublicense, and/or sell copies of the Software, and to
////  permit persons to whom the Software is furnished to do so, subject to
////  the following conditions:
////
////  The above copyright notice and this permission notice shall be
////  included in all copies or substantial portions of the Software.
////
////  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
////  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
////  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
////  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
////  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
////  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
////  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////
//
//#import "INTUEasingFunctions.h"
//#include <math.h>
//
////缓动函数指定动画效果在执行时的速度
//
//// Modeled after the line y = x
//INTUEasingFunction INTULinear = ^CGFloat (CGFloat p) {
//    return p;
//};
//
//// Modeled after quarter-cycle of sine wave
//INTUEasingFunction INTUEaseInSine = ^CGFloat (CGFloat p) {
//    return sin((p - 1) * M_PI_2) + 1;
//};
//
//// Modeled after quarter-cycle of sine wave (different phase)
//INTUEasingFunction INTUEaseOutSine = ^CGFloat (CGFloat p) {
//    return sin(p * M_PI_2);
//};
//
//// Modeled after half sine wave
//INTUEasingFunction INTUEaseInOutSine = ^CGFloat (CGFloat p) {
//    return 0.5 * (1 - cos(p * M_PI));
//};
//
//// Modeled after the parabola y = x^2
//INTUEasingFunction INTUEaseInQuadratic = ^CGFloat (CGFloat p) {
//    return p * p;
//};
//
//// Modeled after the parabola y = -x^2 + 2x
//INTUEasingFunction INTUEaseOutQuadratic = ^CGFloat (CGFloat p) {
//    return -(p * (p - 2));
//};
//
//// Modeled after the piecewise quadratic
//// y = (1/2)((2x)^2)             ; [0, 0.5)
//// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
//INTUEasingFunction INTUEaseInOutQuadratic = ^CGFloat (CGFloat p) {
//    if(p < 0.5)
//    {
//        return 2 * p * p;
//    }
//    else
//    {
//        return (-2 * p * p) + (4 * p) - 1;
//    }
//};
//
//// Modeled after the cubic y = x^3
//INTUEasingFunction INTUEaseInCubic = ^CGFloat (CGFloat p) {
//    return p * p * p;
//};
//
//// Modeled after the cubic y = (x - 1)^3 + 1
//INTUEasingFunction INTUEaseOutCubic = ^CGFloat (CGFloat p) {
//    CGFloat f = (p - 1);
//    return f * f * f + 1;
//};
//
//// Modeled after the piecewise cubic
//// y = (1/2)((2x)^3)       ; [0, 0.5)
//// y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
//INTUEasingFunction INTUEaseInOutCubic = ^CGFloat (CGFloat p) {
//    if(p < 0.5)
//    {
//        return 4 * p * p * p;
//    }
//    else
//    {
//        CGFloat f = ((2 * p) - 2);
//        return 0.5 * f * f * f + 1;
//    }
//};
//
//// Modeled after the quartic x^4
//INTUEasingFunction INTUEaseInQuartic = ^CGFloat (CGFloat p) {
//    return p * p * p * p;
//};
//
//// Modeled after the quartic y = 1 - (x - 1)^4
//INTUEasingFunction INTUEaseOutQuartic = ^CGFloat (CGFloat p) {
//    CGFloat f = (p - 1);
//    return f * f * f * (1 - p) + 1;
//};
//
//// Modeled after the piecewise quartic
//// y = (1/2)((2x)^4)        ; [0, 0.5)
//// y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
//INTUEasingFunction INTUEaseInOutQuartic = ^CGFloat (CGFloat p) {
//    if(p < 0.5)
//    {
//        return 8 * p * p * p * p;
//    }
//    else
//    {
//        CGFloat f = (p - 1);
//        return -8 * f * f * f * f + 1;
//    }
//};
//
//// Modeled after the quintic y = x^5
//INTUEasingFunction INTUEaseInQuintic = ^CGFloat (CGFloat p) {
//    return p * p * p * p * p;
//};
//
//// Modeled after the quintic y = (x - 1)^5 + 1
//INTUEasingFunction INTUEaseOutQuintic = ^CGFloat (CGFloat p) {
//    CGFloat f = (p - 1);
//    return f * f * f * f * f + 1;
//};
//
//// Modeled after the piecewise quintic
//// y = (1/2)((2x)^5)       ; [0, 0.5)
//// y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
//INTUEasingFunction INTUEaseInOutQuintic = ^CGFloat (CGFloat p) {
//    if(p < 0.5)
//    {
//        return 16 * p * p * p * p * p;
//    }
//    else
//    {
//        CGFloat f = ((2 * p) - 2);
//        return  0.5 * f * f * f * f * f + 1;
//    }
//};
//
//// Modeled after the exponential function y = 2^(10(x - 1))
//INTUEasingFunction INTUEaseInExponential = ^CGFloat (CGFloat p) {
//    return (p == 0.0) ? p : pow(2, 10 * (p - 1));
//};
//
//// Modeled after the exponential function y = -2^(-10x) + 1
//INTUEasingFunction INTUEaseOutExponential = ^CGFloat (CGFloat p) {
//    return (p == 1.0) ? p : 1 - pow(2, -10 * p);
//};
//
//// Modeled after the piecewise exponential
//// y = (1/2)2^(10(2x - 1))         ; [0,0.5)
//// y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
//INTUEasingFunction INTUEaseInOutExponential = ^CGFloat (CGFloat p) {
//    if(p == 0.0 || p == 1.0) return p;
//    
//    if(p < 0.5)
//    {
//        return 0.5 * pow(2, (20 * p) - 10);
//    }
//    else
//    {
//        return -0.5 * pow(2, (-20 * p) + 10) + 1;
//    }
//};
//
//// Modeled after shifted quadrant IV of unit circle
//INTUEasingFunction INTUEaseInCircular = ^CGFloat (CGFloat p) {
//    return 1 - sqrt(1 - (p * p));
//};
//
//// Modeled after shifted quadrant II of unit circle
//INTUEasingFunction INTUEaseOutCircular = ^CGFloat (CGFloat p) {
//    return sqrt((2 - p) * p);
//};
//
//// Modeled after the piecewise circular function
//// y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
//// y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
//INTUEasingFunction INTUEaseInOutCircular = ^CGFloat (CGFloat p) {
//    if(p < 0.5)
//    {
//        return 0.5 * (1 - sqrt(1 - 4 * (p * p)));
//    }
//    else
//    {
//        return 0.5 * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
//    }
//};
//
//// Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
//INTUEasingFunction INTUEaseInBack = ^CGFloat (CGFloat p) {
//    return p * p * p - p * sin(p * M_PI);
//};
//
//// Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
//INTUEasingFunction INTUEaseOutBack = ^CGFloat (CGFloat p) {
//    CGFloat f = (1 - p);
//    return 1 - (f * f * f - f * sin(f * M_PI));
//};
//
//// Modeled after the piecewise overshooting cubic function:
//// y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
//// y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
//INTUEasingFunction INTUEaseInOutBack = ^CGFloat (CGFloat p) {
//    if(p < 0.5)
//    {
//        CGFloat f = 2 * p;
//        return 0.5 * (f * f * f - f * sin(f * M_PI));
//    }
//    else
//    {
//        CGFloat f = (1 - (2*p - 1));
//        return 0.5 * (1 - (f * f * f - f * sin(f * M_PI))) + 0.5;
//    }
//};
//
//// Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
//INTUEasingFunction INTUEaseInElastic = ^CGFloat (CGFloat p) {
//    return sin(13 * M_PI_2 * p) * pow(2, 10 * (p - 1));
//};
//
//// Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
//INTUEasingFunction INTUEaseOutElastic = ^CGFloat (CGFloat p) {
//    return sin(-13 * M_PI_2 * (p + 1)) * pow(2, -10 * p) + 1;
//};
//
//// Modeled after the piecewise exponentially-damped sine wave:
//// y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
//// y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
//INTUEasingFunction INTUEaseInOutElastic = ^CGFloat (CGFloat p) {
//    if(p < 0.5)
//    {
//        return 0.5 * sin(13 * M_PI_2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1));
//    }
//    else
//    {
//        return 0.5 * (sin(-13 * M_PI_2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2);
//    }
//};
//
//INTUEasingFunction INTUEaseInBounce = ^CGFloat (CGFloat p) {
//    return 1 - INTUEaseOutBounce(1 - p);
//};
//
//INTUEasingFunction INTUEaseOutBounce = ^CGFloat (CGFloat p) {
//    if(p < 4/11.0)
//    {
//        return (121 * p * p)/16.0;
//    }
//    else if(p < 8/11.0)
//    {
//        return (363/40.0 * p * p) - (99/10.0 * p) + 17/5.0;
//    }
//    else if(p < 9/10.0)
//    {
//        return (4356/361.0 * p * p) - (35442/1805.0 * p) + 16061/1805.0;
//    }
//    else
//    {
//        return (54/5.0 * p * p) - (513/25.0 * p) + 268/25.0;
//    }
//};
//
//INTUEasingFunction INTUEaseInOutBounce = ^CGFloat (CGFloat p) {
//    if(p < 0.5)
//    {
//        return 0.5 * INTUEaseInBounce(p*2);
//    }
//    else
//    {
//        return 0.5 * INTUEaseOutBounce(p * 2 - 1) + 0.5;
//    }
//};
//
////convenient method for float caculation
//CGFloat ARFloatInterpolation(CGFloat from, CGFloat to, CGFloat time, AREasingCurve easing) {
//    CGFloat differ = to - from;
//    return from + differ * easing(time);
//}
//
////
////  DGDownloaderMath.m
////  DGDownloaderButton
////
////  Created by Desgard_Duan on 16/6/27.
////  Copyright © 2016年 Desgard_Duan. All rights reserved.
////
//
//#import "DGDownloaderMath.h"
//#import <UIKit/UIKit.h>
//
//@implementation DGDownloaderMath
//
//#pragma mark - 计算欧几里得距离
//+ (CGFloat) calcDistance: (CGPoint)x to: (CGPoint)y {
//    CGFloat a1 = x.x - y.x;
//    CGFloat a2 = x.y - y.y;
//    return sqrt(a1 * a1 + a2 * a2);
//}
//
//#pragma mark - 计算斜率
//+ (CGFloat) calcGradient: (CGPoint)A1 and: (CGPoint)A2 {
//    return (A1.x - A2.x) / (A1.y - A2.y);
//}
//
//#pragma mark - 计算Control Point Positon
//+ (CGPoint) calcControlPoint: (CGPoint)O1 and: (CGPoint)O2 {
//    return [self calcControlPoint: O1 and: O2 random: NO];
//}
//
//+ (CGPoint) calcControlPoint: (CGPoint)O1 and: (CGPoint)O2 random: (bool)isRandom {
//    CGPoint O_centre = CGPointMake((O1.x + O2.x) / 2.f, (O1.y + O2.y) / 2.f);
//    CGFloat d = [self calcDistance: O_centre to: O1];
//    CGFloat k = d / 40.f;
//    if (isRandom) {
//        int isRandom_int = arc4random() % 2;
//        if (isRandom_int) k = -k;
//        
//    }
//    CGFloat new_x = (O1.y - O2.y) / 2.f / k + (O1.x + O2.x) / 2.f;
//    CGFloat new_y = - ((O1.x - O2.x) / 2.f / k - (O1.y + O2.y) / 2.f);
//    
//    return CGPointMake(new_x, new_y);
//}
//
//#pragma mark - 计算Begin Point Postion
//+ (CGPoint) calcBeginPoint: (CGPoint)O radius: (CGFloat)r coefficent: (CGFloat)c {
//    CGFloat dis = r * c;
//    CGPoint ans;
//    // 生成角度
//    int angel = arc4random() % 360;
//    if (angel <= 180) {
//        double theta = (double)angel / 360 * M_PI * 2;
//        ans = CGPointMake(O.x + dis * cos(theta), O.y - dis * sin(theta));
//    } else {
//        double theta = (double)(360 - angel) / 360 * M_PI * 2;
//        ans = CGPointMake(O.x + dis * cos(theta), O.y + dis * sin(theta));
//    }
//    return ans;
//}
//
//@end
//
//
//
//#ifndef NMATH_PRECISION_H_INCLUDED
//#define NMATH_PRECISION_H_INCLUDED
//
//#include <float.h>
//
//#ifdef __cplusplus
//#include <cmath>
//#else
//#include <math.h>
//#endif    /* __cplusplus */
//
//namespace NMath {
//    
//#ifdef __cplusplus
//    extern "C" {
//#endif    /* __cplusplus */
//        
//        /* Floating point precision */
//#ifdef MATH_SINGLE_PRECISION
//#define SCALAR_T_MAX FLT_MAX
//        
//    typedef float scalar_t;
//        
//    #define nmath_sqrt    sqrtf
//    #define nmath_abs    fabs
//        
//    #define nmath_sin    sinf
//    #define nmath_cos    cosf
//    #define nmath_tan    tanf
//    #define nmath_asin    asinf
//    #define nmath_acos    acosf
//    #define nmath_atan    atanf
//    #define nmath_atan2    atan2
//    #define nmath_pow    pow
//        
//#else
//    #define SCALAR_T_MAX DBL_MAX
//        
//    typedef double scalar_t;
//        
//    #define nmath_sqrt  sqrt
//    #define nmath_abs   fabs
//        
//    #define nmath_sin    sin
//    #define nmath_cos    cos
//    #define nmath_tan    tan
//    #define nmath_asin    asin
//    #define nmath_acos    acos
//    #define nmath_atan    atan
//    #define nmath_atan2    atan2
//    #define nmath_pow    pow
//        
//#endif /* MATH_SINGLE_PRECISION */
//        
//        /* Infinity */
//#ifndef INFINITY
//    #define INFINITY SCALAR_T_MAX
//#endif /* INFINITY */
//        
//#ifndef EPSILON
//    #define EPSILON        1E-8
//#endif /* EPSILON */
//        
///* Useful scalar_t values used in comparisons */
//const scalar_t ERROR_MARGIN       = EPSILON;
//const scalar_t SCALAR_MEDIUM   = 1.e-2;   /* 0.01 */
//const scalar_t SCALAR_SMALL    = 1.e-4;   /* 0.0001 */
//const scalar_t SCALAR_XSMALL   = 1.e-6;   /* 0.000001 */
//const scalar_t SCALAR_XXSMALL  = 1.e-8;   /* 0.00000001 */
//const scalar_t SCALAR_XXXSMALL = 1.e-12;  /* 0.000000000001 */
//
///* PI */
//const scalar_t PI_DOUBLE    = 6.283185307179586232;
//const scalar_t PI            = 3.14159265358979323846;
//const scalar_t PI_HALF        = 1.57079632679489661923;
//const scalar_t PI_QUARTER    = 0.78539816339744830962;
//
///* EULER_E */
//const scalar_t EULER_E = 2.7182818284590452354;
//
//const scalar_t LN2    = 0.69314718055994530942;
//const scalar_t LN10    = 2.30258509299404568402;
//
///* RADIAN */
//const scalar_t RADIAN = 0.017453292519943;
//        
//#ifdef __cplusplus
//    }   /* extern "C" */
//#endif
//    
//} /* namespace NMath */
//
//// Check for standard definitions
//#ifndef M_PI
//    #define M_PI NMath::PI
//#endif /* M_PI */
//
//#ifndef M_E
//    #define M_E    NMath::EULER_E
//#endif /* M_E */
//
//#endif /* NMATH_PRECISION_H_INCLUDED */
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif    /* __cplusplus */
//    
//    namespace NMath {
//        namespace Interpolation {
//            
//            /*
//             **    Smoothstep
//             **    The inputs are values edge0, edge1, x with edge0 < x < edge1.
//             **    Unlike the rest interpolation methods, the returned value
//             **    for smoothstep is in the 0 - 1 range.
//             */
//            static inline scalar_t smoothstep(scalar_t a, scalar_t b, scalar_t t)
//            {
//                /*
//                 **    This is essentially cubic Hermite interpolation.
//                 **    Formula: (3 * (t^2)) - (2 * (t^3)
//                 */
//                
//                /* Scale, bias and saturate t to the [0-1] range */
//                scalar_t y = (t - a) / (b - a);
//                
//                if (y < 0) y = 0;
//                else if (y > 1) y = 1;
//                
//                /* Evaluate polynomial */
//                return y * y * (3 - 2 * y);
//            }
//            
//            /* Ken Perlin's suggested alternative which has zero 1st and 2nd order derivatives at t = 0 and t = 1 */
//            static inline scalar_t smoothstep_perlin(scalar_t a, scalar_t b, scalar_t t)
//            {
//                /*
//                 **    This is essentially Hermite interpolation.
//                 **    Formula (6 * (t^5)) - (15 * (t^4)) + (10 * (t^3))
//                 */
//                
//                /* Scale, and saturate t to the [0-1] range */
//                scalar_t y = (t - a) / (b - a);
//                
//                if (y < 0) y = 0;
//                else if (y > 1) y = 1;
//                
//                /* Evaluate polynomial */
//                return y * y * y * (y * (y * 6 - 15) + 10);
//            }
//            
//            static inline scalar_t step(scalar_t a, scalar_t b, scalar_t t)
//            {
//                return (t < 0.5) ? a : b;
//            }
//            
//            static inline scalar_t linear(scalar_t a, scalar_t b, scalar_t t)
//            {
//                return  a + (b - a) * t;
//            }
//            
//            static inline scalar_t cosine(scalar_t a, scalar_t b, scalar_t t)
//            {
//                /*
//                 **  First we turn the p value into an angle to sample from the
//                 **  cosine wave and sample from the wave but converting the
//                 **  scale run between 0 and 1 instead of the wave's usual -1 to 1.
//                 **  Lastly we perform a normal linear interpolation, but using the
//                 **  value from the cosine wave instead of the value of the given p
//                 */
//                
//                scalar_t t2 = (1 - nmath_cos(t * PI)) / 2;
//                return (a * (1 - t2) + b * t2);
//            }
//            
//            static inline scalar_t acceleration(scalar_t a, scalar_t b, scalar_t t)
//            {
//                scalar_t p2 = t * t;
//                return  (a * (1 - p2)) + (b * p2);
//            }
//            
//            static inline scalar_t deceleration(scalar_t a, scalar_t b, scalar_t t)
//            {
//                scalar_t rt = 1 - t;
//                scalar_t t2 = 1 - (rt * rt);
//                return  (a * (1 - t2)) + (b * t2);
//            }
//            
//            static inline scalar_t cubic(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t)
//            {
//                /*
//                 **  Cubic interpolation is the simplest method that offers true continuity.
//                 **    It requires more than just the two endpoints of the segment but also the two points on
//                 **    either side of them. So the function requires 4 points in all labeled a, b, c, d, in the
//                 **    code below. t still behaves the same way for interpolating between the segment b to c.
//                 */
//                
//                scalar_t P = (d - c) - (a - b);
//                scalar_t Q = (a - b) - P;
//                scalar_t R = c - a;
//                scalar_t S = b;
//                
//                scalar_t t2 = t * t;
//                scalar_t t3 = t2 * t;
//                
//                return (P * t3) + (Q * t2) + (R * t) + S;
//            }
//            
//            static inline scalar_t hermite(scalar_t tang1, scalar_t a, scalar_t b, scalar_t tang2, scalar_t t)
//            {
//                /*
//                 **    Notes:
//                 **    This is valid for  0 < t < 1
//                 **    The fuctionality can easily be generalized for arbitrary space (m, n).
//                 **    However considering the purpose of this library we will mostly use it in the
//                 **    [0-1] space and such a generalization would introduce unnecessary computations.
//                 **
//                 **    a     : the startpoint of the curve.
//                 **    b     : he endpoint of the curve.
//                 **    t     : 0 - 1.
//                 **    tang1 : the tangent (e.g. direction and speed) to how the curve leaves the startpoint.
//                 **    tang2 : the tangent (e.g. direction and speed) to how the curves meets the endpoint.
//                 **
//                 **        Hermite basis functions:
//                 **
//                 **    h1(t) =  2t^3 - 3t^2 + 1
//                 **    h2(t) = -2t^3 + 3t^2
//                 **    h3(t) =   t^3 - 2t^2 + t
//                 **    h4(t) =   t^3 -  t^2
//                 **
//                 **    Final formula: (h1 * a) + (h2 * b) + (h3 * tang1) + (h4 * tang2)
//                 **
//                 **    h3 and h4 are applied to the tangents to make sure that the curve bends in the desired
//                 **    direction at the start and endpoint.
//                 **
//                 **    Matrix notation:
//                 **    Vector T: The interpolation-point and it's powers up to 3:
//                 **    Vector C: The parameters of the hermite curve:
//                 **    Matrix H: The matrix form of the 4 hermite polynomials:
//                 **
//                 **          | t^3 |            | a     |                |  2  -2   1   1 |
//                 **     T =  | t^2 |       C =  | b     |           H =  | -3   3  -2  -1 |
//                 **          | t^1 |            | tang1 |                |  0   0   1   0 |
//                 **          | 1   |            | tang2 |                |  1   0   0   0 |
//                 **
//                 **    To calculate a point Y on the curve you build the Vector T, multiply it with the matrix H
//                 **    and then multiply with C.
//                 **
//                 **    Y = T * H * C
//                 */
//                
//                scalar_t t2 = t * t;
//                scalar_t t3 = t2 * t;
//                
//                scalar_t h1 = (2 * t3) - (3 * t2) + 1;          /* calculate basis function 1 */
//                scalar_t h2 = 1 - h1;                           /* calculate basis function 2 */
//                scalar_t h3 = t3 - (2 * t2) + t;                /* calculate basis function 3 */
//                scalar_t h4 = t3 - t2;                          /* calculate basis function 4 */
//                
//                return (h1 * a) + (h2 * b) + (h3 * tang1) + (h4 * tang2); /* multiply and sum all functions together */
//            }
//            
//            static inline scalar_t cardinal(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t p, scalar_t t)
//            {
//                /*
//                 **    Notes:
//                 **    Cardinal splines are just a subset of the hermite curves.
//                 **    They don't need the tangent points because they will be calculated from the control
//                 **    points. We'll lose some of the flexibility of the hermite curves, but as a tradeoff
//                 **    the curves will be much easier to use.
//                 **
//                 **    We are interpolating between b and c.
//                 **    a and d are control points.
//                 **
//                 **    The formula for the tangents of cardinal splines is:
//                 **
//                 **    Tangenti = p * ( Xi - Xj )
//                 **
//                 **    where
//                 **        Xn : nth point (in the above: j = i - 2).
//                 **        p  : constant which affects the tightness of the curve.
//                 */
//                
//                scalar_t t2 = t * t;
//                scalar_t t3 = t2 * t;
//                
//                scalar_t h1 = (2 * t3) - (3 * t2) + 1;          /* calculate basis function 1 */
//                scalar_t h2 = 1 - h1;                           /* calculate basis function 2 */
//                scalar_t h3 = t3 - (2 * t2) + t;                /* calculate basis function 3 */
//                scalar_t h4 = t3 - t2;                          /* calculate basis function 4 */
//                
//                scalar_t tang1 = p * (c - a);
//                scalar_t tang2 = p * (d - b);
//                
//                return (h1 * b) + (h2 * c) + (h3 * tang1) + (h4 * tang2); /* multiply and sum all functions together */
//            }
//            
//            static inline scalar_t catmullrom(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t)
//            {
//                /*
//                 **  Notes:
//                 **  CatmullRoms are cardinals with a tension (p) of 0.5
//                 **
//                 **    I have verified the correctness of this method both mathematically and
//                 **    by using the cardinal. Both functions yielded the same results. This
//                 **    implementation is chosen due to lower computational cost.
//                 **
//                 **    ATTENTION: This algorithm is NOT proper for general cardinals, don't
//                 **    let the p (0.5) multiplication fool you. It is a trick to save a few
//                 **    multiplications in h. The h coefficients used below are only applicable
//                 **    to Catmull-Rom splines.
//                 */
//                scalar_t P = -a + (3 * (b - c)) + d;
//                scalar_t Q = (2 * a) - (5 * b) + (4 * c) - d;
//                scalar_t R = c - a;
//                scalar_t S = 2 * b;
//                
//                scalar_t t2 = t * t;
//                scalar_t t3 = t2 * t;
//                
//                return 0.5 * ((P * t3) + (Q * t2) + (R * t) + S);
//            }
//            
//            static inline scalar_t bezier_quadratic(scalar_t a, scalar_t b, scalar_t c, scalar_t t)
//            {
//                /* DeCasteljau */
//                scalar_t ab = linear(a, b, t);
//                scalar_t bc = linear(b, c, t);
//                return linear( ab, bc, t);
//            }
//            
//            static inline scalar_t bezier_cubic(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t)
//            {
//                /* DeCasteljau */
//                scalar_t ab  = linear(a, b, t);
//                scalar_t bc  = linear(b, c, t);
//                scalar_t cd  = linear(c, d, t);
//                scalar_t abc = linear(ab, bc, t);
//                scalar_t bcd = linear(bc, cd, t);
//                return linear( abc, bcd, t);
//            }
//            
//        } /* namespace Interpolation */
//    } /* namespace NMath */
//    
//#ifdef __cplusplus
//}   /* extern "C" */
//
//
///***************************************************************************
// * regular power function
// **************************************************************************/
//int pow(int base, int power) {
//    int iterator, solution;
//    
//    solution = 1;
//    
//    //multiply the base by iteself <power> number of times
//    for(iterator=0; iterator<power; iterator++) {
//        solution *= base;
//    }
//    
//    return solution;
//}
