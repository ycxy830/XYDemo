//
//  FlipView.h
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FlipView : UIView

- (instancetype)initWithFrame:(CGRect)frame offset:(int)offset;

- (void)doFlip:(float)duration text:(NSString *)text;

@property(nonatomic, strong)UIView *topView;
@property(nonatomic, strong)UIView *bottomView;

@property(nonatomic, strong)UIView *topViewBeneath;
@property(nonatomic, strong)UIView *bottomViewBeneath;

@property(nonatomic, strong)NSString *text;

@end
