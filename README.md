MCTransceiver
=============

iOS library providing an abstracted interface to the Multipeer Connectivity API

##### Features:
* Quickly add ability for two iOS devices to seamlessly pair and communicate via the [Multipeer Connectivity Framework](https://developer.apple.com/library/ios/documentation/MultipeerConnectivity/Reference/MultipeerConnectivityFramework/_index.html#//apple_ref/doc/uid/TP40013328).

##### Using
* Clone repo
* Drag & drop <code>ABTools.xcodeproj</code> into your workspace
* Follow [Apple's documentation](https://developer.apple.com/library/ios/technotes/iOSStaticLibraries/Articles/configuration.html) on how to use static libraries in iOS

The library uses ARC. It has been developed using Xcode 5 & tested against iOS 7.x.

##### Documentation
The Xcode project includes a `Documentation` target which can be used to generate documentation for the API. It requires the use of [appledoc](http://gentlebytes.com/appledoc/). Once you've built the documentation it will be available through Xcode's Documentation window.

The latest [HTML documentation](https://github.com/KeithErmel/MCTransceiver/docs/index.html) is also available.

##### Examples
The <code>[Examples](https://github.com/KeithErmel/MCTransceiver/tree/master/Examples)</code> folder includes a the [MCTransceiverExample](https://github.com/KeithErmel/MCTransceiver/tree/master/Examples/MCTransceiverExample) project that demonstrates communication between two iOS devices: one acting as the advertiser <code>(host)</code> the other as the browser <code>(join)</code>.

###### Advertising, Browsing and Sending Data
* While this API is presented through a single interface -- [MCTransceiver](https://github.com/KeithErmel/MCTransceiver/blob/master/MCTransceiver/MCTransceiver/MCTransceiver.h) -- the tasks of advertising and browsing are provided separately, through the <code>startAdvertising:</code> and <code>startBrowsing:</code> methods.

* Currently the only way to send data from one device to another is through the <code>sendUnreliableData:toPeers:completion</code> method. From the documentation, sending data unreliably means:
> Messages to peers should be sent immediately without socket-level queueing. If a message cannot be sent immediately, it should be dropped. The order of messages is not guaranteed.

* Future additions to this API will provide the ability to:
    * Send reliable data (guaranteed, in-order delivery, retransmitted as needed)
    * Send a resource based on URL to a peer
    * Stream data to a peer
    

