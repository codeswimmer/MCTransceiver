//
//  MCTransceiverViewController.m
//  MCTransceiverExample
//
//  Created by Keith Ermel on 5/1/14.
//  Copyright (c) 2014 Keith Ermel. All rights reserved.
//

#import "MCTransceiverViewController.h"


@interface MCTransceiverViewController ()<MCTransceiverDelegate>
@property (strong, nonatomic, readonly) MCTransceiver *transceiver;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@end


@implementation MCTransceiverViewController

#pragma mark - MCTransceiverDelegate

-(void)didStartAdvertising
{
    NSLog(@"didStartAdvertising");
}

-(void)didStartBrowsing
{
    NSLog(@"didStartBrowsing");
}

-(void)didFindPeer:(MCPeerID *)peerID
{
    NSLog(@"didFindPeer: %@", peerID.displayName);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        self.statusLabel.text = [NSString stringWithFormat:@"didFindPeer: %@", peerID.displayName];
    });
}

-(void)didLosePeer:(MCPeerID *)peerID
{
    NSLog(@"didLosePeer: %@", peerID.displayName);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        self.statusLabel.text = [NSString stringWithFormat:@"didLosePeer: %@", peerID.displayName];
    });
}

-(void)didReceiveInvitationFromPeer:(MCPeerID *)peerID
{
    NSLog(@"didReceiveInvitationFromPeer: %@", peerID.displayName);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        self.statusLabel.text = [NSString stringWithFormat:@"didReceiveInvitationFromPeer: %@", peerID.displayName];
    });
}

-(void)didConnectToPeer:(MCPeerID *)peerID
{
    NSLog(@"didConnectToPeer: %@", peerID.displayName);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        self.statusLabel.text = [NSString stringWithFormat:@"didConnectToPeer: %@", peerID.displayName];
    });
}

-(void)didDisconnectFromPeer:(MCPeerID *)peerID
{
    NSLog(@"didDisconnectFromPeer: %@", peerID.displayName);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        self.statusLabel.text = [NSString stringWithFormat:@"didDisconnectFromPeer: %@", peerID.displayName];
    });
}

-(void)didReceiveData:(NSData *)data fromPeer:(MCPeerID *)peerID
{
    NSString *message = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSLog(@"    message: %@", message);
}


#pragma mark - Internal API

-(void)startTransceiving
{
    NSLog(@"startTransceiving");
    [self.transceiver startAdvertising];
    [self.transceiver startBrowsing];
}


#pragma mark - Configuration

-(void)configureTransceiver
{
    NSLog(@"configureTransceiver: %@", NSStringFromMCTransceiverMode(self.mode));
    _transceiver = [[MCTransceiver alloc] initWithDelegate:self mode:self.mode];
}


#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self configureTransceiver];
    [self startTransceiving];
}

@end
