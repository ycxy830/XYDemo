//
//  XYGlobalFunctions.h
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void(^ButtonClickBlock) (UIButton* sender);

@interface UIButton(XYAddBlock)

- (void)setBlock:(ButtonClickBlock)block;
- (ButtonClickBlock)getBlock;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface XYGlobalFunctions : NSObject

+ (CGSize)calcTextWidth:(NSString *)text textFont:(UIFont *)textFont;

+ (NSString *)getFirstCharactor:(NSString *)aString;

+ (NSMutableAttributedString *)createAttributedString:(NSString *)preStr valueStr:(NSString *)valueStr suffStr:(NSString *)suffStr valueColor:(UIColor *)valueColor valueFont:(UIFont *)valueFont;

+ (NSMutableAttributedString *)getAttributedString:(NSString *)text font:(UIFont *)font lineSpace:(int)lineSpace;

+ (float)calcAttributedStringHeight:(NSString *)content contentWidth:(float)contentWidth font:(UIFont *)font lineSpace:(int)lineSpace;

+ (BOOL)canInputValue:(NSString *)inputValue keyboardType:(UIKeyboardType)keyboardType textField:(UITextField *)textField textView:(UITextView *)textView showMessage:(BOOL)showMessage filterSymbol:(BOOL)filterSymbol andBlock:(void(^)(NSString *message))block;

+ (BOOL)canInputDecimal:(NSString *)inputValue textField:(UITextField *)textField textView:(UITextView *)textView maxLength:(int)maxLength maxDecimalLength:(int)maxDecimalLength showMessage:(BOOL)showMessage message:(NSString *)message message2:(NSString *)message2 andBlock:(void(^)(NSString *message))block;

+ (NSString *)getFormatValue:(NSString *)prefix value:(float)value valueType:(int)valueType precisionType:(int)precisionType newValue:(CGFloat *)newValue valuePrecision:(int *)valuePrecision;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
+ (UIView *)createView:(CGRect)frame backColor:(UIColor *)backColor borderColor:(UIColor *)borderColor borderWidth:(NSInteger)borderWidth cornerRadius:(float)cornerRadius;

+ (UILabel *)createLabel:(CGRect)frame text:(NSString *)text textFont:(UIFont *)textFont textColor:(UIColor *)textColor textAlignment:(NSTextAlignment)textAlignment calcWidth:(BOOL)calcWidth;

+ (UIButton *)createButton:(CGRect)frame tag:(NSInteger)tag title:(NSString *)title titleFont:(UIFont *)titleFont titleColor:(UIColor *)titleColor titleAlignment:(NSTextAlignment)titleAlignment image:(UIImage *)image edgeInsets:(UIEdgeInsets)edgeInsets borderColor:(UIColor *)borderColor borderWidth:(NSInteger)borderWidth cornerRadius:(float)cornerRadius andBlock:(ButtonClickBlock)block;

+ (UITextField *)createTextField:(CGRect)frame placeHolder:(NSString *)placeHolder textFont:(UIFont *)textFont textAlignment:(NSTextAlignment)textAlignment textColor:(UIColor *)textColor placeHolderColor:(UIColor *)placeHolderColor keyboardType:(UIKeyboardType)keyboardType;

+ (void)setTextFieldDelegate:(UITextField *)textField delegate:(id)delegate beginAction:(SEL)beginAction endAction:(SEL)endAction changeAction:(SEL)changeAction setDelegate:(BOOL)setDelegate;

@end
