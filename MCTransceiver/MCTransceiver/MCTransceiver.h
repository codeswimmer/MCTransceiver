//
//  MCTransceiver.h
//  MCTransceiver
//
//  Created by Keith Ermel on 5/1/14.
//  Copyright (c) 2014 Keith Ermel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MultipeerConnectivity/MultipeerConnectivity.h>


extern NSString *const      kMCTransceiverServiceType;
extern NSTimeInterval const kMCTDefaultPeerInviteTimeout;

typedef void(^MCSendDataCompletion)(NSError *error);

/**
 `MCTransceiverMode` specifies whether the `MCTransceiver` implementation runs as an 
 advertiser or as a browser.
 */
typedef NS_ENUM(NSInteger, MCTransceiverMode){
/** Transceiver mode has not been established */
MCTransceiverModeUnknown,

/** 
 Transceiver mode is as an advertiser. It will advertise its existence and can serve
 data to a connected browser
 */
MCTransceiverModeAdvertiser,

/** 
 Transceiver mode is as a browser. It can search for an advertiser and connect to it.
 */
MCTransceiverModeBrowser
};

/**
 Returns an `NSString` representing the given `MCTransceiverMode`
 @param mode The mode to be converted into a string.
 */

NSString *NSStringFromMCTransceiverMode(MCTransceiverMode mode);

/**
 The `MCTransceiverDelegate` protocol defines a set of methods that you can use to receive
 transceiver events.
 */
@protocol MCTransceiverDelegate <NSObject>
/**
 Indicates the transceiver has found a peer.
 @param peerID The peer that was found.
 */
-(void)didFindPeer:(MCPeerID *)peerID;

/**
 Indicates that the transceiver has lost a previously found peer.
 @param peerID The peer that was lost.
 */
-(void)didLosePeer:(MCPeerID *)peerID;

/**
 Indicates the transceiver has received an invitation to connect from the given peen.
 @param peerID The peer that sent the invitation.
 */
-(void)didReceiveInvitationFromPeer:(MCPeerID *)peerID;

/**
 Indicates the transceiver has connected to the given peer.
 @param peerID The peer that has been connected to.
 */
-(void)didConnectToPeer:(MCPeerID *)peerID;

/**
 Indicates the transceiver has disconnected from a peer which it was previously connected to.
 @param peerID The peer that has disconnected.
 */
-(void)didDisconnectFromPeer:(MCPeerID *)peerID;

/**
 Indicates the transceiver has received a package of data from a peer.
 @param data The data that was sent by the peer.
 @param peerID The peer that sent the data.
 */
-(void)didReceiveData:(NSData *)data fromPeer:(MCPeerID *)peerID;

@optional
/** Indicates the transceiver has initiated advertising. */
-(void)didStartAdvertising;

/** Indicates the transceiver has initiated browsing. */
-(void)didStartBrowsing;
@end

/**
 `MCTransceiver` provides a simplified means of advertising, browsing, connecting and sending
 data to devices via the Multipeer Connectivity framework.
 
 A `MCTransceiver` can operate in one of two modes, either as an advertiser or as a browser, 
 which is establised via the initWithDelegate:mode: initializer.
 
 ### Advertising and Browsing
 * Advertising: Use the startAdvertising method to initate advertising of the device.
 * Browsing: Use the startBrowsing method to begin browsing for advertising devices.
 
 ### Connecting Devices
 The connection with one or more devices is handled seamlessly and automatically. No manual
 paring of devices is required.
 
 ### Sending Data
 The sendUnreliableData:toPeers:completion: method can be used for sending data in an 
 unreliable manner to one or more connected peers. From the `MCSession` documentation:
 
    Messages to peers should be sent immediately without socket-level queueing. If a
    message cannot be sent immediately, it should be dropped. The order of messages is 
    not guaranteed.
 */
@interface MCTransceiver : NSObject
/** The MCTransceiverDelegate object that handles transceiver-related events. */
@property (weak, nonatomic, readonly) id<MCTransceiverDelegate> delegate;

/** 
 The MCTransceiverMode in which the transceiver will operate, either as an advertiser
 or browser. 
 */
@property (readonly) MCTransceiverMode mode;

/**
 Creates a `MCTransceiver` object.
 @param delegate The MCTransceiverDelegate that will receive events from the MCTransceiver.
 @param mode The MCTransceiverMode in which the transceiver will operate.
 @return Returns the initialized transceiver object, or nil if an error occurs.
 */
-(id)initWithDelegate:(id<MCTransceiverDelegate>)delegate mode:(MCTransceiverMode)mode;

/** Begin advertising as a MCNearbyServiceAdvertiser */
-(void)startAdvertising;

/** Begin browsing for advertisers as a MCNearbyServiceBrowser */
-(void)startBrowsing;

/**
 Provides a list of the currently connected peers.
 @return An array containing the connected peers (as `MCPeerID` objects).
 */
-(NSArray *)connectedPeers;

/**
 Sends a package of data to the given peers, with an optional completion handler.
 #### Discussion
 The data is sent asynchronously. If a completion handler is given, it is called on the
 main queue.
 @param data The data to be transmitted.
 @param peers The list of peers to send the data to.
 @param completion An optional block that is called once the data has been sent. This
 block is called on the main queue.
 */
-(void)sendUnreliableData:(NSData *)data
                  toPeers:(NSArray *)peers
               completion:(MCSendDataCompletion)completion;
@end
