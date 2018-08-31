//
//  CustomControlDefine.h
//  CustomControlLibrary
//
//  Created by luck on 2018/5/11.
//  Copyright © 2018年 luck. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^CustomControlActionResultBlock)(NSInteger actionType, NSInteger resultTag, id param1, id param2, id param3, id param4);
typedef void (^CustomControlButtonActionBlock)(NSInteger actionType, NSInteger buttonTag, id param1, id param2, id param3, id param4, CustomControlActionResultBlock block);

#if(0)
typedef struct
{
    __unsafe_unretained NSString *text;
    __unsafe_unretained UIColor *textColor;
    __unsafe_unretained UIFont *textFont;
    NSTextAlignment textAlignment;

    //输入框才有的参数
    __unsafe_unretained NSString *placeText;
    __unsafe_unretained UIColor *placeTextColor;
    UIKeyboardType keyboardType;
    BOOL secureTextEntry;
    UITextFieldViewMode clearButtonMode;
}CustomControlTextParam;

typedef struct
{
    int lineType;
    int lineWidth;
    __unsafe_unretained UIColor *lineColor;
}CustomControlDivideLineParam;

typedef struct
{
    int leftMargin;
    int rightMargin;
    int topMargin;
    int bottomMargin;
    
    int valueMargin;
    int mustFlagMargin;
}CustomControlMarginParam;

typedef struct
{
    CGSize iconSize;
    __unsafe_unretained NSString *iconImageName;
}CustomControlIconParam;
#else
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface CustomControlTextParam : NSObject

@property(nonatomic, weak)NSString *text;
@property(nonatomic, weak)UIColor *textColor;
@property(nonatomic, weak)UIFont *textFont;
@property(nonatomic, assign)NSTextAlignment textAlignment;

//输入框才有的参数
@property(nonatomic, weak)NSString *placeText;
@property(nonatomic, weak)UIColor *placeTextColor;
@property(nonatomic, assign)UIKeyboardType keyboardType;
@property(nonatomic, assign)BOOL secureTextEntry;
@property(nonatomic, assign)UITextFieldViewMode clearButtonMode;

@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface CustomControlDivideLineParam : NSObject

@property(nonatomic, assign)int lineType;
@property(nonatomic, assign)int lineWidth;

@property(nonatomic, assign)int leftMargin;
@property(nonatomic, assign)int rightMargin;

@property(nonatomic, weak)UIColor *lineColor;

@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface CustomControlMarginParam : NSObject

@property(nonatomic, assign)int leftMargin;
@property(nonatomic, assign)int rightMargin;
@property(nonatomic, assign)int topMargin;
@property(nonatomic, assign)int bottomMargin;

@property(nonatomic, assign)int valueMargin;
@property(nonatomic, assign)int mustFlagMargin;

@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface CustomControlIconParam : NSObject

@property(nonatomic, assign)CGSize iconSize;
@property(nonatomic, weak)NSString *iconImageName;

@end
#endif
