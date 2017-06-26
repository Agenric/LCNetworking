//
//  ViewController.m
//  LCNetworking
//
//  Created by Agenric on 2017/2/27.
//  Copyright © 2017年 Agenric. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidLayoutSubviews {

}
@end

@interface MyUIView : UIView

@end
@implementation MyUIView

- (void)layoutSubviews {
    NSLog(@"ssss");
}

- (void)layoutIfNeeded {

}
@end
