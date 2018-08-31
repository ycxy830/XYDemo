//
//  XYChartView.h
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 xy. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, XYChartViewType)
{
    XYChartViewTypeLine,//折线图
    XYChartViewTypePie,//饼状图
    XYChartViewTypeBar//柱状图
};

typedef NSArray* (^XYChartViewGetChartDataBlock) (NSInteger index, NSInteger dataType);

@interface XYChartView : UIView

- (XYChartView *)initWithFrame:(CGRect)frame chartType:(XYChartViewType)chartType contentEdgeInsets:(UIEdgeInsets)contentEdgeInsets;

- (void)setChartParam:(float)xAxisLeftMargin xAxisRightMargin:(float)xAxisRightMargin yAxisTopMargin:(float)yAxisTopMargin yAxisBottomMargin:(float)yAxisBottomMargin axesLineWidth:(float)axesLineWidth axesLineColor:(UIColor *)axesLineColor axesTextColor:(UIColor *)axesTextColor axesFontHeight:(float)axesFontHeight xAxisTextHeight:(float)xAxisTextHeight xAxisTextTopMargin:(float)xAxisTextTopMargin yAxisTextWidth:(float)yAxisTextWidth yAxisTextRightMargin:(float)yAxisTextRightMargin valueDotDadius:(float)valueDotDadius valueDotLineWidth:(float)valueDotLineWidth valueDotLineColor:(UIColor *)valueDotLineColor valueDotFillColor:(UIColor *)valueDotFillColor;

- (void)setChartData:(NSArray *)chartDataArray chartColorArray:(NSArray *)chartColorArray chartTimeArray:(NSArray *)chartTimeArray backColor:(UIColor *)backColor contentBackColor:(UIColor *)contentBackColor xIsTime:(BOOL)xIsTime andBlock:(XYChartViewGetChartDataBlock)block;

@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (^XYChartViewSetLineChartDataBlock) (NSArray *lineDataArray, UIColor *lineColor, UIColor *fillColor, UIColor *valueLineColor, UIColor *valueFillColor);
typedef void (^XYChartViewGetLineChartDataBlock) (XYChartViewSetLineChartDataBlock setLineChartDataBlock);

@interface XYLineChartView : UIView

- (XYLineChartView *)initWithFrame:(CGRect)frame contentEdgeInsets:(UIEdgeInsets)contentEdgeInsets contentBackColor:(UIColor *)contentBackColor;

- (void)setAxesStyle:(NSInteger)xAxisCount xAxisDrawCount:(NSInteger)xAxisDrawCount xAxisBaseIndex:(NSInteger)xAxisBaseIndex xAxisBaseLineWidth:(NSInteger)xAxisBaseLineWidth xAxisBaseLineColor:(UIColor *)xAxisBaseLineColor xAxisLineStyle:(NSInteger)xAxisLineStyle xAxisLineWidth:(NSInteger)xAxisLineWidth xAxisLineColor:(UIColor *)xAxisLineColor yAxisCount:(NSInteger)yAxisCount yAxisDrawCount:(NSInteger)yAxisDrawCount yAxisBaseIndex:(NSInteger)yAxisBaseIndex yAxisBaseLineWidth:(NSInteger)yAxisBaseLineWidth yAxisBaseLineColor:(UIColor *)yAxisBaseLineColor yAxisLineStyle:(NSInteger)yAxisLineStyle yAxisLineWidth:(NSInteger)yAxisLineWidth yAxisLineColor:(UIColor *)yAxisLineColor axesEdgeInsets:(UIEdgeInsets)axesEdgeInsets;

- (void)setAxesTextStyle:(float)xAxisTextWidth xAxisTextMargin:(float)xAxisTextMargin xAxisTextFont:(UIFont *)xAxisTextFont xAxisTextColor:(UIColor *)xAxisTextColor xAxisTextPos:(int)xAxisTextPos yAxisTextWidth:(float)yAxisTextWidth yAxisTextMargin:(float)yAxisTextMargin yAxisTextFont:(UIFont *)yAxisTextFont yAxisTextColor:(UIColor *)yAxisTextColor yAxisTextPos:(int)yAxisTextPos;

- (void)setAxesTextData:(BOOL)xAxisIsBase maxAxisData:(float)maxAxisData baseAxisDataArray:(NSArray *)baseAxisDataArray axisDataArray:axisDataArray;

- (void)setLineData:(float)lineWidth lineDataArray:(NSArray *)lineDataArray lineColor:(UIColor *)lineColor fillColor:(UIColor *)fillColor fillAlpha:(float)fillAlpha valueRadius:(float)valueRadius valueLineWidth:(float)valueLineWidth valueLineColor:(UIColor *)valueLineColor valueFillColor:(UIColor *)valueFillColor andBlock:(XYChartViewGetLineChartDataBlock)block;

@end
