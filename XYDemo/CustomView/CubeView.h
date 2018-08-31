//
//  CubeView.h
//  Nake_iOS
//
//  Created by luck on 2017/4/7.
//  Copyright © 2017年 luck. All rights reserved.
//

#import <UIKit/UIKit.h>

//UIView有仨比较重要的布局属性：frame, bounds, center。
//CALayer也有类似的布局属性：frame, bounds, position。
//frame代表外部坐标（相对于父元素）。bounds代表内部坐标，bounds可以视为x坐标和y坐标都为0的frame。
//position和center都代表anchorPoint相对于superLayer的坐标。

//frame 代表了图层的外部坐标（也就是在父图层上占据的空间）， bounds 是内部坐标（{0, 0}通常是图层的左上角）， center 和 position 都代表了相对于父图层 anchorPoint 所在的位置。对于视图或者图层来说， frame 并不是一个非常清晰的属性，它其实是一个虚拟属性，是根据 bounds ， position 和 transform 计算而来，所以当其中任何一个值发生改变，frame都会变化。当对图层做变换的时候，比如旋转或者缩放， frame 实际上代表了覆盖在图层旋转之后的整个轴对齐的矩形区域，也就是说 frame 的宽高可能和 bounds 的宽高不再一致了。

//anchorPoint是一个相对于bounds的比例值。默认是（0.5，0.5）即中心点。
//那position就是anchorPoint相对于superlayer的坐标。
//frame是一个虚拟值，由position和anchorPoint共同决定。
//公式为
//frame.origin.x = position.x - anchorPoint.x * bounds.size.width;
//frame.origin.y = position.y - anchorPoint.y *bounds.size.height；

//CALayer还有俩额外属性zPosition和anchorPointZ。
//zPosition描述的是layer的覆盖顺序。
//anchorPointZ描述的是3维动画的支点。

//anchorPoint和anchorPointZ都属于动画时要用的，anchorPoint指定x,y轴上的中心点，单位为比例，数值为0-1。anchorPointZ指定Z轴上的中心点，单位为px。
//要特别注意anchorPoint和anchorPointZ的单位是不一样的。

//以(0,0,d)作为眼睛的位置，(x,y,z)代表3d图像的某个点，(x*,y*)代表在x-y屏幕的映射的坐标，则 x* = x/(1-z/d), y*=y/(1-z/d);

//#define RADIANS_TO_DEGREES(x) ((x) / M_PI * 180.0)
//#define DEGREES_TO_RADIANS(x) ((x) / 180.0 * M_PI)
//CGAffineTransform 中的“仿射”的意思是无论变换矩阵用什么值，图层中平行的两条线在变换之后任然保持平行

//m34 的默认值是0，我们可以通过设置 m34 为-1.0 / d 来应用透视效果， d 代表了想象中视角相机和屏幕之间的距离，以像素为单位，那应该如何计算这个距离呢？实际上并不需要，大概估算一个就好了。
//如果有多个视图或者图层，每个都做3D变换，那就需要分别设置相同的m34值，并且确保在变换之前都在屏幕中央共享同一个 position
//CALayer 有一个属性叫做 sublayerTransform 。它也是 CATransform3D 类型，但和对一个图层的变换不同，它影响到所有的子图层。
//CATransformLayer 不同于普通的 CALayer ，因为它不能显示它自己的内容。只有当存在了一个能作用域子图层的变换它才真正存在。 CATransformLayer 并不平面化它的子图层，所以它能够用于构造一个层级的3D结构，

//cornerRadius 和 maskToBounds 独立作用的时候都不会有太大的性能问题，但是当他俩结合在一起，就触发了屏幕外渲染。有时候你想显示圆角并沿着图层裁切子图层的时候，你可能会发现你并不需要沿着圆角裁切，这个情况下用 CAShapeLayer 就可以避免这个问题了。你想要的只是圆角且沿着矩形边界裁切，同时还不希望引起性能问题。其实你可以用现成的 UIBezierPath 的构造器 +bezierPathWithRoundedRect:cornerRadius: （见清单15.1）.这样做并不会比直接用 cornerRadius 更快，但是它避免了性能问题。

//CALayer 有一个属性叫做 contents ，这个属性的类型被定义为id，意味着它可以是任何类型的对象。layer.contents = (__bridge id)image.CGImage;CALayer与 contentMode 对应的属性叫做 contentsGravity ，contentsGravity 的目的是为了决定内容在图层的边界中怎么对齐，当用代码的方式来处理寄宿图的时候，一定要记住要手动的设置图层的 contentsScale 属性，否则，你的图片在Retina设备上就显示得不正确啦。代码如下：layer.contentsScale = [UIScreen mainScreen].scale;

//kCAFillRuleEvenOdd字面意思是“奇偶”。按该规则，要判断一个点是否在图形内，从该点作任意方向的一条射线，然后检测射线与图形路径的交点的数量。如果结果是奇数则认为点在内部，是偶数则认为点在外部。
//kCAFillRuleNonZero字面意思是“非零”。按该规则，要判断一个点是否在图形内，从该点作任意方向的一条射线，然后检测射线与图形路径的交点情况。从0开始计数，路径从左向右穿过射线则计数加1，从右向左穿过射线则计数减1。得出计数结果后，如果结果是0，则认为点在图形外部，否则认为在内部。

//图形性能
//
//1. 关于CALayer的shouldRasterize（光栅化）
//开启shouldRasterize后,CALayer会被光栅化为bitmap,layer的阴影等效果也会被保存到bitmap中。
//
//当我们开启光栅化后,需要注意三点问题。
//
//如果我们更新已光栅化的layer,会造成大量的offscreen渲染。
//
//因此CALayer的光栅化选项的开启与否需要我们仔细衡量使用场景。只能用在图像内容不变的前提下的：
//
//用于避免静态内容的复杂特效的重绘,例如前面讲到的UIBlurEffect
//用于避免多个View嵌套的复杂View的重绘。
//而对于经常变动的内容,这个时候不要开启,否则会造成性能的浪费。
//
//例如我们日程经常打交道的TableViewCell,因为TableViewCell的重绘是很频繁的（因为Cell的复用）,如果Cell的内容不断变化,则Cell需要不断重绘,如果此时设置了cell.layer可光栅化。则会造成大量的offscreen渲染,降低图形性能。
//
//当然,合理利用的话,是能够得到不少性能的提高的,因为使用shouldRasterize后layer会缓存为Bitmap位图,对一些添加了shawdow等效果的耗费资源较多的静态内容进行缓存,能够得到性能的提升。
//
//不要过度使用,系统限制了缓存的大小为2.5X Screen Size.
//
//如果过度使用,超出缓存之后,同样会造成大量的offscreen渲染。
//
//被光栅化的图片如果超过100ms没有被使用,则会被移除
//
//因此我们应该只对连续不断使用的图片进行缓存。对于不常使用的图片缓存是没有意义,且耗费资源的。
//
//2. 关于offscreen rendering
//注意到上面提到的offscreen rendering。我们需要注意shouldRasterize的地方就是会造成offscreen rendering的地方,那么为什么需要避免呢？
//
//WWDC 2011 Understanding UIKit Rendering指出一般导致图形性能的问题大部分都出在了offscreen rendering,因此如果我们发现列表滚动不流畅,动画卡顿等问题,就可以想想和找出我们哪部分代码导致了大量的offscreen 渲染。
//
//首先,什么是offscreen rendering?
//
//offscreen rendring指的是在图像在绘制到当前屏幕前,需要先进行一次渲染,之后才绘制到当前屏幕。
//
//那么为什么offscreen渲染会耗费大量资源呢？
//
//原因是显卡需要另外alloc一块内存来进行渲染,渲染完毕后在绘制到当前屏幕,而且对于显卡来说,onscreen到offscreen的上下文环境切换是非常昂贵的(涉及到OpenGL的pipelines和barrier等),
//
//备注：
//
//这里提到的offscreen rendering主要讲的是通过GPU执行的offscreen,事实上还有的offscreen rendering是通过CPU来执行的（例如使用Core Graphics, drawRect）。其它类似cornerRadios, masks, shadows等触发的offscreen是基于GPU的。
//
//许多人有误区,认为offscreen rendering就是software rendering,只是纯粹地靠CPU运算。实际上并不是的,offscreen rendering是个比较复杂,涉及许多方面的内容。
//
//我们在开发应用,提高性能通常要注意的是避免offscreen rendering。不需要纠结和拘泥于它的定义.
//
//有兴趣可以继续阅读Andy Matuschak, 前UIKit team成员关于offscreen rendering的评论
//
//总之,我们通常需要避免大量的offscreen rendering.
//
//会造成 offscreen rendering的原因有：
//
//Any layer with a mask (layer.mask)
//
//Any layer with layer.masksToBounds being true
//
//Any layer with layer.allowsGroupOpacity set to YES and layer.opacity is less than 1.0
//
//Any layer with a drop shadow (layer.shadow*).
//
//Any layer with layer.shouldRasterize being true
//
//Any layer with layer.cornerRadius, layer.edgeAntialiasingMask, layer.allowsEdgeAntialiasing
//
//因此,对于一些需要优化图像性能的场景,我们可以检查我们是否触发了offscreen rendering。 并用更高效的实现手段来替换。
//
//例如:
//
//阴影绘制:
//
//使用ShadowPath来替代shadowOffset等属性的设置。
//
//两种不同方式来绘制阴影：
//
//不使用shadowPath
//
//CALayer *imageViewLayer = cell.imageView.layer;
//imageViewLayer.shadowColor = [UIColor blackColor].CGColor;
//imageViewLayer.shadowOpacity = 1.0;
//imageViewLayer.shadowRadius = 2.0;
//imageViewLayer.shadowOffset = CGSizeMake(1.0, 1.0);
//
//使用shadowPath
//
//imageViewLayer.shadowPath = CGPathCreateWithRect(imageRect, NULL);
//
//个人推测的shadowPath高效的原因是使用shadowPath避免了offscreen渲染,因为仅需要直接绘制路径即可,不需要提前读取图像去渲染。
//
//
//使用CornerRadius：
//
//CALayer *imageViewLayer = cell.imageView.layer;
//imageViewLayer.cornerRadius = imageHeight / 2.0;
//imageViewLayer.masksToBounds = YES;
//利用一张中间为透明圆形的图片来进行遮盖,虽然会引起blending,但性能仍然高于offerScreen。
//
//根据苹果测试,第二种方式比第一种方式更高效:
//
//以上举了两个例子阐明了在避免大量的offerscreen渲染后,性能能够得到非常直观有效的提高。
//
//3. 关于blending
//前面提到了用透明圆形的图片来进行遮盖,会引起blending。blending也会耗费性能。
//
//：） 笑。如果阅读这篇文章的读者看到这里,是不是觉得已经无眼看下去了。哈哈,我自己学习总结到这里也是感受到了长路慢慢,但是我们仍然还是要不断上下求索的。 ：）
//
//好了 接下来让我们来认识一下Blending.
//
//什么是Blending？
//在iOS的图形处理中,blending主要指的是混合像素颜色的计算。最直观的例子就是,我们把两个图层叠加在一起,如果第一个图层的透明的,则最终像素的颜色计算需要将第二个图层也考虑进来。这一过程即为Blending。
//
//会导致blending的原因:
//
//layer(UIView)的Alpha < 1
//UIImgaeView的image含有Alpha channel(即使UIImageView的alpha是1,但只要image含透明通道,则仍会导致Blending)
//为什么Blending会导致性能的损失？
//
//原因是很直观的,如果一个图层是不透明的,则系统直接显示该图层的颜色即可。而如果图层是透明的,则会引入更多的计算,因为需要把下面的图层也包括进来,进行混合后颜色的计算。
//
//在了解完Blending之后,我们就知道为什么很多优化准则都需要我们尽量使用不透明图层了。接下来就是在开发中留意和进行优化了。

//引起Offscreen-Rendered的操作有：
//- 圆角 cornerRadius masksToBounds同时设置
//- 设置shadow
//- 开启光栅化 shouldRasterize=YES.CALayer 有一个 shouldRasterize 属性，将这个属性设置成 true 后就开启了光栅化。开启光栅化后会将图层绘制到一个屏幕外的图像，然后这个图像将会被缓存起来并绘制到实际图层的 contents 和子图层，对于有很多的子图层或者有复杂的效果应用，这样做就会比重绘所有事务的所有帧来更加高效。但是光栅化原始图像需要时间，而且会消耗额外的内存。光栅化也会带来一定的性能损耗，是否要开启就要根据实际的使用场景了，图层内容频繁变化时不建议使用。最好还是用 Instruments 比对开启前后的 FPS 来看是否起到了优化效果。
//- 图层蒙板

//与CPU擅长逻辑控制，串行的运算和通用类型数据运算不同，GPU擅长的是大规模并发计算，这也正是密码破解等所需要的。所以GPU除了图像处理，也越来越多的参与到计算当中来。

@interface CubeView : UIView

- (CubeView *)initWithFrame:(CGRect)frame degrees:(float)degrees rotatePoint:(CGPoint)rotatePoint;

@end
